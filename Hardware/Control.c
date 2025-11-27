#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Tarce.h"

void Control_Task(void)
{
	//直走
	if(X2 == 1 && X1 == 0 && X3 == 0 && X4 == 1)
	{
		Motor1_SetPWM(100);
		Motor2_SetPWM(100);
	}
	//小左转
	else if(X2 == 1 && X1 == 0 && X3 == 1 && X4 == 1)
	{
//		Motor1_SetPWM(85);
//		Motor2_SetPWM(0);
		Motor1_SetPWM(90);
		Motor2_SetPWM(40);
	}
	//小右转
	else if(X2 == 1 && X1 == 1 && X3 == 0 && X4 == 1)
	{
//		Motor1_SetPWM(0);
//		Motor2_SetPWM(85);
		Motor1_SetPWM(40);
		Motor2_SetPWM(90);
	}
	//大左转
	else if(X2 == 0 && X1 == 1 && X3 == 1 && X4 == 1)
	{
		Motor1_SetPWM(100);
		Motor2_SetPWM(-80);
	}
	//大右转
	else if(X2 == 1 && X1 == 1 && X3 == 1 && X4 == 0)
	{
		Motor1_SetPWM(-80);
		Motor2_SetPWM(100);
	}
	//十字口
	else if(X2 == 0 && X1 == 0 && X3 == 0 && X4 == 0)
	{
		Motor1_SetPWM(100);
		Motor2_SetPWM(100);
	}
	//左直角转弯
	else if(X2 == 0 && X1 == 0 && X3 == 0 && X4 == 1)
	{
		Motor1_SetPWM(100);
		Motor2_SetPWM(0);
	}
	//右直角转弯
	else if(X2 == 1 && X1 == 0 && X3 == 0 && X4 == 0)
	{
		Motor1_SetPWM(0);
		Motor2_SetPWM(100);
	}
	//左直角转弯2
	else if(X2 == 0 && X1 == 0 && X3 == 1 && X4 == 1)
	{
		Motor1_SetPWM(90);
		Motor2_SetPWM(0);
	}
	//右直角转弯2
	else if(X2 == 1 && X1 == 1 && X3 == 0 && X4 == 0)
	{
		Motor1_SetPWM(0);
		Motor2_SetPWM(90);
	}
}
