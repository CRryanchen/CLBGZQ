#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C"{
#endif

/* ͷ�ļ����� */
#include "stm32f10x.h"								// Device header

/* �궨�� */
#define NUMBER_OF_CHANNELS                          (4)                     /**< ADC ת��ͨ���� */
#define SAMPLE_TIMES                                (215)                   /**< ÿ��ͨ��ת���Ĵ��� */

#define ADC_0_GPIO_CLK								(RCC_APB2Periph_GPIOA)  /**< ADC ͨ��0 ��ӦGPIO ʱ�� */
#define ADC_0_GPIO_PORT								(GPIOA)                 /**< ADC ͨ��0 ��ӦGPIO �˿� */
#define ADC_0_GPIO_PIN								(GPIO_Pin_0)            /**< ADC ͨ��0 ��ӦGPIO Pin ���� */
#define ADC_CHANNEL_0                               (ADC_Channel_0)         /**< ADC ͨ��0 */

#define ADC_1_GPIO_CLK								(RCC_APB2Periph_GPIOA)  /**< ADC ͨ��1 ��ӦGPIO ʱ�� */
#define ADC_1_GPIO_PORT								(GPIOA)                 /**< ADC ͨ��1 ��ӦGPIO �˿� */
#define ADC_1_GPIO_PIN								(GPIO_Pin_1)            /**< ADC ͨ��1 ��ӦGPIO Pin ���� */
#define ADC_CHANNEL_1                               (ADC_Channel_1)         /**< ADC ͨ��1 */

#define ADC_2_GPIO_CLK								(RCC_APB2Periph_GPIOA)  /**< ADC ͨ��2 ��ӦGPIO ʱ�� */
#define ADC_2_GPIO_PORT								(GPIOA)                 /**< ADC ͨ��2 ��ӦGPIO �˿� */
#define ADC_2_GPIO_PIN								(GPIO_Pin_2)            /**< ADC ͨ��2 ��ӦGPIO Pin ���� */
#define ADC_CHANNEL_2                               (ADC_Channel_2)         /**< ADC ͨ��2 */

#define ADC_3_GPIO_CLK								(RCC_APB2Periph_GPIOA)  /**< ADC ͨ��3 ��ӦGPIO ʱ�� */
#define ADC_3_GPIO_PORT								(GPIOA)                 /**< ADC ͨ��3 ��ӦGPIO �˿� */
#define ADC_3_GPIO_PIN								(GPIO_Pin_3)            /**< ADC ͨ��3 ��ӦGPIO Pin ���� */
#define ADC_CHANNEL_3                               (ADC_Channel_3)         /**< ADC ͨ��3 */

#define ADC_SampleTime_MACRO                         ADC_SampleTime_1Cycles5/**< ADC ÿ��ͨ���Ĳ������� */

// ADC1 ��ӦDMA1ͨ��1��
#define ADC_DMA_CHANNEL                             (DMA1_Channel1)         /**< ADC1 ��Ӧ��DMAͨ�� */

//#define ADC_CHANNEL_0_MAX                          1962.213457            /**< ADC1 ͨ��0 AD���������ֵ */
#define ADC_CHANNEL_0_MAX                            1937.2766087            /**< ADC1 ͨ��0 AD���������ֵ */
//#define ADC_CHANNEL_0_MIN                            1086.357245            /**< ADC1 ͨ��0 AD��������Сֵ */
#define ADC_CHANNEL_0_MIN                            1010.249833            /**< ADC1 ͨ��0 AD��������Сֵ */

#define ADC_CHANNEL_1_MAX                            1                      /**< ADC1 ͨ��1 AD���������ֵ */
#define ADC_CHANNEL_1_MIN                            1                      /**< ADC1 ͨ��1 AD��������Сֵ */

#define ADC_CHANNEL_2_MAX                            1                      /**< ADC1 ͨ��2 AD���������ֵ */
#define ADC_CHANNEL_2_MIN                            1                      /**< ADC1 ͨ��2 AD��������Сֵ */

#define ADC_CHANNEL_3_MAX                            1                      /**< ADC1 ͨ��3 AD���������ֵ */
#define ADC_CHANNEL_3_MIN                            1                      /**< ADC1 ͨ��3 AD��������Сֵ */

/* �������� */

void ADC_LocalInit(void);
void ADC_CalcRootMeanSquare(void);
void ADC_CalcWeiYi(uint8_t channel);

/* ȫ�ֱ������� */
extern uint16_t ADC_ConvertValue[SAMPLE_TIMES][NUMBER_OF_CHANNELS];
extern float    ADC_RootMeanSquare[NUMBER_OF_CHANNELS];
extern float    ADC_WeiYi[NUMBER_OF_CHANNELS];
extern uint8_t  ADC_ConvertCompleteFlag;

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H */
