/*******************************************************************************
 * BME280_I2C.h
 * ver. 1.3.0
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

#ifndef _BME280_I2C_h

#define _BME280_I2C_h

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Wire.h"

//#define BME280_ADDRESS              0x77      // 1110111 (if SA0 connected to VDDIO)
#define BME280_ADDRESS                0x76      // 1110110 (if SA0 connected to GND)
#define BME280_ID                     0x60

// define Sea Level Pressure
#define SEALEVELPRESSURE_HPA          1013.25   // default value (change if needed)

class BME280_I2C
{
  public:
    //==========================================================
    // enums
    //==========================================================
    typedef enum
    {
      BME280_REGISTER_CALLIB25         = 0xA1,

      BME280_REGISTER_CHIPID           = 0xD0,
      BME280_REGISTER_VERSION          = 0xD1,

      BME280_REGISTER_RESET            = 0xE0,
      BME280_REGISTER_CALLIB26         = 0xE1,

      BME280_REGISTER_CTRL_HUMIDITY    = 0xF2,
      BME280_REGISTER_STATUS           = 0xF3,
      BME280_REGISTER_CTRL_MEASURE     = 0xF4,
      BME280_REGISTER_CONFIG           = 0xF5,
      BME280_REGISTER_PRESSURE_MSB     = 0xF7,
      BME280_REGISTER_PRESSURE_LSB     = 0xF8,
      BME280_REGISTER_PRESSURE_XLSB    = 0xF9,
      BME280_REGISTER_TEMPERATURE_MSB  = 0xFA,
      BME280_REGISTER_TEMPERATURE_LSB  = 0xFB,
      BME280_REGISTER_TEMPERATURE_XLSB = 0xFC,
      BME280_REGISTER_HUMIDITY_MSB     = 0xFD,
      BME280_REGISTER_HUMIDITY_LSB     = 0xFE
    } BME280Register;

    typedef enum
    {                                           // Standby Duration Settings
      BME280_STANDBY_0_5               = 0x00,  // 0x00 = 0b000 =   0.5 ms
      BME280_STANDBY_62_5              = 0x01,  // 0x01 = 0b001 =  62.5 ms
      BME280_STANDBY_125               = 0x02,  // 0x02 = 0b010 =   125 ms
      BME280_STANDBY_250               = 0x03,  // 0x03 = 0b011 =   250 ms
      BME280_STANDBY_500               = 0x04,  // 0x04 = 0b100 =   500 ms
      BME280_STANDBY_1000              = 0x05,  // 0x05 = 0b101 = 1,000 ms
      BME280_STANDBY_10                = 0x06,  // 0x06 = 0b110 =    10 ms
      BME280_STANDBY_20                = 0x07   // 0x07 = 0b111 =    20 ms
    } BME280Standby;

    typedef enum
    {                                           // IIR Filtering Setting
      BME280_FILTER_OFF                = 0x00,  // 0x00 = 0b000 = OFF
      BME280_FILTER_2                  = 0x01,  // 0x01 = 0b001 =  x2
      BME280_FILTER_4                  = 0x02,  // 0x02 = 0b010 =  x4
      BME280_FILTER_8                  = 0x03,  // 0x03 = 0b011 =  x8
      BME280_FILTER_16                 = 0x04   // 0x04 = 0b100 = x16
    } BME280Filter;

    typedef enum
    {                                           // 3-Wire SPI Mode Settings
      BME280_SPI3_ENABLE               = 0x01,  // 0x01 = 0b001 = SPI ENABLE
      BME280_SPI3_DISABLE              = 0x00   // 0x00 = 0b000 = SPI DISABLE
    } BME280SpiMode;

    typedef enum
    {                                           // Oversampling Settings
      BME280_OVERSAMPLING_SKIP         = 0x00,  // 0x00 = 0b000 = OFF
      BME280_OVERSAMPLING_1            = 0x01,  // 0x01 = 0b001 =  x1
      BME280_OVERSAMPLING_2            = 0x02,  // 0x02 = 0b010 =  x2
      BME280_OVERSAMPLING_4            = 0x03,  // 0x03 = 0b011 =  x4
      BME280_OVERSAMPLING_8            = 0x04,  // 0x04 = 0b100 =  x8
      BME280_OVERSAMPLING_16           = 0x05   // 0x05 = 0b101 = x16
    } BME280Oversampling;

    typedef enum
    {                                           // Measure Mode Settings
      BME280_MODE_SLEEP                = 0x00,  // 0x00 = 0b000 = SLEEP
      BME280_MODE_FORCED               = 0x01,  // 0x01 = 0b001 = FORCED
      BME280_MODE_NORMAL               = 0x03   // 0x03 = 0b011 = NORMAL
    } BME280Mode;

    typedef struct bme280data
    {
      double temperature;
      double pressure;
      double humidity;
      double altitude;
    } BME280Data;

    //==========================================================
    // variables (public)
    //==========================================================
    BME280Data data;

    //==========================================================
    // constructors
    //==========================================================
    BME280_I2C();
    BME280_I2C(byte addr, byte sda, byte scl);
    ~BME280_I2C();

    //==========================================================
    // methods (public)
    //==========================================================
    void setAddress(byte addr, byte sda, byte scl);
    void setSeaLevelPressure(double pressure);
    bool begin(
      BME280Standby standby, 
      BME280Filter filter,
      BME280SpiMode spi3mode,
      BME280Oversampling ovrsT,
      BME280Oversampling ovrsP,
      BME280Oversampling ovrsH,
      BME280Mode mode);
    void read();

  private:
    //==========================================================
    // variables (private)
    //==========================================================
    byte _address, _sda, _scl;
    uint8_t _conf, _ctrl_meas, _ctrl_humi;
    uint16_t _dig_T1;
     int16_t _dig_T2;
     int16_t _dig_T3;
    uint16_t _dig_P1;
     int16_t _dig_P2;
     int16_t _dig_P3;
     int16_t _dig_P4;
     int16_t _dig_P5;
     int16_t _dig_P6;
     int16_t _dig_P7;
     int16_t _dig_P8;
     int16_t _dig_P9;
     int8_t  _dig_H1;
     int16_t _dig_H2;
     int8_t  _dig_H3;
     int16_t _dig_H4;
     int16_t _dig_H5;
     int8_t  _dig_H6;
    signed long int _t_fine;
    unsigned long int _temp_raw, _pres_raw, _humi_raw;
    double _seaLevelPressure;

    //==========================================================
    // methods (private)
    //==========================================================
    void readTrim();
    void readRawData();
    signed long calibratedTemperature(signed long int rawT);
    unsigned long calibratedPressure(signed long int rawP);
    unsigned long calibratedHumidity(signed long int rawH);
    double calculateAltitude(double pressure);
    double calculateAltitude(double seaLevelPressure, double pressure);
    void write8(BME280Register reg, byte value);
    byte read8(BME280Register reg);
};

#endif
