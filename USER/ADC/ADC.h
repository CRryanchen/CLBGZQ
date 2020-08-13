#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C"{
#endif

/* 头文件包含 */
#include "stm32f10x.h"								// Device header

/* 宏定义 */
#define NUMBER_OF_CHANNELS                          (4)

#define ADC_0_GPIO_CLK								(RCC_APB2Periph_GPIOA)
#define ADC_0_GPIO_PORT								(GPIOA)
#define ADC_0_GPIO_PIN								(GPIO_Pin_0)
#define ADC_CHANNEL_0                               (ADC_Channel_0)

#define ADC_1_GPIO_CLK								(RCC_APB2Periph_GPIOA)
#define ADC_1_GPIO_PORT								(GPIOA)
#define ADC_1_GPIO_PIN								(GPIO_Pin_1)
#define ADC_CHANNEL_1                               (ADC_Channel_1)

#define ADC_2_GPIO_CLK								(RCC_APB2Periph_GPIOA)
#define ADC_2_GPIO_PORT								(GPIOA)
#define ADC_2_GPIO_PIN								(GPIO_Pin_2)
#define ADC_CHANNEL_2                               (ADC_Channel_2)

#define ADC_3_GPIO_CLK								(RCC_APB2Periph_GPIOA)
#define ADC_3_GPIO_PORT								(GPIOA)
#define ADC_3_GPIO_PIN								(GPIO_Pin_3)
#define ADC_CHANNEL_3                               (ADC_Channel_3)

// ADC1 对应DMA1通道1，
#define ADC_DMA_CHANNEL                             (DMA1_Channel1)


/* 函数声明 */
void ADC_LocalInit(void);

/* 全局变量声明 */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H */
