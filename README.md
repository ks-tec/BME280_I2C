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
  
## Change log
(1.1.0)  
Changed specifications of begin() function.  
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

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:  
  
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.  
  
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  
  
以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェアを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/または販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。  
  
上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。  
  
ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請求、損害、その他の義務について何らの責任も負わないものとします。  
