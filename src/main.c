#include "led.h"
#include "delay.h"
#include "oled.h"
#include "bmp.h"
#include "adc.h"
int main(void)
{
    u16 adcx;
    float temp;
    Adc_Init(); //初始化ADC
    delay_init();
    OLED_Init();
    OLED_ColorTurn(0);   // 0正常显示，1 反色显示
    OLED_DisplayTurn(0); // 0正常显示 1 屏幕翻转显示
    //	OLED_DrawPoint(0,0);
    //	OLED_DrawLine(20,0,50,60);
    //	OLED_DrawCircle(64,32,20);
    OLED_Refresh();
    OLED_Clear();
    while (1)
    {
        adcx=Get_Adc_Average(ADC_Channel_1,20);//获取通道1的转换值，20次取平均
        OLED_ShowNum(5, 8, adcx, 4, 16);
        temp=(float)adcx*(3.3/4096);//获取计算后的带小数的实际电压值，比如3.1111
        adcx=temp;//赋值整数部分给adcx变量，因为adcx为u16整形
        OLED_ShowNum(5, 28, adcx, 1, 16);
        temp=temp-adcx;//把已经显示的整数部分去掉，留下小数部分，比如3.1111-3=0.1111
        temp=temp*1000;//小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数
        OLED_ShowNum(5, 48, temp, 3, 16);
        OLED_ShowChinese(90, 0, 5, 16); // 科
        OLED_ShowChinese(108, 0, 6, 16); // 技
        delay_ms(250);
    }
}
