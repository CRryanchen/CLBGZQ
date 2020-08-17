#ifndef __TIM1_H
#define __TIM1_H

#ifdef __cplusplus
extern "C"{
#endif

/* 头文件包含 */
#include "stm32f10x.h"								// Device header

/* 宏定义 */
// PWM 信号的频率 F = TIM_CLK / {(ARR+1)*(PSC+1)}
#define TIM1_PERIOD                             (1000 - 1)
#define TIM1_PSC                                (720 - 1) 
#define TIM1_PULSE                              500

// TIM1 输出比较通道1
#define TIM1_CH1_GPIO_CLK								(RCC_APB2Periph_GPIOA)
#define TIM1_CH1_GPIO_PORT								(GPIOA)
#define TIM1_CH1_GPIO_PIN								(GPIO_Pin_8)

// TIM1 输出比较通道2
#define TIM1_CH2_GPIO_CLK								(RCC_APB2Periph_GPIOA)
#define TIM1_CH2_GPIO_PORT								(GPIOA)
#define TIM1_CH2_GPIO_PIN								(GPIO_Pin_9)

// TIM1 输出比较通道3
#define TIM1_CH3_GPIO_CLK								(RCC_APB2Periph_GPIOA)
#define TIM1_CH3_GPIO_PORT								(GPIOA)
#define TIM1_CH3_GPIO_PIN								(GPIO_Pin_10)

// TIM1 输出比较通道4
#define TIM1_CH4_GPIO_CLK								(RCC_APB2Periph_GPIOA)
#define TIM1_CH4_GPIO_PORT								(GPIOA)
#define TIM1_CH4_GPIO_PIN								(GPIO_Pin_11)


/* 函数声明 */
static void TIM1_CH_GpioInit(void);
static void TIM1_TimeBaseConfig(void);
static void TIM1_OCConfig(void);
void TIM1_Init(void);

/* 全局变量声明 */

#ifdef __cplusplus
}
#endif

#endif /* __TIM1_H */
