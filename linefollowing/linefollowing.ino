/*
 * Energia Robot Library for Texas Instruments' Robot System Learning Kit (RSLK)
 * Line Following Example
 *
 * Summary:
 * This example has the TI Robotic System Learning Kit (TI RSLK) follow a line
 * using a basic line following algorithm. This example works on a dark floor with
 * a white line, but may be changed by modifying the _lineColor_ value. The robot 
 * first needs to be calibrated (on floor without line). Then place the robot
 * on the line and hit the left button again to begin the line following.
 *
 * How to run:
 * 1) Place the robot on floor away from line to calibrate to background surface.
 * 2) Push left button on Launchpad to have the robot perform calibration.
 * 3) Place the robot center on the line you want it to follow.
 * 4) Push left button again to have the robot begin to follow the line.
 *
 * Parts Info:
 * o Black eletrical tape or white electrical tape. Masking tape does not work well
 *   with IR sensors.
 *
 * Learn more about the classes, variables and functions used in this library by going to:
 * https://ndroid.github.io/msp432-core/RSLK/
 *
 * Learn more about the TI RSLK by going to http://www.ti.com/rslk
 *
 * created by Franklin Cooper Jr.
 * modified by chris miller 
 *
 * This example code is in the public domain.
 */

/* Include RSLK library */

/* Modify the following line to use an alternate UART interface (i.e. Serial1/2/3) */


/* Valid values are either:
 *  DARK_LINE  if your floor is lighter than your line
 *  LIGHT_LINE if your floor is darker than your line
 */

void floorCalibration()
{
    /* Place Robot On Floor (no line) */
    delay(2000);
    /* Wait until button is pressed to start robot */
    waitBtnPressed(LP_LEFT_BTN, RED_LED);

    delay(500);

    /* Set both motors direction forward */
    setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);
    /* Enable both motors */
    enableMotor(BOTH_MOTORS);
    /* Set both motors speed 10 */
    setMotorSpeed(BOTH_MOTORS, 10);

    /* Must be called prior to using getLinePosition() or readCalLineSensor() */
    calibrateLineSensor(lineColor);

    /* Disable both motors */
    disableMotor(BOTH_MOTORS);


}

void linefollowing()
{

    uint32_t linePos = getLinePosition();

    if ((linePos > 0) && (linePos < 4000)) {    // turn left
        setMotorSpeed(LEFT_MOTOR, normalSpeedforlinefollowing);
        setMotorSpeed(RIGHT_MOTOR, fastSpeedforlinefollowing);
    } else if (linePos > 5000) {                // turn right
        setMotorSpeed(LEFT_MOTOR, fastSpeedforlinefollowing);
        setMotorSpeed(RIGHT_MOTOR, normalSpeedforlinefollowing);
    } else {                                    // go straight
        setMotorSpeed(LEFT_MOTOR, normalSpeedforlinefollowing);
        setMotorSpeed(RIGHT_MOTOR, normalSpeedforlinefollowing);
    }
}
