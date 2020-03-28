/*******************************************************************************
 * BME280_I2C.hpp
 * ver. 1.4.0
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

#pragma once

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Wire.h"

#define BME280_ADDRESS_0x77                 0x77                // 1110111 (if SA0 connected to VDDIO)
#define BME280_ADDRESS_0x76                 0x76                // 1110110 (if SA0 connected to GND)
#define BME280_ADDRESS                      BME280_ADDRESS_0x76
#define BME280_ID                           0x60

// define Sea Level Pressure
#define SEALEVELPRESSURE_HPA                1013.25f            // default value (change if needed)

class BME280_I2C
{
  public:

    //==========================================================
    // enums
    //==========================================================

    typedef enum
    {
        BME280_REGISTER_CALLIB25            = 0xA1,

        BME280_REGISTER_CHIPID              = 0xD0,
        BME280_REGISTER_VERSION             = 0xD1,

        BME280_REGISTER_RESET               = 0xE0,
        BME280_REGISTER_CALLIB26            = 0xE1,

        BME280_REGISTER_CTRL_HUMIDITY       = 0xF2,
        BME280_REGISTER_STATUS              = 0xF3,
        BME280_REGISTER_CTRL_MEASURE        = 0xF4,
        BME280_REGISTER_CONFIG              = 0xF5,
        BME280_REGISTER_PRESSURE_MSB        = 0xF7,
        BME280_REGISTER_PRESSURE_LSB        = 0xF8,
        BME280_REGISTER_PRESSURE_XLSB       = 0xF9,
        BME280_REGISTER_TEMPERATURE_MSB     = 0xFA,
        BME280_REGISTER_TEMPERATURE_LSB     = 0xFB,
        BME280_REGISTER_TEMPERATURE_XLSB    = 0xFC,
        BME280_REGISTER_HUMIDITY_MSB        = 0xFD,
        BME280_REGISTER_HUMIDITY_LSB        = 0xFE
    } BME280Register;

    typedef enum
    {                                                           // Standby Duration Settings
        BME280_STANDBY_0_5                  = 0x00,             // 0x00 = 0b000 =   0.5 ms
        BME280_STANDBY_62_5                 = 0x01,             // 0x01 = 0b001 =  62.5 ms
        BME280_STANDBY_125                  = 0x02,             // 0x02 = 0b010 =   125 ms
        BME280_STANDBY_250                  = 0x03,             // 0x03 = 0b011 =   250 ms
        BME280_STANDBY_500                  = 0x04,             // 0x04 = 0b100 =   500 ms
        BME280_STANDBY_1000                 = 0x05,             // 0x05 = 0b101 = 1,000 ms
        BME280_STANDBY_10                   = 0x06,             // 0x06 = 0b110 =    10 ms
        BME280_STANDBY_20                   = 0x07              // 0x07 = 0b111 =    20 ms
    } BME280Standby;

    typedef enum
    {                                                           // IIR Filtering Setting
        BME280_FILTER_OFF                   = 0x00,             // 0x00 = 0b000 = OFF
        BME280_FILTER_2                     = 0x01,             // 0x01 = 0b001 =  x2
        BME280_FILTER_4                     = 0x02,             // 0x02 = 0b010 =  x4
        BME280_FILTER_8                     = 0x03,             // 0x03 = 0b011 =  x8
        BME280_FILTER_16                    = 0x04              // 0x04 = 0b100 = x16
    } BME280Filter;

    typedef enum
    {                                                           // 3-Wire SPI Mode Settings
        BME280_SPI3_ENABLE                  = 0x01,             // 0x01 = 0b001 = SPI ENABLE
        BME280_SPI3_DISABLE                 = 0x00              // 0x00 = 0b000 = SPI DISABLE
    } BME280SpiMode;

    typedef enum
    {                                                           // Oversampling Settings
        BME280_OVERSAMPLING_SKIP            = 0x00,             // 0x00 = 0b000 = OFF
        BME280_OVERSAMPLING_1               = 0x01,             // 0x01 = 0b001 =  x1
        BME280_OVERSAMPLING_2               = 0x02,             // 0x02 = 0b010 =  x2
        BME280_OVERSAMPLING_4               = 0x03,             // 0x03 = 0b011 =  x4
        BME280_OVERSAMPLING_8               = 0x04,             // 0x04 = 0b100 =  x8
        BME280_OVERSAMPLING_16              = 0x05              // 0x05 = 0b101 = x16
    } BME280Oversampling;

    typedef enum
    {                                                           // Measure Mode Settings
        BME280_MODE_SLEEP                   = 0x00,             // 0x00 = 0b000 = SLEEP
        BME280_MODE_FORCED                  = 0x01,             // 0x01 = 0b001 = FORCED
        BME280_MODE_NORMAL                  = 0x03              // 0x03 = 0b011 = NORMAL
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

    /**
     * Constructor
     * Create an instance of this class.
     */
    BME280_I2C()
        : BME280_I2C(-1, -1, -1) {}

    /**
     * Constructor
     * Create an instance of this class.
     */
    BME280_I2C(byte addr, byte sda, byte scl)
        : _address(addr), _sda(sda), _scl(scl)
    {
        setSeaLevelPressure(SEALEVELPRESSURE_HPA);
    }

    /**
     * Destructor
     * Destroys an instance of this class.
     */
    ~BME280_I2C() {}

    //==========================================================
    // methods (public)
    //==========================================================
 
    /**
     * setAddress
     * Set BME280 address and connected pins.
     */
    void setAddress(byte addr, byte sda, byte scl)
    {
        _address = addr;
        _sda = sda;
        _scl = scl;
    }

    /**
     * setSeaLevelPressure
     * Set Sea-Level Pressure.
     */
    void setSeaLevelPressure(double pressure)
    {
        _seaLevelPressure = pressure;
    }

    /**
     * begin
     * Begin of sensing use by BME280.
     */
    bool begin(
        BME280Standby standby, 
        BME280Filter filter,
        BME280SpiMode spi3mode,
        BME280Oversampling ovrsT,
        BME280Oversampling ovrsP,
        BME280Oversampling ovrsH,
        BME280Mode mode)
    {
        _conf = (standby << 5) | (filter << 2) | spi3mode;
        _ctrl_meas = (ovrsT << 5) | (ovrsP << 2) | mode;
        _ctrl_humi = ovrsH; 

        Wire.begin(_sda, _scl, 400000);

        uint8_t id = read8(BME280_REGISTER_CHIPID);
        if (id != BME280_ID)
        {
            return false;
        }

        write8(BME280_REGISTER_CONFIG, _conf);
        write8(BME280_REGISTER_CTRL_MEASURE, _ctrl_meas);
        write8(BME280_REGISTER_CTRL_HUMIDITY, _ctrl_humi);

        readTrim();

        return true;
    }

    /**
     * read
     * Read raw datas from BME280, and stored data to "BME280Data" structure.
     */
    void read()
    {
        signed long temp_cal;
        unsigned long pres_cal, humi_cal;

        readRawData();

        temp_cal = calibratedTemperature(_temp_raw);
        pres_cal = calibratedPressure(_pres_raw);
        humi_cal = calibratedHumidity(_humi_raw);

        data.temperature = (double)temp_cal / 100.0;
        data.pressure = (double)pres_cal / 100.0;
        data.humidity = (double)humi_cal / 1024.0;
        data.altitude = calculateAltitude(data.pressure);
    }

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

    /**
     * readTrim
     */
    void readTrim()
    {
        uint8_t data[32], i = 0;

        Wire.beginTransmission(_address);
        Wire.write(0x88);
        Wire.endTransmission();
        Wire.requestFrom((uint8_t)_address, (uint8_t)24);
        while (Wire.available())
        {
            data[i++] = Wire.read();
        }

        data[i++] = read8(BME280_REGISTER_CALLIB25);

        Wire.beginTransmission(_address);
        Wire.write(BME280_REGISTER_CALLIB26);
        Wire.endTransmission();
        Wire.requestFrom((uint8_t)_address, (uint8_t)7);
        while (Wire.available())
        {
            data[i++] = Wire.read();
        }

        _dig_T1 = (data[1]  << 8) | data[0];
        _dig_T2 = (data[3]  << 8) | data[2];
        _dig_T3 = (data[5]  << 8) | data[4];
        _dig_P1 = (data[7]  << 8) | data[6];
        _dig_P2 = (data[9]  << 8) | data[8];
        _dig_P3 = (data[11] << 8) | data[10];
        _dig_P4 = (data[13] << 8) | data[12];
        _dig_P5 = (data[15] << 8) | data[14];
        _dig_P6 = (data[17] << 8) | data[16];
        _dig_P7 = (data[19] << 8) | data[18];
        _dig_P8 = (data[21] << 8) | data[20];
        _dig_P9 = (data[23] << 8) | data[22];
        _dig_H1 =  data[24];
        _dig_H2 = (data[26] << 8) | data[25];
        _dig_H3 =  data[27];
        _dig_H4 = (data[28] << 4) | (0x0F & data[29]);
        _dig_H5 = (data[30] << 4) | ((data[29] >> 4) & 0x0F);
        _dig_H6 =  data[31];
    }

    /**
     * readRawData
     * Read raw data from BME280.
     */
    void readRawData()
    {
        int i = 0;
        uint32_t data[8];

        Wire.beginTransmission(_address);
        Wire.write(BME280_REGISTER_PRESSURE_MSB);
        Wire.endTransmission();
        Wire.requestFrom((uint8_t)_address, (uint8_t)8);
        while (Wire.available())
        {
            data[i++] = Wire.read();
        }

        _pres_raw = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);
        _temp_raw = (data[3] << 12) | (data[4] << 4) | (data[5] >> 4);
        _humi_raw = (data[6] << 8) | data[7];
    }

    /**
     * calibratedTemperature
     * Calibrate temperature raw data.
     */
    signed long calibratedTemperature(signed long int adc_T)
    {
        signed long int var1, var2, T;

        var1 = ((((adc_T >> 3) - ((signed long int)_dig_T1 << 1))) * ((signed long int)_dig_T2)) >> 11;
        var2 = (((((adc_T >> 4) - ((signed long int)_dig_T1)) * ((adc_T >> 4) - ((signed long int)_dig_T1))) >> 12) * ((signed long int)_dig_T3)) >> 14;

        _t_fine = var1 + var2;
        T = (_t_fine * 5 + 128) >> 8;

        return T; 
    }

    /**
     * calibratedPressure
     * Calibrate Pressure raw data.
     */
    unsigned long calibratedPressure(signed long int adc_P)
    {
        signed long int var1, var2;
        unsigned long int P;

        var1 = (((signed long int)_t_fine)>>1) - (signed long int)64000;
        var2 = (((var1>>2) * (var1>>2)) >> 11) * ((signed long int)_dig_P6);
        var2 = var2 + ((var1*((signed long int)_dig_P5)) << 1);
        var2 = (var2>>2)+(((signed long int)_dig_P4) << 16);

        var1 = (((_dig_P3 * (((var1>>2)*(var1>>2)) >> 13)) >>3) + ((((signed long int)_dig_P2) * var1) >> 1)) >> 18;
        var1 = ((((32768+var1))*((signed long int)_dig_P1)) >> 15);
        if (var1 == 0)
        {
            return 0;
        }

        P = (((unsigned long int)(((signed long int)1048576) - adc_P) - (var2 >> 12))) * 3125;
        if (P < 0x80000000)
        {
            P = (P << 1) / ((unsigned long int) var1);
        }
        else
        {
            P = (P / (unsigned long int)var1) * 2;
        }

        var1 = (((signed long int)_dig_P9) * ((signed long int)(((P >> 3) * (P >> 3)) >> 13))) >> 12;
        var2 = (((signed long int)(P>>2)) * ((signed long int)_dig_P8)) >> 13;
        P = (unsigned long int)((signed long int)P + ((var1 + var2 + _dig_P7) >> 4));

        return P;
    }

    /**
     * calibratedHumidity
     * Calibrate Humidity raw data.
     */
    unsigned long calibratedHumidity(signed long int adc_H)
    {
        signed long int v_x1;
        unsigned long int H;

        v_x1 = (_t_fine - ((signed long int)76800));
        v_x1 = (((((adc_H << 14) -(((signed long int)_dig_H4) << 20) - (((signed long int)_dig_H5) * v_x1)) + ((signed long int)16384)) >> 15) * 
                (((((((v_x1 * ((signed long int)_dig_H6)) >> 10) * (((v_x1 * ((signed long int)_dig_H3)) >> 11) + ((signed long int) 32768))) >> 10) +
                (( signed long int)2097152)) * ((signed long int)_dig_H2) + 8192) >> 14));
        v_x1 = (v_x1 - (((((v_x1 >> 15) * (v_x1 >> 15)) >> 7) * ((signed long int)_dig_H1)) >> 4));
        v_x1 = (v_x1 < 0 ? 0 : v_x1);    v_x1 = (v_x1 > 419430400 ? 419430400 : v_x1);

        H = (unsigned long int)(v_x1 >> 12);

        return H;
    }

    /**
     * calculateAltitude
     * Calculate altitude from atmospheric pressure.
     * Sea-level pressure used is the inner value, and that value can set by calling setSeaLevelPressure().
     */
    double calculateAltitude(double pressure)
    {
        return calculateAltitude(_seaLevelPressure, pressure);
    }

    /**
     * calculateAltitude
     * Calculate altitude from atmospheric pressure and sea-level pressure.
     */
    double calculateAltitude(double seaLevelPressure, double pressure)
    {
        double A = 44330.0 * (1.0 - pow(pressure / seaLevelPressure, (1.0 / 5.255)));

        return A;
    }

    /**
     * write8
     * Write 8bit data to register of BME280.
     */
    void write8(BME280Register reg, byte value)
    {
        Wire.beginTransmission(_address);
        Wire.write((byte)reg);
        Wire.write(value);
        Wire.endTransmission();
    }

    /**
     * read8
     * Read 8bit data from register of BME280.
     */
    byte read8(BME280Register reg)
    {
        byte value;

        Wire.beginTransmission(_address);
        Wire.write((byte)reg);
        Wire.endTransmission();
        Wire.requestFrom(_address, (byte)1);

        value = Wire.read();
        Wire.endTransmission();

        return value;
    }
};
