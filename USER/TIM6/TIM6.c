/**
 * @file TIM6.c
 * @brief  使用基本定时器TIM6进行定时计算Modbus通信的结束。每次接收到数据则开启定时器，
 * 如果定时器溢出，表明达到最长通信时间，即结束通信的判断标准。定时时间为3.5个字节接收时间，
 * 如果我们波特率设置为9600，则时间为：3.5*8/9600，约等于3ms左右
 * @author Ryan·Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 24-07-2020
 *
 * @copyright Copyright (c) 2020  Ryan·Chen
 *
 * @par 更改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>24-07-2020 <td>1.0     <td>Ryan·Chen     <td>使用基本定时器TIM6判断MODBUS通信的结束
 * <tr><td>22-09-2020 <td>1.0     <td>Ryan·Chen     <td>代码规范化
 * </table>
 */

/* 头文件包含 */
#include "TIM6.h"

/**
 * @brief TIM6 时基初始化
 */
static void TIM6_TimeBaseConfig(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;                         // 定时器时基初始化结构体声明

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);                       // 开启TIM6时钟

    TIM_TimeBaseInitStructure.TIM_Prescaler = (72 - 1);                        // 计数器预频率， 72 / 72 = 1MHz
    TIM_TimeBaseInitStructure.TIM_Period    = (3000 - 1);                      // 计数器周期， 3000

    /* 以下三个配置基本定时器不使用 */
    TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);                        // 初始化时基结构体
}


/**
 * @brief TIM6中断优先级配置
 */
static void TIM6_NVICConfig(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;                                       // 声明中断控制向量的初始化结构体变量

    /* 每个工程都需要选择嵌套向量中断控制分组，但是只选择一次，所以我在主函数中选择 */

    NVIC_InitStructure.NVIC_IRQChannel                   = TIM6_IRQn;          // 选择中断源
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;                  // 设置中断的抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;                  // 设置中断的子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;             // 是否使能该中断源
    NVIC_Init(&NVIC_InitStructure);                                            // 初始化结构体
}

/**
 * @brief TIM6初始化，供外部调用
 */
void TIM6_Init(void)
{
    TIM6_NVICConfig();
    TIM6_TimeBaseConfig();

    TIM_ClearFlag(TIM6, TIM_FLAG_Update);                                      // 清除更新中断标志位
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);                                 // 开启TIM6更新中断
    TIM_Cmd(TIM6, DISABLE);                                                    // 暂不使能TIM6
}
