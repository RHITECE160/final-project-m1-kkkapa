
void updateStateMachine() {
  switch (RobotCurrentState) {
    case MANUAL:
      if (ps2x.Button(PSB_START)) {
        // go to Autonomous state when circle button pushed
        RobotCurrentState = AUTONOMOUS;
      }
      break;

    case AUTONOMOUS:
      if (ps2x.Button(PSB_SELECT)) {
        // go to manual state when square button pushed
        RobotCurrentState = MANUAL;
        // reset autonomous state to start state for the next time
        AutoCurrentState = AUTO_TOWALL; 
      }

      break;
  }
}

void executeStateActions() {
  switch (RobotCurrentState) {
    case AUTONOMOUS:
      // Perform actions for the autonomous state
      AutonomousControl();
      // Add any additional actions for the autonomous state
      break;

    case MANUAL:
      // Perform actions for the manual state
      RemoteControl();
      // Add any additional actions for the manual state
      break;
  }
}
