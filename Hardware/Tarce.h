#ifndef __TARCE_H
#define __TARCE_H

#define X1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)
#define X2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)
#define X3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)
#define X4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)

//extern float location;

void Tarce_Init(void);
float Tarce_Location(void);

#endif
