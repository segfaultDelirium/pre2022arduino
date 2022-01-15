/*
Using a 74HC595 Shift Register by swistak / misza
*/
int clockPin = 9;
int latchPin = 10;
int dataPin = 11;
byte leds = 0;
int currentLED = 0;


const int buttonPin = 2;     // the number of the pushbutton pin
const int counterButtonPin = 4;    // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

int readPin = A0;

void shift(int chosenLED, byte leds);
int readCounterFromButton(int buttonPin, int ledPin = 13, int maxCounter = 7);

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  pinMode(readPin, INPUT);
  Serial.begin(9600);

  
  leds = 0;
}

void loop(){
  byte counter = readCounterFromButton(counterButtonPin);
  //Serial.println(counter);
  
  int knobReading = analogRead(readPin);
  int chosenLED = 8 * (knobReading / 1023.0);
  //Serial.println(chosenLED);
  
  // read the state of the pushbutton value:
  //buttonState = digitalRead(buttonPin);
  buttonState = HIGH;

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    shift(chosenLED, counter);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  delay(1);
}


void shift(int chosenLED, byte leds){
  currentLED = chosenLED;
  
  //leds = 0;
  
  /*
  if (currentLED == 7){
    currentLED = 0;
  }else{
    currentLED++;
  }
  */

  
  /*
  long unsigned int chosenDiode = 0;
  if(leds == 0){
    chosenDiode = 1; 
  }else if(leds == 1){
    chosenDiode = 2;    
  }
  else{
    chosenDiode = pow(2, leds) + 1;
  }
  */
  unsigned long int chosenDiode = 0;
  for(int i = 0; i < pow(2,8); i++){
    chosenDiode = i;
    Serial.println(chosenDiode);
    //bitSet(chosenDiode, currentLED);
    
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, chosenDiode);
    digitalWrite(latchPin, HIGH);
    /*
    TIME LED
    */
    delay(250);
  }
  
  
}



int readCounterFromButton(int buttonPin, int ledPin = 13, int maxCounter = 7){
  static volatile int counter = 0;
  // the following variables are unsigned longs because the time, measured in
  // milliseconds, will quickly become a bigger number than can be stored in an int.
  static unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
  static unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
  static int buttonState;             // the current reading from the input pin
  static int lastButtonState = LOW;   // the previous reading from the input pin
  static int ledState = HIGH;         // the current state of the output pin
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
        counter++;
      }
    }
  }
  // set the LED:
  //digitalWrite(ledPin, ledState);
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  // to get reading from 0 to maxCounter
  if(counter > maxCounter){
    counter = 0;
  }
  return counter;
}
