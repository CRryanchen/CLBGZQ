#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C"{
#endif

/* 头文件包含 */
#include "stm32f10x.h"								// Device header

/* 宏定义 */
#define NUMBER_OF_CHANNELS                          (4)                     /**< ADC 转换通道数 */
#define SAMPLE_TIMES                                (215)                   /**< 每个通道转换的次数 */

#define ADC_0_GPIO_CLK								(RCC_APB2Periph_GPIOA)  /**< ADC 通道0 对应GPIO 时钟 */
#define ADC_0_GPIO_PORT								(GPIOA)                 /**< ADC 通道0 对应GPIO 端口 */
#define ADC_0_GPIO_PIN								(GPIO_Pin_0)            /**< ADC 通道0 对应GPIO Pin 引脚 */
#define ADC_CHANNEL_0                               (ADC_Channel_0)         /**< ADC 通道0 */

#define ADC_1_GPIO_CLK								(RCC_APB2Periph_GPIOA)  /**< ADC 通道1 对应GPIO 时钟 */
#define ADC_1_GPIO_PORT								(GPIOA)                 /**< ADC 通道1 对应GPIO 端口 */
#define ADC_1_GPIO_PIN								(GPIO_Pin_1)            /**< ADC 通道1 对应GPIO Pin 引脚 */
#define ADC_CHANNEL_1                               (ADC_Channel_1)         /**< ADC 通道1 */

#define ADC_2_GPIO_CLK								(RCC_APB2Periph_GPIOA)  /**< ADC 通道2 对应GPIO 时钟 */
#define ADC_2_GPIO_PORT								(GPIOA)                 /**< ADC 通道2 对应GPIO 端口 */
#define ADC_2_GPIO_PIN								(GPIO_Pin_2)            /**< ADC 通道2 对应GPIO Pin 引脚 */
#define ADC_CHANNEL_2                               (ADC_Channel_2)         /**< ADC 通道2 */

#define ADC_3_GPIO_CLK								(RCC_APB2Periph_GPIOA)  /**< ADC 通道3 对应GPIO 时钟 */
#define ADC_3_GPIO_PORT								(GPIOA)                 /**< ADC 通道3 对应GPIO 端口 */
#define ADC_3_GPIO_PIN								(GPIO_Pin_3)            /**< ADC 通道3 对应GPIO Pin 引脚 */
#define ADC_CHANNEL_3                               (ADC_Channel_3)         /**< ADC 通道3 */

#define ADC_SampleTime_MACRO                         ADC_SampleTime_1Cycles5/**< ADC 每个通道的采样周期 */

// ADC1 对应DMA1通道1，
#define ADC_DMA_CHANNEL                             (DMA1_Channel1)         /**< ADC1 对应的DMA通道 */

//#define ADC_CHANNEL_0_MAX                          1962.213457            /**< ADC1 通道0 AD均方根最大值 */
#define ADC_CHANNEL_0_MAX                            1937.2766087            /**< ADC1 通道0 AD均方根最大值 */
//#define ADC_CHANNEL_0_MIN                            1086.357245            /**< ADC1 通道0 AD均方根最小值 */
#define ADC_CHANNEL_0_MIN                            1010.249833            /**< ADC1 通道0 AD均方根最小值 */

#define ADC_CHANNEL_1_MAX                            1                      /**< ADC1 通道1 AD均方根最大值 */
#define ADC_CHANNEL_1_MIN                            1                      /**< ADC1 通道1 AD均方根最小值 */

#define ADC_CHANNEL_2_MAX                            1                      /**< ADC1 通道2 AD均方根最大值 */
#define ADC_CHANNEL_2_MIN                            1                      /**< ADC1 通道2 AD均方根最小值 */

#define ADC_CHANNEL_3_MAX                            1                      /**< ADC1 通道3 AD均方根最大值 */
#define ADC_CHANNEL_3_MIN                            1                      /**< ADC1 通道3 AD均方根最小值 */

/* 函数声明 */

void ADC_LocalInit(void);
void ADC_CalcRootMeanSquare(void);
void ADC_CalcWeiYi(uint8_t channel);

/* 全局变量声明 */
extern uint16_t ADC_ConvertValue[SAMPLE_TIMES][NUMBER_OF_CHANNELS];
extern float    ADC_RootMeanSquare[NUMBER_OF_CHANNELS];
extern float    ADC_WeiYi[NUMBER_OF_CHANNELS];
extern uint8_t  ADC_ConvertCompleteFlag;

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H */
