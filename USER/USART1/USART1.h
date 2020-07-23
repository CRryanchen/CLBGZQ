#ifndef __USART1_H
#define __USART1_H

#ifdef __cplusplus
extern "C"{
#endif

/* 头文件包含 */
#include "stm32f10x.h"								// Device header

/* 宏定义 */
// PB6重映射为USART1的TX引脚
#define USART1_TX_GPIO_CLK								(RCC_APB2Periph_GPIOB)
#define USART1_TX_GPIO_PORT								(GPIOB)
#define USART1_TX_GPIO_PIN								(GPIO_Pin_6)

// PB7重映射为USART1的RX引脚
#define USART1_RX_GPIO_CLK								(RCC_APB2Periph_GPIOB)
#define USART1_RX_GPIO_PORT								(GPIOB)
#define USART1_RX_GPIO_PIN								(GPIO_Pin_7)

#define USART1_BAUDRATE								(115200)

/* 函数声明 */
void USART1_Init(void);
void USART1_SendStr(char * l_str);

/* 全局变量声明 */

#ifdef __cplusplus
}
#endif

#endif /* __USART1_H */
