// efficient Digital to Analog Converter

int inputPin1 = 0;     
int inputPin2 = 1;
int inputPin3 = 2;
int inputPin4 = 3;

void setup() {
  DDRD = DDRD | B00001111; // Set D0, D1, D2, D3 as output
}

void loop() {
  PORTD |= B00000001;     // D0 set as high
  delay(10);
  PORTD |= B00000010;     // D1 set as high
  delay(10);
  PORTD |= B00000100;     // D2 set as high
  delay(10);
  PORTD &= !B00001000;    // D3 set as low
  delay(10);

}
