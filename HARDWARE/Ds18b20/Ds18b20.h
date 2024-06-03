#ifndef __Ds18b20_H
#define __Ds18b20_H
#include "sys.h"
void Data_Port_IN(void);  //让PC15为浮空输入模式
void Data_Port_OUT(void); //让PC15为推挽输出模式
int Ds18b20_Init(void);
void Write_Bit(int bit);
unsigned char Read_Bit(void);
void WriteOneChar(unsigned char data);
unsigned char ReadOneChar(void);
unsigned int ReadTemperature(void);
#endif