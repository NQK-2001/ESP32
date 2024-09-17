#include <Arduino.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
Serial.begin(9600);
Serial.println("DHTxx Index");
dht.begin();
}

void loop()
{
delay(2000);
float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);

if(isnan(h)||isnan(t)||isnan(f))
{
  Serial.println("Failed no read from DHT sensor");
  return;
}
float hif = dht.computeHeatIndex(f,h);
float hic = dht.computeHeatIndex(f,h,false);
Serial.print("Humidity: ");
Serial.print(h);
Serial.print("% Temperature: ");
Serial.print(t);
Serial.print("C");
Serial.print(f);
Serial.print("F Heat index: ");
Serial.print(hic);
Serial.print("C");
Serial.print(hif);
Serial.println("F");
}