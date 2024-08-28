#include <Arduino.h>
#define LED1 25
#define LED2 27
hw_timer_t *timer = NULL;
volatile int state = 0;
void IRAM_ATTR onTimer()
{
  switch(state)
  {
    case 0:
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2,LOW);
    state = 1;
    timerWrite(timer, 0);
    timerAlarmWrite(timer, 2000000, true);
    break;
    case 1:
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,HIGH);
    state = 0;
    timerWrite(timer, 0);
    timerAlarmWrite(timer, 2000000, true);
    break; 
  }
}

void setup() 
{
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
timer = timerBegin(0,80,true);
timerAlarmWrite(timer, 2000000, true);
timerAttachInterrupt(timer, &onTimer, true);
timerAlarmEnable(timer);
}

void loop() 
{

}

