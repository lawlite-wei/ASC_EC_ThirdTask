#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Control.h"
#include "Key.h"
#include "PWM.h"
#include "Tarce.h"
#include "Motor.h"

int menu1(void)
{
//	OLED_Clear();
	OLED_ShowChinese(0,0,"发车");
}

int menu2(void)
{
	OLED_ShowChinese(0,0,"启动");
}
