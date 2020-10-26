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
 * <tr><td>26-10-2020 <td>1.0     <td>Ryan��Chen     <td>��ʼ����ADͨ���Ĳο���ֵ
 * </table>
 */
#include "global.h"

/**
 * @brief ��ʼ��Kֵ����ʱ����main����
 */
static void K_ValueInit()
{
    uint32_t temp = 0;
    
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

    temp = 0;
    temp = *(unsigned int *)CH0MIN_ADDR;
    if (temp + 1 == 0)
    {
        ADC_Ch0MinValue = ADC_CHANNEL_0_MIN;
    }
    else
    {
        ADC_Ch0MinValue = *(float *)CH0MIN_ADDR;
    }
    
    temp = 0;
    temp = *(unsigned int *)CH0MAX_ADDR;
    if (temp + 1 == 0)
    {
        ADC_Ch0MaxValue = ADC_CHANNEL_0_MAX;
    }
    else
    {
        ADC_Ch0MaxValue = *(float *)CH0MAX_ADDR;
    }
    
    temp = 0;
    temp = *(unsigned int *)CH1MIN_ADDR;
    if (temp + 1 == 0)
    {
        ADC_Ch1MinValue = ADC_CHANNEL_1_MIN;
    }
    else
    {
        ADC_Ch1MinValue = *(float *)CH1MIN_ADDR;
    }
    
    temp = 0;
    temp = *(unsigned int *)CH1MAX_ADDR;
    if (temp + 1 == 0)
    {
        ADC_Ch1MaxValue = ADC_CHANNEL_1_MAX;
    }
    else
    {
        ADC_Ch1MaxValue = *(float *)CH1MAX_ADDR;
    }

    temp = 0;
    temp = *(unsigned int *)CH2MIN_ADDR;
    if (temp + 1 == 0)
    {
        ADC_Ch2MinValue = ADC_CHANNEL_2_MIN;
    }
    else
    {
        ADC_Ch2MinValue = *(float *)CH2MIN_ADDR;
    }
    
    temp = 0;
    temp = *(unsigned int *)CH2MAX_ADDR;
    if (temp + 1 == 0)
    {
        ADC_Ch2MaxValue = ADC_CHANNEL_2_MAX;
    }
    else
    {
        ADC_Ch2MaxValue = *(float *)CH2MAX_ADDR;
    }

    temp = 0;
    temp = *(unsigned int *)CH3MIN_ADDR;
    if (temp + 1 == 0)
    {
        ADC_Ch3MinValue = ADC_CHANNEL_3_MIN;
    }
    else
    {
        ADC_Ch3MinValue = *(float *)CH3MIN_ADDR;
    }
    
    temp = 0;
    temp = *(unsigned int *)CH3MAX_ADDR;
    if (temp + 1 == 0)
    {
        ADC_Ch3MaxValue = ADC_CHANNEL_3_MAX;
    }
    else
    {
        ADC_Ch3MaxValue = *(float *)CH3MAX_ADDR;
    }
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
        // SysTick_Delayms(100);
        // TIM_SetCompare4(TIM1, 500);

        if (ADC_ConvertCompleteFlag == 1)
        {
            /* Ϊ�˱��ڵ��ԣ��������ѭ�����ڴ�ӡ���������У���һ��ͨ������ÿһ�����ֵ��������Excel�鿴
             * �����Ƿ���С��������ú����ӡ��û�ж�������������һͨ����λ�ƣ��봥����ͨ�š�
             */
#ifdef WAVEPRINT
            // for (int i = 0; i < SAMPLE_TIMES; i++)
            // {
            //     for (int j = 0; j < NUMBER_OF_CHANNELS; j++)
            //     {
            //         printf("%d\t", ADC_ConvertValue[i][j]);
            //     }
            //     printf("\n");
            // }
            
            for (int j = 0; j < NUMBER_OF_CHANNELS; j++)
            {
                ADC_CalcRootMeanSquare(j);
                printf("%.3f\r\n", ADC_RootMeanSquare[j]);
            }
            printf("\n");

            SysTick_Delayms(2000);
#else
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
