#include <Arduino.h>
#include <LiquidCrystal.h>
#include<Wire.h>
void setup()
{
  Serial.begin(115200);
  Serial.println("Hi HCMUT...");
}

void loop()
{
  if(Serial.available() > 0)
  {
    char data = Serial.read();
    Serial.println("Data from ESP32:" + data);
  }
}