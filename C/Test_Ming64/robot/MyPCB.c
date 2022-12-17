#include "MyPCB.h"

UINT32 Get_FCY(void) {return 168000000;}

void IO_Init(void)
{
	//LED�Ŀ��ƣ���PE4�˿�(DSP_LED)����LED��״̬
	SET_GPIO_OUTPUT(GPIOE, GPIO_Pin_4);
	//��OLED��ʾ��ص�IO����
	OLED_IO_Init();
	//�벽����������ص�IO����
	Motor_IO_Init();
}

void Set_LED(UINT8 state)
{
	if(state == 1) PEout(4) = 0;
	else if(state == 0) PEout(4) = 1;
}

void OLED_IO_Init(void)
{
	//����OLED��4���ܽ�OLED_IN4, OLED_IN3, OLED_IN2, OLED_IN1�ֱ��Ӧ��չ��CN8��63,65,67,69 pin
	//��Ӧ���ذ��CN2��63,65,67,69 pin, ��ӦоƬ��PG8��PD3��PC12��PC10
	SET_GPIO_OUTPUT(GPIOG, GPIO_Pin_8);
	SET_GPIO_OUTPUT(GPIOD, GPIO_Pin_3);
	SET_GPIO_OUTPUT(GPIOC, GPIO_Pin_12);
	SET_GPIO_OUTPUT(GPIOC, GPIO_Pin_10);
}

void OLED_rs(BOOL state) {PGout(8) = state;}
void OLED_rst(BOOL state) {PDout(3) = state;}
void OLED_din(BOOL state) {PCout(12) = state;}
void OLED_clk(BOOL state) {PCout(10) = state;}

void Motor_IO_Init(void)
{
	//Motor�Ĳ����ֱ�����STEP_IN1, 2, 3(MD1,2,3)������
	//ʹ���ź�STEP_ENABLE(OE), �����ź�DIR(FR), �����ź�CLK(STP),
	
	//Motor1��IN1,2,3�ֱ��ӦPG11,PG9,PD7, enable��ӦPC11, Dir��ӦPA15�� CLK��ӦPA8
	SET_GPIO_OUTPUT(GPIOG, GPIO_Pin_11);
	SET_GPIO_OUTPUT(GPIOG, GPIO_Pin_9);
	SET_GPIO_OUTPUT(GPIOD, GPIO_Pin_7);
	SET_GPIO_OUTPUT(GPIOC, GPIO_Pin_11);
	SET_GPIO_OUTPUT(GPIOA, GPIO_Pin_15);
	SET_GPIO_OUTPUT(GPIOA, GPIO_Pin_8);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, 2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, 2);
	//GPIO_PinAFConfig(GPIOB, GPIO_Pin_4, GPIO_AF_EVENTOUT);

	//Motor2��IN1,2,3�ֱ��ӦPC14,PE6,PE3, enable��ӦPB4, Dir��ӦPG15�� CLK��ӦPF7	
	SET_GPIO_OUTPUT(GPIOC, GPIO_Pin_14);
	SET_GPIO_OUTPUT(GPIOE, GPIO_Pin_6);
	SET_GPIO_OUTPUT(GPIOE, GPIO_Pin_3);
	SET_GPIO_OUTPUT(GPIOB, GPIO_Pin_4);
	SET_GPIO_OUTPUT(GPIOG, GPIO_Pin_15);
	SET_GPIO_OUTPUT(GPIOF, GPIO_Pin_7);
	
	//Motor3��IN1,2,3�ֱ��ӦPC15,PC13,PE5, enable��ӦPB5, Dir��ӦPG14�� CLK��ӦPF9	
	SET_GPIO_OUTPUT(GPIOC, GPIO_Pin_15);
	SET_GPIO_OUTPUT(GPIOC, GPIO_Pin_13);
	SET_GPIO_OUTPUT(GPIOE, GPIO_Pin_5);
	SET_GPIO_OUTPUT(GPIOB, GPIO_Pin_5);
	SET_GPIO_OUTPUT(GPIOG, GPIO_Pin_14);
	SET_GPIO_OUTPUT(GPIOF, GPIO_Pin_9);
	
	Motor_ENABLE(MOTOR0, 0);
	Motor_ENABLE(MOTOR1, 0);
	Motor_ENABLE(MOTOR2, 0);
}

void Motor_ENABLE(UINT8 index, UINT8 state)
{
	if(index > MOTOR_NUM) return;
	else if(index == MOTOR0) PCout(11) = state;
	else if(index == MOTOR1) PBout(4) = state;
	else if(index == MOTOR2) PBout(5) = state;
}

void Motor_DIR(UINT8 index, UINT8 state)
{
	if(index > MOTOR_NUM) return;
	else if(index == MOTOR0) PAout(15) = 1 - state;
	else if(index == MOTOR1) PGout(15) = 1 - state;
	else if(index == MOTOR2) PGout(14) = state;
}

void Motor_CLK(UINT8 index, UINT8 state)
{
	if(index > MOTOR_NUM) return;
	else if(index == MOTOR0) PAout(8) = state;
	else if(index == MOTOR1) PFout(7) = state;
	else if(index == MOTOR2) PFout(9) = state;
}

void Motor_RES(UINT8 index, UINT8 res)
{
	UINT8 in1, in2, in3, N = 0;
	
	if((res & (res - 1)) || (res > 128)) return;	//����2��N�η�,���ߴ���128��ֱ�ӷ���
	while(res > 1)
	{
		res >>= 1;
		N++;
	}
	in1 = N & 0x01;
	in2 = (N >> 1) & 0x01;
	in3 = (N >> 2) & 0x01;

	if(index > MOTOR_NUM) return;
	else if(index == MOTOR0)
	{
		PGout(11) = in1;
		PGout(9) = in2;
		PDout(7) = in3;
	}
	else if(index == MOTOR1)
	{
		PCout(14) = in1;
		PEout(6) = in2;
		PEout(3) = in3;
	}
	else if(index == MOTOR2)
	{
		PCout(15) = in1;
		PCout(13) = in2;
		PEout(5) = in3;
	}
}

void Motor0_ENABLE(UINT8 state) {Motor_ENABLE(MOTOR0, state);}
void Motor0_DIR(UINT8 state) {Motor_DIR(MOTOR0, state);}
void Motor0_CLK(UINT8 state) {Motor_CLK(MOTOR0, state);}
void Motor0_RES(UINT8 res) {Motor_RES(MOTOR0, res);}
void Motor1_ENABLE(UINT8 state) {Motor_ENABLE(MOTOR1, state);}
void Motor1_DIR(UINT8 state) {Motor_DIR(MOTOR1, state);}
void Motor1_CLK(UINT8 state) {Motor_CLK(MOTOR1, state);}
void Motor1_RES(UINT8 res) {Motor_RES(MOTOR1, res);}
void Motor2_ENABLE(UINT8 state) {Motor_ENABLE(MOTOR2, state);}
void Motor2_DIR(UINT8 state) {Motor_DIR(MOTOR2, state);}
void Motor2_CLK(UINT8 state) {Motor_CLK(MOTOR2, state);}
void Motor2_RES(UINT8 res) {Motor_RES(MOTOR2, res);}




