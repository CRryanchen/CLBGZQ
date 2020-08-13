#include "global.h"

/* 全局变量声明 */
float ADC_ConvertVol[NUMBER_OF_CHANNELS] = {0};


/**
 * @brief 初始化K值，暂时放在main函数
 */
static void K_ValueInit()
{
    K1_Value = *(float *)K1_ADDR;
    K2_Value = *(float *)K2_ADDR;
    K3_Value = *(float *)K3_ADDR;
    K4_Value = *(float *)K4_ADDR;
    K5_Value = *(float *)K5_ADDR;
    K6_Value = *(float *)K6_ADDR;
    K7_Value = *(float *)K7_ADDR;
    K8_Value = *(float *)K8_ADDR;
    K9_Value = *(float *)K9_ADDR;
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
    ADC_LocalInit();

    while(1)
    {
        LED1_TOGGLE;
        ADC_ConvertVol[0] = (float)ADC_ConvertValue[0] / 4096 * 2.5;
        ADC_ConvertVol[1] = (float)ADC_ConvertValue[1] / 4096 * 2.5;
        ADC_ConvertVol[2] = (float)ADC_ConvertValue[2] / 4096 * 2.5;
        ADC_ConvertVol[3] = (float)ADC_ConvertValue[3] / 4096 * 2.5;

        printf("\r\n CH1 Value = %f V\r\n", ADC_ConvertVol[0]);
        printf("\r\n CH2 Value = %f V\r\n", ADC_ConvertVol[1]);
        printf("\r\n CH3 Value = %f V\r\n", ADC_ConvertVol[2]);
        printf("\r\n CH4 Value = %f V\r\n", ADC_ConvertVol[3]);

        SysTick_Delayms(2000);

        

			
// #if defined PRINTF_USE_USART2
//         if (MODBUS_USART2_RECV.MODBUS_USART_COMPLETE_FLAG == 1)
// 				{
// 					MODBUS_USART2_COMMUNICATION();
// 					MODBUS_USART2_RECV.MODBUS_USART_RECV_COUNT = 0;
// 				MODBUS_USART2_RECV.MODBUS_USART_COMPLETE_FLAG = 0;
// 				}
// #else
//         if (MODBUS_USART1_RECV.MODBUS_USART_COMPLETE_FLAG == 1)
// 				{
// 					MODBUS_USART1_COMMUNICATION();
// 					MODBUS_USART1_RECV.MODBUS_USART_RECV_COUNT = 0;
// 					MODBUS_USART1_RECV.MODBUS_USART_COMPLETE_FLAG = 0;
// 				}
// #endif
    }
}
