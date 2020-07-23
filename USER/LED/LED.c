/**
 * @file LED.c
 * @brief 
 * @author Ryan·Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 23-07-2020
 * 
 * @copyright Copyright (c) 2020  Ryan·Chen
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>23-07-2020 <td>1.0     <td>Ryan·Chen     <td>LED使用GPIO引脚初始化
 * </table>
 */

#include "LED.h"

/**
 * @brief LED1 GPIO初始化
 */
static void LED1_GpioInit(void)
{
    /* 初始化结构体定义 */
    GPIO_InitTypeDef GPIO_InitStructure;

    // 开启GPIO时钟
    RCC_APB2PeriphClockCmd(LED1_GPIO_CLK, ENABLE);

    // 结构体配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief LED2 GPIO初始化
 */
static void LED2_GpioInit(void)
{
    /* 初始化结构体定义 */
    GPIO_InitTypeDef GPIO_InitStructure;

    // 开启GPIO时钟
    RCC_APB2PeriphClockCmd(LED2_GPIO_CLK, ENABLE);

    // 结构体配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief LED GPIO初始化，供外部调用
 */
void LED_Init(void)
{
    LED1_GpioInit();
    LED2_GpioInit();
    // 初始关掉LED
    LED1(OFF);
    LED2(OFF);
}
