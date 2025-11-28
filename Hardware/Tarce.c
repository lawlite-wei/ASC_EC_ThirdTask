#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Tarce.h"


void Tarce_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

float Tarce_Location(void)
{
	float location;
	//直走
	if(X2 == 1 && X1 == 0 && X3 == 0 && X4 == 1)
	{
		location = 0;
	}
	//小左转
	else if(X2 == 1 && X1 == 0 && X3 == 1 && X4 == 1)
	{
		location = -4;
	}
	//左未检测点
	else if(X2 == 1 && X1 == 0 && X3 == 1 && X4 == 1)
	{
		if(X2 == 1 && X1 == 1 && X3 == 1 && X4 == 1)
		{
			location = -5;
		}
	}
	//小右转
	else if(X2 == 1 && X1 == 1 && X3 == 0 && X4 == 1)
	{
		location = 4;
	}
	//右未检测点
	else if(X2 == 1 && X1 == 0 && X3 == 1 && X4 == 1)
	{
		if(X2 == 1 && X1 == 1 && X3 == 1 && X4 == 1)
		{
			location = 5;
		}
	}
	//大左转
	else if(X2 == 0 && X1 == 1 && X3 == 1 && X4 == 1)
	{
		location = -10;
	}
	//大右转
	else if(X2 == 1 && X1 == 1 && X3 == 1 && X4 == 0)
	{
		location = 10;
	}
	//十字口
	else if(X2 == 0 && X1 == 0 && X3 == 0 && X4 == 0)
	{
		location = 0;
	}
	//左直角转弯
	else if(X2 == 0 && X1 == 0 && X3 == 0 && X4 == 1)
	{
		location = -7;
	}
	//右直角转弯
	else if(X2 == 1 && X1 == 0 && X3 == 0 && X4 == 0)
	{
		location = 7;
	}

	
	return location;
}
