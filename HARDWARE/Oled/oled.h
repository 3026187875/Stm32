#ifndef __OLED_H
#define __OLED_H
//              ----------------------------------------------------------------
//              GND  电源地
//              VCC  3.3v电源
//              D0   PA3（SCL）
//              D1   PA4（SDA）
//              RES  PA5
//              DC   PA6
//              CS   PA7
//              ----------------------------------------------------------------
#define D0 GPIO_Pin_3
#define D1 GPIO_Pin_4
#define RES GPIO_Pin_5
#define DC GPIO_Pin_6
#define CS GPIO_Pin_7
#include "sys.h"
#include "stdlib.h"	

//-----------------测试LED端口定义---------------- 

#define LED_ON GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define LED_OFF GPIO_SetBits(GPIOB,GPIO_Pin_8)

//-----------------OLED端口定义---------------- 

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOA,D0)
#define OLED_SCLK_Set() GPIO_SetBits(GPIOA,D0)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOA,D1)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOA,D1)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOA,RES)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOA,RES)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOA,DC)//DC
#define OLED_DC_Set() GPIO_SetBits(GPIOA,DC)
 		     
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOA,CS)//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOA,CS)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define u8 unsigned char
#define u32 unsigned int

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1);
void OLED_ScrollDisplay(u8 num,u8 space);
void OLED_WR_BP(u8 x,u8 y);
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
void OLED_Init(void);

#endif