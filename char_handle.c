/**
 * @file      : char_handle.c
 * @brief     : 字符处理函数接口源文件
 * @author    : huenrong (huenrong1028@outlook.com)
 * @date      : 2023-01-18 11:16:56
 *
 * @copyright : Copyright (c) 2023 huenrong
 *
 * @history   : date       author          description
 *              2023-04-07 huenrong        修改字节数组转字符串接口
 *              2023-01-16 huenrong        创建文件
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "./char_handle.h"

/**
 * @brief  字符转换为数字('0'~'9', 'a'~'f', 'A'~'F'转换为0~15)
 * @param  ch: 输入参数, 待转换的字符
 * @return 成功: 转换后的数字
 *         失败: 0xFF
 */
uint8_t char_to_num(const char ch)
{
    uint8_t hex = 0;

    // 字符'0'~'9'
    if (('0' <= ch) && (ch <= '9'))
    {
        hex = (ch - '0');
    }
    // 字符'a'~'f'
    else if (('a' <= ch) && (ch <= 'f'))
    {
        hex = (ch - ('a' - 10));
    }
    // 字符'A'~'F'
    else if (('A' <= ch) && (ch <= 'F'))
    {
        hex = (ch - ('A' - 10));
    }
    else
    {
        hex = 0xFF;
    }

    return hex;
}

/**
 * @brief  数字转换为字符(0~15转换为'0'~'9', 'A'~'F')
 * @param  num: 输入参数, 待转换的数字
 * @return 成功: 转换后的字符
 *         失败: 'Z'
 */
char num_to_char(const uint8_t num)
{
    char ch = 0;

    // 将 0~9 转换成字符
    if (num <= 9)
    {
        ch = (char)('0' + num - 0);
    }
    // 将 10~15 转换成字符
    else if ((10 <= num) && (num <= 15))
    {
        ch = (char)('A' + num - 10);
    }
    else
    {
        ch = 'Z';
    }

    return ch;
}

/**
 * @brief  16位数据大小端交换
 * @param  src_data: 输入参数, 源数据
 * @return 交换后的数据
 */
uint16_t byte_swap_16(const uint16_t src_data)
{
    return (((src_data & 0xFF00) >> 8) |
            ((src_data & 0x00FF) << 8));
}

/**
 * @brief  32位数据大小端交换
 * @param  src_data: 输入参数, 源数据
 * @return 交换后的数据
 */
uint32_t byte_swap_32(const uint32_t src_data)
{
    return (((src_data & 0xFF000000) >> 24) |
            ((src_data & 0x00FF0000) >> 8) |
            ((src_data & 0x0000FF00) << 8) |
            ((src_data & 0x000000FF) << 24));
}

/**
 * @brief  BCD码转10进制
 * @param  bcd_data: 输入参数, 待转换的BCD数
 * @return 转换后的10进制数
 */
uint8_t bcd_to_dec(const uint8_t bcd_data)
{
    return ((((bcd_data & 0xF0) >> 4) * 10) +
            (bcd_data & 0x0F));
}

/**
 * @brief  10进制转BCD码
 * @param  dec_data: 输入参数, 待转换的10进制数
 * @return 转换后的BCD码
 */
uint8_t dec_to_bcd(const uint8_t dec_data)
{
    return (((dec_data / 10) << 4) |
            (dec_data % 10));
}

/**
 * @brief  字符数组转整型
 * @param  dst_data    : 输出参数, 转换后的目标数据
 * @param  src_data    : 输入参数, 待转换的源数据
 * @param  src_data_len: 输入参数, 源数据长度
 * @return true : 成功
 * @return false: 失败
 */
bool char_array_to_u32(uint32_t *dst_data, const char *src_data, const uint8_t src_data_len)
{
    uint8_t len = 0;

    if ((!dst_data) || (!src_data) || (!src_data_len))
    {
        return false;
    }

    len = ((src_data_len > 8) ? 8 : src_data_len);

    for (uint8_t i = 0; i < len; i++)
    {
        *dst_data <<= 4;
        *dst_data |= char_to_num(toupper(src_data[i]));
    }

    return true;
}

/**
 * @brief  获取字节数组转字符串转换后的字符串长度(方便外部使用malloc动态申请内存)
 * @param  byte_array_len: 输入参数, 待转换的字节数组长度
 * @return 转换后的字符串长度
 */
uint32_t get_byte_array_to_str_len(const uint32_t byte_array_len)
{
    return ((!byte_array_len) ? 0 : (byte_array_len * 3 + 1));
}

/**
 * @brief  字节数组转字符串
 * @param  str           : 输出参数, 转换后的字符串
 * @param  byte_array    : 输入参数, 待转换的字节数组
 * @param  byte_array_len: 输入参数, 待转换的字节数组长度
 * @return true : 成功
 * @return false: 失败
 */
bool byte_array_to_str(char *str, const uint8_t *byte_array, const uint32_t byte_array_len)
{
    if ((!str) || (!byte_array) || (!byte_array_len))
    {
        return false;
    }

    uint32_t i = 0;
    for (i = 0; i < byte_array_len; i++)
    {
        snprintf(str + i * 3, 4, "%02X ", byte_array[i]);
    }
    *(str + i * 3) = '\0';

    return true;
}

/**
 * @brief  字符串转字节数组
 * @param  byte_array: 输出参数, 转换后的字节数组
 * @param  str       : 输入参数, 待转换的字符串
 * @param  str_len   : 输入参数, 待转换的字符串长度
 * @return 成功: 转换后的字节数组长度
 *         失败: 0
 */
uint32_t str_to_byte_array(uint8_t *byte_array, const char *str, const uint32_t str_len)
{
    uint8_t byte_high = 0;
    uint8_t byte_low = 0;
    uint32_t len = 0;

    if ((!byte_array) || (!str) || (!str_len))
    {
        return 0;
    }

    for (uint32_t i = 0; i < str_len;)
    {
        // 跳过空格和结束符
        if ((' ' == str[i]) || (0x00 == str[i]))
        {
            i++;

            continue;
        }

        // 高半字节
        byte_high = toupper(str[i]);
        if (byte_high > 0x39)
        {
            byte_high -= 0x37;
        }
        else
        {
            byte_high -= 0x30;
        }

        // 低半字节
        byte_low = toupper(str[i + 1]);
        if (byte_low > 0x39)
        {
            byte_low -= 0x37;
        }
        else
        {
            byte_low -= 0x30;
        }

        byte_array[len] = ((byte_high << 4) | byte_low);
        len++;

        i += 2;
    }

    return len;
}
