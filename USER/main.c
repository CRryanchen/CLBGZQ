#include "global.h"

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
    
    while(1)
    {
        /* ���ʵ���Ч���ǣ�LED2��һֱ��˸��MODBUS��������ʱҲ��һֱ���������������֮��
        �������3S�����϶�Ϊͨ�Ž�����������MODBUS���ӡ����������ݡ� */
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
