#ifndef __MODBUS_USART1_H
#define __MODBUS_USART1_H

#ifdef __cplusplus
extern "C"{
#endif

/* 头文件包含 */
#include "stm32f10x.h"								        // Device header
#include <stdio.h>                                          // 使用 printf()
#include "stm32f10x_it.h"

/* 宏定义 */
/* PE2、PE3控制串口发送还是接受 */
#define MODBUS_USART1_CTL1_GPIO_CLK								(RCC_APB2Periph_GPIOE)                                                                                                                           /**< MODBUS CTL1 GPIO时钟 */
#define MODBUS_USART1_CTL1_GPIO_PORT							(GPIOE)                                                                                                                                          /**< MODBUS CTL1 GPIO端口 */
#define MODBUS_USART1_CTL1_GPIO_PIN								(GPIO_Pin_2)                                                                                                                                     /**< MODBUS CTL1 GPIO Pin引脚 */

#define MODBUS_USART1_CTL2_GPIO_CLK								(RCC_APB2Periph_GPIOE)                                                                                                                           /**< MODBUS CTL2 GPIO时钟 */
#define MODBUS_USART1_CTL2_GPIO_PORT							(GPIOE)                                                                                                                                          /**< MODBUS CTL2 GPIO端口 */
#define MODBUS_USART1_CTL2_GPIO_PIN								(GPIO_Pin_3)                                                                                                                                     /**< MODBUS CTL2 GPIO Pin引脚 */

#define MODBUS_USART1_SEND_STATUS								GPIO_SetBits(MODBUS_USART1_CTL1_GPIO_PORT, MODBUS_USART1_CTL1_GPIO_PIN);GPIO_SetBits(MODBUS_USART1_CTL2_GPIO_PORT, MODBUS_USART1_CTL2_GPIO_PIN)    /**< MODBUS_USART1置为发送状态 */
#define MODBUS_USART1_RECV_STATUS							    GPIO_ResetBits(MODBUS_USART1_CTL1_GPIO_PORT, MODBUS_USART1_CTL1_GPIO_PIN);GPIO_ResetBits(MODBUS_USART1_CTL2_GPIO_PORT, MODBUS_USART1_CTL2_GPIO_PIN)/**< MODBUS_USART1置为接受状态 */

// 宏定义
#define MODBUS_USART_RECV_MAX_BUFSIZE								(100)       /**< 串口MODBUS接收数据数组最大值 */

/**
 * @brief 自定义数据类型，用于处理串口数据
 */
typedef struct
{
    uint8_t MODBUS_USART_RECVBUF[MODBUS_USART_RECV_MAX_BUFSIZE];/**< 接收数据数组 */
    uint8_t MODBUS_USART_RECV_COUNT;                            /**< 接收数据计数器 */
    uint8_t MODBUS_USART_COMPLETE_FLAG;                         /**< MODBUS接收完成标志 */
}MODBUS_USART_RECV_STRUCT;


/* 函数声明 */

void MODBUS_USART1_Init(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
void MODBUS_USART1_COMMUNICATION(void);
unsigned int CRC16(unsigned char *nData, unsigned int wLength);

/* 全局变量声明 */

extern MODBUS_USART_RECV_STRUCT MODBUS_USART1_RECV;          /**< 用于MODBUS_USART1数据接收的结构体 */
extern uint8_t DEVICE_ID;                                    /*!< 设备ID */

extern float WEIYI1 ;                                        /*!< 位移1 */
extern float WEIYI2 ;                                        /*!< 位移2 */
extern float WEIYI3 ;                                        /*!< 位移3 */
extern float WEIYI4 ;                                        /*!< 位移4 */
extern float K1_Value;                                       /*!< 参数1 */
extern float K2_Value;                                       /*!< 参数2 */
extern float K3_Value;                                       /*!< 参数3 */
extern float K4_Value;                                       /*!< 参数4 */
extern float K5_Value;                                       /*!< 参数5 */
extern float K6_Value;                                       /*!< 参数6 */
extern float K7_Value;                                       /*!< 参数7 */
extern float K8_Value;                                       /*!< 参数8 */
extern float K9_Value;                                       /*!< 参数9 */
extern float K10_Value;                                      /*!< 参数10 */

#ifdef __cplusplus
}
#endif

#endif /* __MODBUS_USART1_H */
