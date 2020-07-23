/**
  ******************************************************************************
  * @file    DEBUG_Delay.c
  * @author  Ryan��Chen
  * @version V1.0
  * @date    23-March-2020
  * @brief   ʹ��STM32��ϵͳ�δ�ʱ��ʵ��us,ms,s����ʱ����        
  ******************************************************************************
  */

/* ͷ�ļ����� */
#include "Delay.h"

/**
  * @brief 	ϵͳ��ʱ������
  * @author	Ryan��Chen
  * @date 	23-March-2020
  * @param	ticks ϵͳ��ʱ���ļ�ʱ����
  * @retval	0 ���óɹ�
  * @retval 1 ��װ��ֵ���Ϸ�
  * @note	�ú����ο�@ref core_cm3.h�е�SysTick_Config��������������ʱ��ʱ�Ҹ�Ϊ�˿���ͨ����
  *			  ����ʹ���ڲ�ʱ��(AHB)�����ⲿʱ��(AHB/8)��ͨ��\#if�﷨ʵ�ֲ�ͬʱ��Դ����¶�ʱ��
  *           �ĵ�һ�¡�Ĭ��ʹ���ⲿʱ��(AHB/8)�������Ҫʹ���ڲ�ʱ�ӣ����Ӻ궨��SysTickUseAHB
  *			  ���ɡ�
  */
static u8 SysTick_Configuration(uint32_t ticks)
{
	if (ticks > SysTick_LOAD_RELOAD_Msk)  						/* ��װ��ֵ���Ϸ� */		
	{
		return (1);            
	}
                                                               
	SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;  	/* ������װ�ؼĴ��� */  
	SysTick->VAL   = 0;                             			/* ���������ֵ */
/* ����SysTickԤ��Ƶ */   
#if defined SysTickUseAHB										
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);			/* ʹ��AHB--72M */
#else
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);		/* ʹ��AHB/8--9M */
#endif
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     				/* ʹ��SysTick */
	return (0);    
}

/**
  * @brief	ϵͳ��ʱ����ʱus
  * @author	Ryan��Chen
  * @date 	23-March-2020
  * @param	nus ΢����ʱʱ��
  * @retval	None
  */
void SysTick_Delayus(__IO uint32_t nus)
{
	uint32_t i;
	
	SysTick_Configuration(SysTickClock / 1000000);
	for (i = 0; i < nus; i++)
	{
		while (!(SysTick->CTRL & (1 << 16)));					/* ��ȡCOUNTFLAGλ�������λ */
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;     				/* �ر�SysTick */
}

/**
  * @brief	ϵͳ��ʱ����ʱms
  * @author	Ryan��Chen
  * @date 	23-March-2020
  * @param	nms ������ʱʱ��
  * @retval	None
  */
void SysTick_Delayms(__IO uint32_t nms)
{
	uint32_t i;
	
	SysTick_Configuration(SysTickClock / 1000);
	for (i = 0; i < nms; i++)
	{
		while (!(SysTick->CTRL & (1 << 16)));					/* ��ȡCOUNTFLAGλ�������λ */
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;     				/* �ر�SysTick */
}
