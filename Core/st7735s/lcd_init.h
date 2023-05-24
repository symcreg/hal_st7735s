//
// Created by symct on 2023/5/16.
//
/*
1	VCC	液晶屏电源正(3.3V~5V)
2	GND	液晶屏电源地
3	GND	液晶屏电源地
4	NC	无定义，保留
5	NC	无定义，保留
6	NC	无定义，保留
7	CLK	液晶屏SPI总线时钟信号
8	SDA	液晶屏SPI总线写数据信号
9	RS	液晶屏寄存器/数据选择信号，低电平：寄存器，高电平：数据
10	RST	液晶屏复位信号，低电平复位
11	CS	液晶屏片选信号，低电平使能
*/
#ifndef ST7735S_LCD_INIT_H
#define ST7735S_LCD_INIT_H

#include "stm32f1xx_hal.h"

#define lcdHeight 160
#define lcdWidth 128

#define clkSet() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET)
#define clkReset() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET)

#define sdaSet() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET)
#define sdaReset() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET)

#define rstSet() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET)
#define rstReset() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET)

#define rsSet() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET)
#define rsReset() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET)

#define csSet() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET)
#define csReset() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET)

void lcdWrite(uint8_t data);
void lcdWriteData8(uint8_t data);
void lcdWriteData(uint16_t data);
void lcdWriteCommand(uint8_t command);
void lcdSetAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void lcdReset();
void lcdInit();


#endif //ST7735S_LCD_INIT_H
