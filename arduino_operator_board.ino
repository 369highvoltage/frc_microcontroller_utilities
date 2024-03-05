#include <Joystick.h>

//create the Joystick
Joystick_ Joystick;
  

// digital pin 2 has a pushbutton attached to it. Give it a name:
int button[] = {2,3,4,5,6,7,8,9};

// the setup routine runs once when you press reset:
void setup() {
  Joystick.begin();
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input while cycling through all 8 buttons:
  for(int i = 0; i <= 0; i++)
    pinMode(button[i], INPUT);

}

// the loop routine runs over and over again forever:
void loop() {
  buttonDebug();
}

void buttonDebug() {
  //cycle through all buttons
  for(int i = 0; i <= 9; i++){
      // read the input pin:
  int buttonState = digitalRead(button[i]);
  // print out the state of the button:
  Serial.print(i);
  if(buttonState == 1)
    Serial.println(" state: LOW\n");
  else 
    Serial.println(" state: HIGH\n");
    
  delay(100);  // delay in between reads for stability
  }
}