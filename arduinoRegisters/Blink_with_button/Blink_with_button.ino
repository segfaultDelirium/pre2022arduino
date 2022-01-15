const int led_pin = 5;
const int btn_pin = 2;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led_pin, OUTPUT);
  //pinMode(btn_pin, INPUT_PULLUP);
  DDRD = (1 << 5);
  PORTD = (1 << 2);

  DDRB = (1 << 0);
  PORTB = (1 << 2);
}

// the loop function runs over and over again forever
void loop() {
  int btnState = (PIND & (1 << btn_pin)) >> btn_pin;
  if(btnState == LOW){
    PORTD = (1 << 5) | PORTD;
    PORTB = (1 << 0 ) | PORTB;
    //digitalWrite(led_pin, HIGH);
  }else{
    PORTD = ~(1 << 5) & PORTD;
    PORTB = ~(1 << 0 ) & PORTB;
    //digitalWrite(led_pin, LOW);
  }              
  delay(10);
}
