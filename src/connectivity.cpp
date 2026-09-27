#include "connectivity.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <Update.h>
#include <mbedtls/sha256.h>
#include "alerts.h"

#if __has_include("secrets.h")
  #include "secrets.h"
#else
  #include "secrets.example.h"
#endif

static WiFiClientSecure secureClient;
static PubSubClient     mqttClient(secureClient);

PubSubClient& getMqttClient() {
    return mqttClient;
}

void initConnectivity() {
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setBufferSize(512);
    Serial.println("Connectivity initialized.");
}

bool connectWiFi() {
    if (WiFi.status() == WL_CONNECTED) return true;

    Serial.printf("Connecting to WiFi: %s", WIFI_SSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("WiFi Connected! IP: %s\n", WiFi.localIP().toString().c_str());
        return true;
    }

    Serial.println("Failed to connect to WiFi.");
    return false;
}

bool connectMQTT() {
    if (mqttClient.connected()) return true;
    if (WiFi.status() != WL_CONNECTED) return false;

#if defined(MQTT_ROOT_CA)
    secureClient.setCACert(MQTT_ROOT_CA);
#else
    Serial.println("MQTT disabled: MQTT_ROOT_CA is not configured.");
    return false;
#endif

    char clientId[24];
    snprintf(clientId, sizeof(clientId), "WQM-%08X", (uint32_t)esp_random());

    Serial.printf("Connecting to MQTT broker %s...", MQTT_SERVER);

    if (mqttClient.connect(clientId, MQTT_USER, MQTT_PASS, TOPIC_STATUS, 1, true, "offline")) {
        Serial.println(" Connected!");
        mqttClient.publish(TOPIC_STATUS, "online", true);
        return true;
    }

    Serial.printf(" Failed (rc=%d)\n", mqttClient.state());
    return false;
}

void disconnectConnectivity() {
    if (mqttClient.connected()) {
        mqttClient.publish(TOPIC_STATUS, "offline", true);
        mqttClient.disconnect();
    }
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
}

bool publishTelemetry(SensorData data, float batteryVoltage, uint32_t timestamp) {
    if (!connectWiFi() || !connectMQTT()) return false;

    StaticJsonDocument<256> doc;
    doc["ts"]     = timestamp;
    doc["tds"]    = serialized(String(data.tds, 1));
    doc["turb"]   = serialized(String(data.turbidity, 1));
    doc["ph"]     = serialized(String(data.ph, 2));
    doc["batt_v"] = serialized(String(batteryVoltage, 2));
    doc["alert"]  = data.isError ||
                     data.tds > THRESHOLD_TDS_HIGH ||
                     data.turbidity > THRESHOLD_TURBIDITY_HIGH ||
                     data.ph < THRESHOLD_PH_LOW ||
                     data.ph > THRESHOLD_PH_HIGH;

    char buffer[256];
    size_t len = serializeJson(doc, buffer);

    Serial.printf("Sending telemetry (%d bytes): %s\n", len, buffer);
    return mqttClient.publish(TOPIC_TELEMETRY, buffer, false);
}

bool publishAlert(SensorData data, const char* reason, uint32_t timestamp) {
    if (!connectWiFi() || !connectMQTT()) return false;

    StaticJsonDocument<256> doc;
    doc["ts"]     = timestamp;
    doc["reason"] = reason;
    doc["tds"]    = serialized(String(data.tds, 1));
    doc["turb"]   = serialized(String(data.turbidity, 1));
    doc["ph"]     = serialized(String(data.ph, 2));

    char buffer[256];
    size_t len = serializeJson(doc, buffer);

    Serial.printf("Sending alert (%d bytes): %s\n", len, buffer);
    return mqttClient.publish(TOPIC_ALERT, buffer, false);
}

void checkForUpdates() {
    if (WiFi.status() != WL_CONNECTED) return;

#if !defined(OTA_ROOT_CA) || !defined(OTA_FIRMWARE_SHA256)
    Serial.println("OTA disabled: TLS CA and firmware SHA-256 are required.");
    return;
#else
    Serial.printf("Checking OTA update at: %s\n", OTA_FIRMWARE_URL);

    HTTPClient http;
    secureClient.setCACert(OTA_ROOT_CA);
    http.setTimeout(10000);

    if (!http.begin(secureClient, OTA_FIRMWARE_URL)) {
        Serial.println("OTA: Failed to open HTTP connection.");
        return;
    }

    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
        int contentLength = http.getSize();
        if (contentLength <= 0) {
            Serial.println("OTA: Invalid Content-Length, aborting.");
            http.end();
            return;
        }

        Serial.printf("OTA: Starting update, firmware size: %d bytes\n", contentLength);

        if (!Update.begin(contentLength)) {
            Serial.printf("OTA: Not enough space (error: %d)\n", Update.getError());
            http.end();
            return;
        }

        WiFiClient* stream = http.getStreamPtr();
        mbedtls_sha256_context sha256;
        mbedtls_sha256_init(&sha256);
        mbedtls_sha256_starts_ret(&sha256, 0);
        uint8_t buffer[1024];
        size_t written = 0;
        while (http.connected() && written < (size_t)contentLength) {
            size_t available = stream->available();
            if (available == 0) {
                delay(1);
                continue;
            }
            size_t toRead = min(available, sizeof(buffer));
            int readBytes = stream->readBytes(buffer, toRead);
            if (readBytes <= 0) break;
            if (Update.write(buffer, readBytes) != (size_t)readBytes) break;
            mbedtls_sha256_update_ret(&sha256, buffer, readBytes);
            written += readBytes;
        }
        uint8_t digest[32];
        mbedtls_sha256_finish_ret(&sha256, digest);
        mbedtls_sha256_free(&sha256);

        char actualHash[65];
        for (size_t i = 0; i < sizeof(digest); i++) {
            snprintf(actualHash + (i * 2), 3, "%02x", digest[i]);
        }
        actualHash[64] = '\0';

        if (written != (size_t)contentLength ||
            !String(actualHash).equalsIgnoreCase(OTA_FIRMWARE_SHA256)) {
            Serial.printf("OTA: Download incomplete (%d/%d bytes)\n", written, contentLength);
            Update.abort();
            http.end();
            return;
        }

        if (Update.end() && Update.isFinished()) {
            Serial.println("OTA: Update successful! Restarting system...");
            http.end();
            ESP.restart();
        } else {
            Serial.printf("OTA: Failed to complete update (error: %d)\n", Update.getError());
        }
    } else if (httpCode == HTTP_CODE_NOT_FOUND) {
        Serial.println("OTA: No new firmware available.");
    } else {
        Serial.printf("OTA: HTTP error %d\n", httpCode);
    }

    http.end();
#endif
}
