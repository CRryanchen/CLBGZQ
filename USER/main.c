#include "global.h"

/* ȫ�ֱ������� */
float ADC_ConvertVol[SAMPLE_TIMES][NUMBER_OF_CHANNELS] = {0};
RCC_ClocksTypeDef get_rcc_clock;    //��ȡϵͳʱ��״̬

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
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_Init();
#if defined PRINTF_USE_USART2
	MODBUS_USART2_Init();
#else
    MODBUS_USART1_Init();
#endif /* PRINTF_USE_USART2 */
    TIM6_Init();
    K_ValueInit();
    TIM1_Init();
    TIM3_Init();
    ADC_LocalInit();

    RCC_GetClocksFreq(&get_rcc_clock);

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
            // ADC_ConvertCompleteFlag ��Ϊ0
            ADC_ConvertCompleteFlag = 0;
            // ���� DMA
            ADC_LocalInit();

        }

#if defined PRINTF_USE_USART2
        if (MODBUS_USART2_RECV.MODBUS_USART_COMPLETE_FLAG == 1)
				{
					MODBUS_USART2_COMMUNICATION();
					MODBUS_USART2_RECV.MODBUS_USART_RECV_COUNT = 0;
				MODBUS_USART2_RECV.MODBUS_USART_COMPLETE_FLAG = 0;
				}
#else
        if (MODBUS_USART1_RECV.MODBUS_USART_COMPLETE_FLAG == 1)
				{
					MODBUS_USART1_COMMUNICATION();
					MODBUS_USART1_RECV.MODBUS_USART_RECV_COUNT = 0;
					MODBUS_USART1_RECV.MODBUS_USART_COMPLETE_FLAG = 0;
				}
#endif
    }
}
