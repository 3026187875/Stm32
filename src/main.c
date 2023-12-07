#include "sys.h"
#include "delay.h"
#include "led.h"
#include "timer.h"
#include "usart.h"

extern u8 TIM2ch1_cap_sta;  // 输入捕获状态
extern u16 TIM2ch1_cap_val; // 输入捕获值
int main(void)
{

    u32 temp = 0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置中断优先级分组2
    delay_init();                                   // 延时函数初始化
    uart_init(9600);                                // 9600
    LED_Init();                                     // 初始化与LED连接的硬件接口
    TIM3_PWM_Init(899, 0);                          // 不分频。PWM频率=72000/(899+1)=80Khz
    TIM2_Cap_Init(0XFFFF, 72 - 1);                  // 以1Mhz的频率计数
    while (1) {
        delay_ms(10);
        TIM_SetCompare1(TIM3, TIM_GetCapture1(TIM3) + 1);
        if (TIM_GetCapture1(TIM3) == 300) TIM_SetCompare1(TIM3, 0);
        if (TIM2ch1_cap_sta & 0X80) // 成功捕获到了一次高电平
        {
            temp = TIM2ch1_cap_sta & 0X3F;
            temp *= 65536;                  // 溢出时间总和
            temp += TIM2ch1_cap_val;    // 得到总的高电平时间
            printf("HIGH:%d us\r\n", temp); // 打印总的高点平时间
            TIM2ch1_cap_sta = 0;        // 开启下一次捕获
        }
    }
}
