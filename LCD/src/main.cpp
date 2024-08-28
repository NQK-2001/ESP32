#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD (0x27, 16,2);
byte icon[] = {B01110, B10001, B01110, B00100, B11111, B00100, B01010, B10001};
void setup()
{
Wire.begin(21,22);
LCD.init();
LCD.clear();
LCD.backlight();
LCD.createChar(0,icon);
LCD.setCursor(0,0);
LCD.write(0);
LCD.setCursor(2,0);
LCD.print("Quoc Kiet");
LCD.setCursor(0,1);
LCD.print("HCMUT");
LCD.setCursor(6,1);
LCD.print("Project");
}
void loop()
{
LCD.display();
delay(1000);
LCD.noDisplay();
delay(500);

}