#ifndef __INTER_FLASH_H
#define __INTER_FLASH_H

#ifdef __cplusplus
extern "C"{
#endif

/* ͷ�ļ����� */
#include "stm32f10x.h"								// Device header

/* �궨�� */
#if defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
    #define FLASH_PAGE_SIZE                             ((uint16_t)0X800)   /*!< 2KB */
#else
    #define FLASH_PAGE_SIZE								((uint16_t)0X400)   /*!< 1KB */
#endif

#define DEVICE_ID_ADDR								((uint32_t)0X08008000)   /*!< д����ʱ��Ҫ����һҳ�����Ը�д�ĵ�ַΪ0X08008000-0X080087FF */
#define K1_ADDR								((uint32_t)0X08008800)
#define K2_ADDR								((uint32_t)0X08008804)
#define K3_ADDR								((uint32_t)0X08008808)
#define K4_ADDR								((uint32_t)0X0800880c)
#define K5_ADDR								((uint32_t)0X08008810)
#define K6_ADDR								((uint32_t)0X08008814)
#define K7_ADDR								((uint32_t)0X08008818)
#define K8_ADDR								((uint32_t)0X0800881c)
#define K9_ADDR								((uint32_t)0X08008820)
#define K10_ADDR								((uint32_t)0X08008824)


/* �������� */
int INTER_FLASH_ProgramWord(uint32_t l_address, uint32_t l_data);

/* ȫ�ֱ������� */

#ifdef __cplusplus
}
#endif

#endif /* __INTER_FLASH_H */
