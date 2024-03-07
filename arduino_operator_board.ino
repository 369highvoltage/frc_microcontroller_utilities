/**
A simple arduino operator controller board script by Shehroz B.
Available for public use

Requirements:
ArduinoJoystickLibrary
LiquidCrystal I2C
Encoder
*/ 

#include <Joystick.h>
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

//create the display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// digital pin 2 has a pushbutton attached to it. Give it a name:
int button[] = { 4, 5, 6, 7, 8, 9, 10, 11 };




long positionLeft  = -999;
long positionRight = -999;

#define rot1_A 0
#define rot1_B 1

#define rot2_A 20
#define rot2_B 21

#define encMaxVal 720
#define encMinVal -720

Encoder leftEncoder(rot2_A,rot2_B);
Encoder rightEncoder(rot1_A,rot1_B);

void clearEncoderValue(Encoder enc) {
  enc.readAndReset();
}

void clearRightEncoder() {
  rightEncoder.readAndReset();
}

void nullAction() {}

/*
typedef struct {
  int pin;
  void (*buttonAction)();
} Button;


Button buttonBoard[8] = {
  { .pin = 4, .buttonAction = nullAction },
  { .pin = 5, .buttonAction = nullAction },
  { .pin = 6, .buttonAction = nullAction },
  { .pin = 7, .buttonAction = nullAction },
  { .pin = 8, .buttonAction = nullAction },
  { .pin = 9, .buttonAction = nullAction },
  { .pin = 10, .buttonAction = nullAction },
  { .pin = 11, .buttonAction = clearRightEncoder }
};
*/

void (*buttonAction[8])() = {
  nullAction,
  nullAction,
  nullAction,
  nullAction,
  nullAction,
  nullAction,
  nullAction,
  clearRightEncoder,
};

//create the Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  16, 0,                  // Button Count, Hat Switch Count
  true, false, false,    // X, Y, Z Axis
  false, false, false,    // Rx, Ry, Rz Axis
  false, false,            // rudder, throttle Axis
  false, false, false);   // accelerator, brake, steering Axis

void displayInit() {
  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Offset: ");
}

//define the rotary encoders
// the setup routine runs once when you press reset:
void setup() {
  displayInit();
  Joystick.setXAxisRange(encMinVal, encMaxVal);
  Joystick.begin();
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(rot1_A, INPUT_PULLUP);
  pinMode(rot1_B, INPUT_PULLUP);
  pinMode(rot2_A, INPUT_PULLUP);
  pinMode(rot2_B, INPUT_PULLUP);

  // make the pushbutton's pin an input while cycling through all 8 buttons:
  for(int i = 0; i <= 0; i++)
    pinMode(button[i], INPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  double newLeft, newRight;
  //  newLeft = leftEncoder.read();
  newRight = rightEncoder.read();
  double joystickVal = max(encMinVal, min(encMaxVal, newRight));
  Serial.println(joystickVal);
  Joystick.setXAxis(joystickVal);

  lcd.setCursor(8,0);
  lcd.print(joystickVal/144.0);

  lcd.setCursor(2, 1);
  for(int i = 0; i <= 9; i++){
      // read the input pin:
      int curButtonState = !digitalRead(button[i]);
      if(curButtonState == 1)
        (*buttonAction[i])();
      // bind input to HID button:
      Joystick.setButton(i, curButtonState);      
  }
  //delay(10);
}


