#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern "C"{
#endif

/* 头文件包含 */
#include "stm32f10x.h"								// Device header

/* 宏定义 */
#define LED1_GPIO_CLK								(RCC_APB2Periph_GPIOE)
#define LED1_GPIO_PORT								(GPIOE)
#define LED1_GPIO_PIN								(GPIO_Pin_7)

#define LED2_GPIO_CLK								(RCC_APB2Periph_GPIOE)
#define LED2_GPIO_PORT								(GPIOE)
#define LED2_GPIO_PIN								(GPIO_Pin_8)

#define ON								(1)
#define OFF								(0)
#define LED1(STATUS)								(STATUS?GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN):GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN))
#define LED2(STATUS)								(STATUS?GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO_PIN):GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN))
#define LED1_TOGGLE								(LED1_GPIO_PORT->ODR ^= LED1_GPIO_PIN)
#define LED2_TOGGLE								(LED2_GPIO_PORT->ODR ^= LED2_GPIO_PIN)


/* 函数声明 */
void LED_Init(void);

/* 全局变量声明 */

#ifdef __cplusplus
}
#endif

#endif /* __LED_H */
