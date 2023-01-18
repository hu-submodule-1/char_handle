/**
 * @file      : char_handle.h
 * @brief     : 字符处理函数接口头文件
 * @author    : huenrong (huenrong1028@outlook.com)
 * @date      : 2023-01-18 11:17:07
 *
 * @copyright : Copyright (c) 2023 huenrong
 *
 * @history   : date       author          description
 *              2023-01-16 huenrong        创建文件
 *
 */

#ifndef __CHAR_HANDLE_H
#define __CHAR_HANDLE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief  字符转换为数字('0'~'9', 'a'~'f', 'A'~'F'转换为0~15)
 * @param  ch: 输入参数, 待转换的字符
 * @return 成功: 转换后的数字
 *         失败: 0xFF
 */
uint8_t char_to_num(const char ch);

/**
 * @brief  数字转换为字符(0~15转换为'0'~'9', 'A'~'F')
 * @param  num: 输入参数, 待转换的数字
 * @return 成功: 转换后的字符
 *         失败: 'Z'
 */
char num_to_char(const uint8_t num);

/**
 * @brief  16位数据大小端交换
 * @param  src_data: 输入参数, 源数据
 * @return 交换后的数据
 */
uint16_t byte_swap_16(const uint16_t src_data);

/**
 * @brief  32位数据大小端交换
 * @param  src_data: 输入参数, 源数据
 * @return 交换后的数据
 */
uint32_t byte_swap_32(const uint32_t src_data);

/**
 * @brief  BCD码转10进制
 * @param  bcd_data: 输入参数, 待转换的BCD数
 * @return 转换后的10进制数
 */
uint8_t bcd_to_dec(const uint8_t bcd_data);

/**
 * @brief  10进制转BCD码
 * @param  dec_data: 输入参数, 待转换的10进制数
 * @return 转换后的BCD码
 */
uint8_t dec_to_bcd(const uint8_t dec_data);

/**
 * @brief  字符数组转整型
 * @param  dst_data    : 输出参数, 转换后的目标数据
 * @param  src_data    : 输入参数, 待转换的源数据
 * @param  src_data_len: 输入参数, 源数据长度
 * @return true : 成功
 * @return false: 失败
 */
bool char_array_to_u32(uint32_t *dst_data, const char *src_data, const uint8_t src_data_len);

/**
 * @brief  获取字节数组转字符串转换后的字符串长度(方便外部使用malloc动态申请内存)
 * @param  byte_array_len: 输入参数, 待转换的字节数组长度
 * @return 转换后的字符串长度
 */
uint32_t get_byte_array_to_str_len(const uint32_t byte_array_len);

/**
 * @brief  字节数组转字符串
 * @param  str           : 输出参数, 转换后的字符串
 * @param  byte_array    : 输入参数, 待转换的字节数组
 * @param  byte_array_len: 输入参数, 待转换的字节数组长度
 * @return true : 成功
 * @return false: 失败
 */
bool byte_array_to_str(char *str, const uint8_t *byte_array, const uint32_t byte_array_len);

/**
 * @brief  字符串转字节数组
 * @param  byte_array: 输出参数, 转换后的字节数组
 * @param  str       : 输入参数, 待转换的字符串
 * @param  str_len   : 输入参数, 待转换的字符串长度
 * @return 转换后的字节数组长度
 */
uint32_t str_to_byte_array(uint8_t *byte_array, const char *str, const uint32_t str_len);

#ifdef __cplusplus
}
#endif

#endif // __CHAR_HANDLE_H
