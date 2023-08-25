#include <TimerOne.h>

int inputPin1 = 2;    // pulse arrive on pin2
int inputPin2 = 3;    // pulse arrive on pin3

bool calculate = false;
volatile unsigned long Phase = 0;  
volatile unsigned int pulse1 = 0;
volatile unsigned int pulse2 = 0;

void setup() {
  pinMode(inputPin1, INPUT);
  pinMode(inputPin2, INPUT);
  Serial.begin(9600);
  Timer1.initialize(1000000);   // timer set to 1sec
  Timer1.attachInterrupt(calcPhase);
  attachInterrupt(0, interrupt1, RISING);
  attachInterrupt(0, interrupt2, RISING);
  interrupts();
}

void loop() {
  // Freq = newPulse - pulse;
  Serial.println(Phase);
  calculate = true; 
}

void calcPhase() {
  Phase = (float) (pulse2 - pulse1);
  calculate = false;
}

void interrupt1() {  
  pulse1 = micros();
}

void interrupt2() {  
  pulse2 = micros();
}
