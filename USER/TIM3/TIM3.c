/**
 * @file TIM3.c
 * @brief ���ö�ʱ��3��ͨ��1��2��3��4���Ƶ��Ϊ2Kռ�ձ�Ϊ50%�ķ���
 * @author Ryan��Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 17-08-2020
 * 
 * @copyright Copyright (c) 2020  Ryan��Chen
 * 
 * @par ������־:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>17-08-2020 <td>1.0     <td>Ryan��Chen     <td>����
 * </table>
 */

#include "TIM3.h"

static void TIM3_CH_GpioInit(void)
{
    /* ��ʼ���ṹ�嶨�� */
    GPIO_InitTypeDef GPIO_InitStructure;

    // ����GPIOʱ�ӡ�AFIOʱ��
    RCC_APB2PeriphClockCmd(TIM3_CH1_GPIO_CLK | TIM3_CH2_GPIO_CLK | TIM3_CH3_GPIO_CLK | TIM3_CH4_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

    // ������ӳ��
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);

    // �ṹ������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = TIM3_CH1_GPIO_PIN;
    GPIO_Init(TIM3_CH1_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = TIM3_CH2_GPIO_PIN;
    GPIO_Init(TIM3_CH2_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = TIM3_CH3_GPIO_PIN;
    GPIO_Init(TIM3_CH3_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = TIM3_CH4_GPIO_PIN;
    GPIO_Init(TIM3_CH4_GPIO_PORT, &GPIO_InitStructure);
}

static void TIM3_TimeBaseConfig(void)
{
    // ��ʱ��ʱ����ʼ���ṹ������
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    // ����TIM3ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitStructure.TIM_Prescaler         = TIM3_PSC;            // ������ԤƵ�ʣ� 720
    TIM_TimeBaseInitStructure.TIM_Period            = TIM3_PERIOD;         // ���������ڣ� 1000
    TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;        // ʱ�ӷ�Ƶ���ӣ���������ʱ��ʱ��Ҫ�õ�
    TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;  // ����������ģʽ�����ϼ���
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;                   // �ظ���������ֵ��û��ʹ����Ϊ0
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);                    // ��ʼ��ʱ���ṹ��
}

static void TIM3_OCConfig(void)
{
    // ��ʱ������Ƚϳ�ʼ���ṹ������
    TIM_OCInitTypeDef TIM_OCInitStructure;

    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;           // ����ΪPWMģʽ1
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;    // ���ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;  // ���������ʹ��
    TIM_OCInitStructure.TIM_Pulse        = TIM3_PULSE;                // ����ռ�ձȴ�С
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;       // ���ͨ����ƽ��������
    TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_High;      // �������ͨ����ƽ��������
    TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Set;       // ���ͨ�����е�ƽ��������
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;    // �������ͨ�����е�ƽ��������

    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

    // ʹ�ܼ�����
    TIM_Cmd(TIM3, ENABLE);
    // �����ʹ��
    TIM_CtrlPWMOutputs(TIM3, ENABLE);
}

void TIM3_Init(void)
{
    TIM3_CH_GpioInit();
    TIM3_TimeBaseConfig();
    TIM3_OCConfig();
}
