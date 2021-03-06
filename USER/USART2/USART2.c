/**
 * @file USART2.c
 * @brief USART2 相关配置
 * @author Ryan·Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 23-07-2020
 *
 * @copyright Copyright (c) 2020  Ryan·Chen
 *
 * @par 更改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>23-07-2020 <td>1.0     <td>Ryan·Chen     <td>USART2模式、GPIO、NVIC初始化配置
 * <tr><td>23-09-2020 <td>1.0     <td>Ryan·Chen     <td>代码规范
 * </table>
 */

/* 头文件包含 */
#include "USART2.h"



/**
 * @brief USART2 TX引脚初始化
 */
static void USART2_TX_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;// 初始化结构体定义

    RCC_APB2PeriphClockCmd(USART2_TX_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);// 开启GPIO时钟、AFIO时钟

    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);// 开启重映射

    /* 结构体配置 */
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin   = USART2_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief USART2 RX引脚初始化
 */
static void USART2_RX_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;// 初始化结构体定义

    RCC_APB2PeriphClockCmd(USART2_RX_GPIO_CLK, ENABLE);// 开启GPIO时钟

    /* 上面的TX已经打开过AFIO时钟和USART2的端口重映射了，所以这里不写 */

    /* 结构体配置 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin  = USART2_RX_GPIO_PIN;
    GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief USART2 中断向量配置
 */
static void USART2_NVICConfig(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;// 声明中断控制向量的初始化结构体变量

    /* 每个工程都需要选择嵌套向量中断控制分组，但是只选择一次，所以我在主函数中选择 */

    NVIC_InitStructure.NVIC_IRQChannel                   = USART2_IRQn;  // 选择中断源
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;            // 设置中断的抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;            // 设置中断的子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;       // 是否使能该中断源
    NVIC_Init(&NVIC_InitStructure);                                      // 初始化结构体
}

/**
 * @brief USART2 串口初始化配置
 */
static void USART2_ModeConfig(void)
{
    USART_InitTypeDef USART_InitStructure;// 串口初始化结构体声明

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);// 使能串口时钟,串口1是APB2，串口2,3,4,5是APB1

    USART_InitStructure.USART_BaudRate            = USART2_BAUDRATE;                 // 波特率
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;             // 数据字长，一般为8
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;                // 停止位，一般为1
    USART_InitStructure.USART_Parity              = USART_Parity_No;                 // 校验为，一般无校验
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;   // 模式，一般发送和接收
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  // 硬件流控制，一般不使用
    USART_Init(USART2, &USART_InitStructure);                                        // 初始化串口配置结构体

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);// 需要使用串口接收中断的话，需要开启

    USART_Cmd(USART2, ENABLE);// 使能串口
}

/**
 * @brief USART2 初始化，供外部调用
 */
void USART2_Init(void)
{
    USART2_TX_GpioInit();
    USART2_RX_GpioInit();
    USART2_NVICConfig();
    USART2_ModeConfig();
}

/**
 * @brief USART2 发送1字节数据
 * @param  l_ch             发送的字节数据
 */
static void USART2_SendByte(uint8_t l_ch)
{
    USART_SendData(USART2, l_ch);// USART2发送1字节数据

    /* 等待数据寄存器为空 */
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
    {
        ;
    }
}

/**
 * @brief USART 发送字符串
 * @param  l_str            字符串的起始地址
 */
void USART2_SendStr(char * l_str)
{
    uint32_t l_count = 0;

    do
    {
        USART2_SendByte(*(l_str + l_count));
        l_count++;
    }while (*(l_str + l_count) != '\0');

    /* 等待数据全部发送完毕 */
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
    {
        ;
    }
}
