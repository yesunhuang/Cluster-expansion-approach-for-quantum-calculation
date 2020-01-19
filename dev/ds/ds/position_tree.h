/**
 * @ 文件名: position_tree.h
 * @ 功能: 声明position tree的功能
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 2020年1月18日
 *
 */
#pragma once
#ifndef _POSITION_TREE_H_
#define _POSITION_TREE_H_

#pragma region 宏定义区

#define MAX_QUEUE_CAPACITY 2048

/**
 * @ 宏定义: InitOPTree(pPTree tree, UINT_L csize)
 *
 * @ 功能: 对应OPTree中相同功能
 */
#define InitPTree(tree, csize) ((InitOPTree((pOPTree)tree, csize)))

 /**
  * @ 宏定义: DeleteOfPTree(pPTree tree, pOPArray arr, int len)
  *
  * @ 功能: 对应OPTree中相同功能
  */
#define DeleteOfPTree(tree, arr, len) (DeleteOfOPTree((pOPTree)tree, arr, len))

/**
 * @ 宏定义: DeleteOfPTree(pPTree tree, pOPArray arr, int len)
 *
 * @ 功能: 对应OPTree中相同功能
 */
#define InsertOfPTree(tree, arr, len) (InsertOfOPTree((pOPTree)tree, arr, len))

/**
 * @ 宏定义: ClearOfPTree(pPTree tree)
 *
 * @ 功能: 对应OPTree中相同功能
 */
#define ClearOfPTree(tree) ((ClearOfOPTree((pOPTree)tree)))

#pragma endregion

#pragma region 头文件区

#include "operator_tree.h"

#pragma endregion

#pragma region 结构体及typedef定义区

/* Position树结点 */
typedef struct _Node PNode, *pPNode;

struct _PTree {
	pPNode root;
	UINT_L childSize;
};
typedef struct _PTree PTree, *pPTree;

#pragma endregion

#pragma region 函数声明区

/** TODO
 * @ 函数: int BuildFromPTree(pPTree posTree, pOPArray arr, int len, pOPTree outputOPTree)
 *
 * @ 功能: 根据PositionTree和一个oprator,生成OPTree
 *
 * @ param{posTree}: position tree
 *
 * @ param{arr}: operator的数组表达
 *
 * @ param{len}: operator的数组表达的长度
 *
 * @ param{outputOPTree}: 输出的新opTree
 *
 * @ 返回值: 成功生成时,返回值为1; 否则,返回值为0.
 */
int BuildFromPTree(pPTree posTree, pOPArray arr, int len, pOPTree* outputOPTree);

/** TODO
 * @ 函数: int _BuildFromPTree(pPNode posNode, UINT_L posCsize, pOPNode opNode, UINT_L opCsize)
 *
 * @ 功能: 根据PositionTree和一个oprator,生成OPTree
 *
 * @ param{posNode}: position tree树结点
 *
 * @ param{posCsize}: position tree的csize
 *
 * @ param{opNode}: operator tree树结点
 *
 * @ param{opCsize}: operator tree的csize
 *
 * @ 返回值: 成功生成时,返回值为1; 否则,返回值为0.
 */
int _BuildFromPTree(pPNode posNode, UINT_L posCsize, pOPNode opNode, UINT_L opCsize);

#pragma endregion
#endif // !_POSITION_TREE_H_
