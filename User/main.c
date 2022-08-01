#include "main.h"

/******************************************************  
 本程序只供学习使用
 平衡小车
 作者：Flora233 
 学校：湘潭大学TI实验室
 
 感谢正点原子的部分模块开源代码
									大一 2022年8月1日
******************************************************/

int Motor_1, Motor_2;								 //电机输出参数

int main() {
	
	SYS_Init();										 //初始化
	
	while(1) {

	}
}

void SYS_Init() {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组函数
	OLED_Init();									 //OLED初始化
	MPU_Init();	                                     //初始化MPU6050
	
	Motor_Init();
	Encoder_Init();
	PWM_Init();
	PID_Init();
	//UART_Init();
	
	while(mpu_dmp_init())                            //初始化mpu_dmp库
 	{
		OLED_ShowString(1,1,"Failed");			 	 //显示字符串
		OLED_Clear();                              
		delay_ms(200);          
		OLED_Clear();							
	}
	OLED_ShowString(1, 1, "successed");
	delay_ms(200);          
	OLED_Clear();
	OLED_ShowString(1,5,"OK!");						 //显示字符串
	delay_ms(999);									 //延时初界面显示
	OLED_Clear();	
	mpu6050.flag = 0;                                //采集成功标志位初始化
	mpu6050.speed = 0;								 //上报速度初始化
	
	Timer1_InternalClock_Init();
}

void Control() {
	if(mpu_dmp_get_data(&pitch,&roll,&yaw) == 0)	 //获取欧拉角度数据		
	{ 
		MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);	 //获取加速度
		
		float Control_Temp = roll;
		short Encoder_Left = 0, Encoder_Right = 0;
		
		Encoder_Left = (short)TIM_GetCounter(TIM3);   //获取编码器读数
		Encoder_Right = -(short)TIM_GetCounter(TIM4); //保证电机编码器增加的极性相同
		
		TIM_SetCounter(TIM3, 0);					  //清空编码器读数
		TIM_SetCounter(TIM4, 0);
		
		Blance_Control(Control_Temp, gyrox); 	  	  //平衡环
		
		Speed_Control(Encoder_Left, Encoder_Right);	  //速度环
		
		Motor_1 = (int)(Blance.Out + Speed.Out);
		Motor_2 = (int)(Blance.Out + Speed.Out);
		
		PWM_Restrict(&Motor_1, &Motor_2);			  //限幅
		
		if(Motor_Security(Control_Temp))			  //检测倾倒
			PWM_Updata(Motor_1, Motor_2);			  //更新PWM
		else
			PWM_Updata(0, 0);					
		
		mpu6050.flag = 0;
	}
	else { }										  //防卡死
}

void TIM1_UP_IRQHandler() {
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET) {
		Control();									  //每1ms进行一次PID计算
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}

