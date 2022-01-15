/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadAnalogVoltage
*/

int N = 8;
// pin 0 is ground
int digit = 0;

void lightDigits(int num);
void lightLine(int i, int num);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  for(int i = 0; i < N; i++){
    pinMode(i, OUTPUT); 
  }
}

// the loop routine runs over and over again forever:
void loop() {
  
  lightDigits(digit);
  digit += 1;
  if(digit > 9){
    digit = 0;
  }
  delay(500);
  
  
}


void lightDigits(int num){
  for(int i = 1; i < N; i++){
    lightLine(i, num);
  }
}


void lightLine(int i, int num){
  switch(i){
    case 1: if( num == 2) return;
      break;
    case 2: if(num == 1 || num == 4 || num == 7) return;
      break;
    case 3: if(num == 1 || num == 3 || num == 4 || num == 5 || num == 7 || num == 9) return;
      break;
    case 4: if(num == 0 || num == 1) return;
      break;
    case 5: if(num == 1 || num == 2 || num == 3) return;
      break;
    case 6: if(num == 1 || num == 4) return;
      break;
    case 7: if(num == 5 || num == 6) return;
      break;
  }
  digitalWrite(i, HIGH);
}
