/**
 * @file TIM1.c
 * @brief ��ʱ��1���4·PWM�źţ�ͨ��1��ͨ��2��ͨ��3��ͨ��4��ӦPA8��PA9��PA10��PA11
 *        PWMƵ������Ϊ100HZ
 * @author Ryan��Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 14-08-2020
 *
 * @copyright Copyright (c) 2020  Ryan��Chen
 *
 * @par ������־:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>14-08-2020 <td>1.0     <td>Ryan��Chen     <td>��ʱ��1�������
 * <tr><td>22-09-2020 <td>1.0     <td>Ryan��Chen     <td>����淶��
 * </table>
 */

/* ͷ�ļ����� */
#include "TIM1.h"



/**
 * @brief TIM1 CH1-CH4 GPIO��ʼ��
 */
static void TIM1_CH_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;                                                                          // ��ʼ���ṹ�嶨��

    RCC_APB2PeriphClockCmd(TIM1_CH1_GPIO_CLK | TIM1_CH2_GPIO_CLK | TIM1_CH3_GPIO_CLK | TIM1_CH4_GPIO_CLK, ENABLE);// ����GPIOʱ��

    /* �ṹ������ */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = TIM1_CH1_GPIO_PIN;
    GPIO_Init(TIM1_CH1_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = TIM1_CH2_GPIO_PIN;
    GPIO_Init(TIM1_CH2_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = TIM1_CH3_GPIO_PIN;
    GPIO_Init(TIM1_CH3_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = TIM1_CH4_GPIO_PIN;
    GPIO_Init(TIM1_CH4_GPIO_PORT, &GPIO_InitStructure);
}



/**
 * @brief TIM1 ʱ���ṹ���ʼ��
 */
static void TIM1_TimeBaseConfig(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;                                                            // ��ʱ��ʱ����ʼ���ṹ������

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);                                                          // ����TIM1ʱ��

    TIM_TimeBaseInitStructure.TIM_Prescaler         = TIM1_PSC;                                                   // ������ԤƵ�ʣ� 720
    TIM_TimeBaseInitStructure.TIM_Period            = TIM1_PERIOD;                                                // ���������ڣ� 1000
    TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;                                               // ʱ�ӷ�Ƶ���ӣ���������ʱ��ʱ��Ҫ�õ�
    TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;                                         // ����������ģʽ�����ϼ���
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;                                                          // �ظ���������ֵ��û��ʹ����Ϊ0
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);                                                           // ��ʼ��ʱ���ṹ��
}



/**
 * @brief TIM1 CH1-CH4 ����Ƚ�����
 */
static void TIM1_OCConfig(void)
{
    TIM_OCInitTypeDef TIM_OCInitStructure;                                                                        // ��ʱ������Ƚϳ�ʼ���ṹ������

    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;                                                       // ����ΪPWMģʽ1
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;                                                // ���ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;                                              // ���������ʹ��
    TIM_OCInitStructure.TIM_Pulse        = TIM1_PULSE;                                                            // ����ռ�ձȴ�С
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;                                                   // ���ͨ����ƽ��������
    TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_High;                                                  // �������ͨ����ƽ��������
    TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Set;                                                   // ���ͨ�����е�ƽ��������
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;                                                // �������ͨ�����е�ƽ��������

    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_Cmd(TIM1, ENABLE);                                                                                        // ʹ�ܼ�����
    TIM_CtrlPWMOutputs(TIM1, ENABLE);                                                                             // �����ʹ��
}



/**
 * @brief TIM1 ��ʼ�������ⲿ����
 */
void TIM1_Init(void)
{
    TIM1_CH_GpioInit();
    TIM1_TimeBaseConfig();
    TIM1_OCConfig();
}





