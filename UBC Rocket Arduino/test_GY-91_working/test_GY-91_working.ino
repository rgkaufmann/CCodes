#include <Adafruit_BMP280.h>
#include <MPU9250_asukiaaa.h>


#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

MPU9250 mpu9250;
Adafruit_BMP280 bmp; // I2C

void setup() {
  while (!Serial);

  Serial.begin(115200);
  Serial.println("started");

#ifdef _ESP32_HAL_I2C_H_
  // for esp32
  // If not default values, check
  Wire.begin(SDA_PIN, SCL_PIN); //sda, scl
#else
  Wire.begin();
#endif


  // BMP280
  Serial.println(F("BMP280 test"));
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  /* Default settings from datasheet. */
  //  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
  //                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
  //                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
  //                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
  //                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  // MPU9250
  mpu9250.setWire(&Wire);
  mpu9250.beginAccel();
  mpu9250.beginMag();

  // you can set your own offset for mag values
  // mySensor.magXOffset = -50;
  // mySensor.magYOffset = -55;
  // mySensor.magZOffset = -10;
}

void loop() {
  // BMP280
  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
  Serial.println(" m");

  // MPU9250
  mpu9250.accelUpdate();
  Serial.println("print accel values");
  Serial.println("accelX: " + String(mpu9250.accelX()));
  Serial.println("accelY: " + String(mpu9250.accelY()));
  Serial.println("accelZ: " + String(mpu9250.accelZ()));
  Serial.println("accelSqrt: " + String(mpu9250.accelSqrt()));

  mpu9250.magUpdate();
  Serial.println("print mag values");
  Serial.println("magX: " + String(mpu9250.magX()));
  Serial.println("maxY: " + String(mpu9250.magY()));
  Serial.println("magZ: " + String(mpu9250.magZ()));
  Serial.println("horizontal direction: " + String(mpu9250.magHorizDirection()));

  Serial.println("at " + String(millis()) + "ms");
  delay(2000);
}
