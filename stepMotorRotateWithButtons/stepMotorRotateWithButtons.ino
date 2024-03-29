#define A 2
#define B 3
#define C 4
#define D 5



const int clockwisePin = 8;
const int counterClockwisePin = 7;
int clockwiseButtonState = LOW;
int counterClockwiseButtonState = LOW;

#define NUMBER_OF_STEPS_PER_REV 512

void setup(){
pinMode(A,OUTPUT);
pinMode(B,OUTPUT);
pinMode(C,OUTPUT);
pinMode(D,OUTPUT);

pinMode(clockwisePin, INPUT);
pinMode(counterClockwisePin, INPUT);
}

void write(int a,int b,int c,int d){
digitalWrite(A,a);
digitalWrite(B,b);
digitalWrite(C,c);
digitalWrite(D,d);
}

void onestep(){
write(1,0,0,0);
delay(5);
write(1,1,0,0);
delay(5);
write(0,1,0,0);
delay(5);
write(0,1,1,0);
delay(5);
write(0,0,1,0);
delay(5);
write(0,0,1,1);
delay(5);
write(0,0,0,1);
delay(5);
write(1,0,0,1);
delay(5);
}



void loop(){
  clockwiseButtonState = digitalRead(clockwisePin);
  counterClockwiseButtonState = digitalRead(counterClockwisePin);
  if(clockwiseButtonState == counterClockwiseButtonState){
    // fall through / do nothing
  }else if( clockwiseButtonState == HIGH){
    onestepReverse();
    
  }else if(counterClockwiseButtonState == HIGH){
    onestep();
  }
  
}
