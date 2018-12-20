    #include <Wire.h>
    #include "BMA250.h"

    #if defined (ARDUINO_ARCH_SAMD)
    #define SerialMonitorInterface SerialUSB
    #else
    #define SerialMonitorInterface Serial
    #endif

    #define HMC5883_I2CADDR      0x1E
    
    BMA250 accel;
    int CompassX;
    int CompassY;
    int CompassZ;
    
    void setup()
    {
      SerialMonitorInterface.begin(9600);
      Wire.begin();
      accel.begin(BMA250_range_2g, BMA250_update_time_64ms);
      HMC5883nit();
    }
    
    void loop() {
      accel.read();
      Serial.print("X = ");
      Serial.print(accel.X);
      Serial.print("  ");
      Serial.print("Y = ");
      Serial.print(accel.Y);
      Serial.print("  ");
      Serial.print("Z = ");
      Serial.print(accel.Z);
      Serial.print("  Temperature(C) = ");
      Serial.println((accel.rawTemp*0.5)+24.0,1);

      HMC5883ReadCompass();
      Serial.print("x: ");
      Serial.print(CompassX);
      Serial.print("y: ");
      Serial.print(CompassY);
      Serial.print("z: ");
      Serial.print(CompassZ);
      
      delay(250);
    }

    void HMC5883nit() {
      Wire.beginTransmission(HMC5883_I2CADDR);
      Wire.write(0x02);
      Wire.write(0x00);
      Wire.endTransmission();
    }

    void HMC583ReadCompass() {
      uint8_t ReadBuff[6];

      Wire.beginTransmission(HMC5883_I2CADDR);
      Wire.write(0x03);
      Wire.endTransmission();
      Wire.requestFrom(HMC5883_I2CADDR, 6);

      for(int i = 0; i < 6; i++) {
        ReadBuff[i] = Wire.read();
      }

      CompassX = ReadBuff[0] << 8;
      CompassX |= ReadBuff[1];
      CompassY = ReadBuff[4] << 8;
      CompassY |= ReadBuff[5];
      CompassZ = ReadBuff[2] << 8;
      CompassZ |= ReadBuff[3];
    }
