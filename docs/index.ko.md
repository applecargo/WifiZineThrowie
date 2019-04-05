---
layout: default
---

# 해커스 앤 디자이너스 - 걸어다니는 신호들 / 와이파이-진 워크숍.

## 와이파이-진(zine) 이란?

### 한 줄 설명

- 스마트폰이 핫스팟 로그인을 시도할때, 웹진 형식의 자주독립출판물을 서비스하도록 설계된 무선통신 및 웹서비스 장치

[![hotspot-zine-ssid](./assets/hotspot-zine-ssid.jpg){:width="500px"}](./assets/hotspot-zine-ssid.jpg)
[![hotspot-zine-login](./assets/hotspot-zine-login.jpg){:width="500px"}](./assets/hotspot-zine-login.jpg)

- [더보기](http://pilote.byus.net/wpdiana/?page_id=1064)

### 선행 프로젝트

- [CaptiveIntraweb by AReResearch (Andy Reischle) @ 2015](https://github.com/reischle/CaptiveIntraweb)

  [![construction-overview](./assets/areresearch/img4.png){:width="500px"}](./assets/areresearch/img4.png)

### 구성요소

- 유형 요소 (tangible components)
  - Espressif사의 ESP32 모듈
  - 전원장치 (배터리 또는 DC 아답타)
  - (선택적) 통 또는 외형
  - (선택적) 자석

  [![construction-overview](./assets/areresearch/img1.png){:width="500px"}](./assets/areresearch/img1.png)

  [![construction-overview](./assets/areresearch/img2.png){:width="500px"}](./assets/areresearch/img2.png)

  [![construction-overview](./assets/areresearch/img5.png){:width="500px"}](./assets/areresearch/img5.png)

  [![construction-overview](./assets/areresearch/img6.png){:width="500px"}](./assets/areresearch/img6.png)

  [![construction-overview](./assets/areresearch/img7.png){:width="500px"}](./assets/areresearch/img7.png)

  (위 이미지들은 Andy Reischle (AReResearch) 님이 게시한 것들입니다.)

- 무형 요소 (intangible components)
  - [ESP-IDF 개발 환경](https://github.com/espressif/esp-idf/tree/master/components)
  - [ESP32 아두이노 호환성 패키지](https://github.com/espressif/arduino-esp32)
  - [SPIFFS 파일 시스템](https://github.com/espressif/arduino-esp32/tree/master/libraries/SPIFFS)
  - [ESP 웹서버 라이브러리](https://github.com/me-no-dev/ESPAsyncWebServer)
  - [도메인 네임서버(captive portal)](https://github.com/espressif/arduino-esp32/tree/master/libraries/DNSServer)
  - 웹페이지 (웹-진)

  [![Wi-Fi-zine-stacks](./assets/Wi-Fi-zine-stacks.png){:width="500px"}](./assets/Wi-Fi-zine-stacks.png)

  - [더 많은 정보](http://esp32.net/)
  - [Wi-Fi 스택이 오픈소스가 아닌 문제](https://github.com/espressif/esp32-wifi-lib/issues/2)

### 알아두어야 할 와이파이-진 시스템의 한계

- 저장용량 2MB 이하
- 일반적인 웹서버에 비해 다소 느린 속도
- 일반적인 웹서버에 비해 다소 불안정한 작동 (때때로, 시스템 재시작이 필요할 수 있음)

## 와이파이-진 만들기

### 재료 및 준비물

- 컴퓨터
- ESP32 모듈이 탑재된 개발보드
- 통신용 마이크로 USB 케이블 (안드로이드 데이타 케이블)
- 배터리, 배터리팩 또는 DC 아답타
- 웹페이지 (html/css/js + 미디어 파일)
- (선택적으로) 센서 또는 작동장치 (스피커 등)

### 와이파이-진 보드 준비하기

- [Arduino 다운로드](https://www.arduino.cc/en/Main/Software)

- Arduino 설치하기

  - [Windows](https://www.arduino.cc/en/Guide/Windows)

  - [Mac OSX](https://www.arduino.cc/en/Guide/MacOSX)

    [![arduino-confirm](./assets/arduino-confirm.png){:width="300px"}](./assets/arduino-confirm.png)

    'Open' 을 클릭.

  - [Linux](https://www.arduino.cc/en/Guide/Linux)

- Arduino IDE 실행 화면

  [![arduino-screen](./assets/arduino-screen.png){:width="300px"}](./assets/arduino-screen.png)

- Arduino IDE 설정

  - 컴파일 및 업로드 과정 표시 모드를 '상세한 표기'로 변경

    [![arduino-verbose](./assets/arduino-verbose.png){:width="300px"}](./assets/arduino-verbose.png)

    'Show verbose output during:' 항목에서 compilation과 upload에 체크

- [Arduino IDE에 esp32 보드를 추가하기](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md)

  - 'Additional Boards Manager URLs' 에 다음 내용을 복사하여 붙여넣고 'Ok'.

    ```
    https://dl.espressif.com/dl/package_esp32_index.json
    ```

    [![arduino-board-url](./assets/arduino-board-url.png){:width="300px"}](./assets/arduino-board-url.png)

  - 보드 매니져 실행

    [![arduino-board-manager](./assets/arduino-board-manager.png){:width="300px"}](./assets/arduino-board-manager.png)

  - 보드 매니져 팝업창의 모습

    [![arduino-board-manager-popup](./assets/arduino-board-manager-popup.png){:width="300px"}](./assets/arduino-board-manager-popup.png)

  - 검색창에 'esp32'라고 입력 후, 'Install' 클릭

    [![arduino-board-manager-esp32](./assets/arduino-board-manager-esp32.png){:width="300px"}](./assets/arduino-board-manager-esp32.png)

- Arduino IDE에 와이파이-진 코드와 필요한 라이브러리들 추가하기

  - [와이파이-진](https://github.com/applecargo/WifiZineThrowie/) 다운로드 및 설치

    'Clone or download' -> 'Download ZIP' 클릭

    [![arduino-00010](./assets/arduino-00010.png){:width="300px"}](./assets/arduino-00010.png)

    압축 해제 후, 폴더 이름 변경

    [![arduino-00011](./assets/arduino-00011.png){:width="300px"}](./assets/arduino-00011.png)
    [![arduino-00012](./assets/arduino-00012.png){:width="300px"}](./assets/arduino-00012.png)

    ~/Documents/Arduino에 해당 폴더 복사

    [![arduino-00013](./assets/arduino-00013.png){:width="300px"}](./assets/arduino-00013.png)

  - [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)와 [AsyncTCP](https://github.com/me-no-dev/AsyncTCP) 라이브러리 다운로드 및 설치

    'Clone or download' -> 'Download ZIP' 클릭

    [![arduino-00001](./assets/arduino-00001.png){:width="300px"}](./assets/arduino-00001.png)

    압축 해제 후, 폴더 이름 변경

    [![arduino-00003](./assets/arduino-00003.png){:width="300px"}](./assets/arduino-00003.png)
    [![arduino-00004](./assets/arduino-00004.png){:width="300px"}](./assets/arduino-00004.png)

    'Clone or download' -> 'Download ZIP' 클릭

    [![arduino-00006](./assets/arduino-00006.png){:width="300px"}](./assets/arduino-00006.png)

    압축 해제 후, 폴더 이름 변경

    [![arduino-00007](./assets/arduino-00007.png){:width="300px"}](./assets/arduino-00007.png)
    [![arduino-00008](./assets/arduino-00008.png){:width="300px"}](./assets/arduino-00008.png)

    ~/Documents/Arduino/libraries에 해당 폴더 (2개) 복사

    [![arduino-00009](./assets/arduino-00009.png){:width="300px"}](./assets/arduino-00009.png)

  - 컴파일 확인

    - Arduino IDE를 재시작

    - 'WifiZineThrowie' 스케치를 연다

      [![arduino-wifizine](./assets/arduino-wifizine.png){:width="300px"}](./assets/arduino-wifizine.png)

    - ESP32 Dev Module 보드를 선택한다

      [![arduino-wifizine-select-board](./assets/arduino-wifizine-select-board.png){:width="300px"}](./assets/arduino-wifizine-select-board.png)

    - ESP32 Dev Module 보드 설정을 조정한다

      [![arduino-wifizine-config-board](./assets/arduino-wifizine-config-board.png){:width="300px"}](./assets/arduino-wifizine-config-board.png)

      - Upload Speed : 921600
      - CPU Frequency : 240MHz
      - Flash Frequency : 80MHz
      - Flash Mode : DIO
      - Flash Size : 4MB (32Mb)
      - Partition Scheme : Default
      - Core Debug Level : None
      - PSRAM : Disabled

    - 컴파일 버튼(빨간 화살표)을 클릭한다

      [![arduino-wifizine-popup](./assets/arduino-wifizine-popup.png){:width="300px"}](./assets/arduino-wifizine-popup.png)

    - 컴파일 과정이 정상적으로 끝나면, 성공

      [![arduino-wifizine-compile-done](./assets/arduino-wifizine-compile-done.png){:width="300px"}](./assets/arduino-wifizine-compile-done.png)

    - 컴파일 과정이 비-정상적으로 끝나면, 실패

      [![arduino-wifizine-compile-failed](./assets/arduino-wifizine-compile-failed.png){:width="300px"}](./assets/arduino-wifizine-compile-failed.png)

- ESP32 모듈과 통신하기 위한 USB 장치 드라이버 설치하기 (칩 이름 : SiliconLabs CP2012)

  - [USB 통신 칩 드라이버 다운로드](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)

    - [Windows 10](https://www.silabs.com/documents/public/software/CP210x_Universal_Windows_Driver.zip)
    - [Windows 7/8/8.1](https://www.silabs.com/documents/public/software/CP210x_Windows_Drivers.zip)

      - [설치 과정](https://www.pololu.com/docs/0J7/all)

    - [Mac OSX](https://www.silabs.com/documents/public/software/Mac_OSX_VCP_Driver.zip)

      - [GateKeeper와의 전쟁](https://support.apple.com/en-us/HT202491)

      - Yosemite (10.10.x)

        - [Legacy 드라이버를 설치해야 함](https://www.silabs.com/community/interface/forum.topic.html/latest_vcp_driverfo-96RK)

        [![yosemite-cp2102](./assets/yosemite-cp2102.png){:width="300px"}](./assets/yosemite-cp2102.png)
        [![yosemite-cp2102-legacy](./assets/yosemite-cp2102-legacy.png){:width="300px"}](./assets/yosemite-cp2102-legacy.png)

      - El capitan (10.11.x)

        - [GateKeeper 비활성화 방법](https://medium.com/@krukmat/macos-el-capitan-enabling-usb-for-cp2102-usb-to-ttl-3b63449e02e9)
        - [csrutil enable --without kext](https://forums.developer.apple.com/thread/17452)

      - Sierra (10.12.x)

        - [GateKeeper 비활성화 방법](https://www.tekrevue.com/tip/gatekeeper-macos-sierra/)
        - sudo spctl --master-disable

      - High Sierra (10.13.x)

        - [GateKeeper 비활성화 방법](https://stackoverflow.com/questions/47109036/cp2102-device-is-not-listed-in-dev-on-macos-10-13)
        - [GateKeeper 비활성화 방법](https://pikeralpha.wordpress.com/2017/08/29/user-approved-kernel-extension-loading/)
        - [GateKeeper 비활성화 방법](https://www.silabs.com/community/interface/knowledge-base.entry.html/2018/03/30/usb_to_uart_bridgev-Dnef)
        - spctl kext-consent disable

      - Mojave (10.14.x)

        - [GateKeeper 비활성화 방법](http://osxdaily.com/2016/09/27/allow-apps-from-anywhere-macos-gatekeeper/)
        - sudo spctl --master-disable

    - Linux 3.x.x & 4.x.x

      - 드라이버 설치 불필요 (커널에 포함되어 있음)
      - [udev rules 업데이트 필요](https://docs.platformio.org/en/latest/faq.html#platformio-udev-rules)
      - [99-platformio-udev.rules](https://raw.githubusercontent.com/platformio/platformio-core/develop/scripts/99-platformio-udev.rules)

    - [Linux 2.6.x](https://www.silabs.com/documents/login/software/Linux_2.6.x_VCP_Driver_Source.zip)

      - 정보 없음

- USB 드라이버 작동 여부 확인하기

  - 드라이버를 지금 막 설치했다면, 컴퓨터를 재시작한다

  - 재시작한 후에 GateKeeper가 드라이버 로딩을 방해하지는 않았는지 확인한다.

    - System Preferences -> Security & Privacy -> General

      [![gatekeeper-check](./assets/gatekeeper-check.png){:width="300px"}](./assets/gatekeeper-check.png)
      [![gatekeeper-check-popup](./assets/gatekeeper-check-popup.png){:width="300px"}](./assets/gatekeeper-check-popup.png)

      빨간색으로 표시된 상자안에 에러문구가 있다면, GateKeeper가 드라이버 작동을 방해한 경우이다.

      [![security_and_privacy_kextload_approval](./assets/security_and_privacy_kextload_approval.png){:width="300px"}](./assets/security_and_privacy_kextload_approval.png)

      위와 유사한 상태가 되어있을경우, 'Allow'를 클릭하고 관리자 암호를 넣어 승인해준 후, 컴퓨터를 재시작한다.

  - Arduino IDE를 시작한 후에, ESP32 모듈과 통신 가능한지 확인

    [![arduino-esp32-comm](./assets/arduino-esp32-comm.png){:width="300px"}](./assets/arduino-esp32-comm.png)

    통신이 가능한 경우, 위와 같이 /dev/cu.SLAB_USBtoUART를 선택할 수가 있다.

    [![arduino-esp32-comm-failed](./assets/arduino-esp32-comm-failed.png){:width="300px"}](./assets/arduino-esp32-comm-failed.png)

    통신이 불가능한 경우, 위와 같이 /dev/cu.SLAB_USBtoUART가 존재하지 않는다.

- 와이파이-진 네트워크의 이름, 즉 SSID를 정하고 코드를 수정한다.

  [![arduino-wifizine-ssid-change](./assets/arduino-wifizine-ssid-change.png){:width="300px"}](./assets/arduino-wifizine-ssid-change.png)

  - 글자 수나 띄어쓰기 등에 의해서 안될 수도 있으므로, 처음에는 공백문자가 포함되지 않은 간단한 영문으로 테스트해본다.
  - 한글을 사용해도 된다.

- 보드에 업로드 한다

  - 업로드 버튼(빨간 화살표)을 클릭하고, 'Connecting...' 이란 문구가 나타났을때, [ESP 보드의 'BOOT'라는 버튼을 1초간 눌렀다가 뗍니다](https://randomnerdtutorials.com/solved-failed-to-connect-to-esp32-timed-out-waiting-for-packet-header/).

    [![arduino-wifizine-upload](./assets/arduino-wifizine-upload.png){:width="300px"}](./assets/arduino-wifizine-upload.png)

    업로드 성공한 화면

    [![arduino-wifizine-upload-done](./assets/arduino-wifizine-upload-done.png){:width="300px"}](./assets/arduino-wifizine-upload-done.png)

    업로드 실패한 화면

    [![arduino-wifizine-upload-failed](./assets/arduino-wifizine-upload-failed.png){:width="300px"}](./assets/arduino-wifizine-upload-failed.png)

- [다양한 문제 요인들](https://randomnerdtutorials.com/esp32-troubleshooting-guide/)

### 와이파이-진 보드 업로드 용량 늘리기 (선택적인 과정)

- 제공된 ESP32 모듈의 플래쉬 메모리 용량은 4MB이지만, 전부 다 와이파이-진 컨텐츠를 위해서 사용할 수는 없다. 그 이유는 와이파이-진을 구동하는 코드와 칩 자체의 작동을 위한 코드, 그리고 파일 시스템의 구조 (폴더 구조 및 파일의 구분 등)를 표현하기 위해 사용되는 데이터, 즉 SPIFFS의 구현에 의한 오버헤드와 같은 것들이 4MB 중 일부분을 사용하지 않을 수 없기 때문이다.

- ESP32 모듈의 플래쉬 메모리는 작동하는 데이터(즉, 코드), 저장해 두어야 하는 데이터(즉, 메모리), 구조를 기록하는 데이터(즉, 파일 시스템) 등이 파티션을 통해 4MB를 나누어 사용하도록 되어있다.

- 위의 과정 중에서, ESP32 보드를 설정할때,

  [![arduino-wifizine-config-board](./assets/arduino-wifizine-config-board.png){:width="300px"}](./assets/arduino-wifizine-config-board.png)

  ```
  Partition Scheme : Default
  ```

  를 선택했었는데, 기본 파티션 구성의 경우 와이파이-진을 위해서 반드시 필요하지 않은 요소들을 포함하고 있으며, 기본 파티션 구성에서 와이파이-진 컨텐츠에 사용할 수 있는 메모리 용량은 1MB 정도밖에는 되지 않는다.

- 따라서, Partition Scheme을 보다 효율적으로 재구성하면, 와이파이-진 컨텐츠를 조금 더 많이 업로드 할 수 있게 할 수도 있다. 이렇게 하면, 약 1.9MB 정도의 용량을 사용할 수 있게 된다.

- 본 과정을 마치게 되면, 다음과 같이

  [![arduino-wifizine-custom-partition](./assets/arduino-wifizine-custom-partition.png){:width="300px"}](./assets/arduino-wifizine-custom-partition.png)

  ```
  Partition Scheme : WIFI ZINE
  ```

  을 선택할 수 있게 된다.

- 작업 과정

  - [파티션 설정 파일](https://raw.githubusercontent.com/applecargo/WifiZineThrowie/master/partition/wifi_zine.csv) 다운로드 및 설치

    ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.1/tools/partitions 에 붙여넣는다

    [![arduino-partition-00001](./assets/arduino-partition-00001.png){:width="300px"}](./assets/arduino-partition-00001.png)

    ~/Library/ 폴더는 Finder에서 숨겨진 폴더이므로 Cmd-Shift-G를 누르고 Library 라고 타이핑하여 들어간다

    [![arduino-partition-00002](./assets/arduino-partition-00002.png){:width="300px"}](./assets/arduino-partition-00002.png)

    이후, Arduino15 폴더는 일반적인 폴더와 같이 더블 클릭하여 들어간다

    [![arduino-partition-00003](./assets/arduino-partition-00003.png){:width="300px"}](./assets/arduino-partition-00003.png)

    위와 같은 위치로 이동한다

    [![arduino-partition-00004](./assets/arduino-partition-00004.png){:width="300px"}](./assets/arduino-partition-00004.png)

    위와 같은 상태로 만든다

  - boards.txt 파일 수정

    [![arduino-partition-00005](./assets/arduino-partition-00005.png){:width="300px"}](./assets/arduino-partition-00005.png)

    위와 같은 위치에 존재하는 파일 boards.txt 파일을 열어 다음에 +로 표시된 4줄을 추가한다 (+표시는 제거한다!)

    ```diff
    --- /Users/doohoyi/Downloads/Telegram Desktop/boards.txt
    +++ /Users/doohoyi/Library/Arduino15/packages/esp32/hardware/esp32/1.0.1/boards.txt
    @@ -52,6 +52,10 @@
     esp32.menu.PartitionScheme.min_spiffs.upload.maximum_size=1966080
     esp32.menu.PartitionScheme.fatflash=16M Fat
     esp32.menu.PartitionScheme.fatflash.build.partitions=ffat
    +esp32.menu.PartitionScheme.wifi_zine=WIFI ZINE
    +esp32.menu.PartitionScheme.wifi_zine.build.partitions=wifi_zine
    +esp32.menu.PartitionScheme.wifi_zine.upload.maximum_size=1048576
    +esp32.menu.PartitionScheme.wifi_zine.upload.maximum_data_size=2752512

     esp32.menu.CPUFreq.240=240MHz (WiFi/BT)
     esp32.menu.CPUFreq.240.build.f_cpu=240000000L
    ```

  - Arduino IDE 를 재시작한 후, ESP32 DEV Module 설정 중 PartitionScheme을 WIFI ZINE으로 선택하고, 컴파일해본다.

### 와이파이-진 컨텐츠 업로드/출판 하기

- 와이파이-진 컨텐츠는 작동하는 코드와는 별도로 저장된다. 따라서, 일반적인 Arduino IDE의 코드 업로드 과정과는 별도의 과정을 거친다. 이를 위해, 별도의 확장 플러그인을 설치해야 합니다.

- [ESP32FS 플러그인](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases) 다운로드 및 설치

  ~/Documents/Arduino/tools 라는 폴더 생성

  [![arduino-esp32fs-00002](./assets/arduino-esp32fs-00002.png){:width="300px"}](./assets/arduino-esp32fs-00002.png)

  압축이 풀린 ESP32FS 를 이곳에 복사 설치

  [![arduino-esp32fs-00003](./assets/arduino-esp32fs-00003.png){:width="300px"}](./assets/arduino-esp32fs-00003.png)

  폴더의 구성에 조심해야 합니다. 다음 그림과 같이 설치되어야 합니다. (폴더의 이름이 ESP32FS 인 것도 주의!)

  [![arduino-esp32fs-00004](./assets/arduino-esp32fs-00004.png){:width="300px"}](./assets/arduino-esp32fs-00004.png)

  Arduino IDE를 재시작한 후, 플러그인 설치가 성공했는지 확인합니다. 성공했다면, 'ESP32 Sketch Data Upload' 라는 메뉴가 추가된 것을 확인할 수 있습니다.

  [![arduino-esp32fs-00005](./assets/arduino-esp32fs-00005.png){:width="300px"}](./assets/arduino-esp32fs-00005.png)

  이 메뉴를 실행하면, ~/Documents/Arduino/WifiZineThrowie/data 폴더에 들어있는 모든 파일을 ESP32 모듈의 웹 페이지 저장소에 이동시키게 됩니다.

  [![arduino-wifizine-webpage-upload](./assets/arduino-wifizine-webpage-upload.png){:width="300px"}](./assets/arduino-wifizine-webpage-upload.png)

  업로드를 실행하십시오. 업로드 중 출력되는 메세지의 색깔이 빨간색이 아니라 흰색으로 출력됩니다. 코드를 업로드 할 때와 마찬가지로, 'Connecting...' 이란 문구가 나타났을때, [ESP 보드의 'BOOT'라는 버튼을 1초간 눌렀다가 땝니다](https://randomnerdtutorials.com/solved-failed-to-connect-to-esp32-timed-out-waiting-for-packet-header/).

  업로드가 성공적으로 완료된 경우의 화면

  [![arduino-wifizine-webpage-upload-done](./assets/arduino-wifizine-webpage-upload-done.png){:width="300px"}](./assets/arduino-wifizine-webpage-upload-done.png)

  축하합니다. 와아파이-진을 제작/출판하기 위한 모든 준비가 끝났습니다.

## 와이파이-진 컨텐츠 예시

- 예시 1 텍스트 페이지

  - [Hello, Text?](https://github.com/applecargo/WifiZineThrowie/blob/master/data-text.zip?raw=true)

    - [폰트 구하기](https://www.dafont.com/)

- 예시 2

  - [Imaginary, world](https://github.com/applecargo/WifiZineThrowie/blob/master/data-image.zip?raw=true)

- 예시 3

  - [Sound-world!](https://github.com/applecargo/WifiZineThrowie/blob/master/data-sound.zip?raw=true)

- 예시 4

  - Looooong story! (TBD)

- 예시 5

  - (advanced) WebSocket - socket.io + server-side programming @ arduino (TBD)

    - 해본적 없지만, 가능해 보임. 예제를 만들어 봅시다.

## 형태와 재질을 가지고 놀아보기

- 센서를 붙여보기

  - 스위치?

- 작동하는 것을 붙여보기

  - 모터?

## 장소와 함께 생각하기

- 자석을 이용해서 거리나 공간의 철골 구조에 부착

## 프로젝트에 기여하기

- ZINE 컨텐츠를 공유해주면, 다른 사람들이 각자 ZINE을 제작할 때, 아이디어와 영감을 얻을 수 있습니다. 이때, ZINE이 제작된 배경 이야기나 맥락, 형태 등 부가정보를 알려주면 더 좋습니다.
- 와이파이-진 프로그램의 여러가지 부분을 개선할 수 있는 아이디어가 있으시다면, github의 PR 기능으로 수정내역을 보내주세요.
- 그밖에 여러가지 생각들이나 의견들은 이메일로 주시면 됩니다. <mailto:pilotedeguerre@gmail.com>

## 고맙습니다!
