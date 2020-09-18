#ifndef __GLOBAL_H
#define __GLOBAL_H

#ifdef __cplusplus
extern "C"{
#endif

/* ͷ�ļ����� */
#include "stm32f10x.h"								// Device header
#include "Delay.h"								    // Delay Func
#include "LED.h"                                    // LED
#include "USART1.h"                                 // USART1
#include "USART2.h"																	// USART2
#include "MODBUS_USART1.h"                          // MODBUS_USART1
#include "MODBUS_USART2.h"                          // MODBUS_USART2
#include "stm32f10x_it.h"                           // interrupt
#include "TIM6.h"                                   // TIM6
#include "INTER_FLASH.h"                            // INTER FLASH
#include "ADC.h"
#include "TIM1.h"
#include "TIM3.h"

/* �궨�� */
//#define PRINTF_USE_USART2

#define DEBUG									1
#define DEBUG_INFO(fmt, arg...)					do{\
												if(DEBUG)\
												printf("<<-DEBUG-INFO->> [%s],[%d]"fmt"\n", __FILE__, __LINE__, ##arg );\
												}while(0)
/* �������� */

/* ȫ�ֱ������� */
extern MODBUS_USART_RECV_STRUCT MODBUS_USART1_RECV;
extern MODBUS_USART_RECV_STRUCT MODBUS_USART2_RECV;
extern uint8_t DEVICE_ID;                                    /*!< �豸ID */
extern float WEIYI1 ;                                        /*!< λ��1 */
extern float WEIYI2 ;                                        /*!< λ��2 */
extern float WEIYI3 ;                                        /*!< λ��3 */
extern float WEIYI4 ;                                        /*!< λ��4 */
extern float K1_Value;                                       /*!< ����1 */
extern float K2_Value;                                       /*!< ����2 */
extern float K3_Value;                                       /*!< ����3 */
extern float K4_Value;                                       /*!< ����4 */
extern float K5_Value;                                       /*!< ����5 */
extern float K6_Value;                                       /*!< ����6 */
extern float K7_Value;                                       /*!< ����7 */
extern float K8_Value;                                       /*!< ����8 */
extern float K9_Value;                                       /*!< ����9 */
extern float K10_Value;                                      /*!< ����10 */

extern uint16_t ADC_ConvertValue[SAMPLE_TIMES][NUMBER_OF_CHANNELS];		 /*!< ADת��ֵ */
extern uint16_t ADC_ConvertValue_x[SAMPLE_TIMES * NUMBER_OF_CHANNELS];
extern uint8_t ADC_ConvertCompleteFlag;
extern float ADC_RootMeanSquare[NUMBER_OF_CHANNELS];
extern float ADC_WeiYi[NUMBER_OF_CHANNELS];

#ifdef __cplusplus
}
#endif

#endif /* __GLOBAL_H */
