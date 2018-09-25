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
