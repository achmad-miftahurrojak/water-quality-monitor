<div align="center">

# Water Quality Monitor

[English](README.md) · [Bahasa Indonesia](README.id.md) · [한국어](README.ko.md)

현장에서 TDS, pH, 탁도를 측정하고 기록하는 ESP32 펌웨어입니다.

</div>

---

## 개요

세 가지 수질 값을 측정하고 I2C LCD에 표시하며, RTC 시간과 함께 SD 카드에 저장합니다. MQTT와 OTA는 선택 기능이며 로컬 인증 정보가 설정될 때까지 비활성화됩니다.

## 기능

- ESP32 기반 TDS, pH, 탁도 측정
- 현장 확인을 위한 LCD 표시
- RTC timestamp를 포함한 SD 카드 기록
- threshold 기반 LED 및 buzzer 경보
- 선택 가능한 MQTT 및 OTA 연동 지점

## 아키텍처

데이터 흐름과 설정 경계는 [ARCHITECTURE.md](ARCHITECTURE.md)에서 확인할 수 있습니다.

## 빌드 및 업로드

필요 항목: PlatformIO, ESP32 보드, TDS/pH/탁도 센서, I2C LCD, SD 모듈, RTC.

    git clone https://github.com/achmad-miftahurrojak/water-quality-monitor.git
    cd water-quality-monitor
    pio run
    pio run -t upload

실제 측정 전에 센서 상수를 보정하세요. 개인 값은 <code>src/secrets.example.h</code>를 참고해 로컬에 보관합니다.

## 프로젝트 구조

    src/
    ├── main.cpp
    ├── sensors.*       # 센서 측정 및 변환
    ├── storage.*       # SD 및 RTC 기록
    ├── connectivity.*  # MQTT / 네트워크 hook
    └── alerts.*        # 로컬 경보 출력

## 라이선스

[MIT](LICENSE) · [GitHub 프로필](https://github.com/achmad-miftahurrojak)
