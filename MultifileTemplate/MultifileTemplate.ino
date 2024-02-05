//Qi Xu& Walls Garrate  1/30/2024
//ECE160 FINAL PROJECT MILLISTONE2
//AUTOnomous control&remote control&linefollowing&IR
//Ti robot&led&sharp sensor

// Load libraries used

#include "SimpleRSLK.h"
#include <Servo.h>
#include "PS2X_lib.h"
#include <TinyIRremote.h>
#define UART_SERIAL Serial
#define PS2_DAT 14  //P1.7 <-> brown wire
#define PS2_CMD 15  //P1.6 <-> orange wire
#define PS2_SEL 34  //P2.3 <-> yellow wire (also called attention)
#define PS2_CLK 35  //P6.7 <-> blue wire
#define START_BUTTON 18  //P3.0 a push button on top of the breadboard
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define IR_RCV_PIN      33
#define IR_LED 6 
#include "SimpleRSLK.h"

#define UART_SERIAL     Serial
IRreceiver irRX(IR_RCV_PIN);

IRData IRresults;
IRsender sendIR1(IR_RCV_PIN); 



PS2X ps2x;

Servo myservo;
int pos=0;
enum RemoteMode {
  PLAYSTATION
};


RemoteMode CurrentRemoteMode = PLAYSTATION;


unsigned long lastActionTime = 0;  
const uint8_t lineColor = LIGHT_LINE;

uint16_t distValue; 
uint16_t distMM; 
float distIN;
uint32_t linePos = getLinePosition();
int Leftbut = 18;
int IRLEDpin = 3;
int greenLEDpin = 4;

int redLEDpin = 29; 
int blueLEDpin = 28; 
int yellowLEDpin = 27; 

 // sets the sensor pin used

const uint16_t slowSpeed = 10;
const uint16_t fastSpeed = 20;
const unsigned long movementDuration = 2000;  // Duration for movement forward autonomously in milliseconds
//set auto state
enum AutoState {
  AUTO,
  AUTO_LINEFOLLOW,
  IDLE
};

AutoState AutoCurrentState = AUTO;
//set robot state
enum RobotState {
  MANUAL,
  INITIALIZE,
  AUTONOMOUS
};


RobotState RobotCurrentState = INITIALIZE;

IRData IRmsg1, IRmsg2; 

void setup() {
  Serial.begin(57600);
  Serial.print("Starting up Robot code...... ");
  setupRSLK();
  setupWaitBtn(LP_LEFT_BTN);
  setupLed(RED_LED);
  myservo.attach(SRV_0);
  // attaches the servo on Port 1, pin 5 to the servo object
  pinMode(IRLEDpin, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);
  // Run setup code

    // using the playstation controller
    Serial.println("Using playstation controller, make sure it is paired first ");

    // Initialize PlayStation controller
    delayMicroseconds(500 * 1000);  //added delay to give wireless ps2 module some time to startup, before configuring it
    // declare variables for playstation control
    bool pressures = false;
    bool rumble = false;
    int error = 1;

    while (error) {
      error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

      if (error == 0)
        Serial.println("Found Controller, configured successful ");

      else if (error == 1)
        Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

      else if (error == 2)
        Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

      else if (error == 3)
        Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
      delayMicroseconds(1000 * 1000);
    }
    enableRXLEDFeedback(BLUE_LED);
    pinMode(redLEDpin, OUTPUT); 
    pinMode(blueLEDpin, OUTPUT); 
    pinMode(yellowLEDpin, OUTPUT); 

    IRmsg1.protocol = NEC; 
    IRmsg1.address = 0xEE; 
    IRmsg1.command = 160; 
    IRmsg1.isRepeat = false; 
  //IR message setup for catrina skull 
    IRmsg2.protocol = NEC; 
    IRmsg2.address = 0xCE; 
  //IRmsg1.command = Same as value that is recieved in Remote Control class;  This is set up individualy in the Remote Control Class 
    IRmsg2.isRepeat = false; 
    floorCalibration();
}

void loop() {
  // Read input from PlayStation controller
  ps2x.read_gamepad();

  // Update state machine based on button input
  updateStateMachine();

  // Perform actions based on the current state
  executeStateActions();
  delayMicroseconds(50*1000);
}

void updateStateMachine() {
  switch (RobotCurrentState) {
    case INITIALIZE:
      if (ps2x.Button(PSB_L3)) {
        // go to Autonomous state when L3 button pushed
        RobotCurrentState = MANUAL;
      }
      break;

    case MANUAL:
      if (ps2x.Button(PSB_SELECT)) {
        // go to Autonomous state when Select button pushed
        RobotCurrentState = AUTONOMOUS;
      }
      break;

    case AUTONOMOUS:
      if (ps2x.Button(PSB_START)) {
        // go to manual state when START button pushed
        RobotCurrentState = MANUAL;
        // reset autonomous state to start state for the next time
        AutoCurrentState = AUTO_LINEFOLLOW; 
      }

      break;
  }
}

void executeStateActions() {
  switch (RobotCurrentState) {
    case INITIALIZE:
      Serial.println("Initialzing");

      break;
    case AUTONOMOUS:
      // Perform actions for the autonomous state
      AutonomousControl();
      Serial.println("It is in autonomous mode");
      // Add any additional actions for the autonomous state
      break;

    case MANUAL:
      // Perform actions for the manual state
      RemoteControl();
      Serial.println("It is in Manual mode");
      // Add any additional actions for the manual state
      break;
  }
}


