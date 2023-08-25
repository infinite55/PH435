bool A_STATE = true;
bool B_STATE = true; 

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  cli();                            // Stop interrupts for till we make the settings

  //Timer 1 (interrupt each 50ms)
  TCCR1A = 0;            // Reset entire TCCR1A to 0
  TCCR1B = 0;            // Reset entire TCCR1B to 0
  TCCR1A |= B00000111;

  TCCR1B |= B00000100;   // Set CS12 to 1 so we get prescalar 256
  TIMSK1 |= B00000110;   // Set OCIE1A and OCIE1B to 1 so we enable compare match A and B
  sei();

}

void loop() {
  OCR1A = map(analogRead(A0),0,1024,1000,2000);
  OCR1B = map(analogRead(A1),0,1024,1000,2000);
  // OCR1A = 1200;
  // OCR1B = 5000;
}

ISR(TIMER1_COMPA_vect){
  A_STATE = !A_STATE;           // Invert the state of Led
  digitalWrite(2, A_STATE);      // Write new state to the LED on pin D5
}


ISR(TIMER1_COMPB_vect){
  B_STATE = !B_STATE;           // Invert the state of Led
  digitalWrite(3, B_STATE);      // Write new state to the LED on pin D5
}


//Frequency is same, but width is changing with change in voltage?
// More precision as analogWrite has only a precision of 8bits, that is 0-255 but here we ahve a precision of 16bit, 0-65535