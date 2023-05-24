//
// Created by symct on 2023/5/16.
//

#include "lcd.h"
#include "lcd_font.h"

//参数：起始坐标，终点坐标，颜色
void lcdFill(struct Point p1,struct Point p2,uint16_t color){
    lcdSetAddress(p1.x,p1.y,p2.x,p2.y);
    for(uint16_t i=p1.y;i<p2.y;i++){
        for(uint16_t j=p1.x;j<p2.x;j++){
            lcdWriteData(color);
        }
    }
}
//参数：坐标，颜色
void lcdDrawPoint(struct Point p,uint16_t color){
    lcdSetAddress(p.x,p.y,p.x,p.y);
    lcdWriteData(color);
}
//参数：起始坐标，终点坐标，颜色
void lcdDrawLine(struct Point p1,struct Point p2,uint16_t color){

    int xErr=0,yErr=0,deltaX,deltaY,distance;
    int incX,incY;
    deltaX= p2.x - p1.x;
    deltaY= p2.y - p1.y;
    struct Point p={p1.y,p1.y};
    if(deltaX > 0) {
        incX = 1;
    }
    else if (deltaX == 0) {
        incX = 0;
    }
    else {
        incX=-1;deltaX=-deltaX;
    }
    if(deltaY > 0) {
        incY = 1;
    }
    else if (deltaY == 0) {
        incY = 0;
    }
    else {
        incY=-1;deltaY=-deltaY;
    }
    if(deltaX > deltaY) {
        distance = deltaX;
    }
    else {
        distance = deltaY;
    }
    for(int t=0;t<distance+1;t++){
        lcdDrawPoint(p,color);
        xErr+=deltaX;
        yErr+=deltaY;
        if(xErr > distance){
            xErr-=distance;
            p.x+=incX;
        }
        if(yErr > distance){
            yErr-=distance;
            p.y+=incY;
        }
    }
}
//参数：起始坐标，终点坐标，颜色
void lcdDrawRectangle(struct Point p1,struct Point p2,uint16_t color){
    struct Point leftUp={p1.x,p1.y};
    struct Point leftDown={p1.x,p2.y};
    struct Point rightUp={p2.x,p1.y};
    struct Point rightDown={p2.x,p2.y};
    lcdDrawLine(leftUp,leftDown,color);
    lcdDrawLine(leftUp,rightUp,color);
    lcdDrawLine(rightDown,rightUp,color);
    lcdDrawLine(rightDown,leftDown,color);
}
//参数：坐标位置，显示字符，字的颜色，背景色，字号（12，16，24，32），模式（0-非叠加模式，1-叠加模式）
void lcdDrawChar(struct Point p,uint8_t ch,uint16_t charColor,uint16_t backgroundColor,uint8_t sizeY,uint8_t mode){
    uint8_t temp,sizeX,t,m=0;
    uint16_t i,TypefaceNum;
    uint16_t x0=p.x;
    sizeX=sizeY/2;
    TypefaceNum= (sizeX / 8 + ((sizeX % 8) ? 1 : 0)) * sizeY;
    ch=ch-' ';
    lcdSetAddress(p.x, p.y, p.x + sizeX - 1, p.y + sizeY - 1);
    for(i=0;i<TypefaceNum;i++){
        if(sizeY==12) {
            temp = ascii_1206[ch][i];
        }
        else if(sizeY==16) {
            temp = ascii_1608[ch][i];
        }
        else if(sizeY==24) {
            temp = ascii_2412[ch][i];
        }
        else if(sizeY==32) {
            temp = ascii_3216[ch][i];
        }
        else {
            return;
        }
        for(t=0;t<8;t++){
            if(!mode){
                if(temp&(0x01<<t)) {
                    lcdWriteData(charColor);
                }
                else {
                    lcdWriteData(backgroundColor);
                }
                m++;
                if(m % sizeX == 0){
                    m=0;
                    break;
                }
            }
            else{
                if(temp&(0x01<<t)) {
                    lcdDrawPoint(p, charColor);
                }
                p.x++;
                if((p.x-x0) == sizeX){
                    p.x=x0;
                    p.y++;
                    break;
                }
            }
        }
    }
}
//参数分别为：坐标位置，显示字符，字的颜色，背景色，字号（12，16，24，32），模式（0-非叠加模式，1-叠加模式）
void lcdDrawString(struct Point p,const uint8_t *str,uint16_t charColor,uint16_t backgroundColor,uint8_t sizeY,uint8_t mode){
    while(*str!='\0'){
        lcdDrawChar(p,*str,charColor,backgroundColor,sizeY,mode);
        p.x+=sizeY/2;
        str++;
    }
}
uint32_t myPow(uint8_t m,uint8_t n){
    uint32_t result=1;
    while(n--) {
        result *= m;
    }
    return result;
}
//坐标位置，显示数字，显示位数，字体颜色，背景颜色，字体大小
void lcdDrawIntNum(struct Point p, uint16_t num, uint8_t len, uint16_t frontColor, uint16_t backgroundColor, uint8_t sizeY){
    uint8_t t,temp;
    uint8_t enShow=0;
    uint8_t sizeX= sizeY / 2;
    uint8_t t1=p.x;
    for(t=0;t<len;t++){
        temp=(num/myPow(10,len-t-1))%10;
        if(enShow == 0 && t < (len - 1)){
            if(temp==0){
                p.x=t1+ t * sizeX;
                lcdDrawChar(p, ' ', frontColor, backgroundColor, sizeY, 0);
                continue;
            }else {
                enShow = 1;
            }
        }
        p.x=t1+ t * sizeX;
        lcdDrawChar(p,temp+48, frontColor, backgroundColor, sizeY, 0);
    }
}
//坐标位置，显示数字，显示位数，字体颜色，背景颜色，字体大小
void lcdDrawFloatNum(struct Point p, float num, uint8_t len, uint16_t frontColor, uint16_t backgroundColor, uint8_t sizeY){
    uint8_t t,temp,sizeX;
    uint16_t num1;
    uint8_t t1=p.x;
    sizeX= sizeY / 2;
    num1=num*100;
    for(t=0;t<len;t++){
        temp=(num1/myPow(10,len-t-1))%10;
        if(t==(len-2)){
            p.x=t1+ (len-2) * sizeX;
            lcdDrawChar(p, '.', frontColor, backgroundColor, sizeY, 0);
            t++;
            len+=1;
        }
        p.x=t1+ t * sizeX;
        lcdDrawChar(p,temp+48, frontColor, backgroundColor, sizeY, 0);
    }
}
//坐标位置，宽度，高度，图片数组
void lcdDrawImg(struct Point p,uint16_t length,uint16_t height,const uint8_t *img){
    uint32_t k=0;
    lcdSetAddress(p.y,p.y,p.y+length,p.y+height);
    for(uint16_t i=0;i<length;i++){
        for(uint16_t j=0;j<height;j++){
            lcdWriteData8(img[k*2]);
            lcdWriteData8(img[k*2+1]);
            k++;
        }
    }
}