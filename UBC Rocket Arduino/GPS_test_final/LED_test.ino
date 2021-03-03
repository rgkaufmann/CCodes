#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// LED and check constants
#define LED_RED           2
#define LED_YELLOW        3
#define LED_GREEN         4
#define LANDING_GPS_LONG  -123.253408
#define LANDING_GPS_LAT   49.260657
#define BUFFER            0.0045
#define ALTITUDE_CAP      0

// Instantiations for GPS
TinyGPSPlus gps;
HardwareSerial SerialGPS(1);

// Setup safety boolean
bool wasInBuffer = false;

// Initialization and Setup
void setup() {
  // Laptop Serial Initialization
  Serial.begin(9600);
  Serial.println("Serial port initiated.");
  Serial.println("Serial Txd is on pin: " + String(TX));

  // GPS Serial Initialization
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("Serial Txd is on pin: " + String(TX));
  Serial.println("Serial Rxd is on pin: " + String(RX));

  // Initialize LED pins to output
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_YELLOW, HIGH);
}

void loop() {
  // ----- GPS -----
  // Check if GPS is Ready to Transmit
  while (SerialGPS.available() > 0) {
    Serial.println("GPS is available");
    Serial.println(SerialGPS.read());     // Print Data
    gps.encode(SerialGPS.read());         // Parse Data into GPS Object
  }

  if ((abs(gps.location.lat()-LANDING_GPS_LAT)<BUFFER) and (abs(gps.location.lng()-LANDING_GPS_LONG)<BUFFER) and gps.altitude.meters()>ALTITUDE_CAP)
  {
    digitalWrite(LED_GREEN, HIGH);
    if (not wasInBuffer) wasInBuffer = true;
  }
  else if ((wasInBuffer) and ((abs(gps.location.lat()-LANDING_GPS_LAT)>BUFFER) or (abs(gps.location.lng()-LANDING_GPS_LONG)>BUFFER) or gps.altitude.meters()<ALTITUDE_CAP)) digitalWrite(LED_RED, HIGH);
}
