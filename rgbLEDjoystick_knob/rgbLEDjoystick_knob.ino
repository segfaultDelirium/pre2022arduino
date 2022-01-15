/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadAnalogVoltage
*/

int redLED = 9;           // the PWM pin the LED is attached to
int greenLED = 10;
int blueLED = 11;

int gBrightness = 0;
int bBrightness = 0;

int sensorToVoltage(int reading);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
}

// the loop routine runs over and over again forever:
void loop() {
  int knobReading = analogRead(A0);
  int rBrightness = knobReading * ( 255.0 / 1023.0);
  analogWrite(redLED, rBrightness);
  

  int xVoltage = sensorToVoltage(analogRead(A1));
  Serial.print(xVoltage);
  if(xVoltage > 4.8 && gBrightness < 255){
    gBrightness++;
  }else if(xVoltage < 0.2 && gBrightness > 0){
    gBrightness--;
  }
  analogWrite(greenLED, gBrightness);

  int yVoltage = sensorToVoltage(analogRead(A2));
  Serial.print(yVoltage);
  if(yVoltage > 4.8 && bBrightness < 255){
    bBrightness++;
  }else if(yVoltage < 0.2 && bBrightness > 0){
    bBrightness--;
  }
  analogWrite(blueLED, bBrightness);
  


  

  delay(1);
}


int sensorToVoltage(int reading){
  return reading * (5.0 / 1023.0);
}
