//Multiple Pin change Interrupt: Demonstrates Pin Change Interrupts with two on same port
// (Switches are wired to) Inputs on D2 & D7 (both pins on Port D; hence same interrupt), LEDs on D11 & D13
// Purpose to differentiate between two inputs, whether it came from D2 or D7

// LEDs and switchs
const byte ledPin1 = 11;
const byte ledPin2 = 13;
const byte buttonPin1 = 2;
const byte buttonPin2 = 7;

// Booleans for input states
volatile bool D2_state = LOW;
volatile bool D7_state = LOW;

void setup() {
  // Set LEDs as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  // Set switches as inputs with pullups 
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  // Enable PCIE2 Bit3 = 1 (Port D)
  PCICR |= B00000100;
  // Enable PCINT18 and PCINT23 (Pins D2 & D7)
  PCMSK |= B10000100;

}

void loop() {
  //loop code

}

ISR (PCINT2_vect){
  //Port D Interrupt occured

  // Check if this was D2
  if (digitalRead(buttonPin1) == LOW){
    // Pin D2 triggered the ISR on a FAlling pulse
    D2_state = !D2_state;
    //Set LED 1 to state of D2_state boolean
    digitalWrite(ledPin1, D2_state);
  }

  // Check if this was D7
  if (digitalRead(buttonPin2) == LOw){
    // Pin D7 triggered the ISR on a Falling pulse
    D7_state = !D7_state;
    // Set LED2 to state of D7_state boolean
    digitalWrite(ledPin2, D7_state);      
    }
}
