#include "stm32f10x.h"
#include "myusart.h"
void my_uart1_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 1.使能相关时钟
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    GPIO_InitTypeDef a;
    USART_InitTypeDef uart1;
    NVIC_InitTypeDef nvic1;
    a.GPIO_Mode = GPIO_Mode_AF_PP;
    a.GPIO_Pin = GPIO_Pin_9;
    a.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &a); // 2.初始化相应的gpio模式
    a.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    a.GPIO_Pin = GPIO_Pin_10;
    a.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &a); // 2.初始化相应的gpio模式

    uart1.USART_BaudRate = 115200;
    uart1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uart1.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    uart1.USART_Parity = USART_Parity_No;
    uart1.USART_StopBits = USART_StopBits_1;
    uart1.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &uart1); // 3.初始化串口相关参数
    USART_Cmd(USART1, ENABLE);  // 使能串口1

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // 开启接收中断

    nvic1.NVIC_IRQChannel = USART1_IRQn;
    nvic1.NVIC_IRQChannelCmd = ENABLE;
    nvic1.NVIC_IRQChannelPreemptionPriority = 1;
    nvic1.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&nvic1); // 中断优先级设置
}

void USART1_IRQHandler(void)
{
    u8 res;
    if (USART_GetITStatus(USART1, USART_IT_RXNE))
    {
        res = USART_ReceiveData(USART1);
        USART_SendData(USART1, res);
    }
}
// int main(void)
// {
//     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 配置nvic组
//     my_uart1_init();
//     while (1)
//     {
//     }
// }
