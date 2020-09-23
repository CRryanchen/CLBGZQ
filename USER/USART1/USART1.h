#ifndef __USART1_H
#define __USART1_H

#ifdef __cplusplus
extern "C"{
#endif

/* 头文件包含 */
#include "stm32f10x.h"								// Device header

/* 宏定义 */
/* PB6重映射为USART1的TX引脚 */
#define USART1_TX_GPIO_CLK								(RCC_APB2Periph_GPIOB)/**< UART1 TX 引脚 GPIO 时钟 */
#define USART1_TX_GPIO_PORT								(GPIOB)              /**< UART1 TX 引脚 GPIO 端口 */
#define USART1_TX_GPIO_PIN								(GPIO_Pin_6)          /**< UART1 TX 引脚 GPIO PIN引脚 */

/* PB7重映射为USART1的RX引脚 */
#define USART1_RX_GPIO_CLK								(RCC_APB2Periph_GPIOB)/**< UART1 RX 引脚 GPIO 时钟 */
#define USART1_RX_GPIO_PORT								(GPIOB)              /**< UART1 RX 引脚 GPIO 端口 */
#define USART1_RX_GPIO_PIN								(GPIO_Pin_7)          /**< UART1 RX 引脚 GPIO PIN引脚 */

#define USART1_BAUDRATE							    	(9600)               /**< UART1 波特率 */

/* 函数声明 */

void USART1_Init(void);
void USART1_SendStr(char * l_str);
void USART1_SendData(uint8_t *l_addr, uint8_t l_count);

/* 全局变量声明 */

#ifdef __cplusplus
}
#endif

#endif /* __USART1_H */
