/**
 * @file ADC.c
 * @brief 
 * @author Ryan��Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 13-08-2020
 * 
 * @copyright Copyright (c) 2020  Ryan��Chen
 * 
 * @par ������־:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>13-08-2020 <td>1.0     <td>Ryan��Chen     <td>ADC�ɼ���ѹ�ź�
 * </table>
 */

#include "ADC.h"

/* ȫ�ֱ������� */
uint16_t ADC_ConvertValue[NUMBER_OF_CHANNELS] = {0};

static void ADC_GpioInit(void)
{
    /* ��ʼ���ṹ�嶨�� */
    GPIO_InitTypeDef GPIO_InitStructure;

    // ����GPIOʱ��
    RCC_APB2PeriphClockCmd(ADC_0_GPIO_CLK | ADC_1_GPIO_CLK | ADC_2_GPIO_CLK | ADC_3_GPIO_CLK, ENABLE);

    // �ṹ������
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

    // ��ADCʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    // ADCģʽ����
    // ֻʹ��һ��ADC�����ڵ�ģʽ
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    // ����ɨ��ģʽ
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    // ����ת��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    // ��ʹ���ⲿ�������������
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    // ����Ҷ���
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    // ת��ͨ������
    ADC_InitStructure.ADC_NbrOfChannel = NUMBER_OF_CHANNELS;
    // ��ʼ������
    ADC_Init(ADC1, &ADC_InitStructure);

    // ����ADCʱ��ΪPCLK2��6���䣬��12MHz
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    // ����ADCͨ����ת��˳��Ͳ���ʱ��
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_0, 1, ADC_SampleTime_1Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_1, 2, ADC_SampleTime_1Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_2, 3, ADC_SampleTime_1Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_3, 4, ADC_SampleTime_1Cycles5);

    // ʹ��ADC DMA����
    ADC_DMACmd(ADC1, ENABLE);
    // ����ADC������ʼת��
    ADC_Cmd(ADC1, ENABLE);
    // ��ʼ��ADCУ׼�Ĵ���
    ADC_ResetCalibration(ADC1);
    // �ȴ�У׼�Ĵ�����ʼ�����
    while (ADC_GetResetCalibrationStatus(ADC1));
    // ADC��ʼУ׼
    ADC_StartCalibration(ADC1);
    // �ȴ�У׼���
    while (ADC_GetCalibrationStatus(ADC1));

    // ����û�в����ⲿ����������ʹ���������ADCת��
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

static void ADC_DmaConfig(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    // ��DMAʱ��
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    // DMA ģʽ����
    DMA_DeInit(ADC_DMA_CHANNEL);
    // ����DMA��ʼ���ṹ��
    // �������ַ��ADC ���ݼĴ�����ַ
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR));
    // �洢����ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_ConvertValue;
    // ����Դ��������
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    // ��������С��Ӧ�ô�������Ŀ�ĵصĴ�С
    DMA_InitStructure.DMA_BufferSize = NUMBER_OF_CHANNELS;
    // ����Ĵ�����ַֻ��һ������ַ���õ���
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    // �洢��ַ����
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    // �������ݴ�СΪ���֣��������ֽ�
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    // �ڴ����ݴ�СҲΪ����
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    // ѭ������ģʽ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    // DMA����ͨ�����ȼ�Ϊ�ߣ�ֻʹ��һ��DMAͨ���ǣ�ûӰ��
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    // ��ֹ�洢�����洢��ģʽ
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    // ��ʼ��DMA
    DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
    // ʹ��DMAͨ��
    DMA_Cmd(ADC_DMA_CHANNEL, ENABLE);
}

void ADC_LocalInit(void)
{
    ADC_GpioInit();
    ADC_DmaConfig();
    ADC_ModeConfig();
}