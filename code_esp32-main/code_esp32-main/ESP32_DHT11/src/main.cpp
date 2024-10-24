#include "DHTesp.h"

#define DHTPIN 15     // DHT11 sensor pin
#define DHTTYPE DHT11 // DHT11 sensor type

DHTesp dht;

void setup()
{
  Serial.begin(9600);

  dht.setup(DHTPIN, DHTesp::DHTTYPE); 
}

void loop()
{
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  
  Serial.print(temperature);
  Serial.println("%");
  Serial.print(humidity);
  Serial.println("*C");
  Serial.println();
  delay(1000);
}