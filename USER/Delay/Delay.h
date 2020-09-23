#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
	extern "C"{
#endif

/* 头文件包含 */
#include "stm32f10x.h"                  // Device header

/* 宏定义 */
#if defined SysTickUseAHB
#define SysTickClock	(72000000)		/**<  SysTick时钟频率 */
#else
#define SysTickClock	(9000000)		/**<  SysTick时钟频率 */
#endif
/* 函数声明 */

void SysTick_Delayus(__IO uint32_t nus);
void SysTick_Delayms(__IO uint32_t nms);

#ifdef __cplusplus
}
#endif
#endif /* __DELAY_H */
