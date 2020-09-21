#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C"{
#endif

/* 头文件包含 */
#include "stm32f10x.h"								// Device header


/* 宏定义 */
#define NUMBER_OF_CHANNELS                          (4)
#define SAMPLE_TIMES                                (215)

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

#define ADC_SampleTime_MACRO                         ADC_SampleTime_1Cycles5

// ADC1 对应DMA1通道1，
#define ADC_DMA_CHANNEL                             (DMA1_Channel1)

#define ADC_CHANNEL_0_MAX                            2004.182856
#define ADC_CHANNEL_0_MIN                            1142.077691

#define ADC_CHANNEL_1_MAX                            1
#define ADC_CHANNEL_1_MIN                            1

#define ADC_CHANNEL_2_MAX                            1
#define ADC_CHANNEL_2_MIN                            1

#define ADC_CHANNEL_3_MAX                            1
#define ADC_CHANNEL_3_MIN                            1

/* 函数声明 */
void ADC_LocalInit(void);
void ADC_CalcRootMeanSquare(void);
void ADC_CalcWeiYi(uint8_t channel);

/* 全局变量声明 */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H */
