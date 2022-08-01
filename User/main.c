#include "main.h"

/******************************************************  
 ������ֻ��ѧϰʹ��
 ƽ��С��
 ���ߣ�Flora233 
 ѧУ����̶��ѧTIʵ����
 
 ��л����ԭ�ӵĲ���ģ�鿪Դ����
									��һ 2022��8��1��
******************************************************/

int Motor_1, Motor_2;								 //����������

int main() {
	
	SYS_Init();										 //��ʼ��
	
	while(1) {

	}
}

void SYS_Init() {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����麯��
	OLED_Init();									 //OLED��ʼ��
	MPU_Init();	                                     //��ʼ��MPU6050
	
	Motor_Init();
	Encoder_Init();
	PWM_Init();
	PID_Init();
	//UART_Init();
	
	while(mpu_dmp_init())                            //��ʼ��mpu_dmp��
 	{
		OLED_ShowString(1,1,"Failed");			 	 //��ʾ�ַ���
		OLED_Clear();                              
		delay_ms(200);          
		OLED_Clear();							
	}
	OLED_ShowString(1, 1, "successed");
	delay_ms(200);          
	OLED_Clear();
	OLED_ShowString(1,5,"OK!");						 //��ʾ�ַ���
	delay_ms(999);									 //��ʱ��������ʾ
	OLED_Clear();	
	mpu6050.flag = 0;                                //�ɼ��ɹ���־λ��ʼ��
	mpu6050.speed = 0;								 //�ϱ��ٶȳ�ʼ��
	
	Timer1_InternalClock_Init();
}

void Control() {
	if(mpu_dmp_get_data(&pitch,&roll,&yaw) == 0)	 //��ȡŷ���Ƕ�����		
	{ 
		MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);	 //��ȡ���ٶ�
		
		float Control_Temp = roll;
		short Encoder_Left = 0, Encoder_Right = 0;
		
		Encoder_Left = (short)TIM_GetCounter(TIM3);   //��ȡ����������
		Encoder_Right = -(short)TIM_GetCounter(TIM4); //��֤������������ӵļ�����ͬ
		
		TIM_SetCounter(TIM3, 0);					  //��ձ���������
		TIM_SetCounter(TIM4, 0);
		
		Blance_Control(Control_Temp, gyrox); 	  	  //ƽ�⻷
		
		Speed_Control(Encoder_Left, Encoder_Right);	  //�ٶȻ�
		
		Motor_1 = (int)(Blance.Out + Speed.Out);
		Motor_2 = (int)(Blance.Out + Speed.Out);
		
		PWM_Restrict(&Motor_1, &Motor_2);			  //�޷�
		
		if(Motor_Security(Control_Temp))			  //����㵹
			PWM_Updata(Motor_1, Motor_2);			  //����PWM
		else
			PWM_Updata(0, 0);					
		
		mpu6050.flag = 0;
	}
	else { }										  //������
}

void TIM1_UP_IRQHandler() {
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET) {
		Control();									  //ÿ1ms����һ��PID����
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}

