/***********************************************************************************
*	{PINS_H}
*	Pins.h
*		by Austin Atteberry
*
*	DESCRIPTION:
*	Defines constants, pin assignments, and function prototypes
*
************************************************************************************/

#ifndef _PINS_H
#define _PINS_H

#define LED_OFF 1
#define LED_ON 0
#define SWITCH_OFF 1
#define SWITCH_ON 0

/* LCD */
#define LCD_SDA 8		// I2C Data - Pin 3
#define LCD_SCL 9		// I2C Clock - Pin 5

/* LEDs */
#define LED_1 7			// Power ON - Pin 7
#define LED_2 0			// Motor ON - Pin 11
#define LED_3 2			// Metal Detector ON - Pin 13
#define LED_4 3			// Obstacle Detected - Pin 15
#define LED_5 4			// Metal Not Detected - Pin 16
#define LED_6 5			// Metal Detected - Pin 18
#define SEVEN_SEG_3 12	// BCD bit 3 (MSB) - Pin 19
#define SEVEN_SEG_2 13	// BCD bit 2 - Pin 21
#define SEVEN_SEG_1 6	// BCD bit 1 - Pin 22
#define SEVEN_SEG_0 14	// BCD bit 0 (LSB) - Pin 23

/* Switches */
#define SHUTDOWN_SW 10	// Shutdown switch - Pin 24
#define RESET_SW 11		// Reset switch - Pin 26
#define FSWITCH_1 30	// Metal detector ON/OFF - Pin 27
#define FSWITCH_2 31	// Motor ON/OFF - Pin 28
#define MSWITCH_1 21	// Speed increase - Pin 29
#define MSWITCH_2 22	// Speed decrease - Pin 31

/* Motor Control */
#define EN_A 1			// Right Motor Enable - Pin 12
#define EN_B 23			// Left Motor Enable - Pin 33
#define IN_1 26			// Right Motor Direction 1 - Pin 32
#define IN_2 24			// Right Motor Direction 2 - Pin 35
#define IN_3 27			// Left Motor Direction 1 - Pin 36
#define IN_4 25			// Left Motor Direction 2 - Pin 37

/* Metal Detector */
#define MD_TXD 15		// Send to detector - Pin 8
#define MD_RXD 16		// Receive from detector - Pin 10

/* Ultrasonic Sensor */
#define RM_TRIG 28		// Ranging Module Trigger - Pin 38
#define RM_ECHO 29		// Ranging Module Echo - Pin 40

/* Functions */
int setupPins();		// Configures GPIO pins

#endif
