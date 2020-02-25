/**
 * @ 文件名: normalizer.h
 * @ 功能: 声明有关正交化的功能
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 2020年1月18日
 *
 */
#pragma once
#ifndef _NORMALIZER_H_
#define _NORMALIZER_H_

#pragma region 头文件区
#include "operator_tree.h"
#pragma endregion

#pragma region 宏定义区

// #define MAX_UINTL_BUF_SIZE 128

#pragma endregion

#pragma region 结构体及typedef定义区

#pragma endregion

#pragma region 函数声明区

/** tested?
 * @ 函数: int SONormalize(pOPArray arr, int len, pOPTree* outTree)
 *
 * @ 功能: 正交化并存入一棵新树中
 *
 * @ param{arr}: operator的数组表达
 *
 * @ param{len}: operator的数组表达的长度
 *
 * @ param{outTree}: 存储的树
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int SONormalize(pOPArray arr, int len, int csize, pOPTree* outTree);

/** tested
 * @ 函数: int MONormalize(pOPArray arr, int len, pOPTree* outTree)
 *
 * @ 功能: 多元符号正交化并存入一棵新树中
 *
 * @ param{arr}: operator的数组表达
 *
 * @ param{len}: operator的数组表达的长度
 *
 * @ param{outTree}: 存储的树
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int MONormalize(pOPArray arr, int len, pOPTree* outTree);

/** tested
 * @ 函数: int MultiplyOfOPArray(pOPArray arr1, int len1, pOPArray arr2, int len2, pOPArray output, int* outLen)
 *
 * @ 功能: 让两个operator相乘,生成新的结果
 *
 * @ param{arr1}: operator的数组表达
 *
 * @ param{len1}: operator的数组表达的长度
 *
 * @ param{arr2}: operator的数组表达
 *
 * @ param{len2}: operator的数组表达的长度
 *
 * @ param{output}: 输出结果(需保证空间足够)
 *
 * @ param{outLen}: 输出结果的长度(可省略为NULL)
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int MultiplyOfOPArray(pOPArray arr1, int len1, pOPArray arr2, int len2, pOPArray output, int* outLen);

/** tested
 * @ 函数: int MultiplyConnectOfOPArray(pOPArray arr1, int len1, pOPArray arr2, int len2, pOPArray output, int* outLen)
 *
 * @ 功能: 让两个operator相乘,生成新的结果
 *
 * @ param{arr1}: operator的数组表达
 *
 * @ param{len1}: operator的数组表达的长度
 *
 * @ param{arr2}: operator的数组表达
 *
 * @ param{len2}: operator的数组表达的长度
 *
 * @ param{output}: 输出结果(需保证空间足够)
 *
 * @ param{outLen}: 输出结果的长度(可省略为NULL)
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int MultiplyConnectOfOPArray(pOPArray arr1, int len1, pOPArray arr2, int len2, pOPArray output, int* outLen);

/** tested
 * @ 函数: void _CompareOPArrayBuffer(pOPArray arr1, int len1, pOPArray arr2, int len2, int* result)
 *
 * @ 功能: 比较两个buffer中OPArray的大小
 *
 * @ param{arr1}: operator的数组表达
 *
 * @ param{len1}: operator的数组表达的长度
 *
 * @ param{arr2}: operator的数组表达
 *
 * @ param{len2}: operator的数组表达的长度
  *
 * @ param{rusult}: 结果为1时,arr1 > arr2; 结果为0时,arr1 == arr2; 结果为-1时,arr1 < arr2.
 *
 * @ 返回值: 无
 */
void _CompareOPArrayBuffer(pOPArray arr1, int len1, pOPArray arr2, int len2, int* result);

/** tested
 * @ 函数: int _GetNextCPIndexFromOPArray(pOPArray arr, int len, int now, int* next)
 *
 * @ 功能: 获得下一跳的索引位置
 *
 * @ param{arr}: operator的数组表达
 *
 * @ param{len}: operator的数组表达的长度
 *
 * @ param{now}: 起始点
 *
 * @ param{next}: 更新下一个起始点
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _GetNextCPIndexFromOPArray(pOPArray arr, int len, int now, int* next);

/** tested
 * @ 函数: int _SortMOArray(pOPArray arr, int len)
 *
 * @ 功能: multimode排序
 *
 * @ param{arr}: operator的数组表达
 *
 * @ param{len}: operator的数组表达的长度
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _SortMOArray(pOPArray arr, int len);
#pragma endregion
#endif // !_NORMALIZER_H_
