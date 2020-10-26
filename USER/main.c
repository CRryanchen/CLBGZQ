/**
 * @file main.c
 * @brief 程序的主要执行流程，2020.09.21添加
 * @author Ryan·Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 21-09-2020
 *
 * @copyright Copyright (c) 2020  Ryan·Chen
 *
 * @par 更改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>21-09-2020 <td>1.0     <td>Ryan·Chen     <td>增加文件头说明，规范注释，删除不必要代码、变量
 * <tr><td>26-10-2020 <td>1.0     <td>Ryan·Chen     <td>初始化各AD通道的参考极值
 * </table>
 */
#include "global.h"

int main(void)
{
    globalInit();

    while(1)
    {
        // SysTick_Delayms(100);
        // TIM_SetCompare4(TIM1, 500);
        // globalAdcHandle();

        // ADC转换完成
        if (ADC_ConvertCompleteFlag == 1)
        {
            /* Your Code */


            /* Your Code */
            ADC_ConvertCompleteFlag = 0;                        // ADC_ConvertCompleteFlag 置为0
            ADC_LocalInit();                                    // 重启 DMA
        }
        globalModbusHandle();
    }
}
