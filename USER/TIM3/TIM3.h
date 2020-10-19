#ifndef __TIM3_H
#define __TIM3_H

#ifdef __cplusplus
extern "C"{
#endif

/* ͷ�ļ����� */
#include "stm32f10x.h"								// Device header

/* �궨�� */
/*  PWM �źŵ�Ƶ�� F = TIM_CLK / {(ARR+1)*(PSC+1)} */
#define TIM3_PERIOD                                     (1000 - 1) /**< ��ʱ���������� */
#define TIM3_PSC                                        (36 - 1)   /**< ��ʱ����Ƶ */
#define TIM3_PULSE                                      500        /**< PWMģʽ OC ���� */

// TIM3 ����Ƚ�ͨ��1
#define TIM3_CH1_GPIO_CLK								(RCC_APB2Periph_GPIOC)/**< TIM3 CH1 GPIOʱ�� */
#define TIM3_CH1_GPIO_PORT								(GPIOC)              /**< TIM3 CH1 GPIO�˿� */
#define TIM3_CH1_GPIO_PIN								(GPIO_Pin_6)          /**< TIM3 CH1 GPIO PIN���� */

// TIM3 ����Ƚ�ͨ��2
#define TIM3_CH2_GPIO_CLK								(RCC_APB2Periph_GPIOC)/**< TIM3 CH2 GPIOʱ�� */
#define TIM3_CH2_GPIO_PORT								(GPIOC)              /**< TIM3 CH2 GPIO�˿� */
#define TIM3_CH2_GPIO_PIN								(GPIO_Pin_7)          /**< TIM3 CH2 GPIO PIN���� */

// TIM3 ����Ƚ�ͨ��3
#define TIM3_CH3_GPIO_CLK								(RCC_APB2Periph_GPIOC)/**< TIM3 CH3 GPIOʱ�� */
#define TIM3_CH3_GPIO_PORT								(GPIOC)              /**< TIM3 CH3 GPIO�˿� */
#define TIM3_CH3_GPIO_PIN								(GPIO_Pin_8)          /**< TIM3 CH3 GPIO PIN���� */

// TIM3 ����Ƚ�ͨ��4
#define TIM3_CH4_GPIO_CLK								(RCC_APB2Periph_GPIOC)/**< TIM3 CH4 GPIOʱ�� */
#define TIM3_CH4_GPIO_PORT								(GPIOC)              /**< TIM3 CH4 GPIO�˿� */
#define TIM3_CH4_GPIO_PIN								(GPIO_Pin_9)          /**< TIM3 CH4 GPIO PIN���� */

/* �������� */

static void TIM3_CH_GpioInit(void);
static void TIM3_TimeBaseConfig(void);
static void TIM3_OCConfig(void);
void TIM3_Init(void);

/* ȫ�ֱ������� */

#ifdef __cplusplus
}
#endif

#endif /* __TIM3_H */
