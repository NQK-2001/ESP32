#include <Arduino.h>
#define TIME_TO_SLEEP_uS 5*1000000

RTC_DATA_ATTR int bootCount = 0;

void print_wakeup_cause_by()
{
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0:
    Serial.println("Makeup caused by external signal using RTC_I0");
    break;
    case ESP_SLEEP_WAKEUP_EXT1:
    Serial.println("Makeup caused by external signal using RTC_CNTL");
    break;
    case ESP_SLEEP_WAKEUP_TIMER:
    Serial.println("Makeup caused by timer");
    break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
    Serial.println("Makeup caused by touchpad");
    break;
    case ESP_SLEEP_WAKEUP_ULP:
    Serial.println("Makeup caused by ULP program");
    break;
    default:
    Serial.printf("Makeup was not caused by deep sleep: %d\n", wakeup_reason);
    break;
  }
}

void setup() 
{
 Serial.begin(9600);
 delay(1000);
 ++bootCount;
 Serial.println("Boot number: " + String(bootCount));
 print_wakeup_cause_by();

 esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP_uS);
 Serial.println("Setup ESP32 to sleep for every" + String (TIME_TO_SLEEP_uS / 1000000) + "Seconds");
 Serial.println("Going to sleep now");
 delay(1000);
 Serial.flush();
 esp_deep_sleep_start();
 Serial.println("This will never be printed");
}

void loop() 
{
  
}
