#ifndef __TIM1_H
#define __TIM1_H

#ifdef __cplusplus
extern "C"{
#endif

/* ͷ�ļ����� */
#include "stm32f10x.h"								// Device header

/* �궨�� */
// PWM �źŵ�Ƶ�� F = TIM_CLK / {(ARR+1)*(PSC+1)}
#define TIM1_PERIOD                             (1000 - 1)
#define TIM1_PSC                                (720 - 1) 
#define TIM1_PULSE                              500

// TIM1 ����Ƚ�ͨ��1
#define TIM1_CH1_GPIO_CLK								(RCC_APB2Periph_GPIOA)
#define TIM1_CH1_GPIO_PORT								(GPIOA)
#define TIM1_CH1_GPIO_PIN								(GPIO_Pin_8)

// TIM1 ����Ƚ�ͨ��2
#define TIM1_CH2_GPIO_CLK								(RCC_APB2Periph_GPIOA)
#define TIM1_CH2_GPIO_PORT								(GPIOA)
#define TIM1_CH2_GPIO_PIN								(GPIO_Pin_9)

// TIM1 ����Ƚ�ͨ��3
#define TIM1_CH3_GPIO_CLK								(RCC_APB2Periph_GPIOA)
#define TIM1_CH3_GPIO_PORT								(GPIOA)
#define TIM1_CH3_GPIO_PIN								(GPIO_Pin_10)

// TIM1 ����Ƚ�ͨ��4
#define TIM1_CH4_GPIO_CLK								(RCC_APB2Periph_GPIOA)
#define TIM1_CH4_GPIO_PORT								(GPIOA)
#define TIM1_CH4_GPIO_PIN								(GPIO_Pin_11)


/* �������� */
static void TIM1_CH_GpioInit(void);
static void TIM1_TimeBaseConfig(void);
static void TIM1_OCConfig(void);
void TIM1_Init(void);

/* ȫ�ֱ������� */

#ifdef __cplusplus
}
#endif

#endif /* __TIM1_H */
