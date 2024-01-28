/*
  RemoteControl.ino - Arduino Sketch for Remote Control of the RLSK robot
  
  Description:
  This sketch provides functions for controlling an RLSK robot using a
  playstation controller for input. A few actions are programed for an 
  example. 

  Button map:
  PAD UP button moves both motors forward
  CROSS button stops motors

  Created by: Your Name
  Date: Current Date
  Version: 1.0
*/

void RemoteControl() {
  // put your code here to run in remote control mode

// Receive and decode remote control commands
   if (ps2x.Button(PSB_PAD_UP)) {
      Serial.println("PAD UP button pushed ");
      forward();
    } else if (ps2x.Button(PSB_CROSS)) {
      Serial.println("CROSS button pushed");
      stop();
    } else if (ps2x.Button(PSB_PAD_DOWN)){
      Serial.println("PAD DOWN button pushed ");
      backward();
    } else if (ps2x.Button(PSB_PAD_LEFT)){
      Serial.println("PAD LEFT button pushed");
      turnleft();
    } else if (ps2x.Button(PSB_PAD_RIGHT)){
      Serial.println("PAD RIGHT button pushed");
      turnright();
    } else if (ps2x.Button(PSB_SQUARE)){
      Serial.println("SQUARE button pushed");
      spincounter();
    } else if (ps2x.Button(PSB_CIRCLE)){
      Serial.println("CIRCLE button pushed");
      spinclock();
    } else if (ps2x.Button(PSB_TRIANGLE)){
      Serial.println("TRIANGLE button pushed");
      myServo.write(140);
    }  else if (ps2x.Button(PSB_R1)){
      Serial.println("R1 button pushed");
      myServo.write(40);
    }  else if (ps2x.Button(PSB_SELECT)){
    }
}
