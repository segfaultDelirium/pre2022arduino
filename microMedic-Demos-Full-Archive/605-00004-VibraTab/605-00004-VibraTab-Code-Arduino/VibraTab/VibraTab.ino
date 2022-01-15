// Vibra Tab connected to analog pin A0
const int filmSensor = A0;  

void setup() {
 Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(filmSensor), DEC);
  delay(300); 
}

