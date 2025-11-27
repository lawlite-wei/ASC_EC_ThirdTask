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
#include "Encoder.h"

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
uint16_t last_number = 0xFF; // 初始化为不可能的值
uint16_t right_speed,left_speed;


//尝试加入PID
//float Target = 0;
//float Actual,Out;
//float Kp = 80,Ki,Kd = 130;
//float error0,error1,error2;
//extern float location;
//float last_location;

int main(void)
{
	OLED_Init();
	PWM_Init();
	Motor_Init();
	Tarce_Init();
	Timer_Init();
	Key_Init();
	Encoder1_Init();
	Encoder2_Init();
	
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
//				OLED_ShowSignedNum(70,16,right_speed,4,OLED_8X16);
//				OLED_ShowSignedNum(70,32,left_speed,4,OLED_8X16);
			}
			
			OLED_ShowChinese(0,48,"刘伟权的循迹小车");
			OLED_Update();
			
			last_number = number; // 更新记录值
		}
		
		// 在状态1时持续执行控制任务
		if(number == 1)
		{
			Control_Task();
//			测试电机的差异(电机2的速度较快)
//			Motor1_SetPWM(100);
//			Motor2_SetPWM(100);
//			OLED_ShowSignedNum(70,16,right_speed,4,OLED_8X16);
//			OLED_ShowSignedNum(70,32,left_speed,4,OLED_8X16);
			OLED_Update();
		}
	}
}

void TIM1_UP_IRQHandler(void)
{
	Key_Tick();
	static uint16_t Count = 0;
	
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)  
	{
		
		Count ++;
		if(Count >= 10)
		{
			right_speed = Encoder1_Get();
			left_speed = Encoder2_Get();
		}
		
		
//		if(number == 1)
//		{
//			Count ++;
//			if(Count > 5)
//			{
//				Count = 0;
//				
//				Location_test();
//				
//				last_location = location;
//				error2 = error1;
//				error1 = error0;
//				error0 = Target - location;
//				
//				float deltaOut = Kp * (error0 - error1) + Ki * error0 + Kd * (error0 - 2 * error1 + error2);
//				Out += deltaOut;
//				
//				Motor1_SetPWM(100 + Out);
//				Motor2_SetPWM(100 - Out);
//			}
//		}
		
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update); 
	}
}
