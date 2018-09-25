// Alarm.c
// Runs on LM4F120/TM4C123
// 
// Logan Crow and Samantha Flaim
// 9-19-18

#include "alarm.h"
#include "../inc/tm4c123gh6pm.h"

#define PF1             (*((volatile uint32_t *)0x40025008))

int buffer = 0;

// ***************** TIMER1_Init100Hz ****************
// Activate TIMER1 interrupts to run user task periodically at 100 Hz
// Inputs:  none
// Outputs: none
void Timer1_Init100Hz(){
  SYSCTL_RCGCTIMER_R |= 0x02;   // 0) activate TIMER1
  TIMER1_CTL_R = 0x00000000;    // 1) disable TIMER1A during setup
  TIMER1_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER1_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER1_TAILR_R = 799999;    // 4) reload value
  TIMER1_TAPR_R = 0;            // 5) bus clock resolution
  TIMER1_ICR_R = 0x00000001;    // 6) clear TIMER1A timeout flag
  TIMER1_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0xFFFF00FF)|0x00008000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 37, interrupt number 21
  NVIC_EN0_R = 1<<21;           // 9) enable IRQ 21 in NVIC
}

void Timer1A_Handler(void){
	TIMER1_ICR_R = TIMER_ICR_TATOCINT;
	//if(buffer == 25805){
	PE4 ^= 0x10;         //toggle PE4
	PF1 ^= 0x02;
	//}
	//buffer = (buffer + 1)%25806;
}

//initializes PE4 to be output
void PortE4_Init(){
	SYSCTL_RCGCGPIO_R |= 0x10;        // activate clock for Port E
  while((SYSCTL_PRGPIO_R&0x10)==0){}; // allow time for clock to start
	GPIO_PORTE_AMSEL_R &=~ 0x10;       //disable analog function
	GPIO_PORTE_PCTL_R &= ~0x000F0000; // regular GPIO
	GPIO_PORTE_DIR_R |= 0x10;         // set direction to input
	GPIO_PORTE_AFSEL_R &= ~0x10;      // regular port function
	GPIO_PORTE_DEN_R |= 0x10;         //enable digital
}

//enables timer, causing speaker to make noise
void Alarm_On(){
	TIMER1_CTL_R = 0x00000001;    // enable TIMER1A
}

//disables timer, causing speaker to stop
void Alarm_Off(){
	TIMER1_CTL_R = 0x00000000;    // disable TIMER1A
}
