# hal_st7735s
a hal lcd library of st7735s  
1.8 inch st7735s software spi  
**默认接线：**  
```
3V3				VCC  
GND				GND  
SCL				PB7  
SDA				PA5  
RES				PA6  
DC				PA7  
CS				PB6  
```
**移植自优信电子的代码，若需更改端口修改lcd_init.h中的宏定义，并初始化对应端口即可。**  
**lcdDrawImg函数未测试。**
