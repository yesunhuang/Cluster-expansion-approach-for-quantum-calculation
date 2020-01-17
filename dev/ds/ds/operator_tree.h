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
#ifndef _OPERATOR_TREE_H_
#define _OPERATOR_TREE_H_

#pragma region 宏定义区

#define NULL 0

#define UINT_V_ERROR 0xfefefefe

#pragma endregion

#pragma region 头文件区

#include <stdio.h>

#pragma endregion

#pragma region 结构体及typedef定义区
/* _Node.label的数据类型 */
typedef unsigned char UINT_L;
/* _Node.value的数据类型 */
typedef int INT_V;
/* operator的数组表示 */
typedef UINT_L* pOPArray;

/**
 * @ 结构体: 通用的trie树结点的结构体
 */
struct _Node {
	UINT_L label;
	INT_V value;
	struct _Node* children;
	struct _Node* parent;
};
typedef struct _Node OPNode, *pOPNode;

/**
 * @ 结构体: operator tree的结构体
 */
struct _OPTree {
	/* root->value表示其所有子结点中,value不为0的结点个数. */
	OPNode* root;
	/* 表示有多少个孩子的可能 */
	UINT_L childSize;
};
typedef struct _OPTree OPTree, *pOPTree;
#pragma endregion

#pragma region 函数声明区

/**
 * @ 函数: int InitOPNode(struct _Node* node, UINT_L l, INT_V v, int csize, struct _Node* p)
 *
 * @ param{node}: 将初始化的结点
 *
 * @ param{l}: label
 *
 * @ param{v}: value
 *
 * @ param{csize}: 孩子的个数(不包括0位置)
 *
 * @ param{p}: 父节点
 *
 * @ 返回值: 若初始化成功,返回值为1; 否则,返回值为0.
 */
int InitOPNode(struct _Node* node, UINT_L l, INT_V v, int csize, struct _Node* p);

/**
 * @ 函数: int InitOPTree(pOPTree tree, UINT_L csize)
 *
 * @ param{tree}: operator tree
 *
 * @ param{csize}: 表示有多少个孩子的可能
 *
 * @ 返回值: 若初始化成功,返回值为1; 否则,返回值为0.
 */
int InitOPTree(pOPTree tree, UINT_L csize);

/**
 * @ 函数: void SearchOfOPTree(pOpTree tree, pOPArray arr, int len, UINT_V *output)
 *
 * @ param{tree}: operator tree
 *
 * @ param{arr}: operator的数组表达
 *
 * @ param{len}: operator的数组表达的长度
 *
 * @ param{output}: 存储结果的变量(地址)
 *
 * @ 返回值: 若有,output值设为其coefficient,返回值为1; 否则,返回值为0.
 */
int SearchOfOPTree(pOPTree tree, pOPArray arr, int len, INT_V *output);

/**
 * @ 函数: int DeleteOfOPTree(pOPTree tree, pOPArray arr, int len)
 *
 * @ 功能: 删除tree中对应的operator. 
 *
 * @ param{tree}: operator tree
 *
 * @ param{arr}: operator的数组表达
 *
 * @ param{len}: operator的数组表达的长度
 *
 * @ 返回值: 成功删除时,返回值为1; 否则,返回值为0.
 */
int DeleteOfOPTree(pOPTree tree, pOPArray arr, int len);

/**
 * @ 函数: int InsertOfOPTree(pOPTree tree, pOPArray arr, int len)
 *
 * @ 功能: 删除tree中对应的operator.
 *
 * @ param{tree}: operator tree
 *
 * @ param{arr}: operator的数组表达
 *
 * @ param{len}: operator的数组表达的长度
 *
 * @ 返回值: 成功插入时,返回值为1; 否则,返回值为0.
 */
int InsertOfOPTree(pOPTree tree, pOPArray arr, int len);

/**
 * @ 函数: int MultiplyOfOPTree(pOPTree tree, pOPNode node)
 *
 * @ 功能: 用tree乘以node,结果保留至tree中,并删除node对应的结点.
 *
 * @ param{tree}: operator tree
 *
 * @ param{node}: operator的结点表达
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int MultiplyOfOPTree(pOPTree tree, pOPNode node);

/**
 * @ 函数: int ClearOfOPTree(pOPTree tree)
 *
 * @ 功能: 清除并释放tree中所有已存的结点.
 *
 * @ param{tree}: operator tree
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int ClearOfOPTree(pOPTree tree);
#pragma endregion

#endif // !_OPERATOR_TREE_H_

