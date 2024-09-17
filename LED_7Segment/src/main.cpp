#include <Arduino.h>
const int button_up = 25;
const int button_down = 14;
int count_index = 0;
byte Pin[] = {5, 4, 32, 21, 27, 18, 23, 22};
const byte count[10] = {
B01000000, //0
B11111001, //1
B00100100, //2
B10110000, //3
B00011001, //4
B10010010, //5
B00000010, //6
B11111000, //7
B00000000, //8
B10010000, //9
};
void LedSegment(byte bit)
{
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(Pin[i], bitRead(bit,i));
  }
}

void IRAM_ATTR up_count_index()
{
if(count_index < 9)
count_index++;
}
void IRAM_ATTR down_count_index()
{
if(count_index > 0 )
count_index--;
}

void setup()
{
for(int i = 0; i < 8; i++)
{
  pinMode(Pin[i], OUTPUT);
}
pinMode(button_up, INPUT_PULLUP);
pinMode(button_down, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(button_up), up_count_index, RISING);
attachInterrupt(digitalPinToInterrupt(button_down), down_count_index, RISING);
}
void loop()
{
  LedSegment(count[count_index]);
  delay(1000);
}