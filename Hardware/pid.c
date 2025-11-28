#include "stm32f10x.h"                  // Device header
#include "Tarce.h"
#include "Timer.h"


//无陀螺仪控制，精准度不够
//使用虚拟坐标系
float Tpid_err,Tpid_errsum,Tpid_errdifference;
float Tpid_lasterr;

float Kp = 15,Ki = 0,Kd = 5;

int pid_control(float Actual,float Target)
{
	Tpid_err = Actual - Target;
	float Out;
	
	Tpid_errsum += Tpid_err;
	Tpid_errdifference = Tpid_err - Tpid_lasterr;
	Tpid_lasterr = Tpid_err;
	
	Out = Kp * Tpid_err + Ki * Tpid_errsum + Kd * Tpid_errdifference;
	
	if(Out > 100)
	{
		Out = 100;
	}
	else if(Out < -100)
	{
		Out = -100;
	}
	
	return Out;
}
