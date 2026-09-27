<div align="center">

# Water Quality Monitor

<a href="README.md"><img alt="English" src="https://img.shields.io/badge/English-DFE0E5"></a> <a href="README.id.md"><img alt="Bahasa Indonesia" src="https://img.shields.io/badge/Bahasa%20Indonesia-DFE0E5"></a> <a href="README.ko.md"><img alt="한국어" src="https://img.shields.io/badge/%ED%95%9C%EA%B5%AD%EC%96%B4-DFE0E5"></a>

<img alt="C++" src="https://img.shields.io/badge/C%2B%2B-11-00599C?logo=c%2B%2B&logoColor=white"> <img alt="ESP32" src="https://img.shields.io/badge/ESP32-E7352C?logo=espressif&logoColor=white"> <img alt="PlatformIO" src="https://img.shields.io/badge/PlatformIO-F56600?logo=platformio&logoColor=white">

Firmware ESP32 untuk mengukur dan merekam TDS, pH, dan turbidity pada titik air.

</div>

---

## Ringkasan

Perangkat mengambil sampel tiga parameter air, menampilkan nilai terbaru pada LCD I2C, dan menyimpan pembacaan bertimestamp ke kartu SD. MQTT dan OTA tersedia sebagai integrasi opsional dan tetap nonaktif sampai kredensial lokal dikonfigurasi.

## Fitur

- Pengukuran TDS, pH, dan turbidity dengan ESP32.
- Tampilan LCD lokal untuk pemeriksaan lapangan.
- Pencatatan ke kartu SD dengan timestamp RTC.
- Alert LED dan buzzer berbasis threshold.
- Titik integrasi MQTT dan OTA opsional.

## Arsitektur

Lihat [ARCHITECTURE.md](ARCHITECTURE.md) untuk alur data dan batas konfigurasi.

## Build dan upload

Persyaratan: PlatformIO, board ESP32, sensor TDS/pH/turbidity, LCD I2C, modul SD, dan RTC.

    git clone https://github.com/achmad-miftahurrojak/water-quality-monitor.git
    cd water-quality-monitor
    pio run
    pio run -t upload

Kalibrasikan konstanta sensor sebelum mengandalkan hasil pengukuran. Simpan nilai privat berdasarkan <code>src/secrets.example.h</code> secara lokal.

## Struktur proyek

    src/
    ├── main.cpp
    ├── sensors.*       # Sampling dan konversi sensor
    ├── storage.*       # Logging SD dan RTC
    ├── connectivity.*  # Hook MQTT / jaringan
    └── alerts.*        # Output alert lokal

## Lisensi

[MIT](LICENSE) · [Profil GitHub](https://github.com/achmad-miftahurrojak)
