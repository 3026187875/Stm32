#include"adc.h"
#include "delay.h"
void Adc_Init(void)
{
    // 开启时钟
    RCCAHB1PeriphClockCmd(RCCAHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // 设置ADC时钟，设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
    // 初始化GPIO
    GPIO_InitTypeDef ADC_PA1;
    ADC_PA1.GPIO_Pin = GPIO_Pin_1;
    ADC_PA1.GPIO_Mode = GPIO_Mode_AIN;// 普通输出模式
    ADC_PA1.GPIO_Speed = GPIO_Speed_50MHz;// 100MHz
    // ADC_PA1.GPIO_PuPd = GPIO_PuPd_NOPULL;// 上拉
    ADC_InitTypeDef adc1_1;
    GPIO_Init(GPIOA, &ADC_PA1);
    ADC_DeInit(ADC1);
    adc1_1.ADC_Mode = ADC_Mode_Independent;// adc工作模式 独立模式
    adc1_1.ADC_ContinuousConvMode = DISABLE;// 连续转换是否开启 
    adc1_1.ADC_DataAlign = ADC_DataAlign_Right;// 数据对齐方式
    adc1_1.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;// 触发转换方式 软件触发
    adc1_1.ADC_ScanConvMode = DISABLE;// 扫描模式是否开启
    adc1_1.ADC_NbrOfChannel = 1;// 转换通道数目
    ADC_Init(ADC1, &adc1_1);
    ADC_Cmd(ADC1, ENABLE);
}
u16 Get_Adc(u8 channel){
    ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_7Cycles5); // 通道的转换顺序 如果设置Rank为1，那么这个通道将会首先被转换
    ADC_SoftwareStartConvCmd(ADC1,ENABLE); // 软件触发转换
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))//转换结束，该标志位置1
    {
        
    }
    return ADC_GetConversionValue(ADC1); // 返回转换结果
}
u16 Get_Adc_Average(u8 ch, u8 times){
    u32 temp_val = 0;
    u8 t;
    for ( i = 0; i < times; i++)
    {
        temp_val+=Get_Adc(ch);
        delay_ms(5);
    }
    return temp_val / times;
}