#include <avr/interrupt.h>
int inputpin = 2;   // pulses arrive on pin2
volatile int count = 0;   // variable to count number of pulses

void setup() {
  Serial.begin(9600);          // serial port for sending messages
  pinMode(inputpin, INPUT);    // Set digital pin2 to input mode
  attachInterrupt(0, pulse, RISING);     //Digital pin2 corresponds to interrupt 0, Call ISR function 'pulse' every time
  interrupts();   // enable interrupts

}

void loop() {
  delay(100);
  if(count>100){
    Serial.print("Congratulations! Century");
    Serial.println(count);
  }
  // count = count - 1;             // start counting again??
}
  
void pulse(){         // function called every time rising edge is detected on pin2 
  count++;    // increment count every time a rising edge is detected on pin 2
}