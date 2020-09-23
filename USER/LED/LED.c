/**
 * @file LED.c
 * @brief LED �Ƴ�ʼ��
 * @author Ryan��Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 23-07-2020
 *
 * @copyright Copyright (c) 2020  Ryan��Chen
 *
 * @par �޸���־:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>23-07-2020 <td>1.0     <td>Ryan��Chen     <td>LEDʹ��GPIO���ų�ʼ��
 * <tr><td>21-09-2020 <td>1.0     <td>Ryan��Chen     <td>����淶��
 * </table>
 */

/* ͷ�ļ����� */
#include "LED.h"

/**
 * @brief LED1 GPIO��ʼ��
 */
static void LED1_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(LED1_GPIO_CLK, ENABLE);// ����GPIOʱ��

    /* �ṹ������ */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief LED2 GPIO��ʼ��
 */
static void LED2_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;          // ��ʼ���ṹ�嶨��

    RCC_APB2PeriphClockCmd(LED2_GPIO_CLK, ENABLE);// ����GPIOʱ��

    /* �ṹ������ */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief LED1/2 GPIO��ʼ�������ⲿ����
 */
void LED_Init(void)
{
    LED1_GpioInit();                              // LED1 GPIO��ʼ��
    LED2_GpioInit();                              // LED2 GPIO��ʼ��
    LED1(OFF);                                    // ��ʼ�ص� LED1
    LED2(OFF);                                    // ��ʼ�ص� LED2
}
