/**
 * @file INTER_FLASH.c
 * @brief 
 * @author Ryan·Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 27-07-2020
 * 
 * @copyright Copyright (c) 2020  Ryan·Chen
 * 
 * @par 更改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>27-07-2020 <td>1.0     <td>Ryan·Chen     <td>内部FLASH存储数据
 * </table>
 */

#include "INTER_FLASH.h"

/**
 * @brief  向指定地址写入32位数据
 * @param  l_address        FLASH地址
 * @param  l_data           写入的数据
 * @return 返回0写入成功，-1写入失败
 */
int INTER_FLASH_ProgramWord(uint32_t l_address, uint32_t l_data)
{
    // 解锁
    FLASH_Unlock();

    // 擦除数据
    FLASH_ErasePage(l_address);

    // 写入数据
    FLASH_ProgramWord(l_address, l_data);

    // 上锁
    FLASH_Lock();

    // 验证数据是否正确
    if (*(__IO uint32_t *)l_address == l_data)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

