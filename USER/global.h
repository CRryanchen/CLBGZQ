#ifndef __GLOBAL_H
#define __GLOBAL_H

#ifdef __cplusplus
extern "C"{
#endif

/* 头文件包含 */
#include "stm32f10x.h"								// Device header
#include "Delay.h"								    // Delay Func
#include "LED.h"                                    // LED
#include "USART1.h"                                 // USART1
#include "USART2.h"									// USART2								// USART2
#include "MODBUS_USART1.h"                          // MODBUS_USART1
#include "MODBUS_USART2.h"                          // MODBUS_USART2
#include "stm32f10x_it.h"                           // interrupt
#include "TIM6.h"                                   // TIM6
#include "INTER_FLASH.h"                            // INTER FLASH
#include "ADC.h"									// ADC
#include "TIM1.h"									// TIM1
#include "TIM3.h"									// TIM3

/* 宏定义 */
//#define PRINTF_USE_USART2
#define WAVEPRINT

#define DEBUG									1
#define DEBUG_INFO(fmt, arg...)					do{\
												if(DEBUG)\
												printf("<<-DEBUG-INFO->> [%s],[%d]"fmt"\n", __FILE__, __LINE__, ##arg );\
												}while(0)
/* 函数声明 */
int globalInit(void);

/* 全局变量声明 */

#ifdef __cplusplus
}
#endif

#endif /* __GLOBAL_H */
