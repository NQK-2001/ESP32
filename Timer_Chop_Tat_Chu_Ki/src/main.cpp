#include <Arduino.h>
#define LED 14
#define BUTTON 4
#define time 5
unsigned long now_time = millis();
unsigned long last_time = 0;
boolean start_time = false;
boolean press = false;

void IRAM_ATTR pressedButton()
{
Serial.println("Xay ra ngat");
digitalWrite(LED,HIGH);
start_time = true;
last_time = millis();
}
void setup()
{
Serial.begin(9600);
pinMode(LED, OUTPUT);
pinMode(BUTTON, INPUT);
//digitalWrite(LED, LOW);
attachInterrupt(digitalPinToInterrupt(BUTTON), pressedButton, RISING);
}

void loop()
{
now_time = millis();
if(digitalRead(BUTTON == HIGH) && press == false )
{
Serial.println("Chuan bi nhan nut");
press = true;
}
if(start_time && now_time - last_time > time*1000)
{
  Serial.println("Interrupt stop");
  digitalWrite(LED, LOW);
  start_time = false;
  press = false;
}
}