#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
int main(void)
{
    u16 t,len,times=0;
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(115200);
    while (1)
    {
        if(USART_RX_STA&0x8000){
            len = USART_RX_STA & 0x3fff;
            printf("\r\n你发送的消息为:\r\n\r\n");
            for ( t = 0; t < len; t++)
            {
                USART_SendData(USART1, USART_RX_BUF[t]);
                while (USART_GetITStatus(USART1,USART_FLAG_TC)!=SET){

                }

            }
            printf("\r\n\r\n");
            USART_RX_STA=0;
        }
        else
        {
            times++;
            if (times%5000==0)
            {
                printf("\r\n STM32最小系统板 串口实验\r\n");
                printf("leioukupo@leioukupo\r\n\r\n");
            }
            if (times%200==0)
            {
                printf("请输入数据,以回车键结束\n");
            }
            delay_ms(10);
        }
        
    }
    
}
