

// JANGAN commit file ini ke Git! (sudah ada di .gitignore)







#ifndef SECRETS_H
#define SECRETS_H


#define WIFI_SSID  "NAMA_WIFI_KAMU"
#define WIFI_PASS  "PASSWORD_WIFI_KAMU"





#define MQTT_SERVER  "io.adafruit.com"
#define MQTT_PORT     8883              
#define MQTT_USER    "USERNAME_ADAFRUIT"
#define MQTT_PASS    "AIO_KEY_KAMU"




#define TOPIC_TELEMETRY  "USERNAME_ADAFRUIT/feeds/wq-telemetry"
#define TOPIC_ALERT      "USERNAME_ADAFRUIT/feeds/wq-alert"
#define TOPIC_STATUS     "USERNAME_ADAFRUIT/feeds/wq-status"





#define OTA_FIRMWARE_URL  "https://example.com/firmware/wqm_latest.bin"

#endif 
