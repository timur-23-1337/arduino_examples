#include <Joystick.h>
//-----------------------------------------------
bool android;
Joystick_ Joystick(0x03, JOYSTICK_TYPE_GAMEPAD, 16, 1, true, true, true, true, true, true, false, false, false, false, false);
//-----------------------------------------------
int applyDeadzone(int value) {
  int center = 512;
  int deadzone = 30;
  return (abs(value - center) < deadzone) ? (center) : (value);
}
//-----------------------------------------------
void setup() {
  pinMode(10, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  if (!digitalRead(10) && !digitalRead(16)) {
    android = true;
  }
  for(int i = 0; i < 16; i++){
    if(i <= 10 || i >= 14){
      pinMode(i, INPUT_PULLUP);
    }
  }
  Joystick.begin();
}
//-----------------------------------------------
void readButtons() {
  if (android){
    // Buttons
    Joystick.setButton(3, !digitalRead(6));
    Joystick.setButton(0, !digitalRead(7));
    Joystick.setButton(1, !digitalRead(8));
    Joystick.setButton(4, !digitalRead(9));
    // Shoulders
    Joystick.setButton(6, !digitalRead(0));
    Joystick.setButton(8, !digitalRead(1));
    Joystick.setButton(7, !digitalRead(10));
    Joystick.setButton(9 , !digitalRead(16));
    //Stick buttons
    Joystick.setButton(10, !digitalRead(15));
    Joystick.setButton(11, !digitalRead(14));
  } else {
    // D-pad
    Joystick.setButton(15, !digitalRead(2));
    Joystick.setButton(13, !digitalRead(3));
    Joystick.setButton(14, !digitalRead(4));
    Joystick.setButton(12, !digitalRead(5));
    // Buttons
    Joystick.setButton(2, !digitalRead(6));
    Joystick.setButton(0, !digitalRead(7));
    Joystick.setButton(1, !digitalRead(8));
    Joystick.setButton(3, !digitalRead(9));
    // Shoulders
    Joystick.setButton(4, !digitalRead(0));
    Joystick.setButton(6, !digitalRead(1));
    Joystick.setButton(5, !digitalRead(10));
    Joystick.setButton(7, !digitalRead(16));
    //Stick buttons
    Joystick.setButton(8, !digitalRead(15));
    Joystick.setButton(9, !digitalRead(14));
  }
}
//-----------------------------------------------
void readDpad() {
  bool up    = !digitalRead(5);
  bool right = !digitalRead(2);
  bool down  = !digitalRead(3);
  bool left  = !digitalRead(4);

  int hat = -1; // neutral

  if (up && right) hat = 45;
  else if (right && down) hat = 135;
  else if (down && left) hat = 225;
  else if (left && up) hat = 315;
  else if (up) hat = 0;
  else if (right) hat = 90;
  else if (down) hat = 180;
  else if (left) hat = 270;

  Joystick.setHatSwitch(0, hat);
}
//-----------------------------------------------
void readSticks() {
  // Left stick
  Joystick.setXAxis(applyDeadzone(analogRead(A2)));
  Joystick.setYAxis(applyDeadzone(analogRead(A3)));
  // Right stick
  if (android){
    Joystick.setZAxis(applyDeadzone(analogRead(A0)));
    Joystick.setRxAxis(applyDeadzone(analogRead(A1))); //idk which one is correct
    Joystick.setRyAxis(applyDeadzone(analogRead(A1))); //so i used all of them
    Joystick.setRzAxis(applyDeadzone(analogRead(A1))); //just to be safe
  } else {
    Joystick.setRxAxis(applyDeadzone(analogRead(A1)));
    Joystick.setZAxis(applyDeadzone(analogRead(A0)));
  }
}
//-----------------------------------------------
void loop() {
  readButtons();
  readSticks();
  if (android){
    readDpad();
  }
  delay(5);
}