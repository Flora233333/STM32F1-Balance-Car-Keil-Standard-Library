#ifndef __PID_H
#define __PID_H

typedef struct PID {
    float Angle_target;
	float Speed_target;

    float EK;
    float EK_0;
    float SEK;

	float KP;
    float KI;
    float KD;

    float Out;
} PID;

extern PID Blance, Speed;

void PID_Init(void);
void Blance_Control(float Angle, short Gyro);
void Speed_Control(short Encoder_Left, short Encoder_Right);

#endif
