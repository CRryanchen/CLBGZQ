#ifndef __MODBUS_USART2_H
#define __MODBUS_USART2_H

#ifdef __cplusplus
extern "C"{
#endif

/* ͷ�ļ����� */
#include "stm32f10x.h"								// Device header
#include "MODBUS_USART1.h"                          // �����Զ�������
#include <stdio.h>                                  // ʹ��FILE ��������

/* �궨�� */
/* PE2��PE3���ƴ��ڷ��ͻ��ǽ��� */
#define MODBUS_USART2_CTL1_GPIO_CLK								(RCC_APB2Periph_GPIOE)/**< MODBUS CTL1 GPIOʱ�� */
#define MODBUS_USART2_CTL1_GPIO_PORT							(GPIOE)               /**< MODBUS CTL1 GPIO�˿� */
#define MODBUS_USART2_CTL1_GPIO_PIN								(GPIO_Pin_4)          /**< MODBUS CTL1 GPIO Pin���� */

#define MODBUS_USART2_CTL2_GPIO_CLK								(RCC_APB2Periph_GPIOE)/**< MODBUS CTL2 GPIOʱ�� */
#define MODBUS_USART2_CTL2_GPIO_PORT							(GPIOE)               /**< MODBUS CTL2 GPIO�˿� */
#define MODBUS_USART2_CTL2_GPIO_PIN								(GPIO_Pin_5)          /**< MODBUS CTL2 GPIO Pin���� */


#define MODBUS_USART2_SEND_STATUS								GPIO_SetBits(MODBUS_USART2_CTL1_GPIO_PORT, MODBUS_USART2_CTL1_GPIO_PIN);GPIO_SetBits(MODBUS_USART2_CTL2_GPIO_PORT, MODBUS_USART2_CTL2_GPIO_PIN)// MODBUS_USART2��Ϊ����״̬
#define MODBUS_USART2_RECV_STATUS							    GPIO_ResetBits(MODBUS_USART2_CTL1_GPIO_PORT, MODBUS_USART2_CTL1_GPIO_PIN);GPIO_ResetBits(MODBUS_USART2_CTL2_GPIO_PORT, MODBUS_USART2_CTL2_GPIO_PIN)// MODBUS_USART2��Ϊ����״̬

/* �������� */

void MODBUS_USART2_Init(void);
int  fputc(int ch, FILE *f);
int  fgetc(FILE *f);
void MODBUS_USART2_COMMUNICATION(void);

/* ȫ�ֱ������� */
extern MODBUS_USART_RECV_STRUCT MODBUS_USART2_RECV;/**< ����MODBUS_USART2���ݽ��յĽṹ�� */

#ifdef __cplusplus
}
#endif

#endif /* __MODBUS_USART2_H */
