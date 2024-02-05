


void AutonomousControl() {
  // put your code here to run in Autonomous control mode

  Serial.println("in the AutonomousControl function");

  // State machine loop
  while (AutoCurrentState != IDLE) {
    switch (AutoCurrentState) {
      case AUTO:
        //move forward then update sensor
        forward();  
        LaserSensor();
        if (distMM < 140) {
          //STOP IF DISTANCE < 140 MM
          stop();
          s90spin();
          delay(500);
          forward();
          delay(1500);
          AutoCurrentState = AUTO_LINEFOLLOW;
        }
        
        break;

      case AUTO_LINEFOLLOW:
        Serial.println("Linefollowing");

        LaserSensor();
        linefollowing();
         if (distMM < 150) {
          //STOP IF DISTANCE < 100MM
            stop();
            s180spin();
            delay(500);
            myservo.write(140);
            delay(1000);
            AutoCurrentState = IDLE;
        }
        break;

      default:
        break;
    }
  }
}




