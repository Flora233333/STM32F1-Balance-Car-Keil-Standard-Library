#include "stm32f10x.h"                  // Device header
#include <stdio.h>

uint8_t RxData;
uint8_t RxFlag;

void UART_Init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART3, &USART_InitStructure);
	
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART3, ENABLE);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}

void UART_SendByte(uint8_t byte) {
	USART_SendData(USART3, byte);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}

int fputc(int ch, FILE *f)
{
	UART_SendByte(ch);
	return 0;
}

uint8_t UART_GetRxData() {
	return RxData;
}

uint8_t UART_GetRxFlag() {
	if (RxFlag == 1)
	{
		RxFlag = 0;
		return 1;
	}
	return 0;
}

void USART3_IRQHandler() {
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET) {
		RxData = USART_ReceiveData(USART3);
		RxFlag = 1;
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	}
}

/*void USART1_IRQHandler() {
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
		RxData = USART_ReceiveData(USART1);
		RxFlag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}*/
