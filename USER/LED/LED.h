#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern "C"{
#endif

/* 头文件包含 */
#include "stm32f10x.h"								// Device header

/* 宏定义 */
#define LED1_GPIO_CLK								(RCC_APB2Periph_GPIOE)                                                                           /**< LED1 GPIO 时钟 */
#define LED1_GPIO_PORT								(GPIOE)                                                                                         /**< LED1 GPIO 端口 */
#define LED1_GPIO_PIN								(GPIO_Pin_7)                                                                                     /**< LED1 GPIO PIN引脚 */

#define LED2_GPIO_CLK								(RCC_APB2Periph_GPIOE)                                                                           /**< LED2 GPIO 时钟 */
#define LED2_GPIO_PORT								(GPIOE)                                                                                         /**< LED2 GPIO 端口 */
#define LED2_GPIO_PIN								(GPIO_Pin_8)                                                                                     /**< LED2 GPIO PIN引脚 */

#define ON							            	(1)                                                                                             /**< LED 开状态 */
#define OFF						            		(0)                                                                                            /**< LED 开状态 */
#define LED1(STATUS)								(STATUS?GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN):GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN))/**< LED1 亮灭宏定义 */
#define LED2(STATUS)								(STATUS?GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO_PIN):GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN))/**< LED2 亮灭宏定义 */
#define LED1_TOGGLE						    		(LED1_GPIO_PORT->ODR ^= LED1_GPIO_PIN)                                                         /**< LED1 翻转宏定义 */
#define LED2_TOGGLE						    		(LED2_GPIO_PORT->ODR ^= LED2_GPIO_PIN)                                                         /**< LED1 翻转宏定义 */


/* 函数声明 */

void LED_Init(void);

/* 全局变量声明 */

#ifdef __cplusplus
}
#endif

#endif /* __LED_H */
