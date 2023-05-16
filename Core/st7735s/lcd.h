//
// Created by symct on 2023/5/16.
//

#ifndef ST7735S_LCD_H
#define ST7735S_LCD_H

#include "stm32f1xx.h"
#include "lcd_init.h"

struct Point{
    uint16_t x;
    uint16_t y;
};

void lcdFill(struct Point p1,struct Point p2,uint16_t color);//填充区域
void lcdDrawPoint(struct Point p,uint16_t color);//画点
void lcdDrawLine(struct Point p1,struct Point p2,uint16_t color);//画线
void lcdDrawRectangle(struct Point p1,struct Point p2,uint16_t color);//画矩形
void lcdDrawChar(struct Point p,uint8_t num);

//颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE           	 0x001F
#define BRED             0XF81F
#define GRAY  			 0X8430
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0

#endif //ST7735S_LCD_H
