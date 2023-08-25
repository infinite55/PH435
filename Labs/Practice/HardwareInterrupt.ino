// Hardware Interrupt: Pins D2 and D3 

/* LED Toggle with Delay
Use pushbutton switch to toggle LED with interrupt
*/

// Define LED and switch connections
const byte ledPin = 13;
const byte buttonPin = 2;

// Boolean to represent toggle state
volatile bool toggleState = false;

void checkSwitch(){
  // Check status of switch
  // Toggle LED if button pressed 

  if (digitalRead(buttonPin) == LOW){
    // Switch was pressed 
    // Change state of toggle 
    toggleState = !toggleState;
    // Indicate state on LED 
    digitalWrite(ledPin, toggleState);
    }
}


void setup() {
  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
  // Set switch pin as INPUT with pullup
  pinMode(buttonPin, INPUT_PULLUP);
  // Setup Serial MOnitor
  Serial.begin(9600);
  // Attach Interrupt to Interrupt Service Routine
  attachInterrupt(digitalPinToInterrupt(buttonPin), checkSwitch, FALLING);
}

void loop() {
  // 5-sec time delay
  Serial.println("Delay Started");
  delay(5000);
  Serial.println("Delay Finished");
  Serial.println("-------------------");
}
