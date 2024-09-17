#include <Arduino.h>
#include <WiFi.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const char *ssid = "Quoc Kiet_5G";
const char *password = "0984166810@";
WiFiUDP ntpUDP;
NTPClient timeclient(ntpUDP, "asia.pool.ntp.org", 25200, 60000);
char Time[] = "TIME:00:00:00";
char Date[] = "DATE:00:00:00";
byte last_second, second_, minute_, hour_, day_, month_;
int year_;

void setup()
{
lcd.init();
lcd.backlight();
Serial.begin(9600);
lcd.setCursor(0,0);
lcd.print(Time);
lcd.setCursor(0,1);
lcd.print(Date);
WiFi.begin(ssid, password);
Serial.println("Connecting...");
while(WiFi.status() != WL_CONNECTED)
{
  delay(500);
  Serial.print(".");
}
Serial.println("Connected");
timeclient.begin();
}
void loop()
{
timeclient.update();
unsigned long unix_epoch = timeclient.getEpochTime();
second_ = second(unix_epoch);
if(last_second != second_)
{
minute_ = minute(unix_epoch);
hour_ = hour(unix_epoch);
day_ = day(unix_epoch);
month_ = month(unix_epoch); 
year_ = year(unix_epoch);

Time[12] = second_ % 10 + 48;
Time[11] = second_ % 10 + 48;
Time[9] = minute_ % 10 + 48;
Time[8] = minute_ % 10 + 48;
Time[6] = hour_ % 10 + 48;
Time[5] = hour_ % 10 + 48;

Date[12] = (year_ / 10) % 10 + 48;
Date[11] = (year_ % 10) % 10 + 48;
Date[9] = (month_ / 10) + 48;
Date[8] = (month_ / 10) + 48;
Date[6] = (day_ / 10) + 48;
Date[5] = (day_ / 10) + 48;

Serial.println(Time);
Serial.println(Date);

lcd.setCursor(0,0);
lcd.print(Time);
lcd.setCursor(0,1);
lcd.print(Date);
last_second = second_;
}
delay(1000);
}