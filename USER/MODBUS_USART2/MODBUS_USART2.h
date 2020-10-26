#ifndef __MODBUS_USART2_H
#define __MODBUS_USART2_H

#ifdef __cplusplus
extern "C"{
#endif

/* 头文件包含 */
#include "stm32f10x.h"								// Device header
#include "MODBUS_USART1.h"                          // 串口自定义数据
#include <stdio.h>                                  // 使用FILE 数据类型

/* 宏定义 */
/* PE2、PE3控制串口发送还是接受 */
#define MODBUS_USART2_CTL1_GPIO_CLK								(RCC_APB2Periph_GPIOE)/**< MODBUS CTL1 GPIO时钟 */
#define MODBUS_USART2_CTL1_GPIO_PORT							(GPIOE)               /**< MODBUS CTL1 GPIO端口 */
#define MODBUS_USART2_CTL1_GPIO_PIN								(GPIO_Pin_4)          /**< MODBUS CTL1 GPIO Pin引脚 */

#define MODBUS_USART2_CTL2_GPIO_CLK								(RCC_APB2Periph_GPIOE)/**< MODBUS CTL2 GPIO时钟 */
#define MODBUS_USART2_CTL2_GPIO_PORT							(GPIOE)               /**< MODBUS CTL2 GPIO端口 */
#define MODBUS_USART2_CTL2_GPIO_PIN								(GPIO_Pin_5)          /**< MODBUS CTL2 GPIO Pin引脚 */


#define MODBUS_USART2_SEND_STATUS								GPIO_SetBits(MODBUS_USART2_CTL1_GPIO_PORT, MODBUS_USART2_CTL1_GPIO_PIN);GPIO_SetBits(MODBUS_USART2_CTL2_GPIO_PORT, MODBUS_USART2_CTL2_GPIO_PIN)// MODBUS_USART2置为发送状态
#define MODBUS_USART2_RECV_STATUS							    GPIO_ResetBits(MODBUS_USART2_CTL1_GPIO_PORT, MODBUS_USART2_CTL1_GPIO_PIN);GPIO_ResetBits(MODBUS_USART2_CTL2_GPIO_PORT, MODBUS_USART2_CTL2_GPIO_PIN)// MODBUS_USART2置为接受状态

/* 函数声明 */

void MODBUS_USART2_Init(void);
int  fputc(int ch, FILE *f);
int  fgetc(FILE *f);
void MODBUS_USART2_COMMUNICATION(void);

/* 全局变量声明 */
extern MODBUS_USART_RECV_STRUCT MODBUS_USART2_RECV;/**< 用于MODBUS_USART2数据接收的结构体 */

#ifdef __cplusplus
}
#endif

#endif /* __MODBUS_USART2_H */
