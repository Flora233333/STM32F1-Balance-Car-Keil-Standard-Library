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

char tmp_buf[33];			//�ַ�������
float pitch,roll,yaw; 		//ŷ����:�����ǣ�ƫ���ǣ���ת��
short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����  angular acceleration
short gyrox,gyroy,gyroz;	//������ԭʼ����  gyroscope
short temp;					//�¶�


struct MPU6050				//MPU6050�ṹ��
{
	u8 flag;				//�ɼ��ɹ���־λ
	u8 speed;				//�ϱ��ٶ�
}mpu6050;					//Ψһ�ṹ�����


int main(void);				//������
void SYS_Init(void);		//ϵͳ��ʼ���ܺ���
void MPU_Read(void);		//MPU6050���ݶ�ȡ����	
void DATA_Report(void);		//MPU6050�����ϱ�

