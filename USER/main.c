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
        // ADCת�����
        if (ADC_ConvertCompleteFlag == 1)
        {
            ADC_CalcWeiYi(4);
            /* Your Code */

            PWMx_SetWidth(0,10);
            PWMx_SetWidth(1,10);
            PWMx_SetWidth(2,10);
            PWMx_SetWidth(3,10);

            /* Your Code */
            ADC_ConvertCompleteFlag = 0;                        // ADC_ConvertCompleteFlag ��Ϊ0
            ADC_LocalInit();                                    // ���� ADC
        }
        globalModbusHandle();
    }
}
