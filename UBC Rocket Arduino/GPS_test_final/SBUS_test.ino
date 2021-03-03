// Package Inclusion
#include <Wire.h>
#include <HardwareSerial.h>
#include <SBUS.h>

// Test LED
#define LED_BUILTIN 2

// Instantiations for Flight Controller
HardwareSerial SerialFC(1);
SBUS MatekFC(SerialFC);
uint16_t channels[16] = {1000, 1050, 1100, 1150, 1200, 1250, 1300, 1350, 1400, 1450, 1500, 1550, 1600, 1650, 1700, 1750};
bool failSafe;
bool lostFrame;
  
// Initialization and Setup
void setup() {
  // Laptop Serial Initialization
  Serial.begin(9600);
  Serial.println("Serial port initiated.");
  Serial.println("Serial Txd is on pin: " + String(TX));
  randomSeed(analogRead(0));

  // Initialize LED pins to output
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  // Flight Controller Initialization
  MatekFC.begin();
}

// Infinite Loop for Running/Sampling
void loop() {
  // Blinking LED for test
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);

  // Check current SBUS data
  if(MatekFC.read(&channels[0], &failSafe, &lostFrame)) for(int i = 0; i<=15; i++) Serial.printf("Channel number %d set to be %d.\n", i, channels[i]);

  // Randomize Channels
  for(int i = 0; i<=15; i++) channels[i]=random(1000, 2000);

  // Parse Data to SBUS
  for(int i = 0; i<=15; i++) Serial.printf("Channel number %d set to be %d.\n", i, channels[i]);
  Serial.printf("Pointer test: %d.\n", &channels[0]);
  MatekFC.write(&channels[0]);

  // Wait before next parsing
  delay(1000);
}
