#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHT_PIN 23
#define DHTTYPE DHT11
DHT dht11(DHT_PIN, DHT11);

void setup()
{
  lcd.init();
  lcd.backlight();
  dht11.begin();
}

void loop()
{
  float Humi = dht11.readHumidity();
  float Temp = dht11.readTemperature();
  lcd.clear();
  if(isnan(Humi) || isnan(Temp))
  {
    lcd.setCursor(0,0);
    lcd.print("Failed...");
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(Humi);
    lcd.print(" %");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(Temp);
    lcd.print(" C");
  }
  delay(2000);
}