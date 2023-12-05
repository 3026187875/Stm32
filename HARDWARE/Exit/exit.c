#include "exit.h"
#include "delay.h"
#include "led.h"
void EXITX_Init(void)
{
    LED_Init();
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef Exitinit;
    NVIC_InitTypeDef nvicinit;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能PORTA,PORTC时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;      // PA15
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   // 设置成上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);          // 初始化GPIOA15
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);
    Exitinit.EXTI_Line = EXTI_Line15;
    Exitinit.EXTI_LineCmd = ENABLE;
    Exitinit.EXTI_Mode = EXTI_Mode_Interrupt;
    Exitinit.EXTI_Trigger = EXTI_Trigger_Falling;
    nvicinit.NVIC_IRQChannel=EXTI15_10_IRQn;
    nvicinit.NVIC_IRQChannelCmd = ENABLE;
    nvicinit.NVIC_IRQChannelPreemptionPriority = 2;
    nvicinit.NVIC_IRQChannelSubPriority = 2;
    EXTI_Init(&Exitinit);
    NVIC_Init(&nvicinit);
}
void EXTI15_10_IRQHandler(void)
{
    delay_ms(1000);
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0)
    {
        GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_8)));
    }
    EXTI_ClearITPendingBit(EXTI_Line15);
}