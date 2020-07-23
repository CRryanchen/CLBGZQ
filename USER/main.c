#include "global.h"

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_Init();
		MODBUS_USART1_Init();
    MODBUS_USART1_SEND_STATUS;

    while(1)
    {
        LED1_TOGGLE;
        //printf("Hello World!\n");
        USART1_SendStr("hELLO");
        SysTick_Delayms(1000);
    }
}
