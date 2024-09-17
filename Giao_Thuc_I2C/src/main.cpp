#include <Arduino.h>
#include <Wire.h>

void setup()
{
Wire.begin();
Serial.begin(9600);
Serial.println("I2C scanner");
}

void loop()
{
byte error, address;
int nDevices;
Serial.println("Scanning...");
nDevices = 0;
for(address = 1; address < 127; address++)
{
  Wire.beginTransmission(address);
  error = Wire.endTransmission();
  if (error == 0)
  {
    Serial.println("I2C found that address at 0x");
    if(address < 16)
    {
      Serial.print("0");
    }
    Serial.println(address, HEX);
    nDevices++;
  }
  else if (error == 4)
  {
    Serial.println("Unknown error at address 0x");
  if(address<16)
  {
    Serial.print("0");
  }
  Serial.println(address, HEX);
  }
}

if(nDevices == 0)
{
  Serial.println("I2C not found address at 0x");
}
else
{
  Serial.println("Done");
}
delay(500);
}