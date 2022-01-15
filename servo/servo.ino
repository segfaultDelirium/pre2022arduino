 #include <Servo.h>

 Servo servo;
 const int servoPin = 8;

 int rotateFull = 90;
 int rotateZero = 0;
 int rotate = 0;

void setup() {
  servo.attach(servoPin);
  servo.write(rotateZero);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}


void loop() {

  unsigned long voltage = analogRead(A0) * (5.0 / 1024.0);
  Serial.println( voltage );
  rotate = voltage * (90.0 / 5.0);
  servo.write(rotate);
  delay(1);
}
