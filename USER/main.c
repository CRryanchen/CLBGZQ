#include "global.h"

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_Init();
	MODBUS_USART2_Init();
    MODBUS_USART2_SEND_STATUS;

    while(1)
    {
        LED2_TOGGLE;
        //printf("Hello World!\n");
		USART2_SendStr("Hello ");
        SysTick_Delayms(1000);
    }
}
