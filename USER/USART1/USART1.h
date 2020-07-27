#ifndef __USART1_H
#define __USART1_H

#ifdef __cplusplus
extern "C"{
#endif

/* ͷ�ļ����� */
#include "stm32f10x.h"								// Device header

/* �궨�� */
// PB6��ӳ��ΪUSART1��TX����
#define USART1_TX_GPIO_CLK								(RCC_APB2Periph_GPIOB)
#define USART1_TX_GPIO_PORT								(GPIOB)
#define USART1_TX_GPIO_PIN								(GPIO_Pin_6)

// PB7��ӳ��ΪUSART1��RX����
#define USART1_RX_GPIO_CLK								(RCC_APB2Periph_GPIOB)
#define USART1_RX_GPIO_PORT								(GPIOB)
#define USART1_RX_GPIO_PIN								(GPIO_Pin_7)

#define USART1_BAUDRATE								(9600)

/* �������� */
void USART1_Init(void);
void USART1_SendStr(char * l_str);
void USART1_SendData(uint8_t *l_addr, uint8_t l_count);

/* ȫ�ֱ������� */

#ifdef __cplusplus
}
#endif

#endif /* __USART1_H */
