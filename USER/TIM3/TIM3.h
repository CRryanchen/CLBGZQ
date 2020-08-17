#ifndef __TIM3_H
#define __TIM3_H

#ifdef __cplusplus
extern "C"{
#endif

/* ͷ�ļ����� */
#include "stm32f10x.h"								// Device header

/* �궨�� */
// PWM �źŵ�Ƶ�� F = TIM_CLK / {(ARR+1)*(PSC+1)}
#define TIM3_PERIOD                             (1000 - 1)
#define TIM3_PSC                                (36 - 1) 
#define TIM3_PULSE                              500

// TIM3 ����Ƚ�ͨ��1
#define TIM3_CH1_GPIO_CLK								(RCC_APB2Periph_GPIOA)
#define TIM3_CH1_GPIO_PORT								(GPIOA)
#define TIM3_CH1_GPIO_PIN								(GPIO_Pin_6)

// TIM3 ����Ƚ�ͨ��2
#define TIM3_CH2_GPIO_CLK								(RCC_APB2Periph_GPIOA)
#define TIM3_CH2_GPIO_PORT								(GPIOA)
#define TIM3_CH2_GPIO_PIN								(GPIO_Pin_7)

// TIM3 ����Ƚ�ͨ��3
#define TIM3_CH3_GPIO_CLK								(RCC_APB2Periph_GPIOB)
#define TIM3_CH3_GPIO_PORT								(GPIOB)
#define TIM3_CH3_GPIO_PIN								(GPIO_Pin_0)

// TIM3 ����Ƚ�ͨ��4
#define TIM3_CH4_GPIO_CLK								(RCC_APB2Periph_GPIOB)
#define TIM3_CH4_GPIO_PORT								(GPIOB)
#define TIM3_CH4_GPIO_PIN								(GPIO_Pin_1)

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
