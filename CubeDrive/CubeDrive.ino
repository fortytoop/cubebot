#include <stdio.h>
#include <string.h>
#include <AccelStepper.h>

#define interfaceType 1 // Stepper driver interface: 2 pins
#define quarterTurn 50 // 90˚ rotation: 50 steps
#define halfTurn 100 // 180˚ rotation: 100 steps

// Instantiate motors
AccelStepper frontMotor(interfaceType, A0, A1);
AccelStepper leftMotor(interfaceType, A2, A3);
AccelStepper rightMotor(interfaceType, A4, A5);
AccelStepper backMotor(interfaceType, 4, 5);
AccelStepper upMotor(interfaceType, 6, 7);
AccelStepper downMotor(interfaceType, 8, 9);

void setup() {
	// Connect to serial port
    Serial.begin(9600);
    while (!Serial);

    // Initialise motor parameters
    frontMotor.setMaxSpeed(24000);
	frontMotor.setAcceleration(18000);
	frontMotor.setSpeed(24000);

	leftMotor.setMaxSpeed(24000);
	leftMotor.setAcceleration(18000);
	leftMotor.setSpeed(24000);

	rightMotor.setMaxSpeed(24000);
	rightMotor.setAcceleration(18000);
	rightMotor.setSpeed(24000);

	backMotor.setMaxSpeed(24000);
	backMotor.setAcceleration(18000);
	backMotor.setSpeed(24000);

	upMotor.setMaxSpeed(24000);
	upMotor.setAcceleration(18000);
	upMotor.setSpeed(24000);

	downMotor.setMaxSpeed(24000);
	downMotor.setAcceleration(18000);
	downMotor.setSpeed(24000);
}

// Test code for executing superflip
char rotation_str[] = "U, R2, F, B, R, B2, R, U2, L, B2, R, Ui, Di, R2. F, Ri, L, B2, U2, F2";
char deliminator[] = ", ";
char *ptr = strtok(rotation_str, deliminator);

void loop() {
	// TODO: Add coms code to communicate with Pi
    while(ptr != NULL) {
        translate(ptr);
		ptr = strtok(NULL, deliminator);
        delay(10);
	}
}


enum motorRotation {CLOCKWISE=false, ANTICLOCKWISE=true};

void translate(char move[]) {
    int size = strlen(move);
    int turnDistance;
	bool direction;

    // Determine turn distance and direction for move
    if (size == 1) { // Only one char in move
    	turnDistance = quarterTurn;
    	direction = CLOCKWISE;
    
    } else { // Two char in string
    	if (move[1] == 'i') { // Inverse move
    		turnDistance = quarterTurn;
    		direction = ANTICLOCKWISE;

    	} else if (move[1] == '2') { // 180˚ move
    		turnDistance = halfTurn;
    		direction = CLOCKWISE;
    	}
    }

    // Determine the motor face for move
    if (move[0] == 'F') {
    	rotate(frontMotor, turnDistance, direction);
    } else if (move[0] == 'L') {
    	rotate(leftMotor, turnDistance, direction);
    } else if (move[0] == 'R') {
    	rotate(rightMotor, turnDistance, direction);
    } else if (move[0] == 'B') {
    	rotate(backMotor, turnDistance, direction);
    } else if (move[0] == 'U') {
    	rotate(upMotor, turnDistance, direction);
    } else if (move[0] == 'D') {
    	rotate(downMotor, turnDistance, direction);
    }
}

void rotate(AccelStepper motor, int turnDistance, bool direction) {
	// Set turn distance based on rotation direction
	if (direction == ANTICLOCKWISE) {
		turnDistance = -turnDistance;
	}

	// Rotate motor
	motor.move(turnDistance);
	while (motor.distanceToGo() != 0) {
		motor.run();
	}
}
