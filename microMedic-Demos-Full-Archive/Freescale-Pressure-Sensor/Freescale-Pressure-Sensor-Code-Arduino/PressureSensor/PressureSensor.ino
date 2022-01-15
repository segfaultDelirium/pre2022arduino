// Pin 1 (notch) - Analog output
// Pin 2 - Gnd
// Pin 3 - 5V


int sensorPin = A0;    // Select input pin for the potentiometer
int sensorValue = 0;   // Variable stores value coming from the sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);  // Read sensor
  Serial.println(sensorValue, DEC);     // Display result
  delay(400); 	    // Wait 400 milliseconds
}
