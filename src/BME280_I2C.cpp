/*******************************************************************************
 * BME280_I2C.h
 * ver. 1.0.0
 * 
 * This library assume for use with Arduino core for ESP32.
 * BME280 is a multi-function sensor from BOSCH that can measure temperature, 
 * humidity and pressure.
 * 
 * The MIT License (MIT)
 * Copyright (c) 2020, ks-tec [Modified]
 * 
 * Refered technical URL:
 *   http://trac.switch-science.com/wiki/BME280
 *   - Original License is Unkown
 * 
 * Refered technical URL:
 *   https://kazz12211.wordpress.com/2016/03/10/bme280%e6%b8%a9%e6%b9%bf%e5%ba%a6%e3%83%bb%e6%b0%97%e5%9c%a7%e3%82%bb%e3%83%b3%e3%82%b5%e3%83%bc%e3%81%ae%e5%8b%95%e4%bd%9c%e7%a2%ba%e8%aa%8d/
 *   - Original License is Unkown
 * 
 * Refered library URL:
 *   https://github.com/adafruit/Adafruit_BME280_Library
 *   - Original License is BSD [Copyright (c) 2012, Adafruit Industries]
 ******************************************************************************/

#include "BME280_I2C.h"

//==========================================================
// constructors
//==========================================================

/**
 * Constructor
 * Create an instance of this class.
 */
BME280_I2C::BME280_I2C() {}

/**
 * Destructor
 * Destroys an instance of this class.
 */
BME280_I2C::~BME280_I2C() {}

//==========================================================
// methods (public)
//==========================================================

/**
 * begin
 * Begin of sensing use by BME280.
 */
bool BME280_I2C::begin(
      byte addr,
      byte sda,
      byte scl,
      BME280Standby standby, 
      BME280Filter filter,
      BME280SpiMode spi3mode,
      BME280Oversampling ovrsT,
      BME280Oversampling ovrsP,
      BME280Oversampling ovrsH,
      BME280Mode mode)
{
  Wire.begin(sda, scl, 400000);

  address = addr;

  conf = (standby << 5) | (filter << 2) | spi3mode;
  ctrl_meas = (ovrsT << 5) | (ovrsP << 2) | mode;
  ctrl_hum = ovrsH; 

  uint8_t id = read8(BME280_REGISTER_CHIPID);
  if (id != BME280_ID)
  {
    return false;
  }

  write8(BME280_REGISTER_CONFIG, conf);
  write8(BME280_REGISTER_CTRL_MEASURE, ctrl_meas);
  write8(BME280_REGISTER_CTRL_HUMIDITY, ctrl_hum);

  readTrim();

  return true;
}

/**
 * read
 * Read raw datas from BME280, and stored data to "BME280Data" structure.
 */
void BME280_I2C::read()
{
  signed long temp_cal;
  unsigned long press_cal, hum_cal;

  readRawData();

  temp_cal  = calibratedTemperature(temp_raw);
  press_cal = calibratedPressure(press_raw);
  hum_cal   = calibratedHumidity(hum_raw);

  data.temperature = (double)temp_cal / 100.0;
  data.pressure = (double)press_cal / 100.0;
  data.humidity = (double)hum_cal / 1024.0;
}

//==========================================================
// methods (public)
//==========================================================

/**
 * readTrim
 */
void BME280_I2C::readTrim()
{
  uint8_t data[32], i = 0;

  Wire.beginTransmission(address);
  Wire.write(0x88);
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)address, (uint8_t)24);
  while (Wire.available())
  {
    data[i++] = Wire.read();
  }

  data[i++] = read8(BME280_REGISTER_CALLIB25);

  Wire.beginTransmission(address);
  Wire.write(BME280_REGISTER_CALLIB26);
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)address, (uint8_t)7);
  while (Wire.available())
  {
    data[i++] = Wire.read();
  }

  dig_T1 = (data[1]  << 8) | data[0];
  dig_T2 = (data[3]  << 8) | data[2];
  dig_T3 = (data[5]  << 8) | data[4];
  dig_P1 = (data[7]  << 8) | data[6];
  dig_P2 = (data[9]  << 8) | data[8];
  dig_P3 = (data[11] << 8) | data[10];
  dig_P4 = (data[13] << 8) | data[12];
  dig_P5 = (data[15] << 8) | data[14];
  dig_P6 = (data[17] << 8) | data[16];
  dig_P7 = (data[19] << 8) | data[18];
  dig_P8 = (data[21] << 8) | data[20];
  dig_P9 = (data[23] << 8) | data[22];
  dig_H1 = data[24];
  dig_H2 = (data[26] << 8) | data[25];
  dig_H3 = data[27];
  dig_H4 = (data[28] << 4) | (0x0F & data[29]);
  dig_H5 = (data[30] << 4) | ((data[29] >> 4) & 0x0F);
  dig_H6 = data[31];
}

/**
 * readRawData
 * Read raw data from BME280.
 */
void BME280_I2C::readRawData()
{
  int i = 0;
  uint32_t data[8];

  Wire.beginTransmission(address);
  Wire.write(BME280_REGISTER_PRESSURE_MSB);
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)address, (uint8_t)8);
  while (Wire.available())
  {
    data[i++] = Wire.read();
  }

  press_raw = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);
  temp_raw  = (data[3] << 12) | (data[4] << 4) | (data[5] >> 4);
  hum_raw   = (data[6] << 8) | data[7];
}

/**
 * calibratedTemperature
 * Calibrate temperature raw data.
 */
signed long BME280_I2C::calibratedTemperature(signed long int adc_T)
{
  signed long int var1, var2, T;

  var1 = ((((adc_T >> 3) - ((signed long int)dig_T1 << 1))) * ((signed long int)dig_T2)) >> 11;
  var2 = (((((adc_T >> 4) - ((signed long int)dig_T1)) * ((adc_T >> 4) - ((signed long int)dig_T1))) >> 12) * ((signed long int)dig_T3)) >> 14;

  t_fine = var1 + var2;
  T = (t_fine * 5 + 128) >> 8;

  return T; 
}

/**
 * calibratedPressure
 * Calibrate Pressure raw data.
 */
unsigned long BME280_I2C::calibratedPressure(signed long int adc_P)
{
  signed long int var1, var2;
  unsigned long int P;

  var1 = (((signed long int)t_fine)>>1) - (signed long int)64000;
  var2 = (((var1>>2) * (var1>>2)) >> 11) * ((signed long int)dig_P6);
  var2 = var2 + ((var1*((signed long int)dig_P5)) << 1);
  var2 = (var2>>2)+(((signed long int)dig_P4) << 16);

  var1 = (((dig_P3 * (((var1>>2)*(var1>>2)) >> 13)) >>3) + ((((signed long int)dig_P2) * var1) >> 1)) >> 18;
  var1 = ((((32768+var1))*((signed long int)dig_P1)) >> 15);
  if (var1 == 0)
  {
      return 0;
  }

  P = (((unsigned long int)(((signed long int)1048576) - adc_P) - (var2 >> 12))) * 3125;
  if(P<0x80000000)
  {
    P = (P << 1) / ((unsigned long int) var1);
  }
  else
  {
    P = (P / (unsigned long int)var1) * 2;
  }

  var1 = (((signed long int)dig_P9) * ((signed long int)(((P >> 3) * (P >> 3)) >> 13))) >> 12;
  var2 = (((signed long int)(P>>2)) * ((signed long int)dig_P8)) >> 13;
  P = (unsigned long int)((signed long int)P + ((var1 + var2 + dig_P7) >> 4));

  return P;
}

/**
 * calibratedHumidity
 * Calibrate Humidity raw data.
 */
unsigned long BME280_I2C::calibratedHumidity(signed long int adc_H)
{
  signed long int v_x1;
  unsigned long int H;

  v_x1 = (t_fine - ((signed long int)76800));
  v_x1 = (((((adc_H << 14) -(((signed long int)dig_H4) << 20) - (((signed long int)dig_H5) * v_x1)) + ((signed long int)16384)) >> 15) * 
          (((((((v_x1 * ((signed long int)dig_H6)) >> 10) * (((v_x1 * ((signed long int)dig_H3)) >> 11) + ((signed long int) 32768))) >> 10) +
           (( signed long int)2097152)) * ((signed long int) dig_H2) + 8192) >> 14));
  v_x1 = (v_x1 - (((((v_x1 >> 15) * (v_x1 >> 15)) >> 7) * ((signed long int)dig_H1)) >> 4));
  v_x1 = (v_x1 < 0 ? 0 : v_x1);    v_x1 = (v_x1 > 419430400 ? 419430400 : v_x1);

  H = (unsigned long int)(v_x1 >> 12);

  return H;
}

/**
 * write8
 * Write 8bit data to register of BME280.
 */
void BME280_I2C::write8(BME280Register reg, byte value)
{
  Wire.beginTransmission(address);
  Wire.write((byte)reg);
  Wire.write(value);
  Wire.endTransmission();
}

/**
 * read8
 * Read 8bit data from register of BME280.
 */
byte BME280_I2C::read8(BME280Register reg)
{
  byte value;

  Wire.beginTransmission(address);
  Wire.write((byte)reg);
  Wire.endTransmission();
  Wire.requestFrom(address, (byte)1);

  value = Wire.read();
  Wire.endTransmission();

  return value;
}
