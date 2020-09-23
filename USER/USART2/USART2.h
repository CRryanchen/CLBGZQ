#ifndef __USART2_H
#define __USART2_H

#ifdef __cplusplus
extern "C"{
#endif

/* ͷ�ļ����� */
#include "stm32f10x.h"								    // Device header

/* �궨�� */
/* PB6��ӳ��ΪUSART2��TX���� */
#define USART2_TX_GPIO_CLK								(RCC_APB2Periph_GPIOD)/**< UART2 TX ���� GPIO ʱ�� */
#define USART2_TX_GPIO_PORT								(GPIOD)              /**< UART2 TX ���� GPIO �˿� */
#define USART2_TX_GPIO_PIN								(GPIO_Pin_5)          /**< UART2 TX ���� GPIO PIN���� */

/* PB7��ӳ��ΪUSART2��RX���� */
#define USART2_RX_GPIO_CLK								(RCC_APB2Periph_GPIOD)/**< UART2 RX ���� GPIO ʱ�� */
#define USART2_RX_GPIO_PORT								(GPIOD)              /**< UART2 RX ���� GPIO �˿� */
#define USART2_RX_GPIO_PIN								(GPIO_Pin_6)          /**< UART2 RX ���� GPIO PIN���� */

#define USART2_BAUDRATE							    	(9600)               /**< UART2 ������ */

/* �������� */

void USART2_Init(void);
void USART2_SendStr(char * l_str);

/* ȫ�ֱ������� */

#ifdef __cplusplus
}
#endif

#endif /* __USART2_H */
