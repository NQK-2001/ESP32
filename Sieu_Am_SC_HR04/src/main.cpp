#include <Arduino.h>
long duration;
const int Trig = 21;
const int Echo = 4;
//  cm/microsecond
#define SOUND_SPEED 0.034
#define CM_to_INCH 0.393701
float distanceCM;
float distanceINCH;

void setup() 
{
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
}

void loop() 
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  
  duration = pulseIn(Echo, HIGH);
  distanceCM = duration * SOUND_SPEED / 2;
  distanceINCH = distanceCM * CM_to_INCH;

  Serial.print("Distance (CM): ");
  Serial.println(distanceCM);
  Serial.print("Distance (inch): ");
  Serial.println(distanceINCH);  

}

