/**
 * @ 文件名: solver.h
 * @ 功能: 声明有关solver的功能
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 2020年2月1日
 *
 */
#pragma once
#ifndef _SOLVER_H_
#define _SOLVER_H_

#pragma region 头文件区
#include "operator_tree.h"
#pragma endregion

#pragma region 宏定义区

#pragma endregion

#pragma region 结构体及typedef定义区

#pragma endregion

#pragma region 函数声明区

/**
 * @ 函数: int InitialValue(pOPArray arr, int len, int* sArr, int sArrLen, double* output)
 *
 * @ 功能: 对应第四章的InitialValue操作。默认输入为合法。
 *
 * @ 说明: sArr[0]对应{1,2}的初值,sArr[1]对应{3,4}的初值......以此类推.
 *
 * @ param{arr}: 第一棵operator tree
 *
 * @ param{len}: 第二棵tree的某个结点
 *
 * @ param{sArr}: 第二棵tree的csize
 *
 * @ param{sArrLen}: 第二棵tree的遍历栈
 *
 * @ param{output}: 栈顶的第一个空闲空间的索引号
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int InitialValue(pOPArray arr, int len, int* sArr, int sArrLen, double* output);

#pragma endregion
#endif // !_SOLVER_H_
