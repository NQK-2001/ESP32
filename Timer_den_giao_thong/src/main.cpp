#include <Arduino.h>
#define R 25
#define Y 27
#define G 13
hw_timer_t *timer = NULL;
volatile int state = 0;

void IRAM_ATTR onTimer()
{
switch(state)
{
case 0:
digitalWrite(R, HIGH);
digitalWrite(Y, LOW);
digitalWrite(G, LOW);
state = 1;
timerWrite(timer, 0);
timerAlarmWrite(timer, 5000000, true);
break;
case 1:
digitalWrite(R, LOW);
digitalWrite(Y, HIGH);
digitalWrite(G, LOW);
state = 2;
timerWrite(timer, 0);
timerAlarmWrite(timer, 2000000, true);
break;
case 2:
digitalWrite(R, LOW);
digitalWrite(Y, LOW);
digitalWrite(G, HIGH);
state = 0;
timerWrite(timer, 0);
timerAlarmWrite(timer, 5000000, true);
break;
}
}

void setup()
{
Serial.begin(9600);
pinMode(R, OUTPUT);
pinMode(Y, OUTPUT);
pinMode(G, OUTPUT);
timer = timerBegin(0, 80, true);
timerAlarmWrite(timer, 5000000, true);
timerAttachInterrupt(timer, &onTimer, true);
timerAlarmEnable(timer);
}

void loop()
{

}