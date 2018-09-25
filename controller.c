//controller.c
//
//Logan Crow and Samantha Flaim
//Date Created: 9-19-18
//Date Last Modified: 9-19-18

#include "controller.h"
#include "ST7735.h"
#include "timer0.h"
#include "../inc/tm4c123gh6pm.h"
#include "alarm.h"
#include "stdio.h"
#include "line.h"

uint8_t hours;
uint8_t minutes;
uint8_t seconds;

uint8_t alarm_hours;
uint8_t alarm_minutes;
uint8_t alarm_enable;

//sets global vaiables to 0
void InitializeGlobals(){
	//initialize globals to 0
	alarm_enable = 0;
	hours = 0;
	minutes = 0;
	seconds = 0;
	alarm_hours = 0;
	alarm_minutes = 0;
	flag= 0;
}

//initializes PE0-PE3 to be inputs
void PortD_Init(){
	SYSCTL_RCGCGPIO_R |= 0x08;
  while((SYSCTL_PRGPIO_R&0x08)!=0x08){}; // allow time for clock to start		
	GPIO_PORTD_DEN_R |= 0x0F;	//PD0-3 enable
	GPIO_PORTD_DIR_R &= 0xF0; //PD0-3 input	
  GPIO_PORTD_AFSEL_R &= ~0x0F; //disable alternate function
}

//pass a number and that number * 10ms will be waited
void DelayWait10ms(uint32_t n){
	uint32_t volatile time;
  while(n){
    time = 727240*2/91;  //10msec
    while(time){
	  	time--;
    }
    n--;
  }
}

int menu(){
	DelayWait10ms(50);            //debounce
	ST7735_SetCursor(0,0);
	ST7735_OutString("Main_menu\r");  
	ST7735_OutString("Dispay Mode:  sw1\r");
	ST7735_OutString("Set Time:     sw2\r");
	ST7735_OutString("Set Alarm:    sw3\r");
	ST7735_OutString("Alarm Off:    sw4\r");
	while(!sw1 && !sw2 && !sw3){
		if((hours == alarm_hours) && (minutes == alarm_minutes) && (seconds == 0) && alarm_enable){  //if alarm time is reached, turn it on
	    Alarm_On();		
		}
		if(sw4){
		  Alarm_Off();
		}
	}
	ST7735_FillScreen(ST7735_BLACK);   //clear screen
	//return next state
	if(sw1) return show_display;  
	if(sw2) return set_time;
	if(sw3) return set_alarm;
	else return main_menu;
}

int display(){
	DelayWait10ms(50);            //debounce
	while(!sw1){
		ST7735_SetCursor(0,0);
		ST7735_OutString("Main Menu:  sw1");
		ST7735_SetCursor(0,1);
		ST7735_OutString("Alarm Off:  sw4");
	  char time[6];
		ST7735_SetCursor(0,2);
		sprintf(time,"%02d:%02d:%02d",hours,minutes,seconds);
		ST7735_OutString(time);
		drawCircle(48,64,93);
		drawClockDigits();
		drawSecondHand(seconds);
		drawMinuteHand(minutes);
		drawHourHand(hours,minutes);
		if((hours == alarm_hours) && (minutes == alarm_minutes) && (seconds == 0) && alarm_enable){  //if alarm time is reached, turn it on
		  Alarm_On();			
		}
		if(sw4){
		  Alarm_Off();
		}
	}
	ST7735_FillScreen(ST7735_BLACK);   //clear screen
	//return to next state
	if(sw1) return main_menu;
	else return show_display;
}
	
int time(){
	DelayWait10ms(50);            //debounce
	DisableInterrupts();
	seconds = 0;
	while(!sw1){
		ST7735_SetCursor(0,0);
		ST7735_OutString("Main Menu:    sw1\r");
	  ST7735_OutString("Hour Up:      sw2\r");
	  ST7735_OutString("Minute Up:    sw3\r");
		ST7735_OutString("Set_Time: ");  //replace this with display graphics
		char time[6];
		sprintf(time,"%02d:%02d",hours,minutes);
		ST7735_OutString(time);
		if(sw2){
			DelayWait10ms(10);        //debounce
			hours = (hours + 1)%24;
			ST7735_FillScreen(ST7735_BLACK);   //clear screen
		}
		if(sw3){
			DelayWait10ms(10);        //debounce
			minutes = (minutes +1)%60;
			ST7735_FillScreen(ST7735_BLACK);   //clear screen
		}
	}
	EnableInterrupts();
	ST7735_FillScreen(ST7735_BLACK);   //clear screen
	//return to next state
	if(sw1) return main_menu;
	else return set_time;	
}

int alarm(){
	DelayWait10ms(50);            //debounce
	alarm_enable = 0;    //don't allow alarm to go off while setting it
	while((!sw1) && (!sw4)){
		ST7735_SetCursor(0,0);
	  ST7735_OutString("Set Alarm:      sw1\r");
	  ST7735_OutString("Hour Up:        sw2\r");
	  ST7735_OutString("Minute Up:      sw3\r");
  	ST7735_OutString("Disable Alarm:  sw4\r");
		ST7735_OutString("Set_Alarm: ");      //replace with graphics
		char time[6];
		sprintf(time,"%02d:%02d",alarm_hours,alarm_minutes);
		ST7735_OutString(time);
		if(sw2){
			DelayWait10ms(10);        //debounce
			alarm_hours = (alarm_hours + 1)%24;
			ST7735_FillScreen(ST7735_BLACK);   //clear screen
		}
		if(sw3){
			DelayWait10ms(10);        //debounce
			alarm_minutes = (alarm_minutes +1)%60;
			ST7735_FillScreen(ST7735_BLACK);   //clear screen
		}		
	}
	ST7735_FillScreen(ST7735_BLACK);   //clear screen	
	if(sw1){
		alarm_enable = 1;
		return main_menu;
	}
	if(sw4){
		return main_menu;
	}
	else return set_alarm;
}
