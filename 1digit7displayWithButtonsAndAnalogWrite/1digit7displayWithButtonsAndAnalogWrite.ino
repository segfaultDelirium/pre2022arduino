#include "SevSeg.h"
SevSeg sevseg; 

int num = 0;
const int upButtonPin = 10;
const int downButtonPin = 12;
int upButtonState = LOW;
int downButtonState = LOW;
const int maxNum = 9;
const int minNum = 0;

const int diodePin = 11;

void setup(){
    byte numDigits = 1;
    byte digitPins[] = {};
    byte segmentPins[] = {6, 5, 2, 3, 4, 7, 8, 9};
    bool resistorsOnSegments = true;

    byte hardwareConfig = COMMON_CATHODE; 
    sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);

    pinMode(upButtonPin, INPUT);
    pinMode(downButtonPin, INPUT);
    pinMode(diodePin, OUTPUT);
    
}

void loop(){
  /*
    for(int i = 0; i < 10; i++){
        sevseg.setNumber(i, i%2);
        delay(1000);
        
        }
        */
  upButtonState = digitalRead(upButtonPin);
  downButtonState = digitalRead(downButtonPin);
  if(downButtonState == HIGH){
    num--;
  }
  if(upButtonState == HIGH){
    num++;
  }
  if(num < 0){
    num = 0;
  }
  if(num > 9){
    num = 9;
  }
  analogWrite(diodePin, 255 * (num / 9.0) );
  sevseg.setNumber(num);
  sevseg.refreshDisplay(); 
  delay(200);
}
