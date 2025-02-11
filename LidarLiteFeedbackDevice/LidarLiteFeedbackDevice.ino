 /*------------------------------------------------------------------------------

  LIDARLiteFeedbackDevice
  by Eric T.

  This code allows us to interface the Lidar-Lite to any of the following devices:
  
  (With pigtail cable):
  - Spark Flex

  (With 10-pin IDC cable pigtail):
  - Spark MAX
  - Talon FXS

  Connections:
  Arduino 5 VDC
  Arduino GND
  LIDAR-Lite output (yellow or white) to Arduino digital input (pin 3)
  Arduino digital output (pin 11) to Motor controller data port

  (Capacitor recommended to mitigate inrush current when device is enabled)
  680uF capacitor (+) to Arduino 5v
  680uF capacitor (-) to Arduino GND

  Please calibrate the distance measurements before using.

------------------------------------------------------------------------------*/

const int LIDAR_PWM_IN = 3;
const int CONTROLLER_PWM_OUT = 11;

unsigned long currentMillis;
unsigned long elapsedMillis = 0;
unsigned long pulseWidth, distanceCM;
const unsigned long maxHeight = 56;
const unsigned long minHeight = 0;

void setup() {
  Serial.begin(115200);                                         // Start serial communications
  pinMode(LIDAR_PWM_IN, INPUT);                                 // Set pin 3 as lidar monitor pin
}

void logDistance(unsigned long rawDistance) {

  double distanceMeters = distanceCM / 100.0;                   // Convert cm to m

  Serial.print("Distance (M): ");
  Serial.println(distanceMeters);                               // Print distance in meters
}

void output(unsigned long pulseLength) {
  
  pulseLength = constrain(pulseLength, minHeight, maxHeight);   // Make sure lidar input is within a range (0 to 6 meters)
  pulseLength = map(pulseLength, minHeight, maxHeight, 0, 254); // Map lidar distance to PWM (from 0-6 meters, to 0-255 PWM output)

  analogWrite(CONTROLLER_PWM_OUT, pulseLength);                 // Send out PWM wave

  Serial.print("PWM Output: ");
  Serial.println(pulseLength);                                  // Print PWM output
}

void loop() {
  currentMillis = millis();

  if(elapsedMillis != currentMillis) {                          // Run this action every 1 millisecond.
    elapsedMillis = currentMillis;

    pulseWidth = pulseIn(LIDAR_PWM_IN, HIGH)/10;                // Count how long the pulse is high in microseconds (10 microseconds = 1 cm of distance)
    distanceCM = 0.6520 * pulseWidth - 1.908;                   // Map inaccurate values to actual distances
    logDistance(distanceCM);
    output(pulseWidth);
    
    if(pulseWidth == 0) {                                       // Optional: Set an error line to the controller high, to indicate measurement error.
      
    }
  }
}