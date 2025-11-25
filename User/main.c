#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Motor.h"
#include "PWM.h"
#include "Tarce.h"
#include "Timer.h"
#include "Control.h"
#include "menu.h"


/**
  * 坐标轴定义：
  * 左上角为(0, 0)点
  * 横向向右为X轴，取值范围：0~127
  * 纵向向下为Y轴，取值范围：0~63
  * 
  *       0             X轴           127 
  *      .------------------------------->
  *    0 |
  *      |
  *      |
  *      |
  *  Y轴 |
  *      |
  *      |
  *      |
  *   63 |
  *      v
  * 
  */

uint16_t number = 0;
uint8_t last_number = 0xFF; // 初始化为不可能的值

int main(void)
{
	OLED_Init();
	PWM_Init();
	Motor_Init();
	Tarce_Init();
	Timer_Init();
	Key_Init();
	
	while (1)
	{
		if(Key_Check(KEY_3 , KEY_DOWN))
		{
			number++;
			if(number > 1)
			{
				number = 0;
			}
		}
		
		// 只有number变化时才刷新OLED，避免频繁刷新
		if(number != last_number)
		{
			OLED_Clear();
			
			if(number == 0)
			{
//				OLED_ShowChinese(0,0,"发车");
				menu1();
				// 停止电机
				Motor1_SetPWM(0);
				Motor2_SetPWM(0);
			}
			else if(number == 1)
			{
//				OLED_ShowChinese(0,0,"启动");
				menu2();
			}
			
			OLED_ShowChinese(0,48,"刘伟权的循迹小车");
			OLED_Update();
			
			last_number = number; // 更新记录值
		}
		
		// 在状态1时持续执行控制任务
		if(number == 1)
		{
			Control_Task();
//			测试电机的差异
//			Motor1_SetPWM(100);
//			Motor2_SetPWM(100);
		}
	}
}

void TIM1_UP_IRQHandler(void)
{
	Key_Tick();
	
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)  
	{
		
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update); 
	}
}
