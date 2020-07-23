/**
 * @file USART1.c
 * @brief 
 * @author Ryan·Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 23-07-2020
 * 
 * @copyright Copyright (c) 2020  Ryan·Chen
 * 
 * @par 更改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>23-07-2020 <td>1.0     <td>Ryan·Chen     <td>USART1模式、GPIO、NVIC初始化配置
 * </table>
 */

#include "USART1.h"

/**
 * @brief USART1 TX引脚初始化
 */
static void USART1_TX_GpioInit(void)
{
    /* 初始化结构体定义 */
    GPIO_InitTypeDef GPIO_InitStructure;

    // 开启GPIO时钟、AFIO时钟
    RCC_APB2PeriphClockCmd(USART1_TX_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

    // 开启重映射
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

    // 结构体配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = USART1_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief USART1 RX引脚初始化
 */
static void USART1_RX_GpioInit(void)
{
    /* 初始化结构体定义 */
    GPIO_InitTypeDef GPIO_InitStructure;

    // 开启GPIO时钟
    RCC_APB2PeriphClockCmd(USART1_RX_GPIO_CLK, ENABLE);

    // 上面的TX已经打开过AFIO时钟和USART1的端口重映射了，所以这里不写

    // 结构体配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = USART1_RX_GPIO_PIN;
    GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief USART1 中断向量配置
 */
static void USART1_NVICConfig(void)
{
    // 声明中断控制向量的初始化结构体变量
    NVIC_InitTypeDef NVIC_InitStructure;

    // 每个工程都需要选择嵌套向量中断控制分组，但是只选择一次，所以我在主函数中选择

    // 选择中断源
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    // 设置中断的抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    // 设置中断的子优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    // 是否使能该中断源
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // 初始化结构体
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief USART1 串口初始化配置
 */
static void USART1_ModeConfig(void)
{
    // 串口初始化结构体声明
    USART_InitTypeDef USART_InitStructure;
    
    // 使能串口时钟,串口1是APB2，串口2,3,4,5是APB1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    
    // 波特率
    USART_InitStructure.USART_BaudRate = USART1_BAUDRATE;
    // 数据字长，一般为8
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    // 停止位，一般为1
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    // 校验为，一般无校验
    USART_InitStructure.USART_Parity = USART_Parity_No;
    // 模式，一般发送和接收
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    // 硬件流控制，一般不使用
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    // 初始化串口配置结构体
    USART_Init(USART1, &USART_InitStructure);

    // 需要使用串口接收中断的话，需要开启
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    // 使能串口
    USART_Cmd(USART1, ENABLE);
}

/**
 * @brief USART1 初始化，供外部调用
 */
void USART1_Init(void)
{
    USART1_TX_GpioInit();
    USART1_RX_GpioInit();
    USART1_NVICConfig();
    USART1_ModeConfig();
}

/**
 * @brief USART1 发送1字节数据
 * @param  l_ch             发送的字节数据
 */
static void USART1_SendByte(uint8_t l_ch)
{
    // USART1发送1字节数据
    USART_SendData(USART1, l_ch);

    // 等待数据寄存器为空
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
    {
        ;
    }
}

/**
 * @brief USART 发送字符串
 * @param  l_str            字符串的起始地址
 */
void USART1_SendStr(char * l_str)
{
    uint32_t l_count = 0;

    do
    {
        USART1_SendByte(*(l_str + l_count));
        l_count++;
    }while (*(l_str + l_count) != '\0');

    // 等待数据全部发送完毕
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
        ;
    }
}






