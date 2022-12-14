#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PID.h"
#include "PWM.h"
#include "UART.h"
#include "Timer.h"
#include "MPU6050.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "sys.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

char tmp_buf[33];			//字符串数组
float pitch,roll,yaw; 		//欧拉角:俯仰角，偏航角，滚转角
short aacx,aacy,aacz;		//加速度传感器原始数据  angular acceleration
short gyrox,gyroy,gyroz;	//陀螺仪原始数据  gyroscope
short temp;					//温度


struct MPU6050				//MPU6050结构体
{
	u8 flag;				//采集成功标志位
	u8 speed;				//上报速度
}mpu6050;					//唯一结构体变量


int main(void);				//主函数
void SYS_Init(void);		//系统初始化总函数
void MPU_Read(void);		//MPU6050数据读取函数	
void DATA_Report(void);		//MPU6050数据上报

