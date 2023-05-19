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
void lcdDrawChar(struct Point p,uint8_t ch,uint16_t charColor,uint16_t backgroundColor,uint8_t sizeY,uint8_t mode);
void lcdDrawString(struct Point p,const uint8_t *str,uint16_t charColor,uint16_t backgroundColor,uint8_t sizeY,uint8_t mode);
void lcdDrawImg(struct Point p1,uint16_t length,uint16_t height,const uint8_t *img);

//颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define RED           	 0x001F
#define BLUE           	 0xF800
#define GREEN         	 0x07E0
#define LIGHTBLUE        0xFFE0
#define DARKBLUE 		 0XBC40
#define GRAY  			 0X8430
#define BROWN      	     0X7D7C
#define PINK     	     0X841F

#endif //ST7735S_LCD_H
