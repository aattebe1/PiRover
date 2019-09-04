/***********************************************************************************
*	{PIROVER_H}
*	PiRover.h
*		by Austin Atteberry
*
*	DEFINITIONS:
*	Function prototypes for the PiRover
*
************************************************************************************/

#ifndef _PIROVER_H
#define _PIROVER_H

/* Functions */
void configInterrupts();
void powerOffMessage(char message[]);
void displaySpeed();

/* Interrupts */
void shutdownDevice();
void resetDevice();
void detectorOnOff();
void speedUp();
void slowDown();

/* Threads */
void *motorThread(void *nullPtr);
void *metalDetectorThread(void *nullPtr);

#endif