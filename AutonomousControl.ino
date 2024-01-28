/*
  AutonomousControl.ino - Arduino Sketch for Autonomous Control of the RLSK robot
  
  Description:
  This sketch provides functions for autonomous action of an RLSK robot. A state
  machine is used for autonomous control. A few actions have been programed as
  an example. 

  The robot moves forward for a time (defined by movementDuration). Then 
  transitions to a number of other states. After reaching the final state, 
  the higher-level state is switched to IDLE to await the next instruction.

  State Machine description:
  The robot moves forward for a short time using a non-blocking delay, then 
  the motors stop. Then the next few states are place-holders. The Robot returns
  to IDLE state when autonomous functions are complete.

  Created by: Your Name
  Date: Current Date
  Version: 1.0
*/

// Define lower-level state machine for AUTONOMOUS mode
enum AutoState {
  AUTO_TOWALL,
  AUTO_LINEFOLLOW,
  IDLE
};

AutoState AutoCurrentState = AUTO_TOWALL;

uint16_t distValue; 
uint16_t distMM; 
float distIN;

void AutonomousControl() {
  // put your code here to run in Autonomous control mode

  unsigned long myTime;

  Serial.println("in the AutonomousControl function");

  // State machine loop
  while (AutoCurrentState != IDLE) {
    switch (AutoCurrentState) {
      case AUTO_TOWALL:

        //move forward then update sensor
        forward();  
        LaserSensor();
        // Check if the movement duration has passed
        if (distMM < 120) {
          stop();
          lastActionTime = millis();  // Record the time when the forward state started
          spincounter();
          if ((millis() - lastActionTime) > 500) {
            stop();
            AutoCurrentState = AUTO_LINEFOLLOW;
          }
          
        }
        
        break;

      case AUTO_LINEFOLLOW:
        // Add state instructions here
        delay(1000);  // Placeholder delay
        forward();
        linefollowing();
        if (distMM < 150) {
          AutoCurrentState = IDLE;  // Transition to next state
        }
        break;

      default:
        // Handle unknown state, if needed
        break;
    }
  }

  // The code will exit the while loop when IDLE state is reached
  Serial.println("State: IDLE");
  // Add IDLE state instructions here

}
