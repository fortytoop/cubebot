#include <stdio.h>
#include <string.h>
#include <AccelStepper.h>

// TYPE: Stepper Driver, 2 driver pins required.
#define motorInterfaceType 1


// 90˚ rotation == 50 steps
#define quarterTurn 50

// Pin connections for motors
const int leftMotorDirPin = 4;
const int leftMotorStepPin = 5;

const int rightMotorDirPin = 8;
const int rightMotorStepPin = 9;

const int upMotorDirPin = 13;
const int upMotorStepPin = 12;

const int downMotorDirPin = 6;
const int downMotorStepPin = 7;

const int frontMotorDirPin = 2;
const int frontMotorStepPin = 3;

// NOTE: Switched because pin 13 has a 5V spike when restarting the Arduino,
//       even when there is a pull down resistor.
// TODO: Possibly figure why this occurs.
const int backMotorDirPin = 10;
const int backMotorStepPin = 11;


// Creates motor instance
AccelStepper leftMotor(motorInterfaceType, leftMotorStepPin, leftMotorDirPin);
AccelStepper rightMotor(motorInterfaceType, rightMotorStepPin, rightMotorDirPin);

AccelStepper upMotor(motorInterfaceType, upMotorStepPin, upMotorDirPin);
AccelStepper downMotor(motorInterfaceType, downMotorStepPin, downMotorDirPin);

AccelStepper frontMotor(motorInterfaceType, frontMotorStepPin, frontMotorDirPin);
AccelStepper backMotor(motorInterfaceType, backMotorStepPin, backMotorDirPin);

bool complete = false;

char rotation_str[] = "U, U, U, U, Ui, Ui, Ui, Ui";
// char rotation_str[] = "D, D, D, D, Di, Di, Di, Di";
// char rotation_str[] = "L, L, L, L, Li, Li, Li, Li";
// char rotation_str[] = "R, R, R, R, Ri, Ri, Ri, Ri";
// char rotation_str[] = "F, F, F, F, Fi, Fi, Fi, Fi";
// char rotation_str[] = "B, B, B, B, Bi, Bi, Bi, Bi";
// char rotation_str[] = "F, U, F, U, Fi, Fi, Ui, Ui";

char deliminator[] = ", ";
char *ptr = strtok(rotation_str, deliminator);

void setup() {
    // Connect to serial port
    Serial.begin(9600);
    while (!Serial);

	// Set motor parameters
	leftMotor.setMaxSpeed(3000);
	leftMotor.setAcceleration(18000);
	leftMotor.setSpeed(1500);

    rightMotor.setMaxSpeed(3000);
	rightMotor.setAcceleration(18000);
	rightMotor.setSpeed(1500);

    upMotor.setMaxSpeed(3000);
	upMotor.setAcceleration(18000);
	upMotor.setSpeed(1500);

    downMotor.setMaxSpeed(3000);
	downMotor.setAcceleration(18000);
	downMotor.setSpeed(1500);

    frontMotor.setMaxSpeed(3000);
	frontMotor.setAcceleration(18000);
	frontMotor.setSpeed(1500);

    backMotor.setMaxSpeed(3000);
	backMotor.setAcceleration(18000);
	backMotor.setSpeed(1500);

}

void loop() {
    while(ptr != NULL) {
        translateRotationString(ptr);
		ptr = strtok(NULL, deliminator);
        delay(10);
	}
}


void translateRotationString(char rotation[]) {
    int size = strlen(rotation);
    bool turnInverse = false;

    if (size > 1) {
        turnInverse = true;
    }

    if (rotation[0] == 'L') {
        leftRotation(quarterTurn, turnInverse);
    } else if (rotation[0] == 'R') {
        rightRotation(quarterTurn, turnInverse);
    } else if (rotation[0] == 'U') {
        upRotation(quarterTurn, turnInverse);
    } else if (rotation[0] == 'D') {
        downRotation(quarterTurn, turnInverse);
    } else if (rotation[0] == 'F') {
        frontRotation(quarterTurn, turnInverse);
    } else if (rotation[0] == 'B') {
        backRotation(quarterTurn, turnInverse);
    }
}


void leftRotation(int turnDistance, bool turnInverse) {
    // Counter-clockwise rotation, so negate turnDistance
    if (turnInverse == true) {
        turnDistance = -turnDistance;
    }

    leftMotor.move(turnDistance);
    while (leftMotor.distanceToGo() != 0) {
        leftMotor.run();
    }

}

void rightRotation(int turnDistance, bool turnInverse) {
    // Counter-clockwise rotation, so negate turnDistance
    if (turnInverse == true) {
        turnDistance = -turnDistance;
    }

    rightMotor.move(turnDistance);

    while (rightMotor.distanceToGo() != 0) {
        rightMotor.run();
    }
}

void upRotation(int turnDistance, bool turnInverse) {
    // Counter-clockwise rotation, so negate turnDistance
    if (turnInverse == true) {
        turnDistance = -turnDistance;
    }

    upMotor.move(turnDistance);

    while (upMotor.distanceToGo() != 0) {
        upMotor.run();
    }
}

void downRotation(int turnDistance, bool turnInverse) {
    // Counter-clockwise rotation, so negate turnDistance
    if (turnInverse == true) {
        turnDistance = -turnDistance;
    }

    downMotor.move(turnDistance);

    while (downMotor.distanceToGo() != 0) {
        downMotor.run();
    }
}

void frontRotation(int turnDistance, bool turnInverse) {
    // Counter-clockwise rotation, so negate turnDistance
    if (turnInverse == true) {
        turnDistance = -turnDistance;
    }

    frontMotor.move(turnDistance);

    while (frontMotor.distanceToGo() != 0) {
        frontMotor.run();
    }
}

void backRotation(int turnDistance, bool turnInverse) {
    // Counter-clockwise rotation, so negate turnDistance
    if (turnInverse == true) {
        turnDistance = -turnDistance;
    }

    backMotor.move(turnDistance);

    while (backMotor.distanceToGo() != 0) {
        backMotor.run();
    }
}
