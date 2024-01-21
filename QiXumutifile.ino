/*A multifile project code template
  A template for the Milestone 1 project code that uses multiple files
  for modularity. The compiler first loads the principal file 
  (the one with the same name as the folder) and then loads 
  the others in alphabetical order. Variables defined in an 
  earlier file will be visible to code in a file that is loaded 
  later, but not vice-versa. 

  Calls functions in files:
  MotorFunctions.ino

  written for the MSP432401 board
  Author: Deborah Walter
  Last revised: 11/28/2023

***** Hardware Connections: *****
     start button       P3.0
     playstation connections
     brown wire         P1.7 
     orange wire        P1.6 
     yellow wire        P2.3
     blue wire          P6.7
*/
//sadsadsd
// Load libraries used
#include <TinyIRremote.h>

/*
 * Helper macro for getting a macro definition as string
 */
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define IR_RCV_PIN      33

IRreceiver irRX(IR_RCV_PIN);

/**
 * Struct to hold IR data, defined as (defined in IRData.h):
 * 
 * struct {
 *   decode_type_t protocol;     ///< UNKNOWN, NEC, SONY, RC5, ...
 *   uint16_t address;           ///< Decoded address
 *   uint16_t command;           ///< Decoded command
 *   bool isRepeat;
 * } 
 */
IRData IRresults;



#include "SimpleRSLK.h"
#include <Servo.h>
#include "PS2X_lib.h"

// Define pin numbers for the button on the PlayStation controller
#define PS2_DAT 14  //P1.7 <-> brown wire
#define PS2_CMD 15  //P1.6 <-> orange wire
#define PS2_SEL 34  //P2.3 <-> yellow wire (also called attention)
#define PS2_CLK 35  //P6.7 <-> blue wire

// Create an instance of the playstation controller object
PS2X ps2x;
Servo myServo;
// Define remote mode either playstation controller or IR remote controller
enum RemoteMode {
  PLAYSTATION,
  IR_REMOTE,
};

// Declare and initialize the current state variable
RemoteMode CurrentRemoteMode = IR_REMOTE;

// Tuning Parameters
const uint16_t lowSpeed = 15;
const uint16_t fastSpeed = 30;

void setup() {
  Serial.begin(57600);
  Serial.print("Starting up Robot code...... ");

  // Run setup code
  setupRSLK();
  myServo.attach(SRV_0);
  if (CurrentRemoteMode == 0) {
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
  } else if (CurrentRemoteMode == 1) {
    // put start-up code for IR controller here if neccessary
    Serial.begin(57600);
    delay(500); // To be able to connect Serial monitor after reset or power up 
    Serial.println(F("START " __FILE__ " from " __DATE__));
    /*
     * Must be called to initialize and set up IR receiver pin.
     *  bool initIRReceiver(bool includeRepeats = true, bool enableCallback = false,
                void (*callbackFunction)(uint16_t , uint8_t , bool) = NULL)
     */
    if (irRX.initIRReceiver()) {
        Serial.println(F("Ready to receive NEC IR signals at pin " STR(IR_RCV_PIN)));
    } else {
        Serial.println("Initialization of IR receiver failed!");
        while (1) {;}
    }
    // enable receive feedback and specify LED pin number (defaults to LED_BUILTIN)
    enableRXLEDFeedback(BLUE_LED);
  }
}

void loop() {
  // Read input from PlayStation controller
  ps2x.read_gamepad();

  // Operate the robot in remote control mode
  if (CurrentRemoteMode == 0) {
    Serial.println("Running remote control with the Playstation Controller");
    RemoteControlPlaystation();

  } else if (CurrentRemoteMode == 1) {
    // put code here to run using the IR controller if neccessary
    Serial.println("Running remote control with the IR Playstation Controller");
    IRcontrol();
  }
}


  /* RemoteControlPlaystation() function
  This function uses a playstation controller and the PLSK libraray with
  an RLSK robot using to implement remote controller. 
  
  A few actions are programed for an example. 

  Button control map:
  PAD UP button moves both motors forward
  CROSS button stops motors
  */
  void RemoteControlPlaystation() {
    // put your code here to run in remote control mode

    // Example of receive and decode remote control command
    // the forward() and stop() functions should be independent of
    // the control methods
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
    }
  }
  

  //vol+ button  A=0x0 C=0x46
  //vol- button   A=0x0 C=0x15
  //left  button  A=0x0 C=0x44
  //right button A=0x0 C=0x43
  //4   button  A=0x0 C=0x8
  //5 button   A=0x0 C=0x1C
  //6 button  A=0x0 C=0x5A
  //8 button  A=0x0 C=0x52
  
  void IRcontrol() {
    if (irRX.decodeIR(&IRresults)) {
        // Vol+ button
        if (IRresults.command == 0x46) {
            Serial.println("Vol+ button pressed");
            forward();
        }
        // Vol- button
        else if (IRresults.command == 0x15) {
            Serial.println("Vol- button pressed");
            backward();
        }
        // Left button
        else if (IRresults.command == 0x44) {
            Serial.println("Left button pressed");
            turnleft();
        }
        // Right button
        else if (IRresults.command == 0x43) {
            Serial.println("Right button pressed");
            turnright();
        }
        // Button 4
        else if (IRresults.command == 0x8) {
            Serial.println("Button 4 pressed");
            stop();
        }
        // Button 5
        else if (IRresults.command == 0x1C) {
            Serial.println("Button 5 pressed");
            spincounter();
        }
        // Button 6
        else if (IRresults.command == 0x5A) {
            Serial.println("Button 6 pressed");
            spinclock();
        }
        // Button 8
        else if (IRresults.command == 0x52) {
            Serial.println("Button 8 pressed");
            myServo.write(140); // Example action for servo
        }
        // Add additional else if statements for other buttons as needed
    }
}
  
