//Timer Interrupt: interrupt generated after a predetermined amount of time
// useful when reading something periodically or outputing some periodically
// Interrupt timer frequency: clock/ (Prescaler * (Compare Match Register + 1))
// Compare Match Register Value: [Clock/ (Prescaler * Desired Frequency)] - 1

//Flash LED using Timer1 

// Define the LED pin
#define ledPin 13

// Define timer compare match register value
int timer1_compare_match;

ISR(TIMER1_COMPA_vect){  
  // Interrupt Service Routine for compare mode

  // Preload timer with compare match value (reset)
  TCNT1 = timer1_compare_match;

  // Write opposite value to LED
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);  // writing the inverse of the current state of the LED (another way of doing it)

}

void setup() {
  // Set LED as output
  pinMode(ledPin, OUTPUT);

  // Disable all interrupts
  noInterrupts();

  // Initialize Timer1
  TCCR1A = 0;
  TCCR1B = 0;

  // Set timer1_compare_match to the correct compare match register value
  // 256 prescaler & 31246 compare match = 2Hz
  timer1_compare_match = 31249;

  // Preload timer with compare match value
  TCNT1 = timer1_compare_match;

  // Set prescaler to 256
  TCCR1B |= (1 << CS12);

  // Enable timer interrupt for compare mode
  TIMSK1 |= (1 << OCIE1A);

  // Enable all interrupts
  interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:

}
