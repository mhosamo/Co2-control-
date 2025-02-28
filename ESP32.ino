#include <Wire.h>
#include <TFT_eSPI.h>
#include "SparkFun_SCD30_Arduino_Library.h"


#define TFT_LED_PIN 4 // TFT LED pin
#define TFT_DC_PIN 27  // TFT DC pin
#define TFT_CS_PIN 5   // TFT CS pin
#define SDA_PIN 43     // SDA pin for I2C communication
#define SCL_PIN 44     // SCL pin for I2C communication
#define SCD30_LED_PIN 23 // SCD30 LED pin
#define SCD30_WARMUP_TIME 10 // Warm-up time for the SCD30 sensor in seconds


TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT); // Initialize TFT display
SCD30 airSensor; // Initialize SCD30 sensor


void setup() {
  pinMode(TFT_LED_PIN, OUTPUT);
  digitalWrite(TFT_LED_PIN, HIGH); // Turn on TFT LED
  Wire.begin(SDA_PIN, SCL_PIN); // Initialize I2C communication
  tft.init();
  tft.setRotation(3); // Set display rotation
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.println("SCD30 Sensor Test");
  if (airSensor.begin() == false) {
    tft.println("Could not find SCD30 sensor");
    while (1);
  } else {
    tft.println("SCD30 sensor detected");
    delay(SCD30_WARMUP_TIME * 1000); // Wait for SCD30 to warm up
  }
}


void loop() {
  if (airSensor.dataAvailable()) {
    float co2 = airSensor.getCO2(); // Read CO2 concentration from sensor
    float temperature = airSensor.getTemperature(); // Read temperature from sensor
    float humidity = airSensor.getHumidity(); // Read humidity from sensor
    tft.fillScreen(TFT_BLACK); // Clear screen
    tft.setCursor(0, 0);
    tft.print("CO2: ");
    if (co2 < 425) {
      tft.setTextColor(TFT_GREEN, TFT_BLACK);
    } else if (co2 < 1180) {
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    } else {
      tft.setTextColor(TFT_RED, TFT_BLACK);
    }
    tft.print(co2);
    tft.print(" ppm");
    tft.setCursor(0, 30);
    tft.print("Temperature: ");
    tft.print(temperature, 1);
    tft.print(" C");
    tft.setCursor(0, 60);
    tft.print("Humidity: ");
    tft.print(humidity, 1);
    tft.print(" %");
    digitalWrite(SCD30_LED_PIN, HIGH); // Turn on SCD30 LED
    delay(500);
    digitalWrite(SCD30_LED_PIN, LOW); // Turn off SCD30 LED
    delay(500);
  }
}


