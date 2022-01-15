/*
Using a 74HC595 Shift Register by swistak / misza
*/
int clockPin = 9;
int latchPin = 10;
int dataPin = 11;
byte leds = 0;
int currentLED = 0;

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  leds = 0;
}

void loop(){
  
  leds = 0;
  
  if (currentLED == 7){
    currentLED = 0;
  }else{
    currentLED++;
  }
  
  bitSet(leds, currentLED);
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
  /*
  TIME LED
  */
  delay(250);
}
