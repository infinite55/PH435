#include <avr/interrupt.h> //must be included if your program uses interrupts
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 7, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int inputpin1 = 2;          // expect pulses to arrive at pin 2
volatile long int count = 0;
volatile long int time2 = 0;
volatile long int time3 = 0;
volatile long int diff = 0;
volatile bool diditcalculate = false;

int cursorColumn = 0;
int cursorRow = 0;


const float threshold = 1.5; //in micros

char keys[16] = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'};

int pulse_width[16] = {115, 130, 145, 160, 175, 190, 205, 220, 235, 250, 265, 280, 295, 310, 325, 340};

void setup() 
{
  //Serial.begin(9600);
  pinMode(inputpin1, INPUT);
  lcd.begin(16, 2);
  attachInterrupt(0,rise,RISING); //Digital Pin 2 corresponds to Interrupt 0, Calls ISR function 'Pulse' everytime Pin 2 has a rising edge
  attachInterrupt(1,fall,FALLING); //Digital Pin 2 corresponds to Interrupt 0, Calls ISR function 'Pulse' everytime Pin 3 has a rising edge
  interrupts(); // enables Interrupts

}

void loop() 
{
  //delay(100);                 //do something to waste time as we count rising edges
  if (diditcalculate == true) //print the value of frequency everytime the Calcfreq() interrupt is run
  {
    for (int i = 0; i < 16; i++) {
        if (diff/1000 > pulse_width[i] - threshold & diff/1000 < pulse_width[i]+ threshold) {
            lcd.setCursor(cursorColumn, cursorRow);  // move cursor to   (cursorColumn, cursorRow)
            lcd.print(keys[i]);                          // print key at (cursorColumn, cursorRow)

            cursorColumn++;                 // move cursor to next position
            if(cursorColumn == 16) {        // if reaching limit, clear LCD
                cursorColumn = 0;
                if(cursorRow == 1)
                {
                  lcd.clear();
                  cursorRow = 0;
                }
                else 
                {
                  cursorRow = 1;
                }
              }
          break;
        }
    }
    diditcalculate = false;
  } 
}

void rise()
{
  time2 = micros();
}
void fall()
{
  time3 = micros();
  diff = (time3-time2);
  diditcalculate = true;
}