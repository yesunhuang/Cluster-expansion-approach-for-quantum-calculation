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
#define OFFSETOF(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define MIN(a, b) (((a) < (b))? (a) : (b))
#define MAX(a, b) (((a) > (b))? (a) : (b))
/**
 * @ 宏定义: ROOT_TO_TREE(ROOT, TREE)
 *
 * @ 功能: 根据root的地址,找到树的地址tree
 *
 * @ param{ROOT}: root,类型为pOPNode
 *
 * @ param{TREE}: tree,类型为pOPTree
 */
#define ROOT_TO_TREE(ROOT, TREE) do{ TREE = (OPTree*)((size_t)ROOT - OFFSETOF(OPTree, root));}while(0)

#define UINT_V_ERROR 0xfefefefe
// #define UINT_V_ADD_DELETE_FLAG 0xfefefefc
/* operator的最大长度 */
#define MAX_OPERATOR_LENGTH 256

#pragma endregion

#pragma region 预头文件区

#include <malloc.h>
#include <memory.h>

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
	struct _Node** children;
	struct _Node* parent;
};
typedef struct _Node OPNode, *pOPNode;

/**
 * @ 结构体: operator tree的结构体
 */
struct _OPTree {
	/* root->value表示其所有子结点中,value不为0的结点个数. */
	pOPNode root;
	/* 表示有多少个孩子的可能 */
	UINT_L childSize;
};
typedef struct _OPTree OPTree, *pOPTree;
#pragma endregion

#pragma region 后头文件区

#include "normalizer.h"

#pragma endregion

#pragma region 函数声明区

/**
 * @ 函数: int InitOPNode(struct _Node* node, UINT_L l, INT_V v, int csize, struct _Node* p)
 *
 * @ 功能: 初始化结点.
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
 * @ 函数: int MallocOPNode(UINT_L l, INT_V v, int csize, struct _Node* p, struct _Node** output)
 *
 * @ 功能: 申请一个新结点.
 *
 * @ param{l}: label
 *
 * @ param{v}: value
 *
 * @ param{csize}: 孩子的个数(不包括0位置)
 *
 * @ param{p}: 父节点
 *
 * @ param{output}: 新结点
 *
 * @ 返回值: 若成功,返回值为1; 否则,返回值为0.
 */
int MallocOPNode(UINT_L l, INT_V v, int csize, struct _Node* p, struct _Node** output);

/**
 * @ 函数: int GetRoot(struct _Node* node, struct _Node** output)
 *
 * @ 功能: 寻找某个节点的root结点
 *
 * @ param{node}: 被查找的节点
 *
 * @ param{output}: 结果(可省略)
 *
 * @ 返回值: 若成功,返回值为深度(root的深度在此处定义为0,即此深度即为数组表达的长度); 否则,返回值为0.
 */
int GetRoot(struct _Node* node, struct _Node** output);

/**
 * @ 函数: int ArrayFromNode(pOPNode node, int depth, pOPArray outputArr)
 *
 * @ 功能: 从某个节点生成数组形式的operator.
 *
 * @ param{node}: 被查找的节点
 *
 * @ param{depth}: 节点的深度(见上述的深度定义)
 *
 * @ param{outputArr}: 结果
 *
 * @ 返回值: 若成功,返回值为1; 否则,返回值为0.
 */
int ArrayFromNode(pOPNode node, int depth, pOPArray outputArr);

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
 * @ 函数: int AddOfOPTree_TT(pOPTree tree1, pOPTree tree2)
 *
 * @ 功能: 将tree2中的每个元素插入至tree1中.
 *
 * @ param{tree1}: operator tree 1
 *
 * @ param{tree2}: operator tree 2
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int AddOfOPTree_TT(pOPTree tree1, pOPTree tree2);

/**
 * @ 函数: int SearchOfOPTree(pOpTree tree, pOPArray arr, int len, UINT_V *output)
 *
 * @ 功能: 根据operator,搜索一个结点,并返回该结点的value.
 *
 * @ param{tree}: operator tree
 *
 * @ param{arr}: operator的数组表达
 *
 * @ param{len}: operator的数组表达的长度
 *
 * @ param{output}: 存储结果的变量(地址)
 *
 * @ 返回值: 若有,output值设为其coefficient,返回值为1; 否则,output值设为UINT_V_ERROR,返回值为0.
 */
int SearchOfOPTree(pOPTree tree, pOPArray arr, int len, INT_V *output);

/**
 * @ 函数: int InsertOfOPTree(pOPTree tree, pOPArray arr, int len, int coef)
 *
 * @ 功能: 插入(或更新)tree中对应的operator.
 *
 * @ param{tree}: operator tree
 *
 * @ param{arr}: operator的数组表达
 *
 * @ param{len}: operator的数组表达的长度
 *
 * @ param{coef}: operator的coefficient
 *
 * @ 返回值: 成功插入时,返回值为1; 否则,返回值为0.
 */
int InsertOfOPTree(pOPTree tree, pOPArray arr, int len, int coef);

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
 * @ 函数: int MultiplyOfOPTree_TO(pOPTree tree, pOPNode node)
 *
 * @ 功能: 用tree乘以node,结果保留至tree中,并删除node对应的结点.
 *
 * @ param{tree}: operator tree
 *
 * @ param{node}: operator的结点表达
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int MultiplyOfOPTree_TO(pOPTree tree, pOPNode node);

/**
 * @ 函数: int MultiplyOfOPTree_TT(pOPTree tree1, pOPTree tree2, pOPTree* outputTree)
 *
 * @ 功能: 两树相乘,并放于outputTree中
 *
 * @ param{tree1}: operator tree 1
 *
 * @ param{tree2}: operator tree 2
 *
 * @ param{outputTree}: 结果存放
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int MultiplyOfOPTree_TT(pOPTree tree1, pOPTree tree2, pOPTree outputTree);

/** TODO
 * @ 函数: int ReserveChildSize(pOPTree tree, UINT_L newCsize)
 *
 * @ 功能: 不改变拓扑结构的前提下,调整树的childsize.
 *
 * @ param{tree}: operator tree
 *
 * @ param{newCsize}: 新的childsize
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int ReserveChildSize(pOPTree tree, UINT_L newCsize);

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

/**
 * @ 函数: int _AddOfOPTree_TT(pOPNode node1, pOPNode node2, pOPTree tree2)
 *
 * @ 功能: 将tree2中的每个元素插入至tree1中.
 *
 * @ param{node1}: operator 1
 *
 * @ param{node2}: operator 2
 *
 * @ param{tree1}: 第一棵树
 *
 * @ param{tree2}: 第二棵树
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _AddOfOPTree_TT(pOPNode node1, pOPNode node2, pOPTree tree1, pOPTree tree2);

/**
 * @ 函数: int _AdjustRootValue(pOPTree tree)
 *
 * @ 功能: 更新树中的value
 *
 * @ param{tree}: 需要调整的树
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _AdjustRootValue(pOPTree tree);

/**
 * @ 函数: int _AdjustRootValue_Sum(pOPNode node, int csize, int* psum)
 *
 * @ 功能: 更新树中的value
 *
 * @ param{node}: 结点
 *
 * @ param{csize}: 略
 *
 * @ param{psum}: 用于计数的变量
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _AdjustRootValue_Sum(pOPNode node, int csize, int* psum);

/**
 * @ 函数: int _SearchOfOPTree(pOpTree tree, pOPArray arr, int len, pOPNode* output)
 *
 * @ 功能: 根据operator,搜索一个结点,并返回该结点.
 *
 * @ param{tree}: operator tree
 *
 * @ param{arr}: operator的数组表达
 *
 * @ param{len}: operator的数组表达的长度
 *
 * @ param{output}: 存储结果的变量(地址)
 *
 * @ 返回值: 若有,output值设为该节点,返回值为1; 否则,output值设为NULL,返回值为0.
 */
int _SearchOfOPTree(pOPTree tree, pOPArray arr, int len, pOPNode* output);

/**
 * @ 函数: int _SearchOfOPTree(pOpTree tree, pOPArray arr, int len, pOPNode* output)
 *
 * @ 功能: 判断一个结点是否为叶子节点.
 *
 * @ param{node}: 需要判断的结点
 *
 * @ param{csize}: 除0单元外,子节点的最大可能个数
 *
 * @ 返回值: 若为叶子节点,返回值为1; 否则,返回值为0.
 */
int _IsLeafNode(struct _Node* node, int csize);

/**
 * @ 函数: int _DeleteNode(pOPNode node, pOPTree tree)
 *
 * @ 功能: 删除某个operator
 *
 * @ param{node}: 待删除的operator
 *
 * @ param{tree}: operator tree
 *
 * @ 返回值: 成功删除时,返回值为1; 否则,返回值为0.
 */
int _DeleteNode(pOPNode node, pOPTree tree);

/**
 * @ 函数: void _FreeNode(struct _Node* node, int csize)
 *
 * @ 功能: (递归)释放一个结点及其所有子节点. 注意,此操作并不更新parent和root.
 *
 * @ param{node}: 需要释放的结点
 *
 * @ param{csize}: 除0单元外,子节点的最大可能个数
 *
 * @ 返回值: 无
 */
void _FreeNode(struct _Node* node, int csize);

/**
 * @ 函数: int _MultiplyOfOPTree_TO(pOPTree tree, pOPArray arr, int len, INT_V coef, pOPTree otherTree)
 *
 * @ 功能: 用tree乘以node,结果保留至tree中,并删除node对应的结点.
 *
 * @ param{tree}: 第一棵operator tree
 *
 * @ param{arr}: 乘数operator的数组表达
 *
 * @ param{len}: 乘数operator的数组表达长度
 *
 * @ param{coef}: 乘数operator的系数
 *
 * @ param{otherTree}: 乘数operator所在的树
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _MultiplyOfOPTree_TO(pOPTree tree, pOPArray arr, int len, INT_V coef, pOPTree otherTree);

/**
 * @ 函数: int _MultiplyOfOPTree_TT(pOPTree tree1, pOPNode tree2node, int tree2csize, UINT_L* tree2Stack, int nextIndex, pOPTree outputTree)
 *
 * @ 功能: 两树相乘,并生成一颗新树,放于outputTree中
 *
 * @ param{tree1}: 第一棵operator tree
 *
 * @ param{tree2node}: 第二棵tree的某个结点
 *
 * @ param{tree2csize}: 第二棵tree的csize
 *
 * @ param{tree2Stack}: 第二棵tree的遍历栈
 *
 * @ param{nextIndex}: 栈顶的第一个空闲空间的索引号
 *
 * @ param{outputTree}: 输出的树
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _MultiplyOfOPTree_TT(pOPTree tree1, pOPNode tree2node, int tree2csize,
	UINT_L* tree2Stack, int nextIndex, pOPTree outputTree);

/**
 * @ 函数: int _MultiplyNodeWithOP(pOPNode node, UINT_L csize, pOPArray arr, int len, INT_V coef, UINT_L* lStack, int nextIndex, pOPTree otherTree);
 *
 * @ 功能: 用tree乘以node,结果保留至tree中,并删除node对应的结点.
 *
 * @ param{node}: 某个结点
 *
 * @ param{csize}: 除0单元外,子节点的最大可能个数
 *
 * @ param{arr}: 乘数operator的数组表达
 *
 * @ param{len}: 乘数operator的数组表达长度
 *
 * @ param{coef}: 乘数operator的系数
 *
 * @ param{lStack}: 栈
 *
 * @ param{nextIndex}: 栈顶的第一个空闲空间的索引号
 *
 * @ param{otherTree}: 乘数operator所在的树
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _MultiplyNodeWithOP(pOPNode node, UINT_L csize, pOPArray arr, int len, INT_V coef, 
	UINT_L* lStack, int nextIndex, pOPTree otherTree);

/**
 * @ 函数: int _ReserveChildSize(pOPNode node, UINT_L originCsize, UINT_L newCsize)
 *
 * @ 功能: 不改变拓扑结构的前提下,调整树的childsize.
 *
 * @ param{tree}: operator tree
 *
 * @ param{originCsize}: 原来的childsize
 *
 * @ param{newCsize}: 新的childsize
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _ReserveChildSize(pOPNode node, UINT_L originCsize, UINT_L newCsize);
#pragma endregion

#endif // !_OPERATOR_TREE_H_

