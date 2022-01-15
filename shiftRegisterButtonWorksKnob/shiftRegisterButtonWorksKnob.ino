/*
Using a 74HC595 Shift Register by swistak / misza
*/
int clockPin = 9;
int latchPin = 10;
int dataPin = 11;
byte leds = 0;
int currentLED = 0;


const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

int readPin = A0;

void shift(int chosenLED, byte leds);
//byte counter = 0;
//int intcounter = 0;
int counter = 0;



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

  int knobReading = analogRead(readPin);
  int chosenLED = 8 * (knobReading / 1023.0);
  Serial.println(chosenLED);
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    shift(chosenLED, 0);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  
  
  delay(1);
}


void shift(int chosenLED, byte leds){
  currentLED = chosenLED;
  leds = 0;
  /*
  if (currentLED == 7){
    currentLED = 0;
  }else{
    currentLED++;
  }
  */
  
  bitSet(leds, currentLED);
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
  /*
  TIME LED
  */
  //delay(250);
}
