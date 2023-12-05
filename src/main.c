#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "pwm.h"
#include "led.h"
int main(void){
    u16 led0pwmval = 0;
    u8 dir         = 1;
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_Init();
    TIM4_PWM_Init(899, 0);
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
        TIM_SetCompare3(TIM4, led0pwmval);
    }
    
}