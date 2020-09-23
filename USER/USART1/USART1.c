/**
 * @file USART1.c
 * @brief USART1 �������
 * @author Ryan��Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 23-07-2020
 *
 * @copyright Copyright (c) 2020  Ryan��Chen
 *
 * @par ������־:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>23-07-2020 <td>1.0     <td>Ryan��Chen     <td>USART1ģʽ��GPIO��NVIC��ʼ������
 * <tr><td>23-09-2020 <td>1.0     <td>Ryan��Chen     <td>����淶
 * </table>
 */

/* ͷ�ļ����� */
#include "USART1.h"



/**
 * @brief USART1 TX���ų�ʼ��
 */
static void USART1_TX_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;                                     // ��ʼ���ṹ�嶨��

    RCC_APB2PeriphClockCmd(USART1_TX_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);// ����GPIOʱ�ӡ�AFIOʱ��

    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);                          // ������ӳ��

    /* �ṹ������ */
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin   = USART1_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);
}



/**
 * @brief USART1 RX���ų�ʼ��
 */
static void USART1_RX_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;               // ��ʼ���ṹ�嶨��

    RCC_APB2PeriphClockCmd(USART1_RX_GPIO_CLK, ENABLE);// ����GPIOʱ��

    /* �����TX�Ѿ��򿪹�AFIOʱ�Ӻ�USART1�Ķ˿���ӳ���ˣ��������ﲻд */

    /* �ṹ������ */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin  = USART1_RX_GPIO_PIN;
    GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);
}



/**
 * @brief USART1 �ж���������
 */
static void USART1_NVICConfig(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;                                 // �����жϿ��������ĳ�ʼ���ṹ�����

    /* ÿ�����̶���Ҫѡ��Ƕ�������жϿ��Ʒ��飬����ֻѡ��һ�Σ�����������������ѡ�� */

    NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;  // ѡ���ж�Դ
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;            // �����жϵ���ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;            // �����жϵ������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;       // �Ƿ�ʹ�ܸ��ж�Դ
    NVIC_Init(&NVIC_InitStructure);                                      // ��ʼ���ṹ��
}



/**
 * @brief USART1 ���ڳ�ʼ������
 */
static void USART1_ModeConfig(void)
{
    USART_InitTypeDef USART_InitStructure;                                           // ���ڳ�ʼ���ṹ������

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);                            // ʹ�ܴ���ʱ��,����1��APB2������2,3,4,5��APB1

    USART_InitStructure.USART_BaudRate            = USART1_BAUDRATE;                 // ������
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;             // �����ֳ���һ��Ϊ8
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;                // ֹͣλ��һ��Ϊ1
    USART_InitStructure.USART_Parity              = USART_Parity_No;                 // У��Ϊ��һ����У��
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;   // ģʽ��һ�㷢�ͺͽ���
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  // Ӳ�������ƣ�һ�㲻ʹ��
    USART_Init(USART1, &USART_InitStructure);                                        // ��ʼ���������ýṹ��

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                                   // ��Ҫʹ�ô��ڽ����жϵĻ�����Ҫ����
    USART_Cmd(USART1, ENABLE);                                                       // ʹ�ܴ���
}



/**
 * @brief USART1 ��ʼ�������ⲿ����
 */
void USART1_Init(void)
{
    USART1_TX_GpioInit();
    USART1_RX_GpioInit();
    USART1_NVICConfig();
    USART1_ModeConfig();
}



/**
 * @brief USART1 ����1�ֽ�����
 * @param  l_ch             ���͵��ֽ�����
 */
static void USART1_SendByte(uint8_t l_ch)
{
    USART_SendData(USART1, l_ch);// USART1����1�ֽ�����

    /* �ȴ����ݼĴ���Ϊ�� */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
    {
        ;
    }
}



/**
 * @brief USART �����ַ���
 * @param  l_str            �ַ�������ʼ��ַ
 */
void USART1_SendStr(char * l_str)
{
    uint32_t l_count = 0;

    do
    {
        USART1_SendByte(*(l_str + l_count));
        l_count++;
    }while (*(l_str + l_count) != '\0');

    /* �ȴ�����ȫ��������� */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
        ;
    }
}



/**
 * @brief  USART1 ��������
 * @param  l_addr           ���ݵ���ʼ��ַ
 * @param  l_count          ���ݵĸ���
 */
void USART1_SendData(uint8_t *l_addr, uint8_t l_count)
{
    while (l_count != 0)
    {
        USART1_SendByte(*l_addr++);
        l_count--;
    }

    /* �ȴ�����ȫ��������� */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
        ;
    }
}
