# BME280_I2C
BME280 library for I2C interface.  
Using this library, BME280 can be easying used with I2C interface of ESP32.  
  
I2C インターフェース用 BME280 ライブラリ  
このライブラリを使用することで ESP32 の I2C インターフェース接続で BME280 を簡単に使用できます。  
  
## Overview
This library assume for use with 'PlatformIO' or 'Arduino core for ESP32'.  
BME280 is a multi-function sensor from BOSCH that can measure temperature, humidity and atmospheric pressure.  
  
このライブラリは "PlatformIO" または "Arduino core for ESP32" での使用を想定しています。  
BME280 は BOSCH社製が提供する多機能センサーで 温度・湿度・大気圧 を計測できるマルチセンサーです。  
  
<img src="./resources/GY-BME280_001.png" title="GY-BME280">
  
## Usage
This library support only BME280 connected with I2C interface.  
  
And using this library, BME280 can be easying used with I2C interface of ESP32.  
For use this library, install bellow libraries to your development environment.
  
このライブラリは、I2Cインターフェイスに接続されたBME280のみをサポートしています。  
  
このライブラリを使用することで ESP32 の I2C インターフェース接続で BME280 を簡単に使用できます。  
開発環境に 以下のライブラリを導入してください。  
  
- Wire  
  
## Example
as follows, the usage outline of this library is.  

以下に、このライブラリの使い方を示します。  

### I2C with BME280_I2C.h ( BME280_I2C.h include Wire.h )
```C++
#include "BME280_I2C.h"

// define the wiring settings for I2C interface connection.
#define BME280_I2C_SCL    26
#define BME280_I2C_SDA    25
#define BME280_FREQUENCY  400000

// define the instance of BME280_I2C class.
BME280_I2C bme280;

// set address and connected pins.
// since the address of BME280 is defined in the header file.
// it changes according to the setting of BME280.
bme280.setAddress(BME280_ADDRESS, BME280_I2C_SDA, BME280_I2C_SCL);

// as follows, you can also omit setAddress() by intantiating the class.
// BME280_I2C bme280(BME280_ADDRESS, BME280_I2C_SDA, BME280_I2C_SCL);

// and then begin the sensor.
// each parameter uses the enum values ​​defined in the header file.
// typically, SPI mode uses BME280_SPI3_DISABLE because it is for I2C.
bme280.begin(standby_time, filter, spi_mode, temp_oversampling, pres_oversampling, humi_oversampling, exec_mode);

// read values from BME280.
// and the calibrated values is storeed to BME280.data in the library.
// the stored data is temperature, atmospheric pressure, humidity and altitude.
bme280.read();
```
  
## Download and Install
Download and Install of this library is supported by GitHub and PlatformIO.  
  
このライブラリのダウンロードおよびインストールは GitHub と PlatformIO でサポートされています。  
  
- GitHub  
    https://github.com/ks-tec/BME280_I2C
  
    How to installation, it is "Clone or Download" from the following page.  
    https://github.com/ks-tec/BME280_I2C
  
- PlatformIO  
  https://platformio.org/lib/show/7143/BME280_I2C

    How to installation, it is writen in the following page.  
    https://platformio.org/lib/show/7143/BME280_I2C/installation
  
## TODO Tasks
- [x] Getting the sea level pressure by hour  
~~Now defined constant value in header file is 1 atmospheric pressure. (1 atmospheric pressure = 1013.25 hPa)~~  
    
    Getting the sea level pressure by hour, it is possible to calculate more than right altitude.  
    ~~Therefore, In the future, add new calculate function to BME280_I2C class or extend existing function.  
    The functions to be added or extended will receive sea level pressure as a parameter.~~  

    １時間ごとの海面気圧を取得することで より正確な高度を算出できます。  
    ~~そのため、BME280_I2C クラスに新しい計算関数を追加するか、既存の関数を拡張します。
    その関数は 海面気圧を引数に受け取ることになるでしょう。~~
  
    The function was added at ver.1.3.0, and fixed bug at ver.1.3.1 .
  
    海面気圧を設定する関数が ver.1.3.0 で追加され、ver1.3.1 で不具合が修正されました。
  
## Refered Site
http://trac.switch-science.com/wiki/BME280  
Original License is Unkown  
  
adafruit/Adafruit_BME280_Library: Arduino Library for BME280 sensors  
https://github.com/adafruit/Adafruit_BME280_Library  
  
BME280温湿度・気圧センサーの動作確認  
https://kazz12211.wordpress.com/2016/03/10/bme280%e6%b8%a9%e6%b9%bf%e5%ba%a6%e3%83%bb%e6%b0%97%e5%9c%a7%e3%82%bb%e3%83%b3%e3%82%b5%e3%83%bc%e3%81%ae%e5%8b%95%e4%bd%9c%e7%a2%ba%e8%aa%8d/  
  
BME280 とesp32で温度・湿度・気圧を測定する  
https://raspberry-pi.nomad-life.net/1928977/memo/esp32%e3%81%a7%e6%b8%a9%e5%ba%a6%e3%83%bb%e6%b9%bf%e5%ba%a6%e3%83%bb%e6%b0%97%e5%9c%a7%e3%82%92%e8%a8%88%e6%b8%ac%e3%81%99%e3%82%8b  
  
## Change log
(1.3.1)
Fixed bug at setSeaLevelPressure() function.
  
setSeaLevelPressure() 関数の不具合を修正しました。

(1.3.0)
Added function that set sea-level pressure.  
  
海面気圧を設定する関数を追加しました。  
  
(1.2.0)  
Added calculate altitude function.  
It can be obtained with data.altitude, and just needs to call read() function as before.  
  
標高を計算する関数 calculateAltitude() を追加しました。  
data.altitude で取得でき 従来どおり read() 関数の呼び出しのみで済みます。  
  
(1.1.0)  
Changed specifications of the begin() function.  
Changed to set BME280 address and connected pins using constructor or setAddress() function.  
  
BME280_I2C クラスの begin() 関数の仕様を変更しました。  
BME280 のアドレスおよび接続ピンの設定は コンストラクタ または setAddress() 関数を使用するように変更しました。  
  
(1.0.0)  
First released.  
  
最初のリリースです。  
  
## Credits and license
The MIT License (MIT)  
Copyright (c) 2020, ks-tec.
