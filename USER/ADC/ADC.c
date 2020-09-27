/**
 * @file ADC.c
 * @brief ADC ���������Լ�λ�Ƽ���
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
 * <tr><td>22-09-2020 <td>1.0     <td>Ryan��Chen     <td>����淶
 * <tr><td>27-09-2020 <td>1.0     <td>Ryan��Chen     <td>��λ��������0-20mm֮��
 * </table>
 */

/* ͷ�ļ����� */
#include "ADC.h"
#include <math.h>
#include "MODBUS_USART1.h"

/* ȫ�ֱ������� */
uint16_t ADC_ConvertValue       [SAMPLE_TIMES][NUMBER_OF_CHANNELS] = {0};  /**< �洢AD 4��ͨ��ת����ADֵ */
float    ADC_RootMeanSquare     [NUMBER_OF_CHANNELS]               = {0.0};/**< �洢AD 4��ͨ����ת��ֵ����ľ�����ֵ */
float    ADC_WeiYi              [NUMBER_OF_CHANNELS]               = {0.0};/**< �洢AD 4��ͨ����Ӧ�����λ��ֵ */
uint8_t  ADC_ConvertCompleteFlag                                   = 0;    /**< ADC-DMAת�����һ�α�־λ */

/**
 * @brief ADC ��������
 */
static void ADC_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;                                                              // ��ʼ���ṹ�嶨��

    RCC_APB2PeriphClockCmd(ADC_0_GPIO_CLK | ADC_1_GPIO_CLK | ADC_2_GPIO_CLK | ADC_3_GPIO_CLK, ENABLE);// ����GPIOʱ��

    /* �ṹ������ */
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
 * @brief ADC ģʽ����
 */
static void ADC_ModeConfig(void)
{
    ADC_InitTypeDef ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);                   // ��ADCʱ��

    /* ADCģʽ���� */
    ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;       // ֻʹ��һ��ADC�����ڵ�ģʽ
    ADC_InitStructure.ADC_ScanConvMode       = ENABLE;                     // ����ɨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                     // ����ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;  // ��ʹ���ⲿ�������������
    ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;        // ����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel       = NUMBER_OF_CHANNELS;         // ת��ͨ������
    ADC_Init(ADC1, &ADC_InitStructure);                                    // ��ʼ������

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);                                      // ����ADCʱ��ΪPCLK2��6��Ƶ����12MHz

    /* ����ADCͨ����ת��˳��Ͳ���ʱ�� */
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_0, 1, ADC_SampleTime_MACRO);
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_1, 2, ADC_SampleTime_MACRO);
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_2, 3, ADC_SampleTime_MACRO);
    ADC_RegularChannelConfig(ADC1, ADC_CHANNEL_3, 4, ADC_SampleTime_MACRO);

    ADC_DMACmd(ADC1, ENABLE);                                              // ʹ��ADC DMA����
    ADC_Cmd(ADC1, ENABLE);                                                 // ����ADC������ʼת��
    ADC_ResetCalibration(ADC1);                                            // ��ʼ��ADCУ׼�Ĵ���
    while (ADC_GetResetCalibrationStatus(ADC1));                           // �ȴ�У׼�Ĵ�����ʼ�����
    ADC_StartCalibration(ADC1);                                            // ADC��ʼУ׼
    while (ADC_GetCalibrationStatus(ADC1));                                // �ȴ�У׼���

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);                                // ����û�в����ⲿ����������ʹ���������ADCת��
}


/**
 * @brief ADC DMA �ж�����
 */
static void ADC_DMA_NVICConfig(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;                                        // �����жϿ��������ĳ�ʼ���ṹ�����

    /* ÿ�����̶���Ҫѡ��Ƕ�������жϿ��Ʒ��飬����ֻѡ��һ�Σ�����������������ѡ�� */

    NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Channel1_IRQn;  // ѡ���ж�Դ
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;                   // �����жϵ���ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;                   // �����жϵ������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;              // �Ƿ�ʹ�ܸ��ж�Դ
    NVIC_Init(&NVIC_InitStructure);                                             // ��ʼ���ṹ��
}



/**
 * @brief ADC DMA ����
 */
static void ADC_DmaConfig(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                               // ��DMAʱ��

    DMA_DeInit(DMA1_Channel1);                                                       // ��λDMA������

    /* ����DMA��ʼ���ṹ�� */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR));              // �������ַ��ADC ���ݼĴ�����ַ
    DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)(&ADC_ConvertValue[0][0]);  // �洢����ַ
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;                // ����Դ��������
    DMA_InitStructure.DMA_BufferSize         = (SAMPLE_TIMES * NUMBER_OF_CHANNELS);  // ��������С��Ӧ�ô�������Ŀ�ĵصĴ�С
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;            // ����Ĵ�����ַֻ��һ������ַ���õ���
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;                 // �洢��ַ����
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;      // �������ݴ�СΪ���֣��������ֽ�
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;          // �ڴ����ݴ�СҲΪ����
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;                    // ѭ������ģʽ
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;                    // DMA����ͨ�����ȼ�Ϊ�ߣ�ֻʹ��һ��DMAͨ���ǣ�ûӰ��
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;                      // ��ֹ�洢�����洢��ģʽ
    DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);                                   // ��ʼ��DMA

    ADC_DMA_NVICConfig();                                                            // DMA �ж�����
    DMA_ITConfig(ADC_DMA_CHANNEL, DMA_IT_TC, ENABLE);                                // ʹ��DMA��������ж�

    DMA_Cmd(ADC_DMA_CHANNEL, ENABLE);                                                // ʹ��DMAͨ��
}

/**
 * @brief ADC ��ʼ��
 */
void ADC_LocalInit(void)
{
    ADC_GpioInit();
    ADC_DmaConfig();
    ADC_ModeConfig();
}

/**
 * @brief ���������ֵ
 */
void ADC_CalcRootMeanSquare(void)
{
    uint64_t SumOfSquare = 0;
    uint16_t i           = 0;
    uint16_t j           = 0;

    for ( i = 0; i < 1; i++)
    {
        for (j = 0; j < SAMPLE_TIMES; j++)
        {
            SumOfSquare += (uint64_t)ADC_ConvertValue[j][i] * (uint64_t)ADC_ConvertValue[j][i];
        }

        ADC_RootMeanSquare[i] = sqrt((double)SumOfSquare / SAMPLE_TIMES);
        SumOfSquare = 0;
    }
}


/**
 * @brief  ADC ����ֵ��λ�ƻ��㷽��
 * @param  Value            ͨ������ֵ
 * @param  Max              0 λ�ƶ�Ӧ�� ͨ������ֵ
 * @param  Min              20 λ�ƶ�Ӧ�� ͨ������ֵ
 * @return double           ��Ӧ��λ��ֵ
 */
static double ADC_CalcHuanSuan(double Value, float Max, float Min)
{
    /* ���㷽��
    MAX -- MIN
    0   -- 20   ����20����2���� */
    float temp = 0.0;
    temp = (20 * ((Value - Max) / (Min - Max)));
    
    /* ������޶���0-20֮�� */
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
 * @brief  ����λ��
 * @param  channel          ͨ��ѡ��0��ʾ����ͨ��1��1��ʾͨ��2����������
 */
void ADC_CalcWeiYi(uint8_t channel)
{
    if (4 == channel)
    {
        ADC_WeiYi[0] = ADC_CalcHuanSuan(ADC_RootMeanSquare[0], ADC_CHANNEL_0_MAX, ADC_CHANNEL_0_MIN);
        ADC_WeiYi[1] = ADC_CalcHuanSuan(ADC_RootMeanSquare[1], ADC_CHANNEL_1_MAX, ADC_CHANNEL_1_MIN);
        ADC_WeiYi[2] = ADC_CalcHuanSuan(ADC_RootMeanSquare[2], ADC_CHANNEL_2_MAX, ADC_CHANNEL_2_MIN);
        ADC_WeiYi[3] = ADC_CalcHuanSuan(ADC_RootMeanSquare[3], ADC_CHANNEL_3_MAX, ADC_CHANNEL_3_MIN);
    }
    else if (0 == channel)
    {
        ADC_WeiYi[0] = ADC_CalcHuanSuan(ADC_RootMeanSquare[0], ADC_CHANNEL_0_MAX, ADC_CHANNEL_0_MIN);
    }
    else if (1 == channel)
    {
        ADC_WeiYi[1] = ADC_CalcHuanSuan(ADC_RootMeanSquare[1], ADC_CHANNEL_1_MAX, ADC_CHANNEL_1_MIN);
    }
    else if (2 == channel)
    {
        ADC_WeiYi[2] = ADC_CalcHuanSuan(ADC_RootMeanSquare[2], ADC_CHANNEL_2_MAX, ADC_CHANNEL_2_MIN);
    }
    else if (3 == channel)
    {
        ADC_WeiYi[3] = ADC_CalcHuanSuan(ADC_RootMeanSquare[3], ADC_CHANNEL_3_MAX, ADC_CHANNEL_3_MIN);
    }

    /* λ�Ƹ�ֵ */
    WEIYI1 = ADC_WeiYi[0];
    WEIYI2 = ADC_WeiYi[1];
    WEIYI3 = ADC_WeiYi[2];
    WEIYI4 = ADC_WeiYi[3];
}

