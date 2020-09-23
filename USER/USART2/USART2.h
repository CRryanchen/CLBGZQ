#ifndef __USART2_H
#define __USART2_H

#ifdef __cplusplus
extern "C"{
#endif

/* 头文件包含 */
#include "stm32f10x.h"								    // Device header

/* 宏定义 */
/* PB6重映射为USART2的TX引脚 */
#define USART2_TX_GPIO_CLK								(RCC_APB2Periph_GPIOD)/**< UART2 TX 引脚 GPIO 时钟 */
#define USART2_TX_GPIO_PORT								(GPIOD)              /**< UART2 TX 引脚 GPIO 端口 */
#define USART2_TX_GPIO_PIN								(GPIO_Pin_5)          /**< UART2 TX 引脚 GPIO PIN引脚 */

/* PB7重映射为USART2的RX引脚 */
#define USART2_RX_GPIO_CLK								(RCC_APB2Periph_GPIOD)/**< UART2 RX 引脚 GPIO 时钟 */
#define USART2_RX_GPIO_PORT								(GPIOD)              /**< UART2 RX 引脚 GPIO 端口 */
#define USART2_RX_GPIO_PIN								(GPIO_Pin_6)          /**< UART2 RX 引脚 GPIO PIN引脚 */

#define USART2_BAUDRATE							    	(9600)               /**< UART2 波特率 */

/* 函数声明 */

void USART2_Init(void);
void USART2_SendStr(char * l_str);

/* 全局变量声明 */

#ifdef __cplusplus
}
#endif

#endif /* __USART2_H */
