#include <DallasTemperature.h>
#include <OneWire.h>


#define PH_SENSOR_PIN A0       // Analog pin for pH sensor
#define TEMP_SENSOR_PIN 2      // Digital pin for DS18B20 temperature sensor
#define HEATING_PIN D1         // GPIO pin for heating system
#define COOLING_PIN D2         // GPIO pin for cooling system
#define BUFFER_PIN D3          // GPIO pin for buffer addition


OneWire oneWire(TEMP_SENSOR_PIN);
DallasTemperature sensors(&oneWire);


float targetTemp = 37.0; // Set target temperature in °C and ph this is for just for amalyse
float targetPH = 7.0;    

void setup() {
  Serial.begin(115200);
  sensors.begin();

  pinMode(HEATING_PIN, OUTPUT);
  pinMode(COOLING_PIN, OUTPUT);
  pinMode(BUFFER_PIN, OUTPUT);

  digitalWrite(HEATING_PIN, LOW);
  digitalWrite(COOLING_PIN, LOW);
  digitalWrite(BUFFER_PIN, LOW);
}

void loop() {
  sensors.requestTemperatures();
  float currentTemp = sensors.getTempCByIndex(0);
  Serial.print("Current Temperature: ");
  Serial.println(currentTemp);


  if (currentTemp < targetTemp) {
    digitalWrite(HEATING_PIN, HIGH); // Turn on heating
    digitalWrite(COOLING_PIN, LOW);  // Turn off cooling
  } else if (currentTemp > targetTemp) {
    digitalWrite(HEATING_PIN, LOW);  // Turn off heating
    digitalWrite(COOLING_PIN, HIGH); // Turn on cooling
  } else {
    digitalWrite(HEATING_PIN, LOW);
    digitalWrite(COOLING_PIN, LOW);
  }


  int phValue = analogRead(PH_SENSOR_PIN);
  float currentPH = map(phValue, 0, 1023, 0, 14); // Map sensor value to 0-14 pH scale
  Serial.print("Current pH: ");
  Serial.println(currentPH);


  if (currentPH < targetPH) {
    digitalWrite(BUFFER_PIN, HIGH); // Add basic buffer
  } else if (currentPH > targetPH) {
    digitalWrite(BUFFER_PIN, LOW);  // Add acidic buffer
  } else {
    digitalWrite(BUFFER_PIN, LOW);  // No buffer needed
  }

  delay(2000);
}