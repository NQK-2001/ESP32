#include <Arduino.h>
#define LED 25

int channel = 0;
int freq = 5000;
int resolution = 8;
void setup()
{
//Serial.begin(9600);
pinMode(LED,OUTPUT);
ledcSetup(channel, freq, resolution);
ledcAttachPin(LED, channel);
}

void loop()
{
for(int i= 0; i<=255; i++)
{
  ledcWrite(channel, i);
  delay(20);
}
for (int i=255; i>=0; i--)
{
  ledcWrite(channel, i);
  delay(20);
}

}