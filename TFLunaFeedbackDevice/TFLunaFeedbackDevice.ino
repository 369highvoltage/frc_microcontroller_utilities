/*------------------------------------------------------------------------------

  TFLunaFeedbackDevice
  by Eric T.

  This code allows us to interface the TF-Luna to any of the following devices:
  
  (With pigtail cable):
  - Spark Flex

  (With 10-pin IDC cable pigtail):
  - Spark MAX
  - Talon FXS

  Connections:
  - Arduino +5 VDC
  - Arduino GND
  - TF-Luna Data (SDA) output (Blue Wire) to Arduino digital input (Pin A4)
  - TF-Luna Clock (SCL) output (White Wire) to Arduino digital input (Pin A5)
  - Arduino digital output (pin 11) to Motor controller data port

------------------------------------------------------------------------------*/
 
#include <Arduino.h>     // every sketch needs this
#include <Wire.h>        // instantiate the Wire library
#include <TFLI2C.h>      // TFLuna-I2C Library v.0.2.0

TFLI2C tflI2C;

int16_t tfDist;                 // Distance in centimeters
int16_t output;
int16_t  tfAddr = TFL_DEF_ADR;  // Use this default I2C address or set variable to your own value
const int16_t maxDistance = 255;
const int8_t pwmOutputPin = 11;

void setup()
{
    Serial.begin(115200);                                   // Initialize serial port
    Wire.begin();                                           // Initialize Wire library
    Serial.println("Initializing TFLunaFeedbackDevice: "); // say "Hello!"
}

void loop()
{
    if( tflI2C.getData( tfDist, tfAddr) ) // If read okay...
    {
      logDistance();        // Print the data
      pwmOutput();
    }
    else {
      tflI2C.printStatus(); // else, print error.
    }

    delay(1);
}

void logDistance() {
  Serial.print("Dist: ");
  Serial.println(tfDist);  
}

void pwmOutput() {
  output = min(tfDist, maxDistance);  // Constrain values to a certain limit
  analogWrite(pwmOutputPin, output);  // Output signal
}