#include "MyApp.h"

#define pos_origin 10

struct APP_Data* MyData;

void Test1(void);

int main(void)
{
	Init_App();
	
	u8 fsm = 0;

	while(1)
	{
		switch(fsm)
		{
			case 0:
				if(Arm_MoveTo(0, 200, 100, 1000) == 1) fsm = 1;
				break;
			
			case 1:
				if(Arm_Rotate(-10, 0, 0, 1000) == 1) fsm = 2;
				break;
			
			case 2:
				if(Arm_Move(0, 0, -15, 1000) == 1) fsm = 3;
				break;
			
			case 3:
				if(Arm_Rotate(20, 0, 0, 1000) == 1) fsm = 4;
				break;
			
			case 4:
				if(Arm_Move(0, 0, 30, 1000) == 1) fsm = 5;
				break;
			
			case 5:
				if(Arm_MoveTo(0, 150, 90, 1000) == 1) fsm = 6;
				break;
			
			case 6:
				if(Arm_Move(0, 0, -10, 1000) == 1) fsm = 7;
				break;
			
			case 7:
				if(Arm_Rotate(0, 20, -20, 1000) == 1) fsm = 8;
				break;
			
			case 8:
			if(Arm_RotateTo(origin_pos[0], origin_pos[1], origin_pos[2], 1000) == 1) fsm = 10;
				break;
			
			case 10:
				Motor_ENABLE(MOTOR0, 0);
				Motor_ENABLE(MOTOR1, 0);
				Motor_ENABLE(MOTOR2, 0);
				fsm = 0;
				return 0;
				break;
		}
		
	}
}

void Init_App(void)
{
	Init_Data();
	MyData = Get_MyData();
	
	IO_Init();
	Delay_Init(MyData->fcy);
	
	//³õÊ¼»¯OLED
	OLED_Init(OLED_rst, OLED_rs, OLED_clk, OLED_din);	
	
	Config_SysTick(1000);
	SysTick_Register(Test1);
	
	Config_TIMER(TIMER_5, 4, 1000);
	Config_TIMER(TIMER_6, 4, 1000);
	Config_TIMER(TIMER_7, 4, 1000);
}

void Test1(void)
{
	static UINT16 i = 0;
	i++;
	if(i >= 1000)
	{
		Set_LED(MyData->LED_State);
		MyData->LED_State = 1 - MyData->LED_State;
		i = 0;
	}
}
