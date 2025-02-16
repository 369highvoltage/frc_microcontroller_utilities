 /*------------------------------------------------------------------------------

  ProximityBeamBreak
  by Eric T.

  This code allows us to interface a VL53L0X to a Robot.

  Wiring:
  Plug the 3-pin molex cable into a RoboRIO's DIO port.

  Change the DISTANCE_THRESHOLD variable to your desired value.

  Sensor should be mounted to point directly at the object it is detecting.

------------------------------------------------------------------------------*/

#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

const int DISTANCE_THRESHOLD = 200; // Change this to whatever distance is necessary.

const int OUTPUT_PIN = 13;

void setup() {
  pinMode(OUTPUT_PIN, OUTPUT);

  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test.");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power
  Serial.println(F("VL53L0X API Continuous Ranging example\n\n"));

  // start continuous ranging
  lox.startRangeContinuous();
}

void loop() {

  if (lox.isRangeComplete()) {
    
    int distance = lox.readRange();
    
    digitalWrite(OUTPUT_PIN, distance < DISTANCE_THRESHOLD ? HIGH : LOW);

    Serial.print("Distance in mm: ");
    Serial.println(distance);
  }
}