// Alarm.h
// Runs on LM4F120/TM4C123
// function definitions for alarm.c
// Logan Crow and Samantha Flaim
// 9-19-18

#include "stdint.h"

#define PE4 (*((volatile uint32_t *)0x40024040))

// ***************** TIMER1_Init100Hz ****************
// Activate TIMER1 interrupts to run user task periodically at 100 Hz
// Inputs:  none
// Outputs: none
void Timer1_Init100Hz(void);

//handler routine for timer 1A, toggles PE4
void Timer1A_Handler(void);

//initializes PE4 to be output
void PortE4_Init(void);

//enables timer, causing speaker to make noise
void Alarm_On(void);

//disables timer, causing speaker to stop
void Alarm_Off(void);
