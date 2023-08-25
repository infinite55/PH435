void setup() {
  // put your setup code here, to run once:
  pinMode(4, INPUT_PULLUP);               // Push button 1
  pinMode(5, INPUT_PULLUP);               // Push button 2
  tempSensor.init(i2c);

  PCICR |= B00000100;                      // Enable PCMSK2(PCINT 16 to 23), Group 2 ISR active
  PCMSK2 |= B00110000;                     //pin D4 and D5 (B00100000) could trigger interrupt, but how to know which pin triggered the ISR
}

bool D4_state = LOW;
bool D5_state = HIGH;

void loop() {
  // put your main code here, to run repeatedly:
  readTemperature();      // Read real temperature

  compute.PID(setpoint, duty);      // Calculate PID and output duty cycle

  apply_PWM(duty);

}

ISR(PCINT2_vector){
  if(PIND & B00010000){     //D4 is HIGH
    setpoint --;
  }                                                        // if(digitalRead(4)){}

  if(PIND & B00100000){   // D5 is HIGH
    setpoint ++;
  }
}


ISR(PCINT2_vector){
  if(digitalRead(4) && !D4_state){     
    // D4 changed state RISING
  }                                                       
  else if (!digitalRead(4) && D4_state){
    //D4 changed state FALLING
  }

  if(digitalRead(5) && !D5_state){   
    //D5 changed state RISING
  }
  else if (!digitalRead(5) && D5_state){
    // D5 changed state FALLING     
  }
}
