// main.c
// Runs on TM4C123
// This program periodically samples ADC channel 0 and stores the
// result to a global variable that can be accessed with the JTAG
// debugger and viewed with the variable watch feature.
// Daniel Valvano
// September 5, 2015

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// center of X-ohm potentiometer connected to PE3/AIN0
// bottom of X-ohm potentiometer connected to ground
// top of X-ohm potentiometer connected to +3.3V 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "ADCSWTrigger.h"
#include "../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include "ST7735.h"
#include "fixed.h"
#include "Timer0A.h" 
#include "line.h"
#include "controller.h"
#include "alarm.h"

#define PF1             (*((volatile uint32_t *)0x40025008))
#define PF2             (*((volatile uint32_t *)0x40025010))
#define PF3             (*((volatile uint32_t *)0x40025020))
#define PF4  					  (*((volatile uint32_t *)0x40025040))

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
void PortF_Init(void);


int main(void){
  PLL_Init(Bus80MHz);    	// 80 MHz
	Timer0A_Init1Hz();               // set up Timer0A for 1 Hz interrupts
	PortD_Init();
  //PortE4_Init();	
	PortF_Init();
	ST7735_InitR(INITR_REDTAB);
	ST7735_FillScreen(ST7735_BLACK);       
	//Timer1_Init100Hz();
	InitializeGlobals();
  EnableInterrupts();
	uint8_t CS = main_menu;
  while(1){
		if(CS == main_menu) CS = menu();
		if(CS == show_display) CS = display();
		if(CS == set_time) CS = time();
		if(CS == set_alarm) CS = alarm(); 
  }
}



// Make PF2 an output, enable digital I/O, ensure alt. functions off
void PortF_Init(void){ 
  SYSCTL_RCGCGPIO_R |= 0x20;        // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R&0x20)==0){}; // allow time for clock to start
                                    // 2) no need to unlock PF2, PF4
  GPIO_PORTF_PCTL_R &= ~0x000F0FF0; // 3) regular GPIO
  GPIO_PORTF_AMSEL_R &= ~0x16;      // 4) disable analog function on PF2, PF1
  GPIO_PORTF_DIR_R |= 0x06;         // 5) set direction to output
  GPIO_PORTF_PUR_R |= 0x10;         // 5) pullup for PF4
  GPIO_PORTF_AFSEL_R &= ~0x16;      // 6) regular port function
  GPIO_PORTF_DEN_R |= 0x16;         // 7) enable digital port
}
