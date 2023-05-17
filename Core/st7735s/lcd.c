//
// Created by symct on 2023/5/16.
//

#include "lcd.h"

void lcdFill(struct Point p1,struct Point p2,uint16_t color){
    lcdSetAddress(p1.x,p1.y,p2.x,p2.y);
    for(uint16_t i=p1.y;i<p2.y;i++){
        for(uint16_t j=p1.x;j<p2.x;j++){
            lcdWriteData(color);
        }
    }
}