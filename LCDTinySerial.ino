// LCD Details
#define LCD_CHARACTERS      16
#define LCD_LINES           2

// ATtiny PIN Assignments
#define SERIAL_RX_PIN       3
#define SERIAL_TX_PIN       4
#define SHIFT_DATA_PIN      0   // ATtiny PIN number connecting to 74HC595 pin 14 (SER)
#define SHIFT_LATCH_PIN     1   // ATtiny PIN number connecting to 74HC595 pin 12 (RCLK)
#define SHIFT_CLOCK_PIN     2   // ATtiny PIN number connecting to 74HC595 pin 11 (SRCLK)

// General Configration Details
#define LCD_CLEAR_ASCII     7   // ASCII code for clearing the screen (use a code that is not often used)
#define LCD_NEW_LINE_ASCII  13  // ASCII code for the new line carriage (eg. 13 or 10)
#define PRINT_BY_CHAR           // Comment out to enable line by line mode eg. only show data after new line



// NO CHANGES NEEDED BELOW

#include <LiquidCrystal595.h>    // include the library
#include <SoftwareSerial.h>
const int rx = 3;
const int tx = 4;
const int DATA = 0;
const int LATCH = 1;
const int CLOCK = 2;

SoftwareSerial mySerial(rx, tx);
LiquidCrystal595 lcd(DATA, LATCH, CLOCK);   // datapin, latchpin, clockpin

int i = 0;
#ifndef PRINT_BY_CHAR
char buffr[LCD_CHARACTERS];
#else
char buffr[LCD_LINES][LCD_CHARACTERS];
#endif

int line = 0;


void setup() {
  pinMode(rx, INPUT);
  pinMode(tx, OUTPUT);
  mySerial.begin(9600);

  lcd.begin(LCD_CHARACTERS, LCD_LINES);
  lcd.clear();
  lcd.setCursor(0, 0);
#ifdef PRINT_BY_CHAR
  lcd.cursor();
  lcd.blink();
#endif
  lcd.println("ATTiny LCD");
  lcd.setCursor(0, 1);
  lcd.println("1 Wire Serial v1");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, line);

}

void loop() {
#ifdef PRINT_BY_CHAR
  if (mySerial.available() > 0) {
    char in_char = mySerial.read();
    if (int(in_char) == LCD_CLEAR_ASCII) { // Clear screen and buffers
      line = 0;
      lcd.clear();
      for (int y = 0; y <= (LCD_LINES - 1); y++) {
        for (int x = 0; x <= LCD_CHARACTERS; x++) {
          buffr[y][x] = ' ';
        }
      }
      i = 0;
    } else if (int(in_char) == LCD_NEW_LINE_ASCII || i >= LCD_CHARACTERS) {
      if (line == (LCD_LINES - 1)) { // Move everything up a line
        for (int y = 0; y <= (LCD_LINES - 2); y++) {
          strcpy(buffr[y], buffr[y + 1]); //Copy next line to current line
          lcd.setCursor(0, y);
          lcd.print(buffr[y]);
        }
      } else {
        if (line >= (LCD_LINES - 1)) {
          line = 0;
        } else {
          line++;
        }
      }
      lcd.setCursor(0, line);
      for (int x = 0; x <= LCD_CHARACTERS; x++) {
        lcd.print(" ");
        buffr[line][x] = ' ';
      }
      lcd.setCursor(0, line);
      i = 0;
    } else {
      lcd.print(in_char);
      buffr[line][i] = in_char;
      i++;
    }

  }
#else
  if (mySerial.available() > 0) {
    char in_char = mySerial.read();
    if (int(in_char) == LCD_CLEAR_ASCII) {
      line = 0;
      lcd.clear();
      for (int x = 0; x <= LCD_CHARACTERS; x++) {
        buffr[x] = ' ';
      }
      i = 0;
    } else if (int(in_char) == LCD_NEW_LINE_ASCII || i >= LCD_CHARACTERS) { //If Carriage return has been reached
      lcd.setCursor(0, line);
      lcd.print(buffr);
      if (line >= (LCD_LINES - 1)) {
        line = 0;
      } else {
        line++;
      }
      for (int x = 0; x <= LCD_CHARACTERS; x++) {
        buffr[x] = ' ';
      }
      i = 0; //start over again

    } else { //if enter
      buffr[i] = in_char;
      i++;
    }

  }
#endif
}
