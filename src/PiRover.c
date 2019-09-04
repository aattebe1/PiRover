/***********************************************************************************
*	{PIROVER_C}
*	PiRover.c
*		by Austin Atteberry
*
*	PERFORMANCE:
*	Demos the PWM functionality of the project
*
************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>
#include<pthread.h>
#include "Pins.h"
#include "L298.h"
#include "LCM1602.h"
#include "HCSR04.h"
#include "PiRover.h"

/* Interrupt globals */
volatile int detectorStatus, motorStatus, currentSpeed;

/* File descriptor global */
volatile int fd;

/* main function
*  The program's entry point
*/
int main(int argc, char *argv[]) {

	/* Declare POSIX threads */
	pthread_t motor_t, LCD_t, metalDetector_t;

	/* WiringPi initialization */
	if(wiringPiSetup() != 0) {
		return(-1);
	}

	/* Configure pins */
	fd = setupPins();	// Save file descriptor

	if(fd == 766768) {
		printf("Error setting up LCD\n");
		resetDevice();
	}

	/* Initialize interrupt globals */
	detectorStatus = digitalRead(FSWITCH_1);
	motorStatus = digitalRead(FSWITCH_2);
	currentSpeed = 9;

	/* Configure interrupts */
	configInterrupts();
	
	/* Create threads */
	pthread_create(&LCD_t, NULL, LCDThread, NULL);
	pthread_create(&motor_t, NULL, motorThread, NULL);
	//pthread_create(&metalDetector_t, NULL, metalDetectorThread, NULL);

	/* Loop indefinitely, change message every 5s */
	for(;;) {

		/* Message 1 */
		lcm1602ClearDisplay(fd);
		lcm1602WriteLine(fd, "PiRover (C)2018 ", LINE_1);
		lcm1602WriteLine(fd, " Team Minecraft ", LINE_1);
		delayMicroseconds(5000000);

		/* Message 2 */
		lcm1602ClearDisplay(fd);
		lcm1602WriteLine(fd, "Atteberry Ñ Tran", LINE_1);
		lcm1602WriteLine(fd, "  Karmajian     ", LINE_1);
		delayMicroseconds(5000000);
	}

	return(0);
}

/* configInterrupts function
*  Configures the hw interrupts, resets the device if a failure occurs
*/
void configInterrupts() {

	if(wiringPiISR(SHUTDOWN_SW, INT_EDGE_FALLING, &shutdownDevice) != 0) {
		printf("Error setting up shutdown switch\n");
		//resetDevice();
	}
	else if(wiringPiISR(RESET_SW, INT_EDGE_FALLING, &resetDevice) != 0) {
		printf("Error setting up reset switch\n");
		//resetDevice();
	}
	else if(wiringPiISR(FSWITCH_1, INT_EDGE_BOTH, &detectorOnOff) != 0) {
		printf("Error setting up metal detector ON/OFF switch\n");
		//resetDevice();
	}
	else if(wiringPiISR(FSWITCH_2, INT_EDGE_BOTH, &motorOnOff) != 0) {
		printf("Error setting up motor ON/OFF switch\n");
		//resetDevice();
	}
	else if(wiringPiISR(MSWITCH_1, INT_EDGE_FALLING, &speedUp) != 0) {
		printf("Error setting up speed up switch\n");
		//resetDevice();
	}
	else if(wiringPiISR(MSWITCH_2, INT_EDGE_FALLING, &slowDown) != 0) {
		printf("Error setting up slow down switch\n");
		//resetDevice();
	}
}

/* shutdownDevice function
*  Shuts down the device
*/
void shutdownDevice() {

	int debounce = 0; // Debounce counter

	/* Software debounce */
	while(digitalRead(SHUTDOWN_SW) == SWITCH_ON) {
		debounce++;
	}

	/* Shutdown on button release */
	if(debounce >= 700) {

		/* Turn off LEDs */
		digitalWrite(LED_1, LED_OFF);
		digitalWrite(LED_2, LED_OFF);
		digitalWrite(LED_3, LED_OFF);
		digitalWrite(LED_4, LED_OFF);
		digitalWrite(LED_5, LED_OFF);
		digitalWrite(LED_6, LED_OFF);
		digitalWrite(SEVEN_SEG_3, LED_OFF);
		digitalWrite(SEVEN_SEG_2, LED_OFF);
		digitalWrite(SEVEN_SEG_1, LED_OFF);
		digitalWrite(SEVEN_SEG_0, LED_OFF);

		/* Count down to power off */
		powerOffMessage("Powering off... ");

		/* Shutdown */
		system("sudo shutdown -h now");
	}
}

/* resetDevice function
*  Resets the device
*/
void resetDevice() {

	int debounce = 0; // Debounce counter

	/* Software debounce */
	while(digitalRead(RESET_SW) == SWITCH_ON) {
		debounce++;
	}

	/* Restart on button release */
	if(debounce >= 700) {
		digitalWrite(LED_1, LED_OFF);
		digitalWrite(LED_2, LED_OFF);
		digitalWrite(LED_3, LED_OFF);
		digitalWrite(LED_4, LED_OFF);
		digitalWrite(LED_5, LED_OFF);
		digitalWrite(LED_6, LED_OFF);
		digitalWrite(SEVEN_SEG_3, LED_OFF);
		digitalWrite(SEVEN_SEG_2, LED_OFF);
		digitalWrite(SEVEN_SEG_1, LED_OFF);
		digitalWrite(SEVEN_SEG_0, LED_OFF);

		/* Count down to restart */
		powerOffMessage(" Restarting...  ");

		/* Restart */
		system("sudo shutdown -r now");
	}
}

/* detectorOnOff function
*  Turns the metal detector on and off
*/
void detectorOnOff() {

	/* Read detector switch */
	detectorStatus = digitalRead(FSWITCH_1);
}

/* motorOnOff function
*  Turns the motor on and off
*/
void motorOnOff() {

	/* Read motor switch */
	motorStatus = digitalRead(FSWITCH_2);
}

/* speedUp function
*  Increases the motor speed
*/
void speedUp() {

	int debounce = 0; // Debounce counter

	/* Software debounce */
	while(digitalRead(MSWITCH_2) == ENABLED) {
		debounce++;
	}

	/* Increase speed */
	if((debounce >= 700) && (currentSpeed > 1)) {

		currentSpeed--;		// Increase speed
		displaySpeed();		// Display speed on 7-seg display
	}
}

/* slowDown function
*  Decreases the motor speed
*/
void slowDown() {

	int debounce = 0; // Debounce counter

	/* Software debounce */
	while(digitalRead(MSWITCH_2) == ENABLED) {
		debounce++;
	}

	/* Decrease speed */
	if((debounce >= 700) && (currentSpeed < 9)) {

		currentSpeed++;		// Decrease speed
		displaySpeed();		// Display speed on 7-seg display
	}
}

/* powerOffMessage function
*  Displays a countdown to the LCD
*/
void powerOffMessage(char message[]) {

	/* Display message */
	lcm1602Clear(fd, LCD_BACKLIGHT_ON);
	lcm1602WriteLine(fd, message, LCD_LINE_1, LCD_BACKLIGHT_ON);

	/* Display countdown */
	lcm1602WriteLine(fd, "       10       ", LCD_LINE_2, LCD_BACKLIGHT_ON);
	delayMicroseconds(1000000);
	lcm1602WriteLine(fd, "        9       ", LCD_LINE_2, LCD_BACKLIGHT_ON);
	delayMicroseconds(1000000);
	lcm1602WriteLine(fd, "        8       ", LCD_LINE_2, LCD_BACKLIGHT_ON);
	delayMicroseconds(1000000);
	lcm1602WriteLine(fd, "        7       ", LCD_LINE_2, LCD_BACKLIGHT_ON);
	delayMicroseconds(1000000);
	lcm1602WriteLine(fd, "        6       ", LCD_LINE_2, LCD_BACKLIGHT_ON);
	delayMicroseconds(1000000);
	lcm1602WriteLine(fd, "        5       ", LCD_LINE_2, LCD_BACKLIGHT_ON);
	delayMicroseconds(1000000);
	lcm1602WriteLine(fd, "        4       ", LCD_LINE_2, LCD_BACKLIGHT_ON);
	delayMicroseconds(1000000);
	lcm1602WriteLine(fd, "        3       ", LCD_LINE_2, LCD_BACKLIGHT_ON);
	delayMicroseconds(1000000);
	lcm1602WriteLine(fd, "        2       ", LCD_LINE_2, LCD_BACKLIGHT_ON);
	delayMicroseconds(1000000);
	lcm1602WriteLine(fd, "        1       ", LCD_LINE_2, LCD_BACKLIGHT_ON);
	delayMicroseconds(1000000);
	lcm1602WriteLine(fd, "        0       ", LCD_LINE_2, LCD_BACKLIGHT_ON);
}

/* displaySpeed function
*  Displays the current speed on the 7-segment LED
*/
void displaySpeed() {

	switch(currentSpeed) {
		case 9:
			digitalWrite(SEVEN_SEG_3, LED_OFF);
			digitalWrite(SEVEN_SEG_2, LED_OFF);
			digitalWrite(SEVEN_SEG_1, LED_OFF);
			digitalWrite(SEVEN_SEG_0, LED_ON);
			break;
		case 8:
			digitalWrite(SEVEN_SEG_3, LED_OFF);
			digitalWrite(SEVEN_SEG_2, LED_OFF);
			digitalWrite(SEVEN_SEG_1, LED_ON);
			digitalWrite(SEVEN_SEG_0, LED_OFF);
			break;
		case 7:
			digitalWrite(SEVEN_SEG_3, LED_OFF);
			digitalWrite(SEVEN_SEG_2, LED_OFF);
			digitalWrite(SEVEN_SEG_1, LED_ON);
			digitalWrite(SEVEN_SEG_0, LED_ON);
			break;
		case 6:
			digitalWrite(SEVEN_SEG_3, LED_OFF);
			digitalWrite(SEVEN_SEG_2, LED_ON);
			digitalWrite(SEVEN_SEG_1, LED_OFF);
			digitalWrite(SEVEN_SEG_0, LED_OFF);
			break;
		case 5:
			digitalWrite(SEVEN_SEG_3, LED_OFF);
			digitalWrite(SEVEN_SEG_2, LED_ON);
			digitalWrite(SEVEN_SEG_1, LED_OFF);
			digitalWrite(SEVEN_SEG_0, LED_ON);
			break;
		case 4:
			digitalWrite(SEVEN_SEG_3, LED_OFF);
			digitalWrite(SEVEN_SEG_2, LED_ON);
			digitalWrite(SEVEN_SEG_1, LED_ON);
			digitalWrite(SEVEN_SEG_0, LED_OFF);
			break;
		case 3:
			digitalWrite(SEVEN_SEG_3, LED_OFF);
			digitalWrite(SEVEN_SEG_2, LED_ON);
			digitalWrite(SEVEN_SEG_1, LED_ON);
			digitalWrite(SEVEN_SEG_0, LED_ON);
			break;
		case 2:
			digitalWrite(SEVEN_SEG_3, LED_ON);
			digitalWrite(SEVEN_SEG_2, LED_OFF);
			digitalWrite(SEVEN_SEG_1, LED_OFF);
			digitalWrite(SEVEN_SEG_0, LED_OFF);
			break;
		case 1:
			digitalWrite(SEVEN_SEG_3, LED_ON);
			digitalWrite(SEVEN_SEG_2, LED_OFF);
			digitalWrite(SEVEN_SEG_1, LED_OFF);
			digitalWrite(SEVEN_SEG_0, LED_ON);
			break;
	}
}

/* motorThread function
*  The motor control thread
*/
void *motorThread(void *nullPtr) {

	double distance;				// Distance to object

	/* Move forward */
	L298Forward(EN_A, EN_B, IN_1, IN_2, IN_3, IN_4, 800/currentSpeed);

	/* Loop indefinitely */
	for(;;) {

		/* Get ultrasonic sensor reading */
		distance = getDistance(RM_TRIG, RM_ECHO);

		/* Check distance to object */
		while((distance > 0) && (distance <= 0.305)) {
			
			/* Stop */
			L298Brake(IN_1, IN_2, IN_3, IN_4);
			delayMicroseconds(500000);

			/* Reverse */
			L298Reverse(EN_A, EN_B, IN_1, IN_2, IN_3, IN_4, 800/currentSpeed);
			delayMicroseconds(500000/currentSpeed);

			/* Stop */
			L298Brake(IN_1, IN_2, IN_3, IN_4);
			delayMicroseconds(500000);

			/* Turn */
			L298Right(EN_A, EN_B, IN_1, IN_2, IN_3, IN_4, 800/currentSpeed);
			delayMicroseconds(500000/currentSpeed);

			/* Stop */
			L298Brake(IN_1, IN_2, IN_3, IN_4);
			delayMicroseconds(500000);

			/* Forward */
			L298Forward(EN_A, EN_B, IN_1, IN_2, IN_3, IN_4, 800/currentSpeed);
		}
	}
}

/* metalDetectorThread function
*  The metal detector control thread
*/
/*void *metalDetectorThread(void *nullPtr) {

	/* Loop indefinitely */
	for(;;) {
		
	}
}*/

