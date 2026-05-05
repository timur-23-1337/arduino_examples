#include <Joystick_ESP32S2.h>
#define X_BTN 18
#define B_BTN 34
#define A_BTN 33
#define Y_BTN 21
#define R1_BTN 16
#define R2_BTN 17
#define L1_BTN 39
#define L2_BTN 40
#define LF_BTN 10
#define RF_BTN 11
#define ST_BTN 13
#define MN_BTN 12
#define CN_BTN 14
#define DPAD_U 38
#define DPAD_D 37
#define DPAD_L 35
#define DPAD_R 36
#define LAXISX 7
#define LAXISY 9
#define RAXISX 6
#define RAXISY 8
int pins[] = {38, 37, 36, 35, 40, 39, 17, 16, 6, 7, 34, 33, 21, 18, 10, 11, 8, 9, 13, 12, 14};
//-----------------------------------------------
bool android = false;
Joystick_ Joystick(0x03, JOYSTICK_TYPE_GAMEPAD, 17, 1, true, true, true, false, true, false, false, false, false, false, false);
//-----------------------------------------------
int applyDeadzone(int value) {
  value = map(value, 0, 8191, 0, 1023);
  int center = 512;
  int deadzone = 100;
  if (value <= 660 && value >= 590){
    return center;
  }
  else{
    return value;
  }
}
//-----------------------------------------------
void setup() {
  pinMode(R1_BTN, INPUT_PULLUP);
  pinMode(R2_BTN, INPUT_PULLUP);
  if (!digitalRead(R1_BTN) && !digitalRead(R2_BTN)) {
    android = true;
  }
  for(int i : pins){
    pinMode(i, INPUT_PULLUP);
  }
  Joystick.begin();
}
//-----------------------------------------------
void readButtons() {
  if (android){
    // Buttons
    Joystick.setButton(4, !digitalRead(Y_BTN));
    Joystick.setButton(0, !digitalRead(A_BTN));
    Joystick.setButton(1, !digitalRead(B_BTN));
    Joystick.setButton(3, !digitalRead(X_BTN));
    // Shoulders
    Joystick.setButton(7, !digitalRead(R1_BTN));
    Joystick.setButton(9, !digitalRead(R2_BTN));
    Joystick.setButton(6, !digitalRead(L1_BTN));
    Joystick.setButton(8 , !digitalRead(L2_BTN));
    //Stick buttons
    Joystick.setButton(14, !digitalRead(LF_BTN));
    Joystick.setButton(13, !digitalRead(RF_BTN));
    // Center buttons
    Joystick.setButton(10, !digitalRead(ST_BTN));
    Joystick.setButton(11, !digitalRead(MN_BTN));
    Joystick.setButton(12, !digitalRead(CN_BTN));
  } else {
    // Buttons
    Joystick.setButton(2, !digitalRead(X_BTN));
    Joystick.setButton(0, !digitalRead(A_BTN));
    Joystick.setButton(1, !digitalRead(B_BTN));
    Joystick.setButton(3, !digitalRead(Y_BTN));
    // Shoulders
    Joystick.setButton(4, !digitalRead(R1_BTN));
    Joystick.setButton(6, !digitalRead(R2_BTN));
    Joystick.setButton(5, !digitalRead(L1_BTN));
    Joystick.setButton(7, !digitalRead(L2_BTN));
    // Stick buttons
    Joystick.setButton(10, !digitalRead(RF_BTN));
    Joystick.setButton(11, !digitalRead(LF_BTN));
    // Center buttons
    Joystick.setButton(8, !digitalRead(ST_BTN));
    Joystick.setButton(9, !digitalRead(MN_BTN));
    Joystick.setButton(16, !digitalRead(CN_BTN));
  }
}
//-----------------------------------------------
void readDpad() {
  if (android){
    bool up    = !digitalRead(DPAD_U);
    bool right = !digitalRead(DPAD_D);
    bool down  = !digitalRead(DPAD_L);
    bool left  = !digitalRead(DPAD_R);

    int hat = -1; // neutral

    if (up) hat = 90;
    else if (right) hat = 180;
    else if (down) hat = 270;
    else if (left) hat = 0;

    Joystick.setHatSwitch(0, hat);
  }
  else {
    Joystick.setButton(15, !digitalRead(DPAD_U));
    Joystick.setButton(16, !digitalRead(DPAD_D));
    Joystick.setButton(14, !digitalRead(DPAD_L));
    Joystick.setButton(17, !digitalRead(DPAD_R));
  }
}
//-----------------------------------------------
void readSticks() {
  // Left stick
  Joystick.setXAxis(applyDeadzone(analogRead(LAXISX)));
  Joystick.setYAxis(applyDeadzone(analogRead(LAXISY)));
  // Right stick
  if (android){
    Joystick.setZAxis(applyDeadzone(analogRead(RAXISX)));
    Joystick.setRyAxis(applyDeadzone(analogRead(RAXISY)));
  } else {
    Joystick.setRxAxis(applyDeadzone(analogRead(RAXISX)));
    Joystick.setZAxis(applyDeadzone(analogRead(RAXISY)));
  }
}
//-----------------------------------------------
void loop() {
  readButtons();
  readSticks();
  readDpad();
  delay(5);
}