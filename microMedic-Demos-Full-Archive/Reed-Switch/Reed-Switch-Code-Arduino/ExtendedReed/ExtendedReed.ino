// Reed switch repetition counter

int sense0 = 2;
int sense1 = 3;
int counter0 = 0;
int counter1 = 0;
long lastDebounce0 = 0;
long lastDebounce1 = 0;
long debounceDelay = 500;	// Ignore bounces under 1/2 second

void setup() {
  Serial.begin(9600);
  pinMode(sense0, INPUT);
  digitalWrite(sense0, HIGH);
  pinMode(sense1, INPUT);
  digitalWrite(sense1, HIGH);
  attachInterrupt(0, trigger0, FALLING);
  attachInterrupt(1, trigger1, FALLING);
  Serial.println("Repetition counter");
  Serial.print("Start");
  Serial.print("\t");
  Serial.println("End");
}

void loop() {
  // Nothing here
}

void trigger0() {
  if( (millis() - lastDebounce0) > debounceDelay){
    counter0++;
    Serial.print(counter0);
    Serial.print(" : ");
    Serial.println(counter1);
    lastDebounce0 = millis();
  }
}

void trigger1() {
  if( (millis() - lastDebounce1) > debounceDelay){
    counter1++;
    lastDebounce1 = millis();
  }
}
