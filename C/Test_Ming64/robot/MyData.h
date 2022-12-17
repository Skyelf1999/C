#ifndef MYDATA_H
#define MYDATA_H

#include "MyPCB.h"

struct APP_Data
{
	//add App data here
	UINT32 fcy;
	UINT8 LED_State;
	
	struct StepMotor* g_StepMotor;
	
	struct Arm_Data* g_Arm_Data;
};

void Init_Data(void);
struct APP_Data* Get_MyData(void);

#endif
