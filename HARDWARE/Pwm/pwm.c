#include "pwm.h"
#include "led.h"
// led是PB8    tim4_ch3
void TIM4_Init(u16 arr, u16 psc)
{
    LED_Init();
    TIM_TimeBaseInitTypeDef a;
    NVIC_InitTypeDef b;
    a.TIM_Period = arr;
    a.TIM_Prescaler = psc;
    a.TIM_CounterMode = TIM_CounterMode_Up;
    a.TIM_ClockDivision = TIM_CKD_DIV1;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    TIM_TimeBaseInit(TIM4, &a);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    b.NVIC_IRQChannel = TIM4_IRQn;
    b.NVIC_IRQChannelPreemptionPriority = 0;
    b.NVIC_IRQChannelSubPriority = 3;
    b.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&b);
    TIM_Cmd(TIM4, ENABLE);
}
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
    {
        GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_8)));
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}
void TIM4_PWM_Init(u16 arr, u16 psc)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 重映射要开启AFIO时钟
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //重映射
    //定时器初始化
    TIM_TimeBaseInitTypeDef a;
    TIM_OCInitTypeDef tim;
    a.TIM_Period = arr;// ARPE=1,ARR立即生效   ARPE=0,ARR下个比较周期生效
    a.TIM_Prescaler = psc;
    a.TIM_CounterMode = TIM_CounterMode_Up;
    a.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM4, &a);
    tim.TIM_OCMode = TIM_OCMode_PWM2;// 模式1，计数值小有效    模式2，计数值大有效
    tim.TIM_OCPolarity = TIM_OCPolarity_High;// 有效电平是高电平还是低电平
    // TIM_OCPolarityConfig  单独改变有效电平是低还是高
    tim.TIM_OutputState = TIM_OutputState_Enable;// 使能输出
    TIM_OC3Init(TIM4, &tim);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);// 使能预装载寄存器
    TIM_Cmd(TIM4, ENABLE);
}

// void TIM5_Cap_Init(u16 arr,u16 psc){
    
// }
