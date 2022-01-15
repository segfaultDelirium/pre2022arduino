#define led 2
#define btnPin 5

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(btnPin, INPUT);
}

void loop() {
  int btn = digitalRead(btnPin);

  if(btn){
     digitalWrite(led, HIGH);
     
  }else{
    digitalWrite(led, LOW);
  }
  delay(10);
}
