/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = A0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

int clockwisePin = 7;
int counterClockwisePin = 8;
int clockwisePinState = LOW;
int counterClockwisePinState = LOW;
int previousVal = 0;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  pinMode(clockwisePin, INPUT);
  pinMode(counterClockwisePin, INPUT);
}

void loop() {

  clockwisePinState = digitalRead(clockwisePin);
  counterClockwisePinState = digitalRead(counterClockwisePin);
  
  //val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  //val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  if(clockwisePinState == counterClockwisePinState){
    // do nothing
  }else if( clockwisePinState == HIGH){
    val = previousVal + 1;
  }else{
    val = previousVal - 1;
  }
  previousVal = val;

  // normalizing val 
  val = (val > 180) ? 180 : val;
  val = (val < 0) ? 0 : val;
  
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(5);                           // waits for the servo to get there
}
