/**
 * @ 文件名: cluster_expansion.h
 * @ 功能: 声明与CE有关的函数
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 2020年1月30日
 *
 */
#pragma once

#ifndef _CLUSTER_EXPANSION_H_
#define _CLUSTER_EXPANSION_H_

#pragma region 头文件区
#include "operator_tree.h"
#include "position_tree.h"
#pragma endregion

#pragma region 宏定义区

#define MAX_UINTL_BUFFER_SIZE 128

#pragma endregion

#pragma region 结构体及typedef定义区

#pragma endregion

#pragma region 函数声明区

/**
 * @ 函数: int DeltaTree(int N, pOPTree* outTree)
 *
 * @ 功能: 返回Deltatree<N>
 *
 * @ param{len}: operator的数组表达的长度
 *
 * @ param{outTree}: 存储的树
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int DeltaTree(int N, pOPTree* outTree);

/**
 * @ 函数: int ClusterExpansion(pOPArray arr, int len, pOPTree* outTree)
 *
 * @ 功能: 进行CE
 *
 * @ param{arr}: operator的数组表达
 *
 * @ param{len}: operator的数组表达的长度
 *
 * @ param{outTree}: 存储的树
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int ClusterExpansion(pOPArray arr, int len, pOPTree* outTree);

/**
 * @ 函数: int DTToBT(pOPTree tree)
 *
 * @ 功能: 将delta树转为B树
 *
 * @ param{tree}: delta tree
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int DTToCEBT(pOPTree tree);

/**
 * @ 函数: int _DT(int i, int N, int nextIndex, UINT_L* buf, pOPTree outTree)
 *
 * @ 功能: 对应论文中的step1,2,3
 *
 * @ param{i}: i
 *
 * @ param{N}: N
 *
 * @ param{prevIndex}: 下一个用于buf中的索引号
 *
 * @ param{alCount}: 已经用过的数目
 *
 * @ param{buf}: 缓存区
 *
 * @ param{outTree}: 结果
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _DT(int i, int N, int prevIndex, int alCount, UINT_L* buf, pOPTree outTree);

/**
 * @ 函数: int _DTToCEBT(pOPNode node, pOPTree tree, int flag)
 *
 * @ 功能: 将delta树转为B树
 *
 * @ param{node}: 节点
 *
 * @ param{tree}: 树
 *
 * @ param{flag}: 标记这个结点之前,有没有经过0结点
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _DTToCEBT(pOPNode node, pOPTree tree, int flag);

#pragma endregion

#endif // !_CLUSTER_EXPANSION_H_
