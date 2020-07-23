#include "global.h"

int main(void)
{
	LED_Init();

    while(1)
    {
        LED1(ON);	
        SysTick_Delayms(1000);
        LED1(OFF);
        SysTick_Delayms(1000);
        LED2(ON);
        SysTick_Delayms(1000);
        LED2(OFF);
        SysTick_Delayms(1000);
        LED2_TOGGLE;
        SysTick_Delayms(1000);
		LED1_TOGGLE;
        SysTick_Delayms(1000);
    }
}
