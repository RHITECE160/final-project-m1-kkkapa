const float wheelDiameter = 2.7559055; 

/* Number of encoder (rising) pulses every time the wheel turns completely */
const int cntPerRevolution = 360;

const int wheelSpeed = 10; // Default raw pwm speed for motor.

float distanceTraveled(float wheel_diam, uint16_t cnt_per_rev, uint8_t current_cnt)
{
    float temp = (wheel_diam * PI * current_cnt) / cnt_per_rev;
    return temp;
}

uint32_t countForDistance(float wheel_diam, uint16_t cnt_per_rev, uint32_t distance)
{
    float temp = (wheel_diam * PI) / cnt_per_rev;
    temp = distance / temp;
    return int(temp);
}




void s90spin(){
  uint16_t totalCount = 0;        // Total amount of encoder pulses received
  uint16_t leftCount, rightCount;
  int inchesToTravel = 4;

  UART_SERIAL.print("Driving forward distance (inches): ");
  UART_SERIAL.println(inchesToTravel);

    /* Amount of encoder pulses needed to achieve distance */
  uint16_t target = countForDistance(wheelDiameter, cntPerRevolution, inchesToTravel);
 
  delay(2000);

    /* Set the encoder pulses count back to zero */
  resetLeftEncoderCnt();
  resetRightEncoderCnt();

    /* Cause the robot to spin */
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);

    /* "Turn on" the motor */
  enableMotor(BOTH_MOTORS);

    /* Set motor speed */
  setMotorSpeed(BOTH_MOTORS, wheelSpeed);

    /* Drive motor until it has received x pulses */
  while (totalCount < target) {
    leftCount = getEncoderLeftCnt();
    rightCount = getEncoderRightCnt();
    totalCount = (leftCount + rightCount) / 2;
    UART_SERIAL.print("\t"); UART_SERIAL.print(leftCount);
    UART_SERIAL.print("\t"); UART_SERIAL.println(rightCount);
    }

    /* Halt motors */
  disableMotor(BOTH_MOTORS);

    /* Calculate traveled distance from encoder ticks */
  float traveled = distanceTraveled(wheelDiameter, cntPerRevolution, totalCount);
  UART_SERIAL.print("Distance traveled (inches): ");
  UART_SERIAL.println(traveled);
  UART_SERIAL.println();
}



void s180spin(){
  uint16_t totalCount = 0;        // Total amount of encoder pulses received
  uint16_t leftCount, rightCount;
  int inchesToTravel = 9;

  UART_SERIAL.print("Driving forward distance (inches): ");
  UART_SERIAL.println(inchesToTravel);

    /* Amount of encoder pulses needed to achieve distance */
  uint16_t target = countForDistance(wheelDiameter, cntPerRevolution, inchesToTravel);
 
  delay(2000);

    /* Set the encoder pulses count back to zero */
  resetLeftEncoderCnt();
  resetRightEncoderCnt();

    /* Cause the robot to spin */
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
    /* "Turn on" the motor */
  
  enableMotor(BOTH_MOTORS);

    /* Set motor speed */
  setMotorSpeed(BOTH_MOTORS, wheelSpeed);

    /* Drive motor until it has received x pulses */
  while (totalCount < target) {
    leftCount = getEncoderLeftCnt();
    rightCount = getEncoderRightCnt();
    totalCount = (leftCount + rightCount) / 2;
    UART_SERIAL.print("\t"); UART_SERIAL.print(leftCount);
    UART_SERIAL.print("\t"); UART_SERIAL.println(rightCount);
    }

    /* Halt motors */
  disableMotor(BOTH_MOTORS);

    /* Calculate traveled distance from encoder ticks */
  float traveled = distanceTraveled(wheelDiameter, cntPerRevolution, totalCount);
  UART_SERIAL.print("Distance traveled (inches): ");
  UART_SERIAL.println(traveled);
  UART_SERIAL.println();
}

