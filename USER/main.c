#include "global.h"

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
    
    while(1)
    {
        /* 这个实验的效果是，LED2会一直闪烁，MODBUS接收数据时也会一直闪，如果两个数据之间
        间隔超过3S，则认定为通信结束，结束后MODBUS会打印你输入的数据。 */
        LED2_TOGGLE;
        
        // printf("MODBUS_USART2_RECVBUF:%s\n",MODBUS_USART2_RECV.MODBUS_USART_RECVBUF);
        // printf("MODBUS_USART2_RECV_COUNT = %d\n", MODBUS_USART2_RECV.MODBUS_USART_RECV_COUNT);
        
        // printf("MODBUS_USART1_RECVBUF:%s\n",MODBUS_USART1_RECV.MODBUS_USART_RECVBUF);
        // printf("MODBUS_USART1_RECV_COUNT = %d\n", MODBUS_USART1_RECV.MODBUS_USART_RECV_COUNT);

        SysTick_Delayms(1000);
			
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
