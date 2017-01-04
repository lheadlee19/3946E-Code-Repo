float LCDSelect(){

	int Program = 0;

	bStopTasksBetweenModes = true;

	int lcdScreenMin = 1;

	int lcdScreen = 1;

	int lcdScreenMax = 4;

	bLCDBacklight = true;

	const short leftButton = 1;
	const short centerButton = 2;
	const short rightButton = 4;

	int requiredLCDValue = 1;

	while (bIfiRobotDisabled) {
		requiredLCDValue = 1;
		if (nLCDButtons == leftButton) {
			if (lcdScreenMin == lcdScreen) {
				lcdScreen = 4;
				wait1Msec(250);
				} else {
				lcdScreen --;
				wait1Msec(250);
			}
		}
		if (nLCDButtons == rightButton) {
			if (lcdScreenMax == lcdScreen) {
				lcdScreen = 1;
				wait1Msec(250);
				} else {
				lcdScreen++;
				wait1Msec(250);
			}
		}
		if (lcdScreen == 1 && Program != 1) {
			displayLCDCenteredString (0, "No Autonomous");
			displayLCDCenteredString (1, "1");
			if (nLCDButtons == centerButton) {
				Program = 1;
				displayLCDCenteredString (0, "Autonomous Has");
				displayLCDCenteredString (1, "Been Selected!");
				wait1Msec(1500);
			}
			} else if (lcdScreen == 1 && Program == 1) {
			displayLCDCenteredString (0, "No Autonomous");
			displayLCDCenteredString (1, "[1]");
			} else if (lcdScreen == 2 && Program != 2) {
			displayLCDCenteredString (0, "Red Autonomous");
			displayLCDCenteredString (1, "2");
			if (nLCDButtons == centerButton) {
				lcdScreen = 1;
				while(requiredLCDValue == 1 && bIfiRobotDisabled) {
					if (nLCDButtons == leftButton) {
						if (lcdScreenMin == lcdScreen) {
							lcdScreen = 4;
							wait1Msec(250);
							} else {
							lcdScreen --;
							wait1Msec(250);
						}
					}
					if (nLCDButtons == rightButton) {
						if (lcdScreenMax == lcdScreen) {
							lcdScreen = 1;
							wait1Msec(250);
							} else {
							lcdScreen++;
							wait1Msec(250);
						}
					}
					if (nLCDButtons == 5){
						requiredLCDValue = 0;
						} else if (lcdScreen == 1 && Program != 2) {
						displayLCDCenteredString (0, "Red Front Main");
						displayLCDCenteredString (1, "1");
						if (nLCDButtons == centerButton) {
							Program = 2;
							displayLCDCenteredString (0, "Autonomous Has");
							displayLCDCenteredString (1, "Been Selected!");
							wait1Msec(1500);
						}
						} else if (lcdScreen == 1 && Program == 2) {
						displayLCDCenteredString (0, "Red Front Main");
						displayLCDCenteredString (1, "[1]");
						} else if (lcdScreen == 2 && Program != 3) {
						displayLCDCenteredString (0, "Red Hoard");
						displayLCDCenteredString (1, "2");
						if (nLCDButtons == centerButton) {
							Program = 3;
							displayLCDCenteredString (0, "Autonomous Has");
							displayLCDCenteredString (1, "Been Selected!");
							wait1Msec(1500);
						}
						} else if (lcdScreen == 2 && Program == 3) {
						displayLCDCenteredString (0, "Red Hoard");
						displayLCDCenteredString (1, "[2]");
						} else if (lcdScreen == 3 && Program != 4) {
						displayLCDCenteredString (0, "Red Back Main");
						displayLCDCenteredString (1, "3");
						if (nLCDButtons == centerButton) {
							Program = 4;
							displayLCDCenteredString (0, "Autonomous Has");
							displayLCDCenteredString (1, "Been Selected!");
							wait1Msec(1500);
						}
						} else if (lcdScreen == 3 && Program == 4) {
						displayLCDCenteredString (0, "Red Back Main");
						displayLCDCenteredString (1, "[3]");
						} else if (lcdScreen == 4 && Program != 5) {
						displayLCDCenteredString (0, "Red Defense");
						displayLCDCenteredString (1, "4");
						if (nLCDButtons == centerButton) {
							Program = 5;
							displayLCDCenteredString (0, "Autonomous Has");
							displayLCDCenteredString (1, "Been Selected!");
							wait1Msec(1500);
						}
						} else if (lcdScreen == 4 && Program == 5) {
						displayLCDCenteredString (0, "Red Defense");
						displayLCDCenteredString (1, "[4]");
					}
				}
			}
			} else if (lcdScreen == 3 && Program != 6) {
			displayLCDCenteredString (0, "Blue Autonomous");
			displayLCDCenteredString (1, "3");
			if (nLCDButtons == centerButton) {
				lcdScreen = 1;
				while(requiredLCDValue == 1 && bIfiRobotDisabled) {
					if (nLCDButtons == leftButton) {
						if (lcdScreenMin == lcdScreen) {
							lcdScreen = 4;
							wait1Msec(250);
							} else {
							lcdScreen --;
							wait1Msec(250);
						}
					}
					if (nLCDButtons == rightButton) {
						if (lcdScreenMax == lcdScreen) {
							lcdScreen = 1;
							wait1Msec(250);
							} else {
							lcdScreen++;
							wait1Msec(250);
						}
					}
					if (nLCDButtons == 5){
						requiredLCDValue = 0;
						} else if (lcdScreen == 1 && Program != 7) {
						displayLCDCenteredString (0, "Blue Front Main");
						displayLCDCenteredString (1, "1");
						if (nLCDButtons == centerButton) {
							Program = 7;
							displayLCDCenteredString (0, "Autonomous Has");
							displayLCDCenteredString (1, "Been Selected!");
							wait1Msec(1500);
						}
						} else if (lcdScreen == 1 && Program == 7) {
						displayLCDCenteredString (0, "Blue Front Main");
						displayLCDCenteredString (1, "[1]");
						} else if (lcdScreen == 2 && Program != 8) {
						displayLCDCenteredString (0, "Blue Hoard");
						displayLCDCenteredString (1, "2");
						if (nLCDButtons == centerButton) {
							Program = 8;
							displayLCDCenteredString (0, "Autonomous Has");
							displayLCDCenteredString (1, "Been Selected!");
							wait1Msec(1500);
						}
						} else if (lcdScreen == 2 && Program == 8) {
						displayLCDCenteredString (0, "Blue Hoard");
						displayLCDCenteredString (1, "[2]");
						} else if (lcdScreen == 3 && Program != 9) {
						displayLCDCenteredString (0, "Blue Back Main");
						displayLCDCenteredString (1, "3");
						if (nLCDButtons == centerButton) {
							Program = 9;
							displayLCDCenteredString (0, "Autonomous Has");
							displayLCDCenteredString (1, "Been Selected!");
							wait1Msec(1500);
						}
						} else if (lcdScreen == 3 && Program == 9) {
						displayLCDCenteredString (0, "Blue Back Main");
						displayLCDCenteredString (1, "[3]");
						} else if (lcdScreen == 4 && Program != 10) {
						displayLCDCenteredString (0, "Blue Defense");
						displayLCDCenteredString (1, "4");
						if (nLCDButtons == centerButton) {
							Program = 10;
							displayLCDCenteredString (0, "Autonomous Has");
							displayLCDCenteredString (1, "Been Selected!");
							wait1Msec(1500);
						}
						} else if (lcdScreen == 4 && Program == 10) {
						displayLCDCenteredString (0, "Blue Defense");
						displayLCDCenteredString (1, "[4]");
					}
				}
			}
			} else if (lcdScreen == 4 && Program != 11) {
			displayLCDCenteredString (0, "Programming");
			displayLCDCenteredString (1, "4");
			if (nLCDButtons == centerButton) {
				Program = 11;
				displayLCDCenteredString (0, "Autonomous Has");
				displayLCDCenteredString (1, "Been Selected!");
				wait1Msec(1500);
			}
			} else if (lcdScreen == 4 && Program == 11) {
			displayLCDCenteredString (0, "Programming");
			displayLCDCenteredString (1, "[4]");
		}
	}

	return Program;

}
