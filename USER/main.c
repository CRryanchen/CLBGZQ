/**
 * @file main.c
 * @brief 程序的主要执行流程，2020.09.21添加
 * @author Ryan·Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 21-09-2020
 *
 * @copyright Copyright (c) 2020  Ryan·Chen
 *
 * @par 更改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>21-09-2020 <td>1.0     <td>Ryan·Chen     <td>增加文件头说明，规范注释，删除不必要代码、变量
 * <tr><td>26-10-2020 <td>1.0     <td>Ryan·Chen     <td>初始化各AD通道的参考极值
 * </table>
 */
#include "global.h"

/**
 * @brief 初始化K值，暂时放在main函数
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
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);             // 选择NVIC 分组
    LED_Init();                                                 // LED初始化
#if defined PRINTF_USE_USART2
	MODBUS_USART2_Init();                                       // 初始化串口2
#else
    MODBUS_USART1_Init();                                       // 初始化串口1
#endif /* PRINTF_USE_USART2 */
    TIM6_Init();                                                // TIM6 初始化
    K_ValueInit();                                              // K值初始化
    TIM1_Init();                                                // TIM1 初始化
    TIM3_Init();                                                // TIM3 初始化
    ADC_LocalInit();                                            // ADC1 初始化

    while(1)
    {
        // SysTick_Delayms(100);
        // TIM_SetCompare4(TIM1, 500);

        if (ADC_ConvertCompleteFlag == 1)
        {
            /* 为了便于调试，下面这个循环用于打印采样数组中（第一个通道）的每一个点的值，用于在Excel查看
             * 波形是否可行。如果定义该宏则打印。没有定义则输出计算第一通道的位移，与触摸屏通信。
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
            ADC_ConvertCompleteFlag = 0;                        // ADC_ConvertCompleteFlag 置为0
            ADC_LocalInit();                                    // 重启 DMA
        }

#if defined PRINTF_USE_USART2
        if (MODBUS_USART2_RECV.MODBUS_USART_COMPLETE_FLAG == 1)
				{
					MODBUS_USART2_COMMUNICATION();                    // 处理MODBUS信息
					MODBUS_USART2_RECV.MODBUS_USART_RECV_COUNT = 0;   // 串口计数器清零
				MODBUS_USART2_RECV.MODBUS_USART_COMPLETE_FLAG = 0;    // 串口通信标志清零
				}
#else
        if (MODBUS_USART1_RECV.MODBUS_USART_COMPLETE_FLAG == 1)
				{
					MODBUS_USART1_COMMUNICATION();                    // 处理MODBUS信息
					MODBUS_USART1_RECV.MODBUS_USART_RECV_COUNT = 0;   // 串口计数器清零
					MODBUS_USART1_RECV.MODBUS_USART_COMPLETE_FLAG = 0;// 串口通信标志清零
				}
#endif
    }
}
