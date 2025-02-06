// code for main PCB - everything except the right motor
#include <Servo.h>
#include <LiquidCrystal.h>

// initialize the LCD library driver with the display pins connected to the arduino pins
const int rs = 8, en = 9, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  
// assign the switches connected to the arduino pins
const int right_switch_pin = 7;
const int left_switch_pin = 10;
int right_switch_state = 0;
int left_switch_state = 0;

// create the servo objects to control the left, center, and right servo motors
Servo left_servo;
Servo center_servo;
// Servo right_servo;
const int lservo_pin = 0;
const int cservo_pin = 2;

int pages_read = 0; // only keeps track of pages turned forward
int bookmark = 50; // this is where we are starting from
int display_flag = 0; // used to update display

void setup() {
  // LCD setup
  lcd.begin(16, 4); // set up of the LCD's number of columns and rows
  lcd.setCursor(0, 0);
  lcd.print("Turn Counter:");
  lcd.setCursor(0, 1);
  lcd.print("0 pages turned");
  lcd.setCursor(0, 3);
  lcd.print("Bookmark: Pg 50");

  // foot pedal switches setup
  pinMode(right_switch_pin, INPUT);
  pinMode(left_switch_pin, INPUT);

  // orientation setup for the motors (all set to 0 degrees)
  Serial.begin(9600); // send and receive at 9600 baud (needed to send data to the motors)
  left_servo.attach(lservo_pin); // attaches the left servo on pin 7 to the servo object
  left_servo.write(45);
  center_servo.attach(cservo_pin); // attaches the center servo on pin 6 to the servo object
  center_servo.write(0);
}

void loop() {
  // read the state of the foot pedal switches
  right_switch_state = digitalRead(right_switch_pin); 
  left_switch_state = digitalRead(left_switch_pin); 

  // check if the foot pedals were pressed
  if (left_switch_state==HIGH && right_switch_state==LOW) { // backwards turning code
    center_servo.write(0);
    delay(1000);
    left_servo.write(155);
    delay(1000);
    center_servo.write(60);
    delay(1000);
    left_servo.write(45);
    delay(1000);
    center_servo.write(165);
    pages_read--; // decrement pages read
    bookmark--;
    display_flag = 1;
  }

  if (left_switch_state==LOW && right_switch_state==HIGH) { // forwards turning code
    center_servo.write(165);
    delay(2000);
    // right_servo.write(25);
    // delay(1000);
    center_servo.write(120);
    delay(2000);
    // right_servo.write(145);
    // delay(1250);
    center_servo.write(0);
    pages_read++; // increment pages read
    bookmark++;
    display_flag = 1;
  }  

  // update display
  if (display_flag == 1) {
    lcd.setCursor(0, 1);
    if (pages_read == 1) {
      lcd.print("                "); // clear the row
      lcd.setCursor(0, 1);
      lcd.print("1 page forward");
    }
    else if (pages_read == -1) {
      lcd.print("                "); // clear the row
      lcd.setCursor(0, 1);
      lcd.print("1 page backward");
    }
    else if (pages_read > 1) {
      lcd.print("                "); // clear the row
      lcd.setCursor(0, 1);
      lcd.print(pages_read); // constantly display the page count (never negative)
      lcd.print(" pages forward");
    }
    else if (pages_read < -1) {
      lcd.print("                "); // clear the row
      lcd.setCursor(0, 1);
      lcd.print(abs(pages_read)); // constantly display the page count (never negative)
      lcd.print(" pages backward");
    }
    else {
      lcd.print("                "); // clear the row
      lcd.setCursor(0, 1);
      lcd.print("0 pages turned");
    }
    lcd.setCursor(0, 3);
    lcd.print("                "); // clear the row
    lcd.setCursor(0, 3);
    lcd.print("Bookmark: Pg ");
    lcd.print(bookmark);
    display_flag = 0;
  }
}
