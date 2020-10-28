/**
 * @file main.c
 * @brief �������Ҫִ�����̣�2020.09.21���
 * @author Ryan��Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 21-09-2020
 *
 * @copyright Copyright (c) 2020  Ryan��Chen
 *
 * @par ������־:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>21-09-2020 <td>1.0     <td>Ryan��Chen     <td>�����ļ�ͷ˵�����淶ע�ͣ�ɾ������Ҫ���롢����
 * <tr><td>26-10-2020 <td>1.0     <td>Ryan��Chen     <td>��ʼ����ADͨ���Ĳο���ֵ
 * </table>
 */
#include "global.h"

int main(void)
{
    globalInit();

    while(1)
    {
        // globalAdcHandle();


        // // ADCת�����
        if (ADC_ConvertCompleteFlag == 1)
        {
            /* Your Code */
            ADC_CalcWeiYi(4);

            // TIM_SetCompare1(TIM1, 40000 * 0.115);

            /* Your Code */
            ADC_ConvertCompleteFlag = 0;                        // ADC_ConvertCompleteFlag ��Ϊ0
            ADC_LocalInit();                                    // ���� DMA
        }
        globalModbusHandle();
    }
}
