# BME280_I2C
BME280 library for I2C interface.  
Using this library, BME280 can be easying used with I2C interface of ESP32.  
  
I2C インターフェース用 BME280 ライブラリ  
このライブラリを使用することで ESP32 の I2C インターフェース接続で BME280 を簡単に使用できます。  
  
## Overview
This library assume for use with 'Arduino core for ESP32'.  
BME280 is a multi-function sensor from BOSCH that can measure temperature, humidity and pressure.  
  
このライブラリは "Arduino core for ESP32" 上での使用を想定しています。  
BME280 は BOSCH社製が提供する多機能センサーで 温度・湿度・気圧 を計測できるセンサーです。  
  
<img src="./resources/GY-BME280_001.png" title="GY-BME280">
  
## Usage
This library support only BME280 connected with I2C interface.  
  
このライブラリは、I2Cインターフェイスに接続されたBME280のみをサポートしています。  
  
### I2C with BME280_I2C.h ( BME280_I2C.h include Wire.h )
```C++
#include "BME280_I2C.h"

// define the wiring settings for I2C interface connection
#define BME280_I2C_SCL    26
#define BME280_I2C_SDA    25
#define BME280_FREQUENCY  400000

// define the instance of BME280_I2C class
BME280_I2C bme280;
// also possible to omit the subsequent setAddress()
// BME280_I2C bme280(BME280_ADDRESS, BME280_I2C_SDA, BME280_I2C_SCL);

// set address and pins
bme280.setAddress(BME280_ADDRESS, BME280_I2C_SDA, BME280_I2C_SCL);

// and then begin the sensor
bme280.begin(standby_time, filter, spi_mode, temp_oversampling, pres_oversampling, humi_oversampling, exec_mode);

// read values from BME280 and store calibrated values in the library
bme280.read();
```
  
## Change log
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
Using this library, BME280 can be easying used with I2C interface of ESP32.  
For use this library, install bellow libraries to Arduino IDE.  

このライブラリを使用することで ESP32 の I2C インターフェース接続で BME280 を簡単に使用できます。  
Arduino IDE に 以下のライブラリを導入してください。  
  
- Wire
  
## Refered Site
http://trac.switch-science.com/wiki/BME280  
Original License is Unkown  
  
adafruit/Adafruit_BME280_Library: Arduino Library for BME280 sensors  
https://github.com/adafruit/Adafruit_BME280_Library  
  
BME280温湿度・気圧センサーの動作確認  
https://kazz12211.wordpress.com/2016/03/10/bme280%e6%b8%a9%e6%b9%bf%e5%ba%a6%e3%83%bb%e6%b0%97%e5%9c%a7%e3%82%bb%e3%83%b3%e3%82%b5%e3%83%bc%e3%81%ae%e5%8b%95%e4%bd%9c%e7%a2%ba%e8%aa%8d/  
  
BME280 とesp32で温度・湿度・気圧を測定する  
https://raspberry-pi.nomad-life.net/1928977/memo/esp32%e3%81%a7%e6%b8%a9%e5%ba%a6%e3%83%bb%e6%b9%bf%e5%ba%a6%e3%83%bb%e6%b0%97%e5%9c%a7%e3%82%92%e8%a8%88%e6%b8%ac%e3%81%99%e3%82%8b  
  
## Credits and license
The MIT License (MIT)  
Copyright (c) 2020, ks-tec.