#include <Servo.h>

// assign the switches connected to the arduino pins
const int right_switch_pin = 7;
int right_switch_state = 0;

// create the servo objects to control the right servo motors
Servo right_servo;
const int rservo_pin = 2;

void setup() {
  // put your setup code here, to run once:

  // foot pedal switches setup
  pinMode(right_switch_pin, INPUT);

  // orientation setup for the motors (all set to 0 degrees)
  Serial.begin(9600); // send and receive at 9600 baud (needed to send data to the motors)
  right_servo.attach(rservo_pin); // attaches the right servo on pin 5 to the servo object
  right_servo.write(145);
}

void loop() {
  // put your main code here, to run repeatedly:
  right_switch_state = digitalRead(right_switch_pin); 

  if (right_switch_state==HIGH) { // forwards turning code
    delay(1250);
    right_servo.write(25);
    delay(2000);
    right_servo.write(145);
    delay(1000);
  }  
}
