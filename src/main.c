#include "stm32f10x.h"
#include "myusart.h"
#include "delay.h"
int main(void)
{
    int i;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    my_uart1_init();
    while (1)
    {

    }
}
