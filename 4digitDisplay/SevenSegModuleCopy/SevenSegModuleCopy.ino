
#include <Multiplex7Seg.h>

int voltsToMilivolts2(float voltage);

byte digitPins[] = {9, 10, 11, 12};         // LSB to MSB
byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8}; // Segment a to g
unsigned int adc;

void setup() {
  Multiplex7Seg::set(1, 4, digitPins, segmentPins);   // Initialize 
  // See the example in Multiplex7Seg library for initialization parameters
  Serial.begin(9600);
}

void loop() { 
  float voltage = analogRead(A0) * ( 5.0 / 1023.0);
  int milivolts = voltsToMilivolts2(voltage);
  Serial.println(milivolts);
  
  Multiplex7Seg::loadValue(milivolts);  // Display incrementing value
  delay(100);
}

int voltsToMilivolts2(float voltage){
  return int(voltage * 1000);
}
