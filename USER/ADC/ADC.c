/**
 * @file ADC.c
 * @brief 
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
 * </table>
 */

#include "ADC.h"

/* 全局变量定义 */
uint16_t ADC_ConvertValue[NUMBER_OF_CHANNELS] = {0};

static void ADC_GpioInit(void)
{
    /* 初始化结构体定义 */
    GPIO_InitTypeDef GPIO_InitStructure;

    // 开启GPIO时钟
    RCC_APB2PeriphClockCmd(ADC_0_GPIO_CLK | ADC_1_GPIO_CLK | ADC_2_GPIO_CLK | ADC_3_GPIO_CLK, ENABLE);

    // 结构体配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = ADC_0_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ADC_0_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = ADC_1_GPIO_PIN;
    GPIO_Init(ADC_1_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = ADC_2_GPIO_PIN;
    GPIO_Init(ADC_2_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = ADC_3_GPIO_PIN;
    GPIO_Init(ADC_3_GPIO_PORT, &GPIO_InitStructure);
}

static void ADC_ModeConfig(void)
{
    ADC_InitTypeDef ADC_InitStructure;

    // 打开ADC时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    // ADC模式配置
    // 只使用一个ADC，属于单模式
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    // 开启扫描模式
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    // 连续转换模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    // 不使用外部触发，软件开启
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    // 结果右对齐
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    // 转换通道个数
    ADC_InitStructure.ADC_NbrOfChannel = NUMBER_OF_CHANNELS;
    // 初始化配置
    ADC_Init(ADC1, &ADC_InitStructure);

    // 配置ADC时钟为PCLK2的6分配，即12MHz
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    // 配置ADC通道的转换顺序和采样时间
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_0, 1, ADC_SampleTime_1Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_1, 2, ADC_SampleTime_1Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_2, 3, ADC_SampleTime_1Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_3, 4, ADC_SampleTime_1Cycles5);

    // 使能ADC DMA请求
    ADC_DMACmd(ADC1, ENABLE);
    // 开启ADC，并开始转换
    ADC_Cmd(ADC1, ENABLE);
    // 初始化ADC校准寄存器
    ADC_ResetCalibration(ADC1);
    // 等待校准寄存器初始化完成
    while (ADC_GetResetCalibrationStatus(ADC1));
    // ADC开始校准
    ADC_StartCalibration(ADC1);
    // 等待校准完成
    while (ADC_GetCalibrationStatus(ADC1));

    // 由于没有采用外部触发，所以使用软件触发ADC转换
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

static void ADC_DmaConfig(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    // 打开DMA时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    // DMA 模式配置
    DMA_DeInit(ADC_DMA_CHANNEL);
    // 配置DMA初始化结构体
    // 外设基地址：ADC 数据寄存器地址
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR));
    // 存储器地址
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_ConvertValue;
    // 数据源来自外设
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    // 缓冲区大小，应该大于数据目的地的大小
    DMA_InitStructure.DMA_BufferSize = NUMBER_OF_CHANNELS;
    // 外设寄存器地址只有一个，地址不用递增
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    // 存储地址递增
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    // 外设数据大小为半字，即两个字节
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    // 内存数据大小也为半字
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    // 循环传输模式
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    // DMA传输通道优先级为高，只使用一个DMA通道是，没影响
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    // 禁止存储器到存储器模式
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    // 初始化DMA
    DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
    // 使能DMA通道
    DMA_Cmd(ADC_DMA_CHANNEL, ENABLE);
}

void ADC_LocalInit(void)
{
    ADC_GpioInit();
    ADC_DmaConfig();
    ADC_ModeConfig();
}