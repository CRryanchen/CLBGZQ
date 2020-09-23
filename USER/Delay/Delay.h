#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
	extern "C"{
#endif

/* ͷ�ļ����� */
#include "stm32f10x.h"                  // Device header

/* �궨�� */
#if defined SysTickUseAHB
#define SysTickClock	(72000000)		/**<  SysTickʱ��Ƶ�� */
#else
#define SysTickClock	(9000000)		/**<  SysTickʱ��Ƶ�� */
#endif
/* �������� */

void SysTick_Delayus(__IO uint32_t nus);
void SysTick_Delayms(__IO uint32_t nms);

#ifdef __cplusplus
}
#endif
#endif /* __DELAY_H */
