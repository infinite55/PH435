#include <TimerOne.h>

int inputPin = 2;    // pulse arrive on pin2

volatile unsigned long Freq = 0;  
volatile unsigned int pulse = 0;
volatile unsigned int newPulse = 0;
volatile unsigned int prevPulse = 0;

void setup() {
  pinMode(inputPin, INPUT);
  Serial.begin(9600);
  Timer1.initialize(1000000);   // timer set to 1sec
  Timer1.attachInterrupt(calcFreq);
  attachInterrupt(0, interrupt, RISING);
  interrupts();
}

void loop() {
  // Freq = newPulse - pulse;
  Serial.print(Freq);
  Serial.println("Hz"); 
}

void calcFreq() {
  //newPulse++;
  newPulse = pulse;
  Freq = newPulse - prevPulse;
  prevPulse = newPulse;
}

void interrupt() {  
  pulse++;
}
