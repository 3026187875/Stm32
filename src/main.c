#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "pwm.h"
#include "led.h"
// int main(void)
// {

//     u8 t;
//     delay_init();
//     OLED_Init();
//     OLED_ColorTurn(0);   // 0正常显示，1 反色显示
//     OLED_DisplayTurn(0); // 0正常显示 1 屏幕翻转显示
//     //	OLED_DrawPoint(0,0);
//     //	OLED_DrawLine(20,0,50,60);
//     //	OLED_DrawCircle(64,32,20);
//     OLED_Refresh();
//     t = ' ';
//     OLED_Clear();
//     while (1) {
//         // OLED_ShowPicture(0, 0, 128, 8, BMP1);
//         // delay_ms(500);
//         // OLED_Clear();
//         // OLED_ShowChinese(0, 0, 0, 16);   // 中
//         // OLED_ShowChinese(18, 0, 1, 16);  // 景
//         // OLED_ShowChinese(36, 0, 2, 16);  // 园
//         // OLED_ShowChinese(54, 0, 3, 16);  // 电
//         // OLED_ShowChinese(72, 0, 4, 16);  // 子
//         // OLED_ShowChinese(90, 0, 5, 16);  // 科
//         // OLED_ShowChinese(108, 0, 6, 16); // 技
//         // OLED_ShowString(8, 16, "ZHONGJINGYUAN", 16);
//         // OLED_ShowString(20, 32, "2014/05/01", 16);
//         // OLED_ShowString(0, 48, "ASCII:", 16);
//         // OLED_ShowString(63, 48, "CODE:", 16);
//         // OLED_ShowChar(48, 48, t, 16); // 显示ASCII字符
//         // t++;
//         // if (t > '~') t = ' ';
//         // OLED_ShowNum(103, 48, t, 3, 16);
//         // OLED_Refresh();
//         // delay_ms(500);
//         // OLED_Clear();
//         // OLED_ShowChinese(0, 0, 0, 16);   // 16*16 中
//         // OLED_ShowChinese(16, 0, 0, 24);  // 24*24 中
//         // OLED_ShowChinese(24, 20, 0, 32); // 32*32 中
//         // OLED_ShowChinese(64, 0, 0, 64);  // 64*64 中
//         // OLED_Refresh();
//         // delay_ms(500);
//         // OLED_Clear();
//         // OLED_ShowString(0, 0, "ABC", 12);  // 6*12 “ABC”
//         // OLED_ShowString(0, 12, "ABC", 16); // 8*16 “ABC”
//         // OLED_ShowString(0, 28, "ABC", 24); // 12*24 “ABC”
//         // OLED_Refresh();
//         // delay_ms(500);
//         // OLED_ScrollDisplay(11, 4);
//         delay_ms(500);
//         OLED_ShowPicture(0, 0, 128, 8, BMP1); // 图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
//         delay_ms(1000);
//         OLED_ShowPicture(0, 0, 128, 8, BMP2);
//         delay_ms(800);
//     }
// }
int main(void){
    u16 led0pwmval = 0;
    u8 dir         = 1;
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_Init();
    TIM4_Init(899, 0);
    while (1)
    {
        delay_ms(10);
        if (dir)
        {
            led0pwmval++;
        }
        else
        {
            led0pwmval--;
        }
        if (led0pwmval>300)
        {
            dir=0;
        }
        if (led0pwmval==0)
        {
            dir = 1;
        }
        TIM_SetCompare4(TIM4, led0pwmval);
    }
    
}