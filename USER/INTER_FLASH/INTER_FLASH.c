/**
 * @file INTER_FLASH.c
 * @brief 
 * @author Ryan��Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 27-07-2020
 * 
 * @copyright Copyright (c) 2020  Ryan��Chen
 * 
 * @par ������־:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>27-07-2020 <td>1.0     <td>Ryan��Chen     <td>�ڲ�FLASH�洢����
 * </table>
 */

#include "INTER_FLASH.h"

/**
 * @brief  ��ָ����ַд��32λ����
 * @param  l_address        FLASH��ַ
 * @param  l_data           д�������
 * @return ����0д��ɹ���-1д��ʧ��
 */
int INTER_FLASH_ProgramWord(uint32_t l_address, uint32_t l_data)
{
    // ����
    FLASH_Unlock();

    // ��������
    FLASH_ErasePage(l_address);

    // д������
    FLASH_ProgramWord(l_address, l_data);

    // ����
    FLASH_Lock();

    // ��֤�����Ƿ���ȷ
    if (*(__IO uint32_t *)l_address == l_data)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

