/***********************************************************************************
*	{HCSR04_C}
*	HCSR04.c
*		by Austin Atteberry
*
*	PERFORMANCE:
*	Defines the functions used to measure distance with the HC-SR04 module
*
************************************************************************************/

/* Header files */
#include<stdio.h>
#include<sys/time.h>
#include<wiringPi.h>

/* getDistance function 
*  Returns the distance from the ranging module to an object 
*/
double getDistance(int trigPin, int echoPin) {

	double distance;				// Distance to the object
	struct timeval currentTime;		// Current time
	double startPulse;				// Start time of pulse
	double stopPulse;				// Stop time of pulse
	double timeTraveled;			// Duration of echo pulse

	/* Send trigger signal */
	digitalWrite(trigPin, HIGH);	// Set the pin high
	delayMicroseconds(10);			// Delay 10µs
	digitalWrite(trigPin, LOW);		// Set the pin low

	gettimeofday(&currentTime, NULL);			// Get current time
	startPulse = (double)currentTime.tv_usec;	// Set starting time

	/* Wait for echo to go high */
	do {
		gettimeofday(&currentTime, NULL);			// Get current time
		startPulse = (double)currentTime.tv_usec;	// Update starting time
	}while(digitalRead(echoPin) == LOW);

		gettimeofday(&currentTime, NULL);			// Get current time
		stopPulse = (double)currentTime.tv_usec;	// Get stopping time

	/* Wait for echo to go low */
	do {
		gettimeofday(&currentTime, NULL);			// Get current time
		stopPulse = (double)currentTime.tv_usec;	// Update stopping time
	}while(digitalRead(echoPin) == HIGH);

	/* Calculate distance */
	timeTraveled = (stopPulse - startPulse) / 2000000;
	distance = 343 * timeTraveled;

	return(distance);
}
