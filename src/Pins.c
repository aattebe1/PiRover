/***********************************************************************************
*	{PINS_C}
*	Pins.c
*		by Austin Atteberry
*
*	PERFORMANCE:
*	Sets up the pins project pins
*
************************************************************************************/

#include<stdio.h>
#include<wiringPi.h>
#include "Pins.h"
#include "LCM1602.h"


/* setupPins function
* Sets pin modes and initial states 
*/
int setupPins() {

	/* Motor pin modes */
	pinMode(EN_A, PWM_OUTPUT);
	pinMode(EN_B, PWM_OUTPUT);
	pinMode(IN_1, OUTPUT);
	pinMode(IN_2, OUTPUT);
	pinMode(IN_3, OUTPUT);
	pinMode(IN_4, OUTPUT);

	/* LED pin modes */
	pinMode(LED_1, OUTPUT);
	pinMode(LED_2, OUTPUT);
	pinMode(LED_3, OUTPUT);
	pinMode(LED_4, OUTPUT);
	pinMode(LED_5, OUTPUT);
	pinMode(LED_6, OUTPUT);
	pinMode(SEVEN_SEG_3, OUTPUT);
	pinMode(SEVEN_SEG_2, OUTPUT);
	pinMode(SEVEN_SEG_1, OUTPUT);
	pinMode(SEVEN_SEG_0, OUTPUT);

	/* Switch pin modes */
	pinMode(SHUTDOWN_SW, INPUT);
	pinMode(RESET_SW, INPUT);
	pinMode(FSWITCH_1, INPUT);
	pinMode(FSWITCH_2, INPUT);
	pinMode(MSWITCH_1, INPUT);
	pinMode(MSWITCH_2, INPUT);

	/* Ultrasonic Sensor pin modes */
	pinMode(RM_TRIG, OUTPUT);
	pinMode(RM_ECHO, INPUT);

	/* Turn off internal pull-up/down resistors on all inputs */
	pullUpDnControl(SHUTDOWN_SW, PUD_OFF);
	pullUpDnControl(RESET_SW, PUD_OFF);
	pullUpDnControl(FSWITCH_1, PUD_OFF);
	pullUpDnControl(FSWITCH_2, PUD_OFF);
	pullUpDnControl(MSWITCH_1, PUD_OFF);
	pullUpDnControl(MSWITCH_2, PUD_OFF);
	pullUpDnControl(RM_ECHO, PUD_OFF);

	/* Set initial states for outputs */
	pwmWrite(EN_A, LOW);
	pwmWrite(EN_B, LOW);
	digitalWrite(IN_1, HIGH);
	digitalWrite(IN_2, HIGH);
	digitalWrite(IN_3, HIGH);
	digitalWrite(IN_4, HIGH);
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
	digitalWrite(RM_TRIG, LOW);

	/* Setup LCD pins */
	int fd = lcm1602Setup(0x27, 0, 0);	// File descriptor

	if(fd < 0) {
		return(766768);					// LCD setup error
	}

	/* Delay 0.5s for inputs to stablize */
	delayMicroseconds(500000);

	return(fd);
}