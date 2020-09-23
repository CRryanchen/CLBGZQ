/**
 * @file TIM6.c
 * @brief  ʹ�û�����ʱ��TIM6���ж�ʱ����Modbusͨ�ŵĽ�����ÿ�ν��յ�����������ʱ����
 * �����ʱ������������ﵽ�ͨ��ʱ�䣬������ͨ�ŵ��жϱ�׼����ʱʱ��Ϊ3.5���ֽڽ���ʱ�䣬
 * ������ǲ���������Ϊ9600����ʱ��Ϊ��3.5*8/9600��Լ����3ms����
 * @author Ryan��Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 24-07-2020
 *
 * @copyright Copyright (c) 2020  Ryan��Chen
 *
 * @par ������־:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>24-07-2020 <td>1.0     <td>Ryan��Chen     <td>ʹ�û�����ʱ��TIM6�ж�MODBUSͨ�ŵĽ���
 * <tr><td>22-09-2020 <td>1.0     <td>Ryan��Chen     <td>����淶��
 * </table>
 */

/* ͷ�ļ����� */
#include "TIM6.h"

/**
 * @brief TIM6 ʱ����ʼ��
 */
static void TIM6_TimeBaseConfig(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;                         // ��ʱ��ʱ����ʼ���ṹ������

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);                       // ����TIM6ʱ��

    TIM_TimeBaseInitStructure.TIM_Prescaler = (72 - 1);                        // ������ԤƵ�ʣ� 72 / 72 = 1MHz
    TIM_TimeBaseInitStructure.TIM_Period    = (3000 - 1);                      // ���������ڣ� 3000

    /* �����������û�����ʱ����ʹ�� */
    TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);                        // ��ʼ��ʱ���ṹ��
}


/**
 * @brief TIM6�ж����ȼ�����
 */
static void TIM6_NVICConfig(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;                                       // �����жϿ��������ĳ�ʼ���ṹ�����

    /* ÿ�����̶���Ҫѡ��Ƕ�������жϿ��Ʒ��飬����ֻѡ��һ�Σ�����������������ѡ�� */

    NVIC_InitStructure.NVIC_IRQChannel                   = TIM6_IRQn;          // ѡ���ж�Դ
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;                  // �����жϵ���ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;                  // �����жϵ������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;             // �Ƿ�ʹ�ܸ��ж�Դ
    NVIC_Init(&NVIC_InitStructure);                                            // ��ʼ���ṹ��
}

/**
 * @brief TIM6��ʼ�������ⲿ����
 */
void TIM6_Init(void)
{
    TIM6_NVICConfig();
    TIM6_TimeBaseConfig();

    TIM_ClearFlag(TIM6, TIM_FLAG_Update);                                      // ��������жϱ�־λ
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);                                 // ����TIM6�����ж�
    TIM_Cmd(TIM6, DISABLE);                                                    // �ݲ�ʹ��TIM6
}
