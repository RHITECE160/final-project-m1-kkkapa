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
#include <TinyIRremote.h>

/*
 * Helper macro for getting a macro definition as string
 */
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define IR_RCV_PIN      33

//IRreceiver irRX(IR_RCV_PIN);
int greenLED = 26;

//IRData = IRmsg;
void RemoteControl() {
 // Read input from PlayStation controller
  ps2x.read_gamepad();

  // Operate the robot in remote control mode
  RemoteControlPlaystation();

  //IRmsg.protocol = NEC;
  /*IRmsg.address = 0xA5;
  IRmsg.command = 0xC3;
  IRmsg.isRepeat = false;*/
}


void RemoteControlPlaystation() {

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
      myservo.write(140);
    }  else if (ps2x.Button(PSB_R1)){
      Serial.println("R1 button pushed");
      myservo.write(45);
    }  
    else if (ps2x.Button(PSB_L1)){
      Serial.println("L1 button pushed");
      digitalWrite(IRLEDpin, HIGH);
      digitalWrite(greenLEDpin, HIGH);
      delay(5000);
      digitalWrite(IRLEDpin, LOW);
      digitalWrite(greenLEDpin, LOW);
      delay(1000);
    }
  }

