/**
 * @file MODBUS_USART2.c
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
 * <tr><td>23-07-2020 <td>1.0     <td>Ryan·Chen     <td>使用串口2进行MODBUS通信
 * </table>
 */

#include "MODBUS_USART2.h"

// 全局变量声明
// 声明一个用于接收数据的结构体
MODBUS_USART_RECV_STRUCT MODBUS_USART2_RECV;                 /**< 用于MODBUS_USART2数据接收的结构体 */

/**
 * @brief MODBUS_USART2_CTL1引脚初始化
 */
static void MODBUS_USART2_CTL1_GpioInit(void)
{
    /* 初始化结构体定义 */
    GPIO_InitTypeDef GPIO_InitStructure;

    // 开启GPIO时钟
    RCC_APB2PeriphClockCmd(MODBUS_USART2_CTL1_GPIO_CLK, ENABLE);

    // 结构体配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = MODBUS_USART2_CTL1_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MODBUS_USART2_CTL1_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief MODBUS_USART2_CTL2引脚初始化
 */
static void MODBUS_USART2_CTL2_GpioInit(void)
{
    /* 初始化结构体定义 */
    GPIO_InitTypeDef GPIO_InitStructure;

    // 开启GPIO时钟
    RCC_APB2PeriphClockCmd(MODBUS_USART2_CTL2_GPIO_CLK, ENABLE);

    // 结构体配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = MODBUS_USART2_CTL2_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MODBUS_USART2_CTL2_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief MODBUS_USART2初始化，供外部调用
 */
void MODBUS_USART2_Init(void)
{
    // 初始化串口1
    USART2_Init();
    // 初始化控制引脚
    MODBUS_USART2_CTL1_GpioInit();
    MODBUS_USART2_CTL2_GpioInit();

    // MODBUS_USART2置为接收模式
    MODBUS_USART2_RECV_STATUS;

    // 清零MODBUS_USART2数据接收计数器
    MODBUS_USART2_RECV.MODBUS_USART_RECV_COUNT = 0;
}

// 因为串口2测试时也会用重写printf函数，所以我用一个宏来区分
#if defined PRINTF_USE_USART2

/**
 * @brief 重定向C库函数printf到串口1
 * @param  ch               发送的字节数据
 * @param  f                文件流指针
 * @return int 
 */
int fputc(int ch, FILE *f)
{
    // 切换为发送模式
    MODBUS_USART2_SEND_STATUS;

    // 这里我不使用自己写的USART_SendByte函数，因为那个函数里面判断使用的是TXE标志位
    // 这里因为要切换发送和接收，所以不能使用TXE标志位进行判断，所以这里我使用库函数，并判断TC标志位
    USART_SendData(USART2, ch);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
    {
        ;
    }

    // 发送完成，置为接收模式
    MODBUS_USART2_RECV_STATUS;

    return ch;
}

/**
 * @brief 重定向C库函数scanf到串口1
 * @param  f                文件流指针
 * @return int 
 */
int fgetc(FILE *f)
{
    while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET)
    {
        ;
    }

    return (int)USART_ReceiveData(USART1);
}

#endif /* PRINTF_USE_USART2 */

/**
 * @brief MOSBUS_USART2通信处理函数
 */
void MODBUS_USART2_COMMUNICATION(void)
{
    printf("MODBUS_USART2 通信结束，您输入的字符串是%s，共%d个。\n", MODBUS_USART2_RECV.MODBUS_USART_RECVBUF, MODBUS_USART2_RECV.MODBUS_USART_RECV_COUNT);
}
