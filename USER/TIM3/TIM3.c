/**
 * @file TIM3.c
 * @brief 配置定时器3，通道1，2，3，4输出频率为2K占空比为50%的方波
 * @author Ryan·Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 17-08-2020
 *
 * @copyright Copyright (c) 2020  Ryan·Chen
 *
 * @par 更改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>17-08-2020 <td>1.0     <td>Ryan·Chen     <td>配置定时器3
 * <tr><td>22-09-2020 <td>1.0     <td>Ryan·Chen     <td>代码规范化
 * <tr><td>27-09-2020 <td>1.0     <td>Ryan·Chen     <td>更正引脚宏定义错误定义在TIM1头文件中
 */

/* 头文件包含 */
#include "TIM3.h"



/**
 * @brief TIM3 CH1-CH4 GPIO初始化
 */
static void TIM3_CH_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;                                                                                                // 初始化结构体定义

    RCC_APB2PeriphClockCmd(TIM3_CH1_GPIO_CLK | TIM3_CH2_GPIO_CLK | TIM3_CH3_GPIO_CLK | TIM3_CH4_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);// 开启GPIO时钟、AFIO时钟

    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);                                                                                   // 开启重映射

    /* 结构体配置 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = TIM3_CH1_GPIO_PIN;
    GPIO_Init(TIM3_CH1_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = TIM3_CH2_GPIO_PIN;
    GPIO_Init(TIM3_CH2_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = TIM3_CH3_GPIO_PIN;
    GPIO_Init(TIM3_CH3_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = TIM3_CH4_GPIO_PIN;
    GPIO_Init(TIM3_CH4_GPIO_PORT, &GPIO_InitStructure);
}



/**
 * @brief TIM3 时基结构体初始化
 */
static void TIM3_TimeBaseConfig(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;                                                                                  // 定时器时基初始化结构体声明

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                                                                                // 开启TIM3时钟

    TIM_TimeBaseInitStructure.TIM_Prescaler         = TIM3_PSC;                                                                         // 计数器预频率， 720
    TIM_TimeBaseInitStructure.TIM_Period            = TIM3_PERIOD;                                                                      // 计数器周期， 1000
    TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;                                                                     // 时钟分频因子，配置死区时间时需要用到
    TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;                                                               // 计数器技术模式，向上计数
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;                                                                                // 重复计数器的值，没有使用设为0
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);                                                                                 // 初始化时基结构体
}



/**
 * @brief TIM3 CH1-CH4 输出比较配置
 */
static void TIM3_OCConfig(void)
{
    TIM_OCInitTypeDef TIM_OCInitStructure;                                                                                              // 定时器输出比较初始化结构体声明

    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;                                                                             // 配置为PWM模式1
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;                                                                      // 输出使能
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;                                                                    // 互补输出不使能
    TIM_OCInitStructure.TIM_Pulse        = TIM3_PULSE;                                                                                  // 设置占空比大小
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;                                                                         // 输出通道电平极性设置
    TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_High;                                                                        // 互补输出通道电平极性设置
    TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Set;                                                                         // 输出通道空闲电平极性设置
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;                                                                      // 互补输出通道空闲电平极性设置

    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_Cmd(TIM3, ENABLE);                                                                                                              // 使能计数器
    TIM_CtrlPWMOutputs(TIM3, ENABLE);                                                                                                   // 主输出使能
}



/**
 * @brief TIM3 初始化，供外部调用
 */
void TIM3_Init(void)
{
    TIM3_CH_GpioInit();
    TIM3_TimeBaseConfig();
    TIM3_OCConfig();
}
