#include <Arduino.h>
#define LED 33
#define BUTTON 4

void setup() 
{
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED,LOW);
}

void loop() 
{
  if(digitalRead(BUTTON) == HIGH )
  {
    Serial.println("LED TURN ON");
    digitalWrite(LED, HIGH);
  }
  else  
  {
    Serial.println("LED TURN OFF");
    digitalWrite(LED, LOW);
  }
}


