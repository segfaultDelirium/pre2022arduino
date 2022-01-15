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

// RTC start header

#include <stdio.h>
#include <virtuabotixRTC.h>   

// Creation of the Real Time Clock Object
virtuabotixRTC myRTC(6, 7, 8);
// RTC end header

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void lcdPrintTime();

// button variables
const int buttonPin = 9; 
int buttonState = LOW;
int previousButtonState = LOW;
unsigned counter = 0;

// no delay variables
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;

void setup() {
  Serial.begin(9600);
// Set the current date, and time in the following format:
// seconds, minutes, hours, day of the week, day of the month, month, year
  //myRTC.setDS1302Time(00, 38, 8, 2, 13, 7, 2021);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");

  pinMode(buttonPin, INPUT);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcdPrintTime();
}



void lcdPrintTime() {
  

  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    if(buttonState != previousButtonState){
      counter++;
      previousButtonState = HIGH;
    }
  }else{
    previousButtonState = LOW;
  }
  delay(1);

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval){
    previousMillis = currentMillis;
    
    myRTC.updateTime();                                                                                    //| 
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    char buf[50] = "";
    snprintf(buf, 50, "%02d.%02d.%02d", myRTC.dayofmonth, myRTC.month, myRTC.year);
    lcd.print(buf);
    lcd.setCursor(0, 1);
    snprintf(buf, 50, "%02d:%02d:%02d",  myRTC.hours, myRTC.minutes, myRTC.seconds);
    lcd.print(buf);
    
    snprintf(buf, 50, " %5u", counter);
    lcd.print(buf);
  } 
  
}
