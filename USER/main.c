#include "global.h"

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_Init();
	//MODBUS_USART2_Init();
    MODBUS_USART1_Init();
    
    while(1)
    {
        LED2_TOGGLE;
        
        // printf("MODBUS_USART2_RECVBUF:%s\n",MODBUS_USART2_RECV.MODBUS_USART_RECVBUF);
        // printf("MODBUS_USART2_RECV_COUNT = %d\n", MODBUS_USART2_RECV.MODBUS_USART_RECV_COUNT);
        
        printf("MODBUS_USART1_RECVBUF:%s\n",MODBUS_USART1_RECV.MODBUS_USART_RECVBUF);
        printf("MODBUS_USART1_RECV_COUNT = %d\n", MODBUS_USART1_RECV.MODBUS_USART_RECV_COUNT);

        SysTick_Delayms(1000);
    }
}
