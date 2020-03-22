//******************************************************************************
// BME280_I2C_sample.ino
//******************************************************************************

#include "BME280_I2C.h"

// define the baud rate for serial communication
#define SERIAL_BAUD_RATE 115200

// define the wiring settings for I2C interface connection
#define BME280_I2C_SCL    26
#define BME280_I2C_SDA    25
#define BME280_FREQUENCY  400000

// define the instance of BME280_I2C class
BME280_I2C bme280;
// also possible to omit the subsequent address setting
// BME280_I2C bme280(BME280_ADDRESS, BME280_I2C_SDA, BME280_I2C_SCL);

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println(F("Hardware serial initialized."));
  delay(100);

  // set address and pins
  bme280.setAddress(BME280_ADDRESS, BME280_I2C_SDA, BME280_I2C_SCL);

  // initialize BME280
  bool isStatus = bme280.begin(
    bme280.BME280_STANDBY_0_5,
    bme280.BME280_FILTER_16,
    bme280.BME280_SPI3_DISABLE,
    bme280.BME280_OVERSAMPLING_2,
    bme280.BME280_OVERSAMPLING_16,
    bme280.BME280_OVERSAMPLING_1,
    bme280.BME280_MODE_NORMAL);
  if (!isStatus)
  {
    Serial.println("can NOT initialize for using BME280.\n");
    while(true);
  }
  else
  {
    Serial.println("ready to using BME280.\n");
  }
  delay(1000);
}

void loop()
{
  // read data from BME280
  readBme280();
  delay(3000);
}

void readBme280()
{
  // read values from BME280 and store calibrated values in the library
  bme280.read();

  // format the read values
  char temp_c[12], humi_c[12], pres_c[12], altd_c[12];
  sprintf(temp_c, "%2.2lf", bme280.data.temperature);
  sprintf(humi_c, "%2.2lf", bme280.data.humidity);
  sprintf(pres_c, "%4.2lf", bme280.data.pressure);
  sprintf(altd_c, "%4.2lf", bme280.data.altitude);

  // output values to serial console
  Serial.println("-----------------------");
  Serial.print("Temperature: "); Serial.print(temp_c); Serial.println(" ℃");
  Serial.print("Humidity: ");    Serial.print(humi_c); Serial.println(" %");
  Serial.print("Pressure: ");    Serial.print(pres_c); Serial.println(" hPa");
  Serial.print("Altitude: ");    Serial.print(altd_c); Serial.println(" m");
  Serial.println("-----------------------");
  Serial.flush();
}
