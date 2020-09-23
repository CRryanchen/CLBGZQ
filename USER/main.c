/**
 * @file main.c
 * @brief �������Ҫִ�����̣�2020.09.21���
 * @author Ryan��Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 21-09-2020
 *
 * @copyright Copyright (c) 2020  Ryan��Chen
 *
 * @par ������־:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>21-09-2020 <td>1.0     <td>Ryan��Chen     <td>�����ļ�ͷ˵�����淶ע�ͣ�ɾ������Ҫ���롢����
 * </table>
 */
#include "global.h"

/**
 * @brief ��ʼ��Kֵ����ʱ����main����
 */
static void K_ValueInit()
{
    K1_Value  = *(float *)K1_ADDR;
    K2_Value  = *(float *)K2_ADDR;
    K3_Value  = *(float *)K3_ADDR;
    K4_Value  = *(float *)K4_ADDR;
    K5_Value  = *(float *)K5_ADDR;
    K6_Value  = *(float *)K6_ADDR;
    K7_Value  = *(float *)K7_ADDR;
    K8_Value  = *(float *)K8_ADDR;
    K9_Value  = *(float *)K9_ADDR;
    K10_Value = *(float *)K10_ADDR;
}



int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);             // ѡ��NVIC ����
    LED_Init();                                                 // LED��ʼ��
#if defined PRINTF_USE_USART2
	MODBUS_USART2_Init();                                       // ��ʼ������2
#else
    MODBUS_USART1_Init();                                       // ��ʼ������1
#endif /* PRINTF_USE_USART2 */
    TIM6_Init();                                                // TIM6 ��ʼ��
    K_ValueInit();                                              // Kֵ��ʼ��
    TIM1_Init();                                                // TIM1 ��ʼ��
    TIM3_Init();                                                // TIM3 ��ʼ��
    ADC_LocalInit();                                            // ADC1 ��ʼ��

    while(1)
    {
        if (ADC_ConvertCompleteFlag == 1)
        {
            /* Ϊ�˱��ڵ��ԣ��������ѭ�����ڴ�ӡ���������У���һ��ͨ������ÿһ�����ֵ��������Excel�鿴
             * �����Ƿ���С��������ú����ӡ��û�ж�������������һͨ����λ�ƣ��봥����ͨ�š�
             */
#ifdef WAVEPRINT
            for (int i = 0; i < SAMPLE_TIMES; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    printf("%d\r\n", ADC_ConvertValue[i][j]);
                }
            }
            SysTick_Delayms(2000);
#else
            ADC_CalcRootMeanSquare();
            ADC_CalcWeiYi(0);
#endif
            ADC_ConvertCompleteFlag = 0;                        // ADC_ConvertCompleteFlag ��Ϊ0
            ADC_LocalInit();                                    // ���� DMA

        }

#if defined PRINTF_USE_USART2
        if (MODBUS_USART2_RECV.MODBUS_USART_COMPLETE_FLAG == 1)
				{
					MODBUS_USART2_COMMUNICATION();                    // ����MODBUS��Ϣ
					MODBUS_USART2_RECV.MODBUS_USART_RECV_COUNT = 0;   // ���ڼ���������
				MODBUS_USART2_RECV.MODBUS_USART_COMPLETE_FLAG = 0;    // ����ͨ�ű�־����
				}
#else
        if (MODBUS_USART1_RECV.MODBUS_USART_COMPLETE_FLAG == 1)
				{
					MODBUS_USART1_COMMUNICATION();                    // ����MODBUS��Ϣ
					MODBUS_USART1_RECV.MODBUS_USART_RECV_COUNT = 0;   // ���ڼ���������
					MODBUS_USART1_RECV.MODBUS_USART_COMPLETE_FLAG = 0;// ����ͨ�ű�־����
				}
#endif
    }
}
