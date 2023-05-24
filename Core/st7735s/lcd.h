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
void lcdDrawIntNum(struct Point p, uint16_t num, uint8_t len, uint16_t frontColor, uint16_t backgroundColor, uint8_t sizeY);
void lcdDrawFloatNum(struct Point p, float num, uint8_t len, uint16_t frontColor, uint16_t backgroundColor, uint8_t sizeY);
void lcdDrawImg(struct Point p1,uint16_t length,uint16_t height,const uint8_t *img);

//颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE           	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40
#define BRRED 			 0XFC07
#define GRAY  			 0X8430
#define DARKBLUE      	 0X01CF
#define LIGHTBLUE      	 0X7D7C
#define GRAYBLUE       	 0X5458
#define LIGHTGREEN     	 0X841F
#define LGRAY 			 0XC618
#define LGRAYBLUE        0XA651
#define LBBLUE           0X2B12

#endif //ST7735S_LCD_H
