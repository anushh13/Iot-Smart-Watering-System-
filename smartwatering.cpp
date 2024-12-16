#include <DHT.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

#define moistureSensorPin A0
#define relayPin 5

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Read temperature and humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Read soil moisture
  int moistureValue = analogRead(moistureSensorPin);
  float moisturePercentage = map(moistureValue, 0, 1023, 0, 100);

  // Check conditions and control pump
  if (moisturePercentage < 50 || t > 30 || h < 40) {
    digitalWrite(relayPin, HIGH); // Turn on pump
    Serial.println("Pump ON");
  } else {
    digitalWrite(relayPin, LOW); // Turn off pump
    Serial.println("Pump OFF");
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C \t");
  Serial.print("Moisture: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  delay(2000);
}