#include "PID.h"

PID Blance;	
PID Speed;	

void PID_Init() {	//PID������ʼ��

    Blance.Angle_target = 0;

    Blance.KP = 85;
    Blance.KI = 0;
	Blance.KD = 0.53;
    Blance.EK_0 = 0;
    Blance.SEK = 0;

    Speed.KP = 36.89; //(1)35.2, 0.176 (2)36.58, 0.1829
    Speed.KI = 0.1845;
    Speed.KD = 0;
    Speed.EK_0 = 0;
    Speed.SEK = 0;

}

void Blance_Control(float Angle, short Gyro) {	  //ƽ�⻷
    Blance.EK = Angle - 0;
    //Blance.Out = Blance.KP * Blance.EK + Blance.KD * (Blance.EK - Blance.EK_0);
	Blance.Out = Blance.KP * Blance.EK + Blance.KD * Gyro;
	//Blance.EK_0 = Blance.EK;
}

void Speed_Control(short Encoder_Left, short Encoder_Right) { //�ٶȻ�
	float Encoder = 0;
	
	Speed.EK = (Encoder_Left + Encoder_Right) - 0;
	
	Encoder = Speed.EK_0 * 0.8 + Speed.EK * 0.2;			  //��ͨ�˲���ʹ�ñ仯������
	Speed.SEK += Encoder;
	
	if(Speed.SEK > 800) Speed.SEK = 800;					  //�����޷�
	if(Speed.SEK < -800) Speed.SEK = -800;
	
	Speed.Out = Speed.KP * Speed.EK + Speed.KI * Speed.SEK;

	Speed.EK_0 = Encoder;
}
