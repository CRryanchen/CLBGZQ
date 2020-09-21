#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern "C"{
#endif

/* ͷ�ļ����� */
#include "stm32f10x.h"								// Device header

/* �궨�� */
#define LED1_GPIO_CLK								(RCC_APB2Periph_GPIOE)                                                                           /**< LED1 GPIO ʱ�� */
#define LED1_GPIO_PORT								(GPIOE)                                                                                         /**< LED1 GPIO �˿� */
#define LED1_GPIO_PIN								(GPIO_Pin_7)                                                                                     /**< LED1 GPIO PIN���� */

#define LED2_GPIO_CLK								(RCC_APB2Periph_GPIOE)                                                                           /**< LED2 GPIO ʱ�� */
#define LED2_GPIO_PORT								(GPIOE)                                                                                         /**< LED2 GPIO �˿� */
#define LED2_GPIO_PIN								(GPIO_Pin_8)                                                                                     /**< LED2 GPIO PIN���� */

#define ON							            	(1)                                                                                             /**< LED ��״̬ */
#define OFF						            		(0)                                                                                            /**< LED ��״̬ */
#define LED1(STATUS)								(STATUS?GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN):GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN))/**< LED1 ����궨�� */
#define LED2(STATUS)								(STATUS?GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO_PIN):GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN))/**< LED2 ����궨�� */
#define LED1_TOGGLE						    		(LED1_GPIO_PORT->ODR ^= LED1_GPIO_PIN)                                                         /**< LED1 ��ת�궨�� */
#define LED2_TOGGLE						    		(LED2_GPIO_PORT->ODR ^= LED2_GPIO_PIN)                                                         /**< LED1 ��ת�궨�� */


/* �������� */

void LED_Init(void);

/* ȫ�ֱ������� */

#ifdef __cplusplus
}
#endif

#endif /* __LED_H */
