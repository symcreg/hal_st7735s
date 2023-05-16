//
// Created by symct on 2023/5/16.
//

#include "lcd.h"

void lcdFill(struct Point p1,struct Point p2,uint16_t color){
    lcdSetAddress(p1.x,p1.y,p2.x-1,p2.y-1);
    for(uint16_t i=0;i<p2.y;i++){
        for(uint16_t j=0;j<p2.x;j++){
            lcdWriteData(color);
        }
    }
}