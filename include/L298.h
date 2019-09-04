/***********************************************************************************
*	{L298_H}
*	L298.h
*		by Austin Atteberry
*
*	DESCRIPTION:
*	Contains the function prototypes for the L298 Dual H-Bridge Motor Driver
*
************************************************************************************/

#ifndef _L298_H
#define _L298_H

int L298Setup(int enaPin, int enbPin, int pin1, int pin2, int pin3, int pin4);
int L298Forward(int enaPin, int enbPin, int pin1, int pin2, int pin3, int pin4, int speed);
int L298Reverse(int enaPin, int enbPin, int pin1, int pin2, int pin3, int pin4, int speed);
void L298Coast(int enaPin, int enbPin);
void L298Brake(int pin1, int pin2, int pin3, int pin4);
int L298Right(int enaPin, int enbPin, int pin1, int pin2, int pin3, int pin4, int speed);
int L298Left(int enaPin, int enbPin, int pin1, int pin2, int pin3, int pin4, int speed);

#endif