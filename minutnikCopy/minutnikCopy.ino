/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

const int buttonPin = 7;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

int beepPin = 8;
int beepState = LOW;

// used with timer
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)
void startTimer(int timeleft);

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void lcdPrintTime();

void clearLCD(int row = 0);

#define knobPin A0

void setup() {
  Serial.begin(9600);
 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");

  pinMode(knobPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(beepPin, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void loop() {
  
  int knobTime = analogRead(knobPin) * (10.0 * 60.0 / 1023.0);
  int minutes = knobTime / 60;
  int seconds = knobTime % 60;
  Serial.println(knobTime);
  lcd.setCursor(0, 0);
  lcd.print("timer:");
  lcd.print(minutes);
  lcd.print("min. ");
  if(seconds < 10) lcd.print("0");
  lcd.print(seconds);
  lcd.print("s.");

  lcd.setCursor(0,1);
  lcd.print("confirm?");

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    startTimer(knobTime);
    delay(200);
  }
  
  
  
  delay(20);
}


void clearLCD(int row = 0){
  lcd.setCursor(0, row);
  lcd.print("                ");
}


void startTimer(int timeleft){
  clearLCD(0);
  clearLCD(1);
  delay(100);
  while(timeleft >= 0){
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      int minutes = timeleft / 60;
      int seconds = timeleft % 60;
      lcd.setCursor(0,0);
      lcd.print("time left:");
      lcd.setCursor(0,1);
      lcd.print(minutes);
      lcd.print("min. ");
      if(seconds < 10) lcd.print(0);
      lcd.print(seconds);
      lcd.print("s.");
      timeleft -= 1;
    }
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      delay(200);
      clearLCD(0);
      clearLCD(1);
      return;
    }
  }
  buttonState = digitalRead(buttonPin);
  while(buttonState != HIGH){
    buttonState = digitalRead(buttonPin);
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval/2) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
  
      // if the LED is off turn it on and vice-versa:
      if (beepState == LOW) {
        beepState = HIGH;
      } else {
        beepState = LOW;
      }
  
      // set the LED with the ledState of the variable:
      digitalWrite(beepPin, beepState);
    }
  }
  digitalWrite(beepPin, LOW);
  clearLCD(0);
  clearLCD(1);
}
