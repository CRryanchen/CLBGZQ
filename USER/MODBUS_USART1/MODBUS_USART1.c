/**
 * @file MODBUS_USART1.c
 * @brief 使用串口1进行MODBUS通信
 * @author Ryan·Chen (ryan.cr.chen@gmail.com)
 * @version 1.0
 * @date 23-07-2020
 *
 * @copyright Copyright (c) 2020  Ryan·Chen
 *
 * @par 更改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>23-07-2020 <td>1.0     <td>Ryan·Chen     <td>使用串口1进行MODBUS通信
 * <tr><td>21-09-2020 <td>1.0     <td>Ryan·Chen     <td>代码规范化
 * <tr><td>26-10-2020 <td>1.0     <td>Ryan·Chen     <td>加入触摸屏控制设备将当前测得AD当作极值写入FLASH
 * </table>
 */

/* 头文件包含 */
#include "MODBUS_USART1.h"
#include <string.h>                                         // 使用 string 库函数
#include "USART1.h"                                         // 使用串口1
#include "INTER_FLASH.h"                                    // DEVICE_ID_ADDR
#include "adc.h"

/* 全局变量定义 */

MODBUS_USART_RECV_STRUCT MODBUS_USART1_RECV;                /**< 用于MODBUS_USART1数据接收的结构体 */
uint8_t DEVICE_ID;                                          /**< 设备 ID */
float WEIYI1    = 0.555;                                    /**< 位移1 */
float WEIYI2    = 1.0;                                      /**< 位移2 */
float WEIYI3    = 1.5;                                      /**< 位移3 */
float WEIYI4    = 2.0;                                      /**< 位移4 */
float K1_Value  = 0.0;                                      /**< 参数1 */
float K2_Value  = 0.0;                                      /**< 参数2 */
float K3_Value  = 0.0;                                      /**< 参数3 */
float K4_Value  = 0.0;                                      /**< 参数4 */
float K5_Value  = 0.0;                                      /**< 参数5 */
float K6_Value  = 0.0;                                      /**< 参数6 */
float K7_Value  = 0.0;                                      /**< 参数7 */
float K8_Value  = 0.0;                                      /**< 参数8 */
float K9_Value  = 0.0;                                      /**< 参数9 */
float K10_Value = 0.0;                                      /**< 参数10 */



/**
 * @brief MODBUS_USART1_CTL1引脚初始化
 */
static void MODBUS_USART1_CTL1_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;                        // GPIO 初始化结构体定义

    RCC_APB2PeriphClockCmd(MODBUS_USART1_CTL1_GPIO_CLK, ENABLE);// 开启GPIO时钟

    /* 结构体配置 */
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = MODBUS_USART1_CTL1_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MODBUS_USART1_CTL1_GPIO_PORT, &GPIO_InitStructure);
}



/**
 * @brief MODBUS_USART1_CTL2引脚初始化
 */
static void MODBUS_USART1_CTL2_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;                        // GPIO 初始化结构体定义

    RCC_APB2PeriphClockCmd(MODBUS_USART1_CTL2_GPIO_CLK, ENABLE);// 开启GPIO时钟

    /* 结构体配置 */
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = MODBUS_USART1_CTL2_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MODBUS_USART1_CTL2_GPIO_PORT, &GPIO_InitStructure);
}



/**
 * @brief MODBUS_USART1初始化，供外部调用
 */
void MODBUS_USART1_Init(void)
{
    USART1_Init();                                              // 初始化串口1

    MODBUS_USART1_CTL1_GpioInit();                              // 初始化 MODBUS CTL1 引脚
    MODBUS_USART1_CTL2_GpioInit();                              // 初始化 MODBUS CTL2 引脚

    MODBUS_USART1_RECV_STATUS;                                  // MODBUS_USART1置为接收模式

    MODBUS_USART1_RECV.MODBUS_USART_RECV_COUNT = 0;             // 清零MODBUS_USART1数据接收计数器
    MODBUS_USART1_RECV.MODBUS_USART_COMPLETE_FLAG = 0;          // 接收完成标志置1

    DEVICE_ID = *(uint8_t *)DEVICE_ID_ADDR;                     // 读取 DEVICE_ID
}


/**
 * @brief  MODBUS 使用串口1发送数据
 * @param  l_addr           起始地址
 * @param  l_count          数据个数
 */
void MODBUS_USART1_SendData(uint8_t *l_addr, uint8_t l_count)
{
    MODBUS_USART1_SEND_STATUS;                                  // 置于发送状态

    USART1_SendData(l_addr, l_count);                           // 串口1发送数据

    MODBUS_USART1_RECV_STATUS;                                  // 置于接收状态
}

/* 因为串口2测试时也会用重写printf函数，所以我用一个宏来区分 */
#if defined PRINTF_USE_USART2

#else
/**
 * @brief 重定向C库函数printf到串口1
 * @param  ch               发送的字节数据
 * @param  f                文件流指针
 * @return int
 */
int fputc(int ch, FILE *f)
{
    MODBUS_USART1_SEND_STATUS;                                  // 切换为发送模式

    /** 这里我不使用自己写的USART_SendByte函数，因为那个函数里面判断使用的是TXE标志位
     *  这里因为要切换发送和接收，所以不能使用TXE标志位进行判断，所以这里我使用库函数，
     * 并判断TC标志位
     */
    USART_SendData(USART1, ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
        ;
    }

    MODBUS_USART1_RECV_STATUS;                                  // 发送完成，置为接收模式

    return ch;
}



/**
 * @brief 重定向C库函数scanf到串口1
 * @param  f                文件流指针
 * @return int              接收的数据
 */
int fgetc(FILE *f)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
    {
        ;
    }

    return (int)USART_ReceiveData(USART1);
}

#endif /* PRINTF_USE_USART2 */


/**
 * @brief  MODBUS 错误码处理返回
 * @param  l_ErrorNum       错误码
 */
static void MOSBUS_USART_ErrorHandle(uint8_t l_ErrorNum)
{
    uint8_t  l_ErrResponseBuf[5] = {0};                                           // 用于存储返回错误信息
    uint32_t l_CRC16CheckNum     = 0;                                             // CRC校验码

    /* 返回数据的前两个字节固定，都是Device_ID和功能码加0x80 */
    l_ErrResponseBuf[0] = DEVICE_ID;
    l_ErrResponseBuf[1] = MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[1] + 0x80;
    /* 错误码
     * 0X01：不支持该功能码
     * 0X02：内部寄存器寻址异常
     * 0X03：内部寄存器数量异常
     * 0X04：内部寄存器数据异常
     */
    l_ErrResponseBuf[2] = l_ErrorNum;
    l_CRC16CheckNum     = CRC16(l_ErrResponseBuf, sizeof(l_ErrResponseBuf) - 2);
    l_ErrResponseBuf[3] = l_CRC16CheckNum & 0XFF;                                 // 校验码低8位
    l_ErrResponseBuf[4] = l_CRC16CheckNum >> 8;                                   // 校验码高8位

    MODBUS_USART1_SendData(l_ErrResponseBuf, sizeof(l_ErrResponseBuf));           // 发送数据
}



/**
 * @brief  内存中的数据复制到另一块内存，高低字节交换
 * @param  l_des            目的数据地址
 * @param  l_src            源数据地址
 * @param  l_length         数据长度（单位：字节）
 */
static void MOSBUS_USART_Memcpy(void * l_des, void * l_src, uint8_t l_length)
{
    uint8_t * des = (uint8_t *)l_des;
    uint8_t * src = (uint8_t *)l_src;
    while (l_length)
    {
        l_length--;
        *des = *(src + l_length);
        des++;
    }
}



/**
 * @brief  从起始地址作为高字节地址，读取4字节的数据对应的float值
 * @param  l_src            起始地址
 * @return float            对应的float 值
 */
static float MODBUS_USART_FloatAss(uint8_t *l_src)
{
    uint8_t l_tempbuf[4] = {0};
    float   l_tempres    = 0.0;

    l_tempbuf[3] = *(l_src + 0);                                                  // 第1个字节数据赋值给数组[3]
    l_tempbuf[2] = *(l_src + 1);                                                  // 第2个字节数据赋值给数组[2]
    l_tempbuf[1] = *(l_src + 2);                                                  // 第3个字节数据赋值给数组[1]
    l_tempbuf[0] = *(l_src + 3);                                                  // 第4个字节数据赋值给数组[0]

	l_tempres = *(float *)l_tempbuf;

    return l_tempres;
}



/**
 * @brief  MODBUS 03 命令码处理程序
 */
static void MODBUS_USART_03_Handle()
{
    if (8 == MODBUS_USART1_RECV.MODBUS_USART_RECV_COUNT)             // 读取的字节长度应该是8个字节，如果不是，则出错
    {
        /* 局部变量声明 */
        uint16_t l_RegAddr         = 0;                              // 寄存器地址
        uint16_t l_ResCnt          = 0;                              // 寄存器个数
        uint32_t l_CRC16CheckNum   = 0;                              // CRC校验码
        uint8_t  l_ResponseBuf[46] = {0};                            // 用于存储返回数据

        /* 返回数据的前两个字节固定，都是Device_ID和功能码 */
        l_ResponseBuf[0] = DEVICE_ID;
        l_ResponseBuf[1] = MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[1];

		l_RegAddr = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[2] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[3];

        switch (l_RegAddr)
        {
            /* 设备ID号 */
            case 1001:
            {
			    l_ResCnt = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];
                if (1 == l_ResCnt)
                {
                    l_ResponseBuf[2] = 0x02;
                    l_ResponseBuf[3] = 0x00;
                    l_ResponseBuf[4] = DEVICE_ID;

                    l_CRC16CheckNum  = CRC16(l_ResponseBuf, 5);
                    l_ResponseBuf[5] = l_CRC16CheckNum & 0XFF;       // 校验码低8位
                    l_ResponseBuf[6] = l_CRC16CheckNum >> 8;         // 校验码高8位

                    MODBUS_USART1_SendData(l_ResponseBuf, 7);
                }
                /* 寄存器数量异常 */
                else
                {
                    MOSBUS_USART_ErrorHandle(0x03);
                }
            }
            break;

            case 1002:
            {
                l_ResCnt = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];
                if (l_ResCnt == 8)
                {
                    l_ResponseBuf[2] = 0x10;

                    /* 读取位移1-4 */
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[3], (uint8_t *)&WEIYI1, 4);
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[7], (uint8_t *)&WEIYI2, 4);
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[11], (uint8_t *)&WEIYI3, 4);
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[15], (uint8_t *)&WEIYI4, 4);

                    l_CRC16CheckNum   = CRC16(l_ResponseBuf, 19);
                    l_ResponseBuf[19] = l_CRC16CheckNum & 0XFF;      // 校验码低8位
                    l_ResponseBuf[20] = l_CRC16CheckNum >> 8;        // 校验码高8位

                    MODBUS_USART1_SendData(l_ResponseBuf, 21);
                }
                /* 寄存器数量异常 */
                else
                {
                    MOSBUS_USART_ErrorHandle(0x03);
                }
            }
            break;

            case 1010:
            {
                l_ResCnt = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];
                if (l_ResCnt == 20)
                {
                    l_ResponseBuf[2] = 0x28;

                    /* 读取参数K1-K10 */
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[3]  , (uint8_t *)K1_ADDR  , 4);
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[7]  , (uint8_t *)K2_ADDR  , 4);
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[11] , (uint8_t *)K3_ADDR  , 4);
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[15] , (uint8_t *)K4_ADDR  , 4);
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[19] , (uint8_t *)K5_ADDR  , 4);
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[23] , (uint8_t *)K6_ADDR  , 4);
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[27] , (uint8_t *)K7_ADDR  , 4);
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[31] , (uint8_t *)K8_ADDR  , 4);
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[35] , (uint8_t *)K9_ADDR  , 4);
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[39] , (uint8_t *)K10_ADDR , 4);

                    l_CRC16CheckNum   = CRC16(l_ResponseBuf, 43);
                    l_ResponseBuf[43] = l_CRC16CheckNum & 0XFF;      // 校验码低8位
                    l_ResponseBuf[44] = l_CRC16CheckNum >> 8;        // 校验码高8位

                    MODBUS_USART1_SendData(l_ResponseBuf, 45);
                }
                /* 寄存器数量异常 */
                else
                {
                    MOSBUS_USART_ErrorHandle(0x03);
                }
            }
            break;

            /* ADC通道0最小值 */
            case 1030:
            {
			    l_ResCnt = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];
                if (2 == l_ResCnt)
                {
                    l_ResponseBuf[2] = 0x04;
                    
                    //todo: 3、4、5、7传送此时测得的通道0最小值(全部插入)
                    ADC_CalcRootMeanSquare(0);// 计算通道0的均方根
                    ADC_Ch0MinValue = ADC_RootMeanSquare[0];// 重置ADC_Ch0MinValue

                    //todo: 将此时的通道0最小值写入Flash
                    FLASH_Unlock();                                          // 解锁
                    FLASH_ErasePage(CH0MIN_ADDR);                                // 擦除页数据

                    FLASH_ProgramWord(CH0MIN_ADDR  , *(uint32_t *)&ADC_RootMeanSquare[0]);
                    FLASH_Lock();

                    // 将值写入临时数组
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[3] , (uint8_t *)CH0MIN_ADDR , 4);

                    l_CRC16CheckNum  = CRC16(l_ResponseBuf, 7);
                    l_ResponseBuf[7] = l_CRC16CheckNum & 0XFF;       // 校验码低8位
                    l_ResponseBuf[8] = l_CRC16CheckNum >> 8;         // 校验码高8位

                    MODBUS_USART1_SendData(l_ResponseBuf, 9);
                }
                /* 寄存器数量异常 */
                else
                {
                    MOSBUS_USART_ErrorHandle(0x03);
                }
            }
            break;

            /* ADC通道0最大值 */
            case 1032:
            {
			    l_ResCnt = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];
                if (2 == l_ResCnt)
                {
                    l_ResponseBuf[2] = 0x04;
                    
                    //todo: 3、4、5、7传送此时测得的通道0最大值(全部取出)
                    ADC_CalcRootMeanSquare(0);// 计算通道0的均方根
                    ADC_Ch0MaxValue = ADC_RootMeanSquare[0];// 重置ADC_Ch0MaxValue

                    //todo: 将此时的通道0最大值写入Flash
                    FLASH_Unlock();                                          // 解锁
                    FLASH_ErasePage(CH0MAX_ADDR);                                // 擦除页数据

                    FLASH_ProgramWord(CH0MAX_ADDR  , *(uint32_t *)&ADC_RootMeanSquare[0]);
                    FLASH_Lock();

                    // 将值写入临时数组
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[3] , (uint8_t *)CH0MAX_ADDR , 4);

                    l_CRC16CheckNum  = CRC16(l_ResponseBuf, 7);
                    l_ResponseBuf[7] = l_CRC16CheckNum & 0XFF;       // 校验码低8位
                    l_ResponseBuf[8] = l_CRC16CheckNum >> 8;         // 校验码高8位

                    MODBUS_USART1_SendData(l_ResponseBuf, 9);
                }
                /* 寄存器数量异常 */
                else
                {
                    MOSBUS_USART_ErrorHandle(0x03);
                }
            }
            break;

            /* ADC通道1最小值 */
            case 1034:
            {
			    l_ResCnt = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];
                if (2 == l_ResCnt)
                {
                    l_ResponseBuf[2] = 0x04;
                    
                    //todo: 3、4、5、7传送此时测得的通道1最小值(全部插入)
                    ADC_CalcRootMeanSquare(1);// 计算通道1的均方根
                    ADC_Ch1MinValue = ADC_RootMeanSquare[1];// 重置ADC_Ch1MinValue

                    //todo: 将此时的通道1最小值写入Flash
                    FLASH_Unlock();                                          // 解锁
                    FLASH_ErasePage(CH1MIN_ADDR);                                // 擦除页数据

                    FLASH_ProgramWord(CH1MIN_ADDR  , *(uint32_t *)&ADC_RootMeanSquare[1]);
                    FLASH_Lock();

                    // 将值写入临时数组
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[3] , (uint8_t *)CH1MIN_ADDR , 4);

                    l_CRC16CheckNum  = CRC16(l_ResponseBuf, 7);
                    l_ResponseBuf[7] = l_CRC16CheckNum & 0XFF;       // 校验码低8位
                    l_ResponseBuf[8] = l_CRC16CheckNum >> 8;         // 校验码高8位

                    MODBUS_USART1_SendData(l_ResponseBuf, 9);
                }
                /* 寄存器数量异常 */
                else
                {
                    MOSBUS_USART_ErrorHandle(0x03);
                }
            }
            break;

            /* ADC通道1最大值 */
            case 1036:
            {
			    l_ResCnt = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];
                if (2 == l_ResCnt)
                {
                    l_ResponseBuf[2] = 0x04;
                    
                    //todo: 3、4、5、7传送此时测得的通道1最大值(全部取出)
                    ADC_CalcRootMeanSquare(1);// 计算通道1的均方根
                    ADC_Ch1MaxValue = ADC_RootMeanSquare[1];// 重置ADC_Ch1MaxValue

                    //todo: 将此时的通道1最大值写入Flash
                    FLASH_Unlock();                                          // 解锁
                    FLASH_ErasePage(CH1MAX_ADDR);                                // 擦除页数据

                    FLASH_ProgramWord(CH1MAX_ADDR  , *(uint32_t *)&ADC_RootMeanSquare[1]);
                    FLASH_Lock();

                    // 将值写入临时数组
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[3] , (uint8_t *)CH1MAX_ADDR , 4);

                    l_CRC16CheckNum  = CRC16(l_ResponseBuf, 7);
                    l_ResponseBuf[7] = l_CRC16CheckNum & 0XFF;       // 校验码低8位
                    l_ResponseBuf[8] = l_CRC16CheckNum >> 8;         // 校验码高8位

                    MODBUS_USART1_SendData(l_ResponseBuf, 9);
                }
                /* 寄存器数量异常 */
                else
                {
                    MOSBUS_USART_ErrorHandle(0x03);
                }
            }
            break;

            /* ADC通道2最小值 */
            case 1038:
            {
			    l_ResCnt = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];
                if (2 == l_ResCnt)
                {
                    l_ResponseBuf[2] = 0x04;
                    
                    //todo: 3、4、5、7传送此时测得的通道2最小值(全部插入)
                    ADC_CalcRootMeanSquare(2);// 计算通道2的均方根
                    ADC_Ch2MinValue = ADC_RootMeanSquare[2];// 重置ADC_Ch2MinValue

                    //todo: 将此时的通道2最小值写入Flash
                    FLASH_Unlock();                                          // 解锁
                    FLASH_ErasePage(CH2MIN_ADDR);                                // 擦除页数据

                    FLASH_ProgramWord(CH2MIN_ADDR  , *(uint32_t *)&ADC_RootMeanSquare[2]);
                    FLASH_Lock();

                    // 将值写入临时数组
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[3] , (uint8_t *)CH2MIN_ADDR , 4);

                    l_CRC16CheckNum  = CRC16(l_ResponseBuf, 7);
                    l_ResponseBuf[7] = l_CRC16CheckNum & 0XFF;       // 校验码低8位
                    l_ResponseBuf[8] = l_CRC16CheckNum >> 8;         // 校验码高8位

                    MODBUS_USART1_SendData(l_ResponseBuf, 9);
                }
                /* 寄存器数量异常 */
                else
                {
                    MOSBUS_USART_ErrorHandle(0x03);
                }
            }
            break;

            /* ADC通道2最大值 */
            case 1040:
            {
			    l_ResCnt = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];
                if (2 == l_ResCnt)
                {
                    l_ResponseBuf[2] = 0x04;
                    
                    //todo: 3、4、5、7传送此时测得的通道2最大值(全部取出)
                    ADC_CalcRootMeanSquare(2);// 计算通道2的均方根
                    ADC_Ch2MaxValue = ADC_RootMeanSquare[2];// 重置ADC_Ch2MaxValue

                    //todo: 将此时的通道2最大值写入Flash
                    FLASH_Unlock();                                          // 解锁
                    FLASH_ErasePage(CH2MAX_ADDR);                                // 擦除页数据

                    FLASH_ProgramWord(CH2MAX_ADDR  , *(uint32_t *)&ADC_RootMeanSquare[2]);
                    FLASH_Lock();

                    // 将值写入临时数组
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[3] , (uint8_t *)CH2MAX_ADDR , 4);

                    l_CRC16CheckNum  = CRC16(l_ResponseBuf, 7);
                    l_ResponseBuf[7] = l_CRC16CheckNum & 0XFF;       // 校验码低8位
                    l_ResponseBuf[8] = l_CRC16CheckNum >> 8;         // 校验码高8位

                    MODBUS_USART1_SendData(l_ResponseBuf, 9);
                }
                /* 寄存器数量异常 */
                else
                {
                    MOSBUS_USART_ErrorHandle(0x03);
                }
            }
            break;

            /* ADC通道3最小值 */
            case 1042:
            {
			    l_ResCnt = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];
                if (2 == l_ResCnt)
                {
                    l_ResponseBuf[2] = 0x04;
                    
                    //todo: 3、4、5、7传送此时测得的通道3最小值(全部插入)
                    ADC_CalcRootMeanSquare(3);// 计算通道3的均方根
                    ADC_Ch3MinValue = ADC_RootMeanSquare[3];// 重置ADC_Ch3MinValue

                    //todo: 将此时的通道3最小值写入Flash
                    FLASH_Unlock();                                          // 解锁
                    FLASH_ErasePage(CH3MIN_ADDR);                                // 擦除页数据

                    FLASH_ProgramWord(CH3MIN_ADDR  , *(uint32_t *)&ADC_RootMeanSquare[3]);
                    FLASH_Lock();

                    // 将值写入临时数组
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[3] , (uint8_t *)CH3MIN_ADDR , 4);

                    l_CRC16CheckNum  = CRC16(l_ResponseBuf, 7);
                    l_ResponseBuf[7] = l_CRC16CheckNum & 0XFF;       // 校验码低8位
                    l_ResponseBuf[8] = l_CRC16CheckNum >> 8;         // 校验码高8位

                    MODBUS_USART1_SendData(l_ResponseBuf, 9);
                }
                /* 寄存器数量异常 */
                else
                {
                    MOSBUS_USART_ErrorHandle(0x03);
                }
            }
            break;

            /* ADC通道3最大值 */
            case 1044:
            {
			    l_ResCnt = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];
                if (2 == l_ResCnt)
                {
                    l_ResponseBuf[2] = 0x04;
                    
                    //todo: 3、4、5、7传送此时测得的通道3最大值(全部取出)
                    ADC_CalcRootMeanSquare(3);// 计算通道3的均方根
                    ADC_Ch3MaxValue = ADC_RootMeanSquare[3];// 重置ADC_Ch3MaxValue

                    //todo: 将此时的通道3最大值写入Flash
                    FLASH_Unlock();                                          // 解锁
                    FLASH_ErasePage(CH3MAX_ADDR);                                // 擦除页数据

                    FLASH_ProgramWord(CH3MAX_ADDR  , *(uint32_t *)&ADC_RootMeanSquare[3]);
                    FLASH_Lock();

                    // 将值写入临时数组
                    MOSBUS_USART_Memcpy(&l_ResponseBuf[3] , (uint8_t *)CH3MAX_ADDR , 4);

                    l_CRC16CheckNum  = CRC16(l_ResponseBuf, 7);
                    l_ResponseBuf[7] = l_CRC16CheckNum & 0XFF;       // 校验码低8位
                    l_ResponseBuf[8] = l_CRC16CheckNum >> 8;         // 校验码高8位

                    MODBUS_USART1_SendData(l_ResponseBuf, 9);
                }
                /* 寄存器数量异常 */
                else
                {
                    MOSBUS_USART_ErrorHandle(0x03);
                }
            }
            break;



            default:
            {
                /* 寄存器寻址异常 */
                MOSBUS_USART_ErrorHandle(0x02);
            }
        }
    }
    /* 数据长度异常 */
    else
    {
        MOSBUS_USART_ErrorHandle(0X04);
    }
}



/**
 * @brief MODBUS 10 命令码处理程序
 */
static void MODBUS_USART_10_Handle()
{
    if (MODBUS_USART1_RECV.MODBUS_USART_RECV_COUNT >= 11)                        // 写入的字节长度应该大于等于11个字节，如果不是，则出错
    {
        /* 局部变量声明 */
        uint16_t l_RegAddr = 0;                                                  // 寄存器地址
        uint16_t l_ResCnt = 0;                                                   // 寄存器个数
        uint16_t l_ByteCnt = 0;                                                  // 有多少字节数据
        uint32_t l_CRC16CheckNum = 0;                                            // CRC校验码
        uint8_t l_ResponseBuf[8] = {0};                                          // 用于存储返回数据

        /* 返回数据的前两个字节固定，都是Device_ID和功能码 */
        l_ResponseBuf[0] = DEVICE_ID;
        l_ResponseBuf[1] = MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[1];

        l_RegAddr = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[2] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[3];
        switch (l_RegAddr)
        {
            case 1001:
            {
                l_ResCnt = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];
                if (1 == l_ResCnt)
                {
                    l_ByteCnt = MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[6];
                    if (2 == l_ByteCnt)
                    {
                        uint16_t l_temp_DeviceID = 0;

                        l_temp_DeviceID = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[7] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[8];
                        DEVICE_ID = (uint8_t)l_temp_DeviceID;                    // 更新Device ID
                        INTER_FLASH_ProgramWord(DEVICE_ID_ADDR, l_temp_DeviceID);// 写入FLASH，重启后可以更新

                        l_ResponseBuf[0] = DEVICE_ID;                            // 这里需要更新一次

                        /* [2][3]返回时还是寄存器地址，[4][5]返回时依旧是寄存器个数 */
                        l_ResponseBuf[2] = MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[2];
                        l_ResponseBuf[3] = MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[3];
                        l_ResponseBuf[4] = MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4];
                        l_ResponseBuf[5] = MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];

                        l_CRC16CheckNum  = CRC16(l_ResponseBuf, 6);
                        l_ResponseBuf[6] = l_CRC16CheckNum & 0XFF;               // 校验码低8位
                        l_ResponseBuf[7] = l_CRC16CheckNum >> 8;                 // 校验码高8位

                        MODBUS_USART1_SendData(l_ResponseBuf, sizeof(l_ResponseBuf)/sizeof(uint8_t));
                    }
                    /* 内部寄存器数据异常 */
                    else
                    {
                        MOSBUS_USART_ErrorHandle(0x04);
                    }
                }
                /* 寄存器数量异常 */
                else
                {
                    MOSBUS_USART_ErrorHandle(0x03);
                }
            }
            break;

            case 1010:
            {
                l_ResCnt = (uint16_t)MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4] << 8 | MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];
                if (0X14 == l_ResCnt)
                {
                    l_ByteCnt = MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[6];
                    if (0x28 == l_ByteCnt)
                    {
                        /* 存储K值临时变量 */
                        float l_temp_K1 = 0;
                        float l_temp_K2 = 0;
                        float l_temp_K3 = 0;
                        float l_temp_K4 = 0;
                        float l_temp_K5 = 0;
                        float l_temp_K6 = 0;
                        float l_temp_K7 = 0;
                        float l_temp_K8 = 0;
                        float l_temp_K9 = 0;
                        float l_temp_K10 = 0;

                        l_temp_K1  = MODBUS_USART_FloatAss(&MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[7]);
                        l_temp_K2  = MODBUS_USART_FloatAss(&MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[11]);
                        l_temp_K3  = MODBUS_USART_FloatAss(&MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[15]);
                        l_temp_K4  = MODBUS_USART_FloatAss(&MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[19]);
                        l_temp_K5  = MODBUS_USART_FloatAss(&MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[23]);
                        l_temp_K6  = MODBUS_USART_FloatAss(&MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[27]);
                        l_temp_K7  = MODBUS_USART_FloatAss(&MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[31]);
                        l_temp_K8  = MODBUS_USART_FloatAss(&MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[35]);
                        l_temp_K9  = MODBUS_USART_FloatAss(&MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[39]);
                        l_temp_K10 = MODBUS_USART_FloatAss(&MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[43]);

                        /* 更新K1-K10 */
                        K1_Value = l_temp_K1;
                        K2_Value = l_temp_K2;
                        K3_Value = l_temp_K3;
                        K4_Value = l_temp_K4;
                        K5_Value = l_temp_K5;
                        K6_Value = l_temp_K6;
                        K7_Value = l_temp_K7;
                        K8_Value = l_temp_K8;
                        K9_Value = l_temp_K9;
                        K10_Value = l_temp_K10;

                        /* 将新的K1-K10写入FLASH */
                        FLASH_Unlock();                                          // 解锁
                        FLASH_ErasePage(K1_ADDR);                                // 擦除页数据

                        FLASH_ProgramWord(K1_ADDR  , *(uint32_t *)&K1_Value );
                        FLASH_ProgramWord(K2_ADDR  , *(uint32_t *)&K2_Value );
                        FLASH_ProgramWord(K3_ADDR  , *(uint32_t *)&K3_Value );
                        FLASH_ProgramWord(K4_ADDR  , *(uint32_t *)&K4_Value );
                        FLASH_ProgramWord(K5_ADDR  , *(uint32_t *)&K5_Value );
                        FLASH_ProgramWord(K6_ADDR  , *(uint32_t *)&K6_Value );
                        FLASH_ProgramWord(K7_ADDR  , *(uint32_t *)&K7_Value );
                        FLASH_ProgramWord(K8_ADDR  , *(uint32_t *)&K8_Value );
                        FLASH_ProgramWord(K9_ADDR  , *(uint32_t *)&K9_Value );
                        FLASH_ProgramWord(K10_ADDR , *(uint32_t *)&K10_Value);

                        FLASH_Lock();                                            // 上锁

                        /* [2][3]返回时还是寄存器地址，[4][5]返回时依旧是寄存器个数 */
                        l_ResponseBuf[2] = MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[2];
                        l_ResponseBuf[3] = MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[3];
                        l_ResponseBuf[4] = MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[4];
                        l_ResponseBuf[5] = MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[5];

                        l_CRC16CheckNum  = CRC16(l_ResponseBuf, 6);
                        l_ResponseBuf[6] = l_CRC16CheckNum & 0XFF;               // 校验码低8位
                        l_ResponseBuf[7] = l_CRC16CheckNum >> 8;                 // 校验码高8位

                        MODBUS_USART1_SendData(l_ResponseBuf, sizeof(l_ResponseBuf)/sizeof(uint8_t));
                    }
                    /* 内部寄存器数据异常 */
                    else
                    {
                        MOSBUS_USART_ErrorHandle(0x04);
                    }
                }
                /* 寄存器数量异常 */
                else
                {
                    MOSBUS_USART_ErrorHandle(0x03);
                }
            }
            break;

            default:
            break;
        }
    }
    /* 数据长度异常 */
    else
    {
        MOSBUS_USART_ErrorHandle(0X04);
    }
}



/**
 * @brief MOSBUS_USART1通信处理函数
 */
void MODBUS_USART1_COMMUNICATION(void)
{
    /* 局部变量声明 */
    uint16_t l_CRCCheckSum = 0;                                                                                                                                                                                          // CRC校验和

    if (MODBUS_USART1_RECV.MODBUS_USART_COMPLETE_FLAG == 1)
    {
        if (DEVICE_ID == MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[0])                                                                                                                                                     // 设备ID是否正确
        {
            l_CRCCheckSum = ((MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[MODBUS_USART1_RECV.MODBUS_USART_RECV_COUNT - 1] << 8) | (MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[MODBUS_USART1_RECV.MODBUS_USART_RECV_COUNT - 2]));// CRC校验码是否正确
            if (CRC16(MODBUS_USART1_RECV.MODBUS_USART_RECVBUF, MODBUS_USART1_RECV.MODBUS_USART_RECV_COUNT - 2) == l_CRCCheckSum)
            {
                /* 根据功能码选择对应的处理函数 */
                switch (MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[1])
                {
                    case 0x03:
                    {
                        MODBUS_USART_03_Handle();
                    }
                    break;

                    case 0x10:
                    {
                        MODBUS_USART_10_Handle();
                    }
                    break;

                    default:
                    {
                        MOSBUS_USART_ErrorHandle(0x01);                                                                                                                                                                  // 未定义的功能码
                    }
                    break;
                }
            }
        }
        else
        {
            /* 设备ID不同
             * DEBUG_INFO("Error Device_ID");
             */
        }
    }
}

/**
 * @brief  CRC16_Modbus校验码计算
 * @param  nData            数据起始地址
 * @param  wLength          数据长度
 * @return unsigned int     CRC校验和
 */
unsigned int CRC16(unsigned char *nData, unsigned int wLength)
{
    /* 局部变量声明 */
    unsigned char nTemp = 0;
    unsigned int wCRCWord = 0xFFFF;
    static const unsigned int wCRCTable[] =
    {
        0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
        0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
        0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
        0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
        0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,

        0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
        0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
        0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
        0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
        0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
        0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
        0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
        0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,

        0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
        0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
        0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
        0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
        0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
        0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
        0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
        0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,

        0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
        0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
        0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
        0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
        0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
        0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
        0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
        0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,

        0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
        0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
        0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 
    };

    while (wLength--)
    {
        nTemp = *nData++ ^ wCRCWord;
        wCRCWord >>= 8;
        wCRCWord  ^= wCRCTable[nTemp];
    }

    return wCRCWord;
}


/**
* @brief  串口1中断服务函数
* @param  None
* @retval None
*/
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
        // 接收到数据就启动定时器从0计数
        TIM_SetCounter(TIM6, 0);
        TIM_Cmd(TIM6, ENABLE);
        // 如果数组接收数据还没有达到最大
		if(MODBUS_USART1_RECV.MODBUS_USART_RECV_COUNT < MODBUS_USART_RECV_MAX_BUFSIZE)
        {
            MODBUS_USART1_RECV.MODBUS_USART_RECVBUF[MODBUS_USART1_RECV.MODBUS_USART_RECV_COUNT++] = USART_ReceiveData(USART1);
        }

        // 如果接收数据已满，则不保存数据
        else
        {
            USART_ReceiveData(USART1);
        }
	}
}
