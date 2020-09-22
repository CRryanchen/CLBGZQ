#ifndef __TIM3_H
#define __TIM3_H

#ifdef __cplusplus
extern "C"{
#endif

/* 头文件包含 */
#include "stm32f10x.h"								// Device header

/* 宏定义 */
/*  PWM 信号的频率 F = TIM_CLK / {(ARR+1)*(PSC+1)} */
#define TIM3_PERIOD                                     (1000 - 1) /**< 定时器计数周期 */
#define TIM3_PSC                                        (36 - 1)   /**< 定时器分频 */
#define TIM3_PULSE                                      500        /**< PWM模式 OC 配置 */

// TIM3 输出比较通道1
#define TIM3_CH1_GPIO_CLK								(RCC_APB2Periph_GPIOA)/**< TIM3 CH1 GPIO时钟 */
#define TIM3_CH1_GPIO_PORT								(GPIOA)              /**< TIM3 CH1 GPIO端口 */
#define TIM3_CH1_GPIO_PIN								(GPIO_Pin_6)          /**< TIM3 CH1 GPIO PIN引脚 */

// TIM3 输出比较通道2
#define TIM3_CH2_GPIO_CLK								(RCC_APB2Periph_GPIOA)/**< TIM3 CH2 GPIO时钟 */
#define TIM3_CH2_GPIO_PORT								(GPIOA)              /**< TIM3 CH2 GPIO端口 */
#define TIM3_CH2_GPIO_PIN								(GPIO_Pin_7)          /**< TIM3 CH2 GPIO PIN引脚 */

// TIM3 输出比较通道3
#define TIM3_CH3_GPIO_CLK								(RCC_APB2Periph_GPIOB)/**< TIM3 CH3 GPIO时钟 */
#define TIM3_CH3_GPIO_PORT								(GPIOB)              /**< TIM3 CH3 GPIO端口 */
#define TIM3_CH3_GPIO_PIN								(GPIO_Pin_0)          /**< TIM3 CH3 GPIO PIN引脚 */

// TIM3 输出比较通道4
#define TIM3_CH4_GPIO_CLK								(RCC_APB2Periph_GPIOB)/**< TIM3 CH4 GPIO时钟 */
#define TIM3_CH4_GPIO_PORT								(GPIOB)              /**< TIM3 CH4 GPIO端口 */
#define TIM3_CH4_GPIO_PIN								(GPIO_Pin_1)          /**< TIM3 CH4 GPIO PIN引脚 */

/* 函数声明 */

static void TIM3_CH_GpioInit(void);
static void TIM3_TimeBaseConfig(void);
static void TIM3_OCConfig(void);
void TIM3_Init(void);

/* 全局变量声明 */

#ifdef __cplusplus
}
#endif

#endif /* __TIM3_H */
