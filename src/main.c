#include "sys.h"
#include "usart.h"
#include "usmart.h"
#include "led.h"
#include "delay.h"
int main(void)
{
    uart_init(9600);
    usmart_dev.init(72);
    delay_init();
    while (1) {
    }
}