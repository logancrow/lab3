//controller.h
//deinition of state machine to control alarm clock and function declerations
//Logan Crow and Samantha Flaim
//Date Created: 9-19-18
//Date Last Modified: 9-19-18

#include "stdint.h"

#define sw1 (*((volatile uint32_t *)0x40024004))
#define sw2 (*((volatile uint32_t *)0x40024008))
#define sw3 (*((volatile uint32_t *)0x40024010))
#define sw4 (*((volatile uint32_t *)0x40024020))
	
#define main_menu    0
#define show_display 1
#define set_time     2
#define set_alarm    3

extern uint8_t hours;
extern uint8_t minutes;
extern uint8_t seconds;

extern uint8_t alarm_hours;
extern uint8_t alarm_minutes;
extern uint8_t alarm_enable;

//prototypes for functions that define what to do in state
//returns next state
int menu(void);
int display(void);
int time(void);
int alarm(void);

//sets global variable to 0
void InitializeGlobals(void);

//initializes PE0-PE3 to be inputs
void PortD_Init(void);

//pass a number and that number * 10ms will be waited
void DelayWait10ms(uint32_t);

