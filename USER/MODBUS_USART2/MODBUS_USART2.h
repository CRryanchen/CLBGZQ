#ifndef __MODBUS_USART2_H
#define __MODBUS_USART2_H

#ifdef __cplusplus
extern "C"{
#endif

/* ͷ�ļ����� */
#include <stdio.h>
#include "stm32f10x.h"								// Device header
#include "global.h"

/* �궨�� */
// PE2��PE3���ƴ��ڷ��ͻ��ǽ���
#define MODBUS_USART2_CTL1_GPIO_CLK								(RCC_APB2Periph_GPIOE)
#define MODBUS_USART2_CTL1_GPIO_PORT								(GPIOE)
#define MODBUS_USART2_CTL1_GPIO_PIN								(GPIO_Pin_4)

#define MODBUS_USART2_CTL2_GPIO_CLK								(RCC_APB2Periph_GPIOE)
#define MODBUS_USART2_CTL2_GPIO_PORT								(GPIOE)
#define MODBUS_USART2_CTL2_GPIO_PIN								(GPIO_Pin_5)

// MODBUS_USART2��Ϊ����״̬
#define MODBUS_USART2_SEND_STATUS								GPIO_SetBits(MODBUS_USART2_CTL1_GPIO_PORT, MODBUS_USART2_CTL1_GPIO_PIN);GPIO_SetBits(MODBUS_USART2_CTL2_GPIO_PORT, MODBUS_USART2_CTL2_GPIO_PIN)
// MODBUS_USART2��Ϊ����״̬
#define MODBUS_USART2_RECV_STATUS							    GPIO_ResetBits(MODBUS_USART2_CTL1_GPIO_PORT, MODBUS_USART2_CTL1_GPIO_PIN);GPIO_ResetBits(MODBUS_USART2_CTL2_GPIO_PORT, MODBUS_USART2_CTL2_GPIO_PIN)

/* �������� */
void MODBUS_USART2_Init(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

/* ȫ�ֱ������� */

#ifdef __cplusplus
}
#endif

#endif /* __MODBUS_USART2_H */
