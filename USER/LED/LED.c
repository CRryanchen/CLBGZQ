/**
 * @file LED.c
 * @brief LED 灯初始化
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
 * <tr><td>21-09-2020 <td>1.0     <td>Ryan·Chen     <td>代码规范化
 * </table>
 */

/* 头文件包含 */
#include "LED.h"

/**
 * @brief LED1 GPIO初始化
 */
static void LED1_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(LED1_GPIO_CLK, ENABLE);// 开启GPIO时钟

    /* 结构体配置 */
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
    GPIO_InitTypeDef GPIO_InitStructure;          // 初始化结构体定义

    RCC_APB2PeriphClockCmd(LED2_GPIO_CLK, ENABLE);// 开启GPIO时钟

    /* 结构体配置 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief LED1/2 GPIO初始化，供外部调用
 */
void LED_Init(void)
{
    LED1_GpioInit();                              // LED1 GPIO初始化
    LED2_GpioInit();                              // LED2 GPIO初始化
    LED1(OFF);                                    // 初始关掉 LED1
    LED2(OFF);                                    // 初始关掉 LED2
}
