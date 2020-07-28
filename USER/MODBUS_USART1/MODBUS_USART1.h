#ifndef __MODBUS_USART1_H
#define __MODBUS_USART1_H

#ifdef __cplusplus
extern "C"{
#endif

/* 头文件包含 */
#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"								// Device header
#include "global.h"

/* 宏定义 */
// PE2、PE3控制串口发送还是接受
#define MODBUS_USART1_CTL1_GPIO_CLK								(RCC_APB2Periph_GPIOE)
#define MODBUS_USART1_CTL1_GPIO_PORT								(GPIOE)
#define MODBUS_USART1_CTL1_GPIO_PIN								(GPIO_Pin_2)

#define MODBUS_USART1_CTL2_GPIO_CLK								(RCC_APB2Periph_GPIOE)
#define MODBUS_USART1_CTL2_GPIO_PORT								(GPIOE)
#define MODBUS_USART1_CTL2_GPIO_PIN								(GPIO_Pin_3)

// MODBUS_USART1置为发送状态
#define MODBUS_USART1_SEND_STATUS								GPIO_SetBits(MODBUS_USART1_CTL1_GPIO_PORT, MODBUS_USART1_CTL1_GPIO_PIN);GPIO_SetBits(MODBUS_USART1_CTL2_GPIO_PORT, MODBUS_USART1_CTL2_GPIO_PIN)
// MODBUS_USART1置为接受状态
#define MODBUS_USART1_RECV_STATUS							    GPIO_ResetBits(MODBUS_USART1_CTL1_GPIO_PORT, MODBUS_USART1_CTL1_GPIO_PIN);GPIO_ResetBits(MODBUS_USART1_CTL2_GPIO_PORT, MODBUS_USART1_CTL2_GPIO_PIN)

/* 函数声明 */
void MODBUS_USART1_Init(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
void MODBUS_USART1_COMMUNICATION(void);
unsigned int CRC16(unsigned char *nData, unsigned int wLength);

/* 全局变量声明 */

#ifdef __cplusplus
}
#endif

#endif /* __MODBUS_USART1_H */
