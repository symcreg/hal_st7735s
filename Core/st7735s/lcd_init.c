//
// Created by symct on 2023/5/16.
//
#include "lcd_init.h"



void lcdWrite(uint8_t data){
    csReset();//将LCD片选信号拉低，表示开始通信
    for(uint8_t i=0;i<8;i++){
        if(data&0x80){//判断最高位是否是1
            sdaSet();//设置lcd数据信号
        }else{
            sdaReset();
        }
        clkReset();
        clkSet();//将LCD的时钟信号拉高，表示数据有效
        data<<=1;//左移一位，准备发送下一位
    }
    csSet();//将LCD片选信号拉高，表示结束通信
}
void lcdWriteData(uint8_t data){
    lcdWrite(data);
}
void lcdWriteCommand(uint8_t command){
    rsReset();//低电平传输指令
    lcdWrite(command);
    rsSet();//高电平传输数据
}
void lcdSetAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2){
    lcdWriteCommand(0x2a);//列地址设置
    lcdWriteData(0x00);
    lcdWriteData(x1);
    lcdWriteData(0x00);
    lcdWriteData(x2);
    lcdWriteCommand(0x2b);//行地址设置
    lcdWriteData(0x00);
    lcdWriteData(y1);
    lcdWriteData(0x00);
    lcdWriteData(y2);
    lcdWriteCommand(0x2c);//写储存器
}
void lcdReset(){
    rstReset();
    HAL_Delay(10);
    rstSet();
    HAL_Delay(100);
}
void lcdInit(){
    //复制官方的程序进行初始化

    lcdReset();//Reset before LCD Init.

    //LCD Init For 1.44Inch LCD Panel with ST7735R.
    lcdWriteCommand(0x11);//Sleep exit
    HAL_Delay(120);

    //ST7735R Frame Rate	 4
    lcdWriteCommand(0xB1);
    lcdWriteData(0x01);
    lcdWriteData(0x2C);
    lcdWriteData(0x2D);

    lcdWriteCommand(0xB2);
    lcdWriteData(0x01);
    lcdWriteData(0x2C);
    lcdWriteData(0x2D);

    lcdWriteCommand(0xB3);
    lcdWriteData(0x01);
    lcdWriteData(0x2C);
    lcdWriteData(0x2D);
    lcdWriteData(0x01);
    lcdWriteData(0x2C);
    lcdWriteData(0x2D);

    lcdWriteCommand(0xB4); //Column inversion
    lcdWriteData(0x07);

    //ST7735R Power Sequence
    lcdWriteCommand(0xC0);
    lcdWriteData(0xA2);
    lcdWriteData(0x02);
    lcdWriteData(0x84);
    lcdWriteCommand(0xC1);
    lcdWriteData(0xC5);

    lcdWriteCommand(0xC2);
    lcdWriteData(0x0A);
    lcdWriteData(0x00);

    lcdWriteCommand(0xC3);
    lcdWriteData(0x8A);
    lcdWriteData(0x2A);
    lcdWriteCommand(0xC4);
    lcdWriteData(0x8A);
    lcdWriteData(0xEE);

    lcdWriteCommand(0xC5); //VCOM
    lcdWriteData(0x0E);

    lcdWriteCommand(0x36); //MX, MY, RGB mode
    lcdWriteData(0xA0); //竖屏C8 横屏08 A8
//	lcd_write_data(0xC0); //竖屏C8 横屏08 A8

    //ST7735R Gamma Sequence
    lcdWriteCommand(0xe0);
    lcdWriteData(0x0f);
    lcdWriteData(0x1a);
    lcdWriteData(0x0f);
    lcdWriteData(0x18);
    lcdWriteData(0x2f);
    lcdWriteData(0x28);
    lcdWriteData(0x20);
    lcdWriteData(0x22);
    lcdWriteData(0x1f);
    lcdWriteData(0x1b);
    lcdWriteData(0x23);
    lcdWriteData(0x37);
    lcdWriteData(0x00);
    lcdWriteData(0x07);
    lcdWriteData(0x02);
    lcdWriteData(0x10);

    lcdWriteCommand(0xe1);
    lcdWriteData(0x0f);
    lcdWriteData(0x1b);
    lcdWriteData(0x0f);
    lcdWriteData(0x17);
    lcdWriteData(0x33);
    lcdWriteData(0x2c);
    lcdWriteData(0x29);
    lcdWriteData(0x2e);
    lcdWriteData(0x30);
    lcdWriteData(0x30);
    lcdWriteData(0x39);
    lcdWriteData(0x3f);
    lcdWriteData(0x00);
    lcdWriteData(0x07);
    lcdWriteData(0x03);
    lcdWriteData(0x10);

    lcdWriteCommand(0x2a);
    lcdWriteData(0x00);
    lcdWriteData(0x00+2);
    lcdWriteData(0x00);
    lcdWriteData(0x80+2);

    lcdWriteCommand(0x2b);
    lcdWriteData(0x00);
    lcdWriteData(0x00+3);
    lcdWriteData(0x00);
    lcdWriteData(0x80+3);

    lcdWriteCommand(0xF0); //Enable test command
    lcdWriteData(0x01);
    lcdWriteCommand(0xF6); //Disable ram power save mode
    lcdWriteData(0x00);

    lcdWriteCommand(0x3A); //65k mode
    lcdWriteData(0x05);


    lcdWriteCommand(0x29);//Display on
}
