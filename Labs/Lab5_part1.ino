// Digital to Analog Converter
// taking the output from D0, D1, D2, D3 pins to R-2R ladder

int outputPin1 = 0;    // Pin D0
int outputPin2 = 1;    // Pin D1
int outputPin3 = 2;    // Pin D2
int outputPin4 = 3;    // Pin D3

void setup() {
  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin2, OUTPUT);
  pinMode(outputPin3, OUTPUT);
  pinMode(outputPin4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(outputPin1, LOW);
  // delay(10);
  digitalWrite(outputPin2, LOW);
  // delay(10);
  digitalWrite(outputPin3, LOW);
  // delay(10);
  digitalWrite(outputPin4, LOW);
  // delay(10);

  digitalWrite(outputPin1, HIGH);
  delay(10);
  digitalWrite(outputPin2, HIGH);
  delay(10);
  digitalWrite(outputPin3, HIGH);
  delay(10);
  digitalWrite(outputPin4, LOW);
  delay(10);

}
