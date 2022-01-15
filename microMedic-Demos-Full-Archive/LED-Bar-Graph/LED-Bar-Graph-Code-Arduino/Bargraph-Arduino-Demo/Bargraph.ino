// Array of pins attached to LEDs
int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int ledCount = 10;  // Number of LEDs

void setup() {
  Serial.begin(9600);
  // Make all LED pins outputs
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT); 
  }
}

void loop() {
  // Light up one LED going across at a time
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    digitalWrite(ledPins[thisLed], HIGH);  // Turn on LED
    delay(250);     // Wait 1/4 sec

    for (int i = ledCount-1; i >= 0; i--) {         // Display in Serial
      Serial.print(digitalRead(ledPins[i]));
    }
    Serial.println("");                    // New line
    digitalWrite(ledPins[thisLed], LOW);   // Turn off ED 
  }
}
