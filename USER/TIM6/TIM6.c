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
 * </table>
 */

#include "TIM6.h"

/**
 * @brief TIM6 ʱ����ʼ��
 */
static void TIM6_TimeBaseConfig(void)
{
    // ��ʱ��ʱ����ʼ���ṹ������
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    // ����TIM6ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    // ������ԤƵ�ʣ� 72 / 72 = 1MHz
    TIM_TimeBaseInitStructure.TIM_Prescaler = (72 - 1);
    // ���������ڣ� 3000
    TIM_TimeBaseInitStructure.TIM_Period = (3000 - 1);

    // ��Ϊ�����ֶ����ԣ�3ms�����ƿأ��������������ʱ��Ϊ��ʱ3s
    //TIM_TimeBaseInitStructure.TIM_Prescaler = (7200 - 1);
    //TIM_TimeBaseInitStructure.TIM_Period = (30000 - 1);

    // һ���������û�����ʱ����ʹ��
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;

    // ��ʼ��ʱ���ṹ��
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);
}


/**
 * @brief TIM6�ж����ȼ�����
 */
static void TIM6_NVICConfig(void)
{
    // �����жϿ��������ĳ�ʼ���ṹ�����
    NVIC_InitTypeDef NVIC_InitStructure;
    
    // ÿ�����̶���Ҫѡ��Ƕ�������жϿ��Ʒ��飬����ֻѡ��һ�Σ�����������������ѡ��
    
    // ѡ���ж�Դ
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
    // �����жϵ���ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    // �����жϵ������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    // �Ƿ�ʹ�ܸ��ж�Դ
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // ��ʼ���ṹ��
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief TIM6��ʼ�������ⲿ����
 */
void TIM6_Init(void)
{
    TIM6_NVICConfig();
    TIM6_TimeBaseConfig();

    // ��������жϱ�־λ
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
    // ����TIM6�����ж�
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    // �ݲ�ʹ��TIM6
    TIM_Cmd(TIM6, DISABLE);
}
