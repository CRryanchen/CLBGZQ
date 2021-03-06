/**
 * @file ADC.c
 * @brief ADC 采样配置以及位移计算
 * @author Ryan·Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 13-08-2020
 *
 * @copyright Copyright (c) 2020  Ryan·Chen
 *
 * @par 更改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>13-08-2020 <td>1.0     <td>Ryan·Chen     <td>ADC采集电压信号
 * <tr><td>22-09-2020 <td>1.0     <td>Ryan·Chen     <td>代码规范
 * <tr><td>27-09-2020 <td>1.0     <td>Ryan·Chen     <td>将位移限制在0-20mm之间
 * <tr><td>15-10-2020 <td>1.0     <td>Ryan·Chen     <td>修改按通道计算均方根函数和计算位移函数
 * <tr><td>26-10-2020 <td>1.0     <td>Ryan·Chen     <td>计算位移加入中间变量而不是直接用宏定义的极值
 */

/* 头文件包含 */
#include "ADC.h"
#include <math.h>
#include "MODBUS_USART1.h"

/* 全局变量定义 */
uint16_t ADC_ConvertValue       [SAMPLE_TIMES][NUMBER_OF_CHANNELS] = {0};  /**< 存储AD 4个通道转换的AD值 */
float    ADC_RootMeanSquare     [NUMBER_OF_CHANNELS]               = {0.0};/**< 存储AD 4个通道的转换值计算的均方根值 */
float    ADC_WeiYi              [NUMBER_OF_CHANNELS]               = {0.0};/**< 存储AD 4个通道对应计算的位移值 */
uint8_t  ADC_ConvertCompleteFlag                                   = 0;    /**< ADC-DMA转换完成一次标志位 */

float    ADC_Ch0MinValue = 0.0;/**< ADC通道1参考最小值 */
float    ADC_Ch0MaxValue = 0.0;/**< ADC通道1参考最大值 */
float    ADC_Ch1MinValue = 0.0;/**< ADC通道2参考最小值 */
float    ADC_Ch1MaxValue = 0.0;/**< ADC通道2参考最大值 */
float    ADC_Ch2MinValue = 0.0;/**< ADC通道3参考最小值 */
float    ADC_Ch2MaxValue = 0.0;/**< ADC通道3参考最大值 */
float    ADC_Ch3MinValue = 0.0;/**< ADC通道4参考最小值 */
float    ADC_Ch3MaxValue = 0.0;/**< ADC通道4参考最大值 */


/**
 * @brief ADC 引脚配置
 */
static void ADC_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;                                                              // 初始化结构体定义

    RCC_APB2PeriphClockCmd(ADC_0_GPIO_CLK | ADC_1_GPIO_CLK | ADC_2_GPIO_CLK | ADC_3_GPIO_CLK, ENABLE);// 开启GPIO时钟

    /* 结构体配置 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;

    GPIO_InitStructure.GPIO_Pin  = ADC_0_GPIO_PIN;
    GPIO_Init(ADC_0_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = ADC_1_GPIO_PIN;
    GPIO_Init(ADC_1_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = ADC_2_GPIO_PIN;
    GPIO_Init(ADC_2_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = ADC_3_GPIO_PIN;
    GPIO_Init(ADC_3_GPIO_PORT, &GPIO_InitStructure);
}



/**
 * @brief ADC 模式配置
 */
static void ADC_ModeConfig(void)
{
    ADC_InitTypeDef ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);                   // 打开ADC时钟

    /* ADC模式配置 */
    ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;       // 只使用一个ADC，属于单模式
    ADC_InitStructure.ADC_ScanConvMode       = ENABLE;                     // 开启扫描模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                     // 连续转换模式
    ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;  // 不使用外部触发，软件开启
    ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;        // 结果右对齐
    ADC_InitStructure.ADC_NbrOfChannel       = NUMBER_OF_CHANNELS;         // 转换通道个数
    ADC_Init(ADC1, &ADC_InitStructure);                                    // 初始化配置

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);                                      // 配置ADC时钟为PCLK2的6分频，即12MHz

    /* 配置ADC通道的转换顺序和采样时间 */
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_0, 1, ADC_SampleTime_MACRO);
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_1, 2, ADC_SampleTime_MACRO);
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_2, 3, ADC_SampleTime_MACRO);
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_3, 4, ADC_SampleTime_MACRO);

    ADC_DMACmd(ADC1, ENABLE);                                              // 使能ADC DMA请求
    ADC_Cmd(ADC1, ENABLE);                                                 // 开启ADC，并开始转换
    ADC_ResetCalibration(ADC1);                                            // 初始化ADC校准寄存器
    while (ADC_GetResetCalibrationStatus(ADC1));                           // 等待校准寄存器初始化完成
    ADC_StartCalibration(ADC1);                                            // ADC开始校准
    while (ADC_GetCalibrationStatus(ADC1));                                // 等待校准完成

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);                                // 由于没有采用外部触发，所以使用软件触发ADC转换
}



/**
 * @brief ADC DMA 中断配置
 */
static void ADC_DMA_NVICConfig(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;                                        // 声明中断控制向量的初始化结构体变量

    /* 每个工程都需要选择嵌套向量中断控制分组，但是只选择一次，所以我在主函数中选择 */

    NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Channel1_IRQn;  // 选择中断源
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;                   // 设置中断的抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;                   // 设置中断的子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;              // 是否使能该中断源
    NVIC_Init(&NVIC_InitStructure);                                             // 初始化结构体
}



/**
 * @brief ADC DMA 配置
 */
static void ADC_DmaConfig(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                               // 打开DMA时钟

    DMA_DeInit(DMA1_Channel1);                                                       // 复位DMA控制器

    /* 配置DMA初始化结构体 */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR));              // 外设基地址：ADC 数据寄存器地址
    DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)(&ADC_ConvertValue[0][0]);  // 存储器地址
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;                // 数据源来自外设
    DMA_InitStructure.DMA_BufferSize         = (SAMPLE_TIMES * NUMBER_OF_CHANNELS);  // 缓冲区大小，应该大于数据目的地的大小
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;            // 外设寄存器地址只有一个，地址不用递增
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;                 // 存储地址递增
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;      // 外设数据大小为半字，即两个字节
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;          // 内存数据大小也为半字
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;                    // 循环传输模式
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;                    // DMA传输通道优先级为高，只使用一个DMA通道是，没影响
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;                      // 禁止存储器到存储器模式
    DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);                                   // 初始化DMA

    ADC_DMA_NVICConfig();                                                            // DMA 中断配置
    DMA_ITConfig(ADC_DMA_CHANNEL, DMA_IT_TC, ENABLE);                                // 使能DMA传送完成中断

    DMA_Cmd(ADC_DMA_CHANNEL, ENABLE);                                                // 使能DMA通道
}



/**
 * @brief ADC 初始化
 */
void ADC_LocalInit(void)
{
    ADC_GpioInit();
    ADC_DmaConfig();
    ADC_ModeConfig();
}



/**
 * @brief  计算相应通道的均方根值
 * @param  channel          通道选择，0-3对应通道1-4，4表示所有通道。
 */
void ADC_CalcRootMeanSquare(uint8_t channel)
{
    uint64_t SumOfSquare = 0;
    uint16_t i           = 0;
    uint16_t j           = 0;

    if (4 == channel)                           // 计算4个通道的均方根
    {
        for ( i = 0; i < 4; i++)
        {
            for (j = 0; j < SAMPLE_TIMES; j++)
            {
                SumOfSquare += (uint64_t)ADC_ConvertValue[j][i] * (uint64_t)ADC_ConvertValue[j][i];
            }

            ADC_RootMeanSquare[i] = sqrt((double)SumOfSquare / SAMPLE_TIMES);
            SumOfSquare = 0;
        }
    }
    else if (0 == channel)                      // 计算通道1的均方根
    {
        SumOfSquare = 0;
        for (j = 0; j < SAMPLE_TIMES; j++)
        {
            SumOfSquare += (uint64_t)ADC_ConvertValue[j][0] * (uint64_t)ADC_ConvertValue[j][0];
        }

        ADC_RootMeanSquare[0] = sqrt((double)SumOfSquare / SAMPLE_TIMES);
    }
    else if (1 == channel)                      // 计算通道2的均方根
    {
        SumOfSquare = 0;
        for (j = 0; j < SAMPLE_TIMES; j++)
        {
            SumOfSquare += (uint64_t)ADC_ConvertValue[j][1] * (uint64_t)ADC_ConvertValue[j][1];
        }

        ADC_RootMeanSquare[1] = sqrt((double)SumOfSquare / SAMPLE_TIMES);
    }
    else if (2 == channel)                      // 计算通道3的均方根
    {
        SumOfSquare = 0;
        for (j = 0; j < SAMPLE_TIMES; j++)
        {
            SumOfSquare += (uint64_t)ADC_ConvertValue[j][2] * (uint64_t)ADC_ConvertValue[j][2];
        }

        ADC_RootMeanSquare[2] = sqrt((double)SumOfSquare / SAMPLE_TIMES);
    }
    else if (3 == channel)                      // 计算通道4的均方根
    {
        SumOfSquare = 0;
        for (j = 0; j < SAMPLE_TIMES; j++)
        {
            SumOfSquare += (uint64_t)ADC_ConvertValue[j][3] * (uint64_t)ADC_ConvertValue[j][3];
        }

        ADC_RootMeanSquare[3] = sqrt((double)SumOfSquare / SAMPLE_TIMES);
    }
}



/**
 * @brief  ADC 测量值与位移换算方法
 * @param  Value            通道测量值（均方根）
 * @param  Max              0 位移对应的 通道测量值
 * @param  Min              20 位移对应的 通道测量值
 * @return double           对应的位移值
 */
static double ADC_CalcHuanSuan(double Value, float Max, float Min)
{
    /* 计算方法
    MAX -- MIN
    0   -- 20   这里20代表2厘米 */
    float temp = 0.0;
    temp = (20 * ((Value - Max) / (Min - Max)));
    
    /* 将结果限定在0-20之间 */
    if (temp < 0)
    {
        temp = 0;
    }
    if (temp > 20)
    {
        temp = 20;
    }
    
    return temp;
}



/**
 * @brief  计算位移
 * @param  channel          通道选择，0-3对应通道1-4，4表示所有通道。
 */
void ADC_CalcWeiYi(uint8_t channel)
{
    // 首先计算对应通道的均方根值
    ADC_CalcRootMeanSquare(channel);

    if (4 == channel)
    {
        ADC_WeiYi[0] = ADC_CalcHuanSuan(ADC_RootMeanSquare[0], ADC_Ch0MaxValue, ADC_Ch0MinValue);
        ADC_WeiYi[1] = ADC_CalcHuanSuan(ADC_RootMeanSquare[1], ADC_Ch1MaxValue, ADC_Ch1MinValue);
        ADC_WeiYi[2] = ADC_CalcHuanSuan(ADC_RootMeanSquare[2], ADC_Ch2MaxValue, ADC_Ch2MinValue);
        ADC_WeiYi[3] = ADC_CalcHuanSuan(ADC_RootMeanSquare[3], ADC_Ch3MaxValue, ADC_Ch3MinValue);

        /* 位移赋值 */
        WEIYI1 = ADC_WeiYi[0];
        WEIYI2 = ADC_WeiYi[1];
        WEIYI3 = ADC_WeiYi[2];
        WEIYI4 = ADC_WeiYi[3];
    }
    else if (0 == channel)
    {
        ADC_WeiYi[0] = ADC_CalcHuanSuan(ADC_RootMeanSquare[0], ADC_Ch0MaxValue, ADC_Ch0MinValue);

         /* 位移赋值 */
        WEIYI1 = ADC_WeiYi[0];
    }
    else if (1 == channel)
    {
        ADC_WeiYi[1] = ADC_CalcHuanSuan(ADC_RootMeanSquare[1], ADC_Ch1MaxValue, ADC_Ch1MinValue);

         /* 位移赋值 */
        WEIYI2 = ADC_WeiYi[1];
    }
    else if (2 == channel)
    {
        ADC_WeiYi[2] = ADC_CalcHuanSuan(ADC_RootMeanSquare[2], ADC_Ch2MaxValue, ADC_Ch2MinValue);

         /* 位移赋值 */
        WEIYI3 = ADC_WeiYi[2];
    }
    else if (3 == channel)
    {
        ADC_WeiYi[3] = ADC_CalcHuanSuan(ADC_RootMeanSquare[3], ADC_Ch3MaxValue, ADC_Ch3MinValue);

         /* 位移赋值 */
        WEIYI4 = ADC_WeiYi[3];
    }
}

