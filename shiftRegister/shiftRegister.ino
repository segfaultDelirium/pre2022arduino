/*
Using a 74HC595 Shift Register by swistak / misza
*/
int clockPin = 9;
int latchPin = 10;
int dataPin = 11;
byte leds = 0;
int currentLED = 0;

int buttonPin = 2;
int buttonState = LOW;
int previousButtonState = LOW;

bool shiftFlag = false;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup()
{
pinMode(latchPin, OUTPUT);
pinMode(dataPin, OUTPUT);
pinMode(clockPin, OUTPUT);

pinMode(buttonPin, INPUT);

leds = 0;

Serial.begin(9600);
}

void loop(){
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  if(reading != previousButtonState){
    lastDebounceTime = millis();
  }
  
  if( (millis() - lastDebounceTime) > debounceDelay){
    if(reading != buttonState){
      buttonState = reading;

      if(buttonState == HIGH){
        shiftFlag = true;
      }
    }
  }

  if(shiftFlag){
    leds = 0;
    
    if (currentLED == 7)
    {
    currentLED = 0;
    }
    else
    {
    currentLED++;
    }
    
    
    Serial.println(1000 * (log(leds) / log(2)) );
    bitSet(leds, currentLED);
    
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, leds);
    digitalWrite(latchPin, HIGH);
    //currentLED++;
    //delay(250);
  }

  
  Serial.println(1000 * (log(leds) / log(2)) );
  delay(1);
}
