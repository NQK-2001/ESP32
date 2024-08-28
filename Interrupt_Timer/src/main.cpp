#include <Arduino.h>
#define LED 26
#define PIR_Sensor 27
#define TIMEOUT 5
unsigned long last_time = 0;
unsigned long now_time = false;
boolean startTime = false;
boolean detect_motion = false;
void IRAM_ATTR detectCallback()
{
digitalWrite(LED, HIGH);
startTime = true;
last_time = millis();
}
void setup()
{
Serial.begin(9600);
digitalWrite(LED, LOW);
pinMode(PIR_Sensor, INPUT_PULLUP);
pinMode(LED, OUTPUT);
attachInterrupt(digitalPinToInterrupt(PIR_Sensor), detectCallback, RISING);
}

void loop()
{
now_time = millis();
if(digitalRead(PIR_Sensor == HIGH) && (detect_motion = false) )
{
  Serial.println("Detect motion");
  detect_motion = true;
}
if(startTime && (now_time - last_time) > TIMEOUT*1000)
{
Serial.println("Stop motion.....");
digitalWrite(LED, LOW);
startTime = false;
detect_motion = false;
}
}