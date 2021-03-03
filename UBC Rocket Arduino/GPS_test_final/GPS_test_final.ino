// Package Inclusion
#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <SBUS.h>

// Test LED
#define LED_BUILTIN 2

// Instantiations for GPS
TinyGPSPlus gps;
HardwareSerial SerialGPS(1);

// Instantiations for Flight Controller
HardwareSerial SerialFC(2);
SBUS MatekFC(SerialFC);
uint16_t channels[16] = {0, 10, 200, 500, 320, 700, 1000, 1302, 403, 905, 201, 634, 1520, 1942, 1652, 1313};

// Initialization and Setup
void setup() {
  // Laptop Serial Initialization
  Serial.begin(9600);
  Serial.println("Serial port initiated.");
  Serial.println("Serial Txd is on pin: " + String(TX));

  // Initialize LED pins to output
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  // GPS Serial Initialization
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("Serial Txd is on pin: " + String(TX));
  Serial.println("Serial Rxd is on pin: " + String(RX));

  // Flight Controller Initialization
  MatekFC.begin();
  // &channels[0] = 
  // bool failSafe;
  // bool lostFrame;

  // GPS Initial Test (Not Needed)
  delay(10000);
  gps.encode(SerialGPS.read());
  Serial.println(gps.location.lat());
  delay(1000);
  gps.encode(SerialGPS.read());
  Serial.println(gps.location.lat());
}

// Infinite Loop for Running Code
void loop() {
  // ----- Blinking LED for test -----
  digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on
  delay(1000);                       
  digitalWrite(LED_BUILTIN, LOW);    // Turn the LED off
  delay(2000);                       

  // ----- GPS -----
  // Check if GPS is Ready to Transmit
  while (SerialGPS.available() > 0) {
    Serial.println("GPS is available");
    Serial.println(SerialGPS.read());     // Print Data
    gps.encode(SerialGPS.read());         // Parse Data into GPS Object
  }

  // Display Number of Satellites on Laptop Serial Port
  Serial.println("----- GPS -----");
  Serial.print("GPS is encoded with ");
  Serial.print(gps.satellites.value());
  Serial.println(" satellites");

  // Display Time on Laptop Serial Port
  Serial.print("time ");
  Serial.print(gps.time.hour());Serial.print(":"); // Hour (0-23) (u8)
  Serial.print(gps.time.minute());Serial.print(":"); // Minute (0-59) (u8)
  Serial.print(gps.time.second());Serial.print(":"); // Second (0-59) (u8)
  Serial.println(gps.time.centisecond());

  // Display Coordinates on Laptop Serial Port
  Serial.print("coordinates "); 
  Serial.print("lat : ");Serial.print(gps.location.lat());
  Serial.print(", lon : ");Serial.print(gps.location.lng());
  Serial.print(", alt : ");Serial.println(gps.altitude.meters());

  // Parse Data to SBUS
  MatekFC.write(&channels[0]);

  // Wait Until Next Data Acquisition
  delay(1000);
}
