#ifndef __MODBUS_USART1_H
#define __MODBUS_USART1_H

#ifdef __cplusplus
extern "C"{
#endif

/* ͷ�ļ����� */
#include "stm32f10x.h"								        // Device header
#include <stdio.h>                                          // ʹ�� printf()
#include "stm32f10x_it.h"

/* �궨�� */
/* PE2��PE3���ƴ��ڷ��ͻ��ǽ��� */
#define MODBUS_USART1_CTL1_GPIO_CLK								(RCC_APB2Periph_GPIOE)                                                                                                                           /**< MODBUS CTL1 GPIOʱ�� */
#define MODBUS_USART1_CTL1_GPIO_PORT							(GPIOE)                                                                                                                                          /**< MODBUS CTL1 GPIO�˿� */
#define MODBUS_USART1_CTL1_GPIO_PIN								(GPIO_Pin_2)                                                                                                                                     /**< MODBUS CTL1 GPIO Pin���� */

#define MODBUS_USART1_CTL2_GPIO_CLK								(RCC_APB2Periph_GPIOE)                                                                                                                           /**< MODBUS CTL2 GPIOʱ�� */
#define MODBUS_USART1_CTL2_GPIO_PORT							(GPIOE)                                                                                                                                          /**< MODBUS CTL2 GPIO�˿� */
#define MODBUS_USART1_CTL2_GPIO_PIN								(GPIO_Pin_3)                                                                                                                                     /**< MODBUS CTL2 GPIO Pin���� */

#define MODBUS_USART1_SEND_STATUS								GPIO_SetBits(MODBUS_USART1_CTL1_GPIO_PORT, MODBUS_USART1_CTL1_GPIO_PIN);GPIO_SetBits(MODBUS_USART1_CTL2_GPIO_PORT, MODBUS_USART1_CTL2_GPIO_PIN)    /**< MODBUS_USART1��Ϊ����״̬ */
#define MODBUS_USART1_RECV_STATUS							    GPIO_ResetBits(MODBUS_USART1_CTL1_GPIO_PORT, MODBUS_USART1_CTL1_GPIO_PIN);GPIO_ResetBits(MODBUS_USART1_CTL2_GPIO_PORT, MODBUS_USART1_CTL2_GPIO_PIN)/**< MODBUS_USART1��Ϊ����״̬ */

/* �������� */

void MODBUS_USART1_Init(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
void MODBUS_USART1_COMMUNICATION(void);
unsigned int CRC16(unsigned char *nData, unsigned int wLength);

/* ȫ�ֱ������� */

extern MODBUS_USART_RECV_STRUCT MODBUS_USART1_RECV;          /**< ����MODBUS_USART1���ݽ��յĽṹ�� */
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

#ifdef __cplusplus
}
#endif

#endif /* __MODBUS_USART1_H */
