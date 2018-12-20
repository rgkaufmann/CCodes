    #include 
    #include "BMA250.h"
    
    BMA250 accel;
    
    void setup()
    {
      Serial.begin(9600);
      Wire.begin();
      accel.begin(BMA250_range_2g, BMA250_update_time_64ms);
    }
    
    void loop() {
      accel.read();//This function gets new data from the accelerometer
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
      delay(250);
    }
