

int ledPIN = 13;
int interval = 15;

void setup(){
  pinMode(ledPIN, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(ledPIN, HIGH);
  delay(interval);
  digitalWrite(ledPIN, LOW);
  delay(interval);
  
  Serial.println(  analogRead(A0) * (5000.0 / 1023.0) );
}
