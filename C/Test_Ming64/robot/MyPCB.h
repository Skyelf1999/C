#ifndef MYPCB_H
#define MYPCB_H

#include "Device.h"
#include "Peripheral.h"
#include "Tools.h"

UINT32 Get_FCY(void);
void IO_Init(void);

void Set_LED(UINT8 state);

void OLED_IO_Init(void);
void OLED_rst(BOOL state);
void OLED_rs(BOOL state);
void OLED_clk(BOOL state);
void OLED_din(BOOL state);

enum
{
		MOTOR0 = 0,
		MOTOR1,
		MOTOR2,
		MOTOR_NUM
};

void Motor_IO_Init(void);
void Motor_ENABLE(UINT8 index, UINT8 state);
void Motor_DIR(UINT8 index, UINT8 state);
void Motor_CLK(UINT8 index, UINT8 state);
void Motor_RES(UINT8 index, UINT8 res);
void Motor0_ENABLE(UINT8 state);
void Motor0_DIR(UINT8 state);
void Motor0_CLK(UINT8 state);
void Motor0_RES(UINT8 res);
void Motor1_ENABLE(UINT8 state);
void Motor1_DIR(UINT8 state);
void Motor1_CLK(UINT8 state);
void Motor1_RES(UINT8 res);
void Motor2_ENABLE(UINT8 state);
void Motor2_DIR(UINT8 state);
void Motor2_CLK(UINT8 state);
void Motor2_RES(UINT8 res);

#endif
