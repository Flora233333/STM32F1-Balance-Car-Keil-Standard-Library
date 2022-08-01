#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Servo_Init() {
	//PWM_Init();
}

void Servo_Spin(uint16_t i) {
	if(i > 4) {
		i = 50;
	} else {
		i = i * 50 + 50;
	}
	TIM_SetCompare1(TIM2, i);
}
