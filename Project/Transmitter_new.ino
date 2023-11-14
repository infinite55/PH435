#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

const int ROW_NUM = 4; // four rows
const int COLUMN_NUM = 4; // four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; // connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

int cursorColumn = 0;
int cursorRow = 0;

void setup() {
  Serial.begin(9600);
  lcd.init(); // initialize the lcd
  lcd.backlight();
  keypad.setDebounceTime(30);
  pinMode(12, OUTPUT);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    int keyValue = 0;

    for (int row = 0; row < ROW_NUM; row++) {
      for (int column = 0; column < COLUMN_NUM; column++) {
        if (key == keys[row][column]) {
          //keyValue = row * COLUMN_NUM + column + 1;
          keyValue = (row * COLUMN_NUM + column + 1)*15 + 100;
          break;
        }
      }
    }

    lcd.setCursor(cursorColumn, cursorRow);  // move cursor to   (cursorColumn, cursorRow)
    lcd.print(key);                          // print key at (cursorColumn, cursorRow)

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
    digitalWrite(12, HIGH);
    delay(keyValue);
    digitalWrite(12, LOW);
    delay(100);
  }
}