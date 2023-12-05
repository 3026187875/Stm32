#include"timer.h"
#include"led.h"
// TODO:占空比
// 高电平占周期的比例

void TIM3_Init(u16 arr, u16 psc){
    LED_Init();
    TIM_TimeBaseInitTypeDef a;
    NVIC_InitTypeDef b;
    a.TIM_Period = arr; //自动重装载值
    a.TIM_Prescaler = psc;  // 预分频系数
    //溢出时间= (ARR+1)*(PSC+1) / TCLK
    //                  ^^^^^^^^^^^^^--->一个周期时间长度 72mhz     72m/(7199+1)=10mhz
    a.TIM_CounterMode = TIM_CounterMode_Up;//计数模式
    a.TIM_ClockDivision = TIM_CKD_DIV1;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//使能时钟
    TIM_TimeBaseInit(TIM3, &a); //定时器参数初始化
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//中断使能
    b.NVIC_IRQChannel = TIM3_IRQn; //TIM_3中断
    b.NVIC_IRQChannelPreemptionPriority = 0;//先占优先级0级
    b.NVIC_IRQChannelSubPriority = 3;//从优先级3级
    b.NVIC_IRQChannelCmd = ENABLE; //IRQ通道使能
    NVIC_Init(&b);//中断优先级分组设置
    TIM_Cmd(TIM3,ENABLE); //定时器使能
}
//中断服务函数
void TIM3_IRQHandler(void){
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET){
        GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_8)));
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}
void TIM3_PWM_Init(u16 arr, u16 psc){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
    TIM_TimeBaseInitTypeDef a;
    TIM_OCInitTypeDef tim;
    a.TIM_Period = arr;//设置自动重装载的周期数
    a.TIM_Prescaler = psc;//预分频系数
    a.TIM_CounterMode = TIM_CounterMode_Up;
    a.TIM_ClockDivision = TIM_CKD_DIV1;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_TimeBaseInit(TIM3, &a);
    tim.TIM_OCMode=TIM_OCMode_PWM2;
    tim.TIM_OCPolarity=TIM_OCPolarity_High;
    tim.TIM_OutputState=TIM_OutputState_Enable;
    TIM_OC2Init(TIM3, &tim);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_Cmd(TIM3, ENABLE);
}