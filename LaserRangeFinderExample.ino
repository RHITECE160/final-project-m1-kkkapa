/* Testing code for measuring distance usint the SHARP 2Y0A21 IR distance sensor
*  Deborah Walter 10/13/2023
*
*  Calls the findDistance function - which reads the analog pin and converts the integer
*  value to a distance in cm, using the calibration curve from the datasheet.
*   Datasheet: https://global.sharp/products/device/lineup/data/pdf/datasheet/gp2y0a21yk_e.pdf 
*
*/


//#define UART_SERIAL Serial1    // for wireless serial monitor using HC05
//Using the HC-06 lets you see the measurements when not tethered


    // According to the RSLK Library:     
    // readSharpDist(0) is the left distance sensor which is tied to P9.1
    // readSharpDist(1) is the center distance sensor which is tied to P6.1
    // readSharpDist(2) is the right distance sensor which is tied to P9.0

uint8_t SensorPos = 1; // sets the sensor pin used



void LaserSensor() {
  //reads the distance as 14bit integer
  distValue = readSharpDist(SensorPos);

  //reads the distance in millimeters
  distMM = readSharpDistMM(SensorPos);

  //reads the distance in inches
  distIN = readSharpDistIN(SensorPos);

  Serial.println(distMM);
}
