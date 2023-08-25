//Pin Change Interrupts
//1. Every I/O pin supports Pin Change Interrupts
//2. ATMega328 has 24 PCi pins
//3. Arduino Uno has 20 PCi pins available
//4. Activated on a change of state only
//5. Pins grouped into Ports
//6. All pins on the same port share a PCI

// INput on D7, LED on D13

//LED and switch
const byte ledPin = 13;
const byte buttonPin = 7;

// boolean to represent toggle state
volatile bool togglestate = false;

void setup() {
  // Set LED as output
  pinMode(ledPin, OUTPUT);

  //Set switch as input with pullup
  pinMode(buttonPin, INPUT_PULLUP);

  // Enable PCIE2 Bit3 = 1 (Port D)
  PCICR |= B00000100;
  // Select PCINT23 Bit7 = 1 (pIn D7) 
  PCMSK2 |= B10000000; 
}

void loop() {
  //No code in loop

}

ISR(PCINT2_vect){
  // INterrupt for Port D
  // Invert toggle state
  togglestate = !togglestate;
  //Indicate state on LED
  digitalWrite(ledPin, togglestate);
}


