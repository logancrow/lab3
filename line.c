//line.c
//function definition for ST7735_Line
//Logan Crow and Samantha Flaim
//Date Created: 9-17-18
//Date Last Modified: 9-19-18
#include "stdint.h"
#include "line.h"
#include "ST7735.h"
#include "PLL.h"
#include "stdlib.h"


void drawCircle (uint16_t radius, uint16_t center_x, uint16_t center_y) {
	uint16_t x = radius;
	uint16_t y = 0;
	int16_t e = -radius;
	
	while (y <= x) {
		ST7735_DrawPixel(x + center_x, y + center_y, ST7735_WHITE);
		ST7735_DrawPixel(x + center_x, center_y - y, ST7735_WHITE);
		ST7735_DrawPixel(center_x - x, y + center_y, ST7735_WHITE);
		ST7735_DrawPixel(center_x - x, center_y - y, ST7735_WHITE);
		ST7735_DrawPixel(y + center_x, x + center_y, ST7735_WHITE);
		ST7735_DrawPixel(center_x - y, center_y + x, ST7735_WHITE);
		ST7735_DrawPixel(center_x + y, center_y - x, ST7735_WHITE);
		ST7735_DrawPixel(center_x - y, center_y - x, ST7735_WHITE);
		e += 2 * y + 1;
		y++;
		if (e >= 0) {
			e -= (2 * x - 1);
			x--;
		}
	}
}
void drawClockDigits(void) {
	//12
	ST7735_DrawChar(60, 35, '1', ST7735_WHITE, ST7735_BLACK, 1);
	ST7735_DrawChar(64, 35, '2', ST7735_WHITE, ST7735_BLACK, 1);
	//11
	ST7735_DrawChar(32, 42, '1', ST7735_WHITE, ST7735_BLACK, 1);
	ST7735_DrawChar(36, 42, '1', ST7735_WHITE, ST7735_BLACK, 1);
	//10
	ST7735_DrawChar(12, 62, '1', ST7735_WHITE, ST7735_BLACK, 1);
	ST7735_DrawChar(16, 62, '0', ST7735_WHITE, ST7735_BLACK, 1);
	//9
	ST7735_DrawChar(6, 88, '9', ST7735_WHITE, ST7735_BLACK, 1);
	//8
	ST7735_DrawChar(14, 116, '8', ST7735_WHITE, ST7735_BLACK, 1);
	//7
	ST7735_DrawChar(32, 138, '7', ST7735_WHITE, ST7735_BLACK, 1);
	//6
	ST7735_DrawChar(61, 144, '6', ST7735_WHITE, ST7735_BLACK, 1);
	//5
	ST7735_DrawChar(92, 138, '5', ST7735_WHITE, ST7735_BLACK, 1);
	//4
	ST7735_DrawChar(109, 118, '4', ST7735_WHITE, ST7735_BLACK, 1);
	//3
	ST7735_DrawChar(115, 92, '3', ST7735_WHITE, ST7735_BLACK, 1);
	//2
	ST7735_DrawChar(110, 64, '2', ST7735_WHITE, ST7735_BLACK, 1);
	//1
	ST7735_DrawChar(90, 42, '1', ST7735_WHITE, ST7735_BLACK, 1);
}

const uint16_t xCoordinates[60] = {
	//12 O'Clock to 2 O'Clock
	 64,  68,  72,  76,  80,  84,  88,  91,  94,  96,  99, 101, 102, 103, 104,
	//3 O'Clock to 5 O'Clock
	104, 104, 103, 102, 101,  99,  96,  94,  91,  88,  84,  80,  76,  72,  68, 
	//6 O'Clock to 8 O'Clock
	 64,  60,  56,  52,  48,  44,  40,  37,  34,  32,  29,  27,  26,  25,  24,
	//9 O'Clock to 11 O'Clock
	 24,  24,  25,  26,  27,  29,  32,  34,  37,  40,  44,  48,  52,  56,  60 
};

const uint16_t yCoordinates[60] = {
	//12 O'Clock to 2 O'Clock
	 53,  53,  54,  55,  56,  58,  61,  63,  66,  69,  73,  77,  81,  85,  89, 
	//3 O'Clock to 5 O'Clock
	 93,  97, 101, 105, 109, 113, 117, 120, 123, 125, 128, 130, 131, 132, 133,
	//6 O'Clock to 8 O'Clock
	133, 133, 132, 131, 130, 128, 125, 123, 120, 117, 113, 109, 105, 101, 97,
	//9 O'Clock to 11 O'Clock
	 93,  89,  85,  81,  77,  73,  69,  66,  63,  61,  58,  56,  55,  54,  53
};


const uint16_t xHour2Coordinates[12] = {
	//12 O'Clock to 2 O'Clock
	 64,  74,  81,
	//3 O'Clock to 5 O'Clock
	 84,  81,  74,
	//6 O'Clock to 8 O'Clock
	 64,  54,  47,
	//9 O'Clock to 11 O'Clock 
	 44,  47,  54
};

const uint16_t xHourCoordinates[60] = {
	//12 O'Clock to 2 O'Clock
	 64,  66,  68,  70,  72,  74,  76,  77,  79,  80,  81,  82,  83,  83,  84,  
	//3 O'Clock to 5 O'Clock
	 84,  84,  83,  83,  82,  81,  80,  79,  77,  76,  74,  72,  70,  68,  66,
	//6 O'Clock to 8 O'Clock
	 64,  62,  60,  58,  56,  54,  52,  51,  49,  48,  47,  46,  45,  44,  44,
	//9 O'Clock to 11 O'Clock 
	 44,  44,  44,  45,  46,  47,  48,  49,  51,  52,  54,  56,  58,  60,  62
};

const uint16_t yHour2Coordinates[12] = {
	//12 O'Clock to 2 O'Clock
	 73,  76,  83,
	//3 O'Clock to 5 O'Clock
	 93, 103, 110,
	//6 O'Clock to 8 O'Clock
	113, 110, 103,
	//9 O'Clock to 11 O'Clock 
	 93,  83,  76
};

const uint16_t yHourCoordinates[60] = {
	//12 O'Clock to 2 O'Clock
	 73,  73,  74,  74,  75,  76,  77,  78,  80,  81,  83,  85,  87,  89,  91,
	//3 O'Clock to 5 O'Clock
	 93,  95,  97,  99, 101, 103, 105, 106, 108, 109, 110, 111, 112, 113, 113,
	//6 O'Clock to 8 O'Clock
	113, 113, 113, 112, 111, 110, 109, 108, 106, 105, 103, 101,  99,  97,  95,
	//9 O'Clock to 11 O'Clock 
	 93,  91,  89,  87,  85,  83,  81,  80,  78,  77,  76,  75,  74,  74,  73
};

void drawMinuteHand(uint16_t minutes) {
	if (minutes == 0) {
		ST7735_Line(64, 93, xCoordinates[59], yCoordinates[59], ST7735_BLACK);
		ST7735_Line(64, 93, xCoordinates[minutes], yCoordinates[minutes], ST7735_WHITE);
	}
	else {
		ST7735_Line(64, 93, xCoordinates[minutes - 1], yCoordinates[minutes - 1], ST7735_BLACK);
		ST7735_Line(64, 93, xCoordinates[minutes], yCoordinates[minutes], ST7735_WHITE);
	}
}

void drawSecondHand(uint16_t seconds) {
	if (seconds == 0) {
			ST7735_Line(64, 93, xCoordinates[59], yCoordinates[59], ST7735_BLACK);
			ST7735_Line(64, 93, xCoordinates[seconds], yCoordinates[seconds], ST7735_RED);
	}
	else {
		ST7735_Line(64, 93, xCoordinates[seconds - 1], yCoordinates[seconds - 1], ST7735_BLACK);
		ST7735_Line(64, 93, xCoordinates[seconds], yCoordinates[seconds], ST7735_RED);
	}
}

void drawHourHand(uint16_t hours, uint16_t minutes) {
	if (hours == 0 && minutes < 12) {
			ST7735_Line(64, 93, xHourCoordinates[59], yHourCoordinates[59], ST7735_BLACK);
			ST7735_Line(64, 93, xHourCoordinates[hours], yHourCoordinates[hours], ST7735_WHITE);
	}
	else {
		ST7735_Line(64, 93, xHourCoordinates[(hours*5)+(minutes/12)-1], yHourCoordinates[(hours*5)+(minutes/12)-1], ST7735_BLACK);
		ST7735_Line(64, 93, xHourCoordinates[(hours*5)+(minutes/12)], yHourCoordinates[(hours*5)+(minutes/12)], ST7735_WHITE);
	}
}

void test(void) {
		for (int i = 0; i < 60; i++) {
			ST7735_Line(64, 93, xHourCoordinates[i], yHourCoordinates[i], ST7735_WHITE);
	}
}

void DrawLineDown (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
	double dx, dy, delta;
	int16_t yi;
	uint16_t y;
	
	dx = x2 - x1;
	dy = y2 - y1;
	yi = 1;
	if (dy < 0) {
		yi = -1;
		dy = -dy;
	}
	delta = 2 * dy - dx;
	y = y1;
	
	for (int x = x1; x <= x2; x++) {
		ST7735_DrawPixel(x, y, color);
		if (delta > 0) {
			y += yi;
			delta -= 2 * dx;
		}
		delta += 2 * dy;
	}
}

void DrawLineUp (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
	double dx, dy, delta;
	int16_t xi;
	uint16_t x;
	
	dx = x2 - x1;
	dy = y2 - y1;
	xi = 1;
	if (dx < 0) {
		xi = -1;
		dx = -dx;
	}
	delta = 2 * dx - dy;
	x = x1;
	
	for (int y = y1; y <= y2; y++) {
		ST7735_DrawPixel(x, y, color);
		if (delta > 0) {
			x += xi;
			delta -= 2 * dy;
		}
		delta += 2 * dx;
	}
}

//************* ST7735_Line********************************************
//  Draws one line on the ST7735 color LCD
//  Inputs: (x1,y1) is the start point
//          (x2,y2) is the end point
// x1,x2 are horizontal positions, columns from the left edge
//               must be less than 128
//               0 is on the left, 126 is near the right
// y1,y2 are vertical positions, rows from the top edge
//               must be less than 160
//               159 is near the wires, 0 is the side opposite the wires
//        color 16-bit color, which can be produced by ST7735_Color565() 
// Output: none
void ST7735_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){
  //for testing purposes to make endpoints visible on LCD
	/*ST7735_DrawPixel(x1 + 1, y1, ST7735_YELLOW);
	ST7735_DrawPixel(x1, y1 + 1, ST7735_YELLOW);
	ST7735_DrawPixel(x1 + 1, y1 + 1, ST7735_YELLOW);
	ST7735_DrawPixel(x1 - 1, y1, ST7735_YELLOW);
	ST7735_DrawPixel(x1, y1 - 1, ST7735_YELLOW);
	ST7735_DrawPixel(x1 - 1, y1 - 1, ST7735_YELLOW);
	ST7735_DrawPixel(x1 - 1, y1 + 1, ST7735_YELLOW);
	ST7735_DrawPixel(x1 + 1, y1 - 1, ST7735_YELLOW);
	ST7735_DrawPixel(x1, y1, ST7735_YELLOW);
	
	ST7735_DrawPixel(x2 + 1, y2, ST7735_YELLOW);
	ST7735_DrawPixel(x2, y2 + 1, ST7735_YELLOW);
	ST7735_DrawPixel(x2 + 1, y2 + 1, ST7735_YELLOW);
	ST7735_DrawPixel(x2 - 1, y2, ST7735_YELLOW);
	ST7735_DrawPixel(x2, y2 - 1, ST7735_YELLOW);
	ST7735_DrawPixel(x2 - 1, y2 - 1, ST7735_YELLOW);
	ST7735_DrawPixel(x2 - 1, y2 + 1, ST7735_YELLOW);
	ST7735_DrawPixel(x2 + 1, y2 - 1, ST7735_YELLOW);
	ST7735_DrawPixel(x2, y2, ST7735_YELLOW);*/
	
  //make sure pixels are within area of screen
  if ((x1 < 128) && (y1 < 160)){
    //horizontal line
    if (x1 == x2){
      if (y1 < y2){
        for (int y = y1; y <= y2; y++){
          ST7735_DrawPixel(x1, y, color);
        }
      }
      else if (y1 > y2){
        for (int y = y2; y <= y1; y++){
          ST7735_DrawPixel(x1, y, color);
        }
      }
    }
    //vertical line
    else if (y1 == y2){
      if (x1 < x2){
        for (int x = x1; x <= x2; x++){
          ST7735_DrawPixel(x, y1, color);
        }
      }
      else if (x1 > x2){
        for (int x = x2; x <= x1; x++){
          ST7735_DrawPixel(x, y1, color);
        }
      }
    }
    //diagonal line
    else {
			if (abs(y2 - y1) < abs(x2 - x1)) {
				if (x1 > x2) {
					DrawLineDown(x2, y2, x1, y1, color);
				}
				else {
					DrawLineDown(x1, y1, x2, y2, color);
				}
			}
			else {
				if (y1 > y2) {
					DrawLineUp (x2, y2, x1, y1, color);
				}
				else {
					DrawLineUp(x1, y1, x2, y2, color);
				}
			}
    }
  }
}
