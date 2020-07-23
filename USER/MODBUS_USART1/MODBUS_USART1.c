/**
 * @file MODBUS_USART1.c
 * @brief 
 * @author Ryan��Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 23-07-2020
 * 
 * @copyright Copyright (c) 2020  Ryan��Chen
 * 
 * @par ������־:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>23-07-2020 <td>1.0     <td>Ryan��Chen     <td>ʹ�ô���1����MODBUSͨ��
 * </table>
 */

#include "MODBUS_USART1.h"


/**
 * @brief MODBUS_USART1_CTL1���ų�ʼ��
 */
static void MODBUS_USART1_CTL1_GpioInit(void)
{
    /* ��ʼ���ṹ�嶨�� */
    GPIO_InitTypeDef GPIO_InitStructure;

    // ����GPIOʱ��
    RCC_APB2PeriphClockCmd(MODBUS_USART1_CTL1_GPIO_CLK, ENABLE);

    // �ṹ������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = MODBUS_USART1_CTL1_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MODBUS_USART1_CTL1_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief MODBUS_USART1_CTL2���ų�ʼ��
 */
static void MODBUS_USART1_CTL2_GpioInit(void)
{
    /* ��ʼ���ṹ�嶨�� */
    GPIO_InitTypeDef GPIO_InitStructure;

    // ����GPIOʱ��
    RCC_APB2PeriphClockCmd(MODBUS_USART1_CTL2_GPIO_CLK, ENABLE);

    // �ṹ������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = MODBUS_USART1_CTL2_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MODBUS_USART1_CTL2_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief MODBUS_USART1��ʼ�������ⲿ����
 */
void MODBUS_USART1_Init(void)
{
    // ��ʼ������1
    USART1_Init();
    // ��ʼ����������
    MODBUS_USART1_CTL1_GpioInit();
    MODBUS_USART1_CTL2_GpioInit();

    // MODBUS_USART1��Ϊ����ģʽ
    MODBUS_USART1_RECV_STATUS;
}

// ��Ϊ����2����ʱҲ������дprintf��������������һ����������
#if defined PRINTF_USE_USART2

#else
/**
 * @brief �ض���C�⺯��printf������1
 * @param  ch               ���͵��ֽ�����
 * @param  f                �ļ���ָ��
 * @return int 
 */
int fputc(int ch, FILE *f)
{
    // �л�Ϊ����ģʽ
    MODBUS_USART1_SEND_STATUS;

    // �����Ҳ�ʹ���Լ�д��USART_SendByte��������Ϊ�Ǹ����������ж�ʹ�õ���TXE��־λ
    // ������ΪҪ�л����ͺͽ��գ����Բ���ʹ��TXE��־λ�����жϣ�����������ʹ�ÿ⺯�������ж�TC��־λ
    USART_SendData(USART1, ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
        ;
    }

    // ������ɣ���Ϊ����ģʽ
    MODBUS_USART1_RECV_STATUS;

    return ch;
}

/**
 * @brief �ض���C�⺯��scanf������1
 * @param  f                �ļ���ָ��
 * @return int 
 */
int fgetc(FILE *f)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
    {
        ;
    }

    return (int)USART_ReceiveData(USART1);
}

#endif /* PRINTF_USE_USART2 */
