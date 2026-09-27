<div align="center">

# Water Quality Monitor

[English](README.md) · [Bahasa Indonesia](README.id.md) · [한국어](README.ko.md)

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
