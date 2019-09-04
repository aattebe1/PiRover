/***********************************************************************************
*	{L298_C}
*	L298.c
*		by Austin Atteberry
*
*	PERFORMANCE:
*	Allows the Raspberry Pi to control the L298 Dual H-Bridge Motor Driver
*
************************************************************************************/

#include<stdio.h>
#include<wiringPi.h>

/* L298Setup function
*  Sets up the pins for the L298
*  The pin modes must be set before calling any of the other L298 functions.
*  However, using this setup function is unnecessary if the pins were already
*  initialized in another function.
*/
int L298Setup(int enaPin, int enbPin, int pin1, int pin2, int pin3, int pin4) {

	/* Set pin modes */
	pinMode(enaPin, PWM_OUTPUT);
	pinMode(enbPin, PWM_OUTPUT);
	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);
	pinMode(pin3, OUTPUT);
	pinMode(pin4, OUTPUT);

	/* Set initial conditions */
	pwmWrite(enaPin, LOW);
	pwmWrite(enbPin, LOW);
	digitalWrite(pin1, HIGH);
	digitalWrite(pin2, HIGH);
	digitalWrite(pin3, HIGH);
	digitalWrite(pin4, HIGH);
}

/* L298Forward function
*  Moves the motor forward at the specified speed
*/
int L298Forward(int enaPin, int enbPin, int pin1, int pin2, int pin3, int pin4, int speed) {

	if((speed < 0) || (speed > 1024)) {
		/* Speed outside of range, return error */
		return(-1);
	}
	else {
		/* Speed within range, set pins */
		digitalWrite(pin1, HIGH);
		digitalWrite(pin4, HIGH);
		digitalWrite(pin2, LOW);
		digitalWrite(pin3, LOW);
		pwmWrite(enaPin, speed);
		pwmWrite(enbPin, speed);
	}

	return(0);
}

/* L298Reverse function
*  Move the motor in reverse at the specified speed
*/
int L298Reverse(int enaPin, int enbPin, int pin1, int pin2, int pin3, int pin4, int speed) {

	if((speed < 0) || (speed > 1024)) {
		/* Speed outside of range, return error */
		return(-1);
	}
	else {
		/* Speed within range, set pins */
		digitalWrite(pin1, LOW);
		digitalWrite(pin4, LOW);
		digitalWrite(pin2, HIGH);
		digitalWrite(pin3, HIGH);
		pwmWrite(enaPin, speed);
		pwmWrite(enbPin, speed);
	}

	return(0);
}

/* L298Coast function
*  Cuts the power to the motors
*/
void L298Coast(int enaPin, int enbPin) {

	pwmWrite(enaPin, LOW);
	pwmWrite(enbPin, LOW);
}

/* L298Brake function
*  Locks the motors
*/
void L298Brake(int pin1, int pin2, int pin3, int pin4) {

	digitalWrite(pin1, HIGH);
	digitalWrite(pin2, HIGH);
	digitalWrite(pin3, HIGH);
	digitalWrite(pin4, HIGH);
}

/* L298Right function
*  Turns the vehicle to the right at the specified speed
*/
int L298Right(int enaPin, int enbPin, int pin1, int pin2, int pin3, int pin4, int speed) {

	if((speed < 0) || (speed > 1024)) {
		/* Speed outside of range, return error */
		return(-1);
	}
	else {
		/* Speed within range, set pins */
		digitalWrite(pin1, LOW);
		digitalWrite(pin3, LOW);
		digitalWrite(pin2, HIGH);
		digitalWrite(pin4, HIGH);
		pwmWrite(enaPin, speed);
		pwmWrite(enbPin, speed);
	}
}

/* L298Left function
*  Turns the vehicle to the left at the specified speed
*/
int L298Left(int enaPin, int enbPin, int pin1, int pin2, int pin3, int pin4, int speed) {

	if((speed < 0) || (speed > 1024)) {
		/* Speed outside of range, return error */
		return(-1);
	}
	else {
		/* Speed within range, set pins */
		digitalWrite(pin1, HIGH);
		digitalWrite(pin3, HIGH);
		digitalWrite(pin4, LOW);
		digitalWrite(pin2, LOW);
		pwmWrite(enaPin, speed);
		pwmWrite(enbPin, speed);
	}
}