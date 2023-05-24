//
// Created by symct on 2023/5/16.
//
#include "lcd_init.h"



void lcdWrite(uint8_t data){
    csReset();//将LCD片选信号拉低，表示开始通信
    for(uint8_t i=0;i<8;i++){
        clkReset();
        if(data&0x80){//判断最高位是否是1
            sdaSet();//设置lcd数据信号
        }else{
            sdaReset();
        }
        clkSet();//将LCD的时钟信号拉高，表示数据有效
        data<<=1;//左移一位，准备发送下一位
    }
    csSet();
}
void lcdWriteData8(uint8_t data){
    lcdWrite(data);
}
void lcdWriteData(uint16_t data){
    lcdWrite(data>>8);
    lcdWrite(data);
}
void lcdWriteCommand(uint8_t command){
    rsReset();//低电平传输指令
    lcdWrite(command);
    rsSet();//高电平传输数据
}
void lcdSetAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2){
    lcdWriteCommand(0x2a);//列地址设置
    lcdWriteData(x1);
    lcdWriteData(x2);
    lcdWriteCommand(0x2b);//行地址设置
    lcdWriteData(y1);
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
    //复制网上的代码进行初始化，指令可在芯片手册96页command标题下查看

    lcdReset();//Reset before LCD Init.

    lcdWriteCommand(0x11); //Sleep out
    HAL_Delay(120); //Delay 120ms

    //------------------------------------ST7735S Frame rate-------------------------------------------------//
    lcdWriteCommand(0xB1); //Frame rate 80Hz
    lcdWriteData8(0x02);
    lcdWriteData8(0x35);
    lcdWriteData8(0x36);
    lcdWriteCommand(0xB2); //Frame rate 80Hz
    lcdWriteData8(0x02);
    lcdWriteData8(0x35);
    lcdWriteData8(0x36);
    lcdWriteCommand(0xB3); //Frame rate 80Hz
    lcdWriteData8(0x02);
    lcdWriteData8(0x35);
    lcdWriteData8(0x36);
    lcdWriteData8(0x02);
    lcdWriteData8(0x35);
    lcdWriteData8(0x36);
    //------------------------------------End ST7735S Frame rate-------------------------------------------//
    lcdWriteCommand(0xB4); //Dot inversion
    lcdWriteData8(0x03);
    //------------------------------------ST7735S Power Sequence-----------------------------------------//
    lcdWriteCommand(0xC0);
    lcdWriteData8(0xA2);
    lcdWriteData8(0x02);
    lcdWriteData8(0x84);
    lcdWriteCommand(0xC1);
    lcdWriteData8(0xC5);
    lcdWriteCommand(0xC2);
    lcdWriteData8(0x0D);
    lcdWriteData8(0x00);
    lcdWriteCommand(0xC3);
    lcdWriteData8(0x8D);
    lcdWriteData8(0x2A);
    lcdWriteCommand(0xC4);
    lcdWriteData8(0x8D);
    lcdWriteData8(0xEE);
    //---------------------------------End ST7735S Power Sequence---------------------------------------//
    lcdWriteCommand(0xC5); //VCOM
    lcdWriteData8(0x0a);
    lcdWriteCommand(0x36);
    lcdWriteData8(0xA0);//横向,RGB格式
    //------------------------------------ST7735S Gamma Sequence-----------------------------------------//
    lcdWriteCommand(0XE0);
    lcdWriteData8(0x12);
    lcdWriteData8(0x1C);
    lcdWriteData8(0x10);
    lcdWriteData8(0x18);
    lcdWriteData8(0x33);
    lcdWriteData8(0x2C);
    lcdWriteData8(0x25);
    lcdWriteData8(0x28);
    lcdWriteData8(0x28);
    lcdWriteData8(0x27);
    lcdWriteData8(0x2F);
    lcdWriteData8(0x3C);
    lcdWriteData8(0x00);
    lcdWriteData8(0x03);
    lcdWriteData8(0x03);
    lcdWriteData8(0x10);
    lcdWriteCommand(0XE1);
    lcdWriteData8(0x12);
    lcdWriteData8(0x1C);
    lcdWriteData8(0x10);
    lcdWriteData8(0x18);
    lcdWriteData8(0x2D);
    lcdWriteData8(0x28);
    lcdWriteData8(0x23);
    lcdWriteData8(0x28);
    lcdWriteData8(0x28);
    lcdWriteData8(0x26);
    lcdWriteData8(0x2F);
    lcdWriteData8(0x3B);
    lcdWriteData8(0x00);
    lcdWriteData8(0x03);
    lcdWriteData8(0x03);
    lcdWriteData8(0x10);
    //------------------------------------End ST7735S Gamma Sequence-----------------------------------------//
    lcdWriteCommand(0x3A); //65k mode
    lcdWriteData8(0x05);
    lcdWriteCommand(0x29); //Display on
}
