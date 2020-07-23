/**
  ******************************************************************************
  * @file    DEBUG_Delay.c
  * @author  Ryan·Chen
  * @version V1.0
  * @date    23-March-2020
  * @brief   使用STM32的系统滴答定时器实现us,ms,s级延时函数        
  ******************************************************************************
  */

/* 头文件包含 */
#include "Delay.h"

/**
  * @brief 	系统定时器配置
  * @author	Ryan·Chen
  * @date 	23-March-2020
  * @param	ticks 系统定时器的计时节拍
  * @retval	0 配置成功
  * @retval 1 重装载值不合法
  * @note	该函数参考@ref core_cm3.h中的SysTick_Config函数，但是设置时钟时我改为了可以通过宏
  *			  设置使用内部时钟(AHB)还是外部时钟(AHB/8)。通过\#if语法实现不同时钟源情况下定时节
  *           拍的一致。默认使用外部时钟(AHB/8)，如果需要使用内部时钟，增加宏定义SysTickUseAHB
  *			  即可。
  */
static u8 SysTick_Configuration(uint32_t ticks)
{
	if (ticks > SysTick_LOAD_RELOAD_Msk)  						/* 重装载值不合法 */		
	{
		return (1);            
	}
                                                               
	SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;  	/* 设置重装载寄存器 */  
	SysTick->VAL   = 0;                             			/* 清零计数器值 */
/* 设置SysTick预分频 */   
#if defined SysTickUseAHB										
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);			/* 使用AHB--72M */
#else
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);		/* 使用AHB/8--9M */
#endif
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     				/* 使能SysTick */
	return (0);    
}

/**
  * @brief	系统定时器延时us
  * @author	Ryan·Chen
  * @date 	23-March-2020
  * @param	nus 微秒延时时间
  * @retval	None
  */
void SysTick_Delayus(__IO uint32_t nus)
{
	uint32_t i;
	
	SysTick_Configuration(SysTickClock / 1000000);
	for (i = 0; i < nus; i++)
	{
		while (!(SysTick->CTRL & (1 << 16)));					/* 读取COUNTFLAG位可清除该位 */
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;     				/* 关闭SysTick */
}

/**
  * @brief	系统定时器延时ms
  * @author	Ryan·Chen
  * @date 	23-March-2020
  * @param	nms 毫秒延时时间
  * @retval	None
  */
void SysTick_Delayms(__IO uint32_t nms)
{
	uint32_t i;
	
	SysTick_Configuration(SysTickClock / 1000);
	for (i = 0; i < nms; i++)
	{
		while (!(SysTick->CTRL & (1 << 16)));					/* 读取COUNTFLAG位可清除该位 */
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;     				/* 关闭SysTick */
}
