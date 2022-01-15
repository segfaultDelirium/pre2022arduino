int sense = 4;
int heater = 6;

void setup() {
  Serial.begin(9600);
  pinMode(heater, OUTPUT);
  pinMode(sense, INPUT);
}

void loop() {
  COCycle();
}

void COCycle() {
  digitalWrite(heater, HIGH);     // Turn heater on
  Serial.println("Purge started...");
  for(int i = 60; i > 0; i--) {   // Delay for 60 seconds
    Serial.println(i);
    delay(1000);
  }
  Serial.println("Purge complete...");

  Serial.println("Sensing...");
  analogWrite(heater, 71);        //1.4V PWM

  for(int i = 0; i <= 90; i++) {  // Read for 90 seconds
    Serial.print(i, DEC);
    if(digitalRead(sense) == 1)   // Show alarm if triggered
      Serial.print("  ALARM");
    Serial.println("");
    delay(1000);
  }
  Serial.println("Sense complete...");
}