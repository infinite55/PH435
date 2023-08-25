// BLINK LED EACH 500ms using TIMER1

// Compare Match
//To compare the timer, there are two main registers: TCCR1A(Timer/Counter1 Control Register A)
// and TCCR1B(Timer/Counter1 Control Register B), each one with the number of timer, tht is, TIMER1

bool LED_STATE = true;


void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);              // Set the pin to be OUTPUT
  cli();                           // Stop interrupts for till we amke the settings

  /* 1. First reset the control register to make sure we start with everything disabled */
  TCCR1A = 0;                     // Reset entire TCCR1A to 0
  TCCR1B = 0;                     // Reset entire TCCR1B to 0

  /* 2. Set the prescalar to the desired value by changing the CS10, CS11 and CS12 bits */
  // TCCR1B = B00000010;
  TCCR1B |= B00000100;            // (OR method) Set CS12 to 1 so we get prescalar 256
  //Use OR operation to add 1s
  //Use AND operation to add 0s
  // TCCR1B |= (1 << CS12);     // Setting only CS12 bit to 1

  /* 3. Enable Compare match mode on register A */
  TIMSK1 |= B00000010;            // Set OCIE1A to 1 so we enable compare match A
  // TIMSK1 |= (1 << OCIE1A);
  //Now we have the interruption each time the timer will reach the value of OCR1A

  /* 4. Set the value of register A to 31250*/
  OCR1A = 31250;                  // Finally we set compare register A to this value
  // In order to count upto 500ms using 256 prescalar, we have to count upto 31250
  sei();                          // Enable back the interrupts
}

void loop() {
  // put your main code here, to run repeatedly:

}

// With the settings above, this IRS will trigger each 500ms
ISR(TIMER1_COMPA_vect){
  TCNT1 = 0;                       // First, set the timer back to 0 so it resets for
  LED_STATE = !LED_STATE;           // Invert the state of Led
  digitalWrite(13, LED_STATE);      // Write new state to the LED on pin D5
}




// If u dont want to reset the timer TCNT1 to 0 each interruption with the line TCNT1 = 0;
// in the void setup() u can also use WGM12 bit and set it to 1 and that will enable the CTC or Clear timer on Compare 
// and that means the timer will automatically set its value to 0, once its OCR1A value is reached:
// 

// TCCR1B |= (1 << WGM12);            // Enable CTC




















