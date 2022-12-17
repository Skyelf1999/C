#include "MyData.h"

struct APP_Data _App_Data;
	
void Init_Data(void)
{
	_App_Data.fcy = Get_FCY();
	_App_Data.LED_State = 0;
	
	Set_MotorPara(0, 1.8, 14.0, 32);
	Set_DriverPara(0, Motor0_ENABLE, Motor0_DIR, Motor0_CLK, Motor0_RES);
	Set_TimerPara(0, TIMER_5);
	
	Set_MotorPara(1, 1.8, 14.0, 32);
	Set_DriverPara(1, Motor1_ENABLE, Motor1_DIR, Motor1_CLK, Motor1_RES);
	Set_TimerPara(1, TIMER_6);
	
	Set_MotorPara(2, 1.8, 14.0, 32);
	Set_DriverPara(2, Motor2_ENABLE, Motor2_DIR, Motor2_CLK, Motor2_RES);
	Set_TimerPara(2, TIMER_7);
	
	_App_Data.g_StepMotor = Get_MotorData();
	
	Set_Arm_Dimension(107, 64.5, 137.5, 170, 90);			//设置机械臂的尺寸，单位 毫米mm
	Set_InitAngle(0, -19.48, 144.0);										//单位 度
	_App_Data.g_Arm_Data = Get_ArmData();
}

struct APP_Data* Get_MyData(void)
{
	return &_App_Data;
}

