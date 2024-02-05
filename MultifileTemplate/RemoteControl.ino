

void RemoteControl() {
  // Read input from PlayStation controller
  ps2x.read_gamepad();

  // Operate the robot in remote control mode

  RemoteControlPlaystation();
  // run using the ps2 controller
}


void RemoteControlPlaystation() {
  if (ps2x.Button(PSB_PAD_UP)) {
    Serial.println("PAD UP button pushed ");
    forward();
  } else if (ps2x.Button(PSB_CROSS)) {
    Serial.println("CROSS button pushed");
    stop();
  } else if (ps2x.Button(PSB_PAD_DOWN)) {
    Serial.println("PAD DOWN button pushed ");
    backward();
  } else if (ps2x.Button(PSB_PAD_LEFT)) {
    Serial.println("PAD LEFT button pushed");
    turnleft();
  } else if (ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.println("PAD RIGHT button pushed");
    turnright();
  } else if (ps2x.Button(PSB_SQUARE)) {
    Serial.println("SQUARE button pushed");
    spincounter();
  } else if (ps2x.Button(PSB_CIRCLE)) {
    Serial.println("CIRCLE button pushed");
    spinclock();
  } else if (ps2x.Button(PSB_TRIANGLE)) {
    Serial.println("TRIANGLE button pushed");
    myservo.write(140);
  } else if (ps2x.Button(PSB_R1)) {
    Serial.println("R1 button pushed");
    myservo.write(45);
  } else if (ps2x.Button(PSB_L1)) {
    digitalWrite(IRLEDpin, HIGH);
    digitalWrite(greenLEDpin, HIGH);
    delay(1000);
    digitalWrite(IRLEDpin, LOW);
    digitalWrite(greenLEDpin, LOW);
  } else if (ps2x.Button(PSB_L2)) {
    Serial.println("L2 button pushed");
    sendIR1.write(&IRmsg1);
    Serial.print('.');
    digitalWrite(redLEDpin, HIGH);
    delay(500);
    digitalWrite(redLEDpin, LOW);
  } else if (ps2x.Button(PSB_R3)) {
    Serial.println("R2 button pushed");
      if (irRX.decodeIR(&IRresults)) {
        IRmsg2.command = IRresults.command;
        sendIR1.write(&IRmsg2);
        Serial.print('.');
        digitalWrite(blueLEDpin, HIGH);
        delay(500);
        digitalWrite(blueLEDpin, LOW);
    }
  }
}
