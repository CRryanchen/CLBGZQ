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
#include "USART2.h"																	// USART2
#include "MODBUS_USART1.h"                          // MODBUS_USART1
#include "MODBUS_USART2.h"                          // MODBUS_USART2

/* 宏定义 */
#define PRINTF_USE_USART2								

/* 函数声明 */

/* 全局变量声明 */

#ifdef __cplusplus
}
#endif

#endif /* __GLOBAL_H */
