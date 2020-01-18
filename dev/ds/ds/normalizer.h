/**
 * @ 文件名: operator_tree.h
 * @ 功能: 声明operator tree的功能
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 2020年1月18日
 *
 */
#pragma once
#ifndef _NORMALIZER_H_
#define _NORMALIZER_H_

#pragma region 预头文件区
#include "operator_tree.h"
#pragma endregion

#pragma region 函数声明区

/**
 * @ 函数: int Normalize(pOPArray arr, int len, pOPTree outTree)
 *
 * @ 功能: 正交化并存入树中
 *
 * @ param{arr}: operator的数组表达
 *
 * @ param{len}: operator的数组表达的长度
 *
 * @ param{outTree}: 存储的树
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int Normalize(pOPArray arr, int len, pOPTree outTree);

/**
 * @ 函数: int Normalize(pOPArray arr, int len, pOPTree outTree)
 *
 * @ 功能: 让两个operator相乘
 *
 * @ param{arr1}: operator的数组表达
 *
 * @ param{len1}: operator的数组表达的长度
 *
 * @ param{arr2}: operator的数组表达
 *
 * @ param{len2}: operator的数组表达的长度
 *
 * @ param{output}: 结果
 *
 * @ param{outLen}: 结果的长度(可省略)
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int MultiplyOfOPArray(pOPArray arr1, int len1, pOPArray arr2, int len2, pOPArray* output, int* outLen);
#pragma endregion
#endif // !_NORMALIZER_H_
