#include <Wire.h>
#include "Adafruit_SHT31.h"
#include <WiFi.h>
#include <FirebaseESP32.h>

// Replace with your WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  if (!sht31.begin(0x44)) {   // Set to your sensor's I2C address, either 0x44 or 0x45
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }
}

void loop() {
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  // Convert Celsius to Fahrenheit
  float tFahrenheit = (t * 9.0 / 5.0) + 32;

  // Use round() to convert to the nearest whole number
  int roundedTempF = round(tFahrenheit);
  int roundedHum = round(h);

  if (!isnan(roundedTempF)) {  // check if 'is not a number'
    Serial.print("Temp *F = "); Serial.println(roundedTempF);
  } else { 
    Serial.println("Failed to read temperature");
  }

  if (!isnan(roundedHum)) {  // check if 'is not a number'
    Serial.print("Hum. % = "); Serial.println(roundedHum);
  } else { 
    Serial.println("Failed to read humidity");
  }

  delay(60000); // Wait for a second between readings
}