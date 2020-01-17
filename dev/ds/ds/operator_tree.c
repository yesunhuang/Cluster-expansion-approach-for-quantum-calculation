/**
 * @文件名: operator_tree.c
 * @功能: 实现operator tree的功能
 * @作者: AyajiLin & YesunHuang
 * @邮箱: 493987054@qq.com & 944812203@qq.com
 * @github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @日期: 2020年1月18日
 *
 */

#include "operator_tree.h"

int InitOPNode(struct _Node* node, UINT_L l, INT_V v, int csize, struct _Node* p)
{
	node->label = l;
	node->value = v;
	node->parent = p;
	node->children = (struct _Node*)malloc((csize + 1) * sizeof(struct _Node));
	return (node->children == NULL) ? 0 : 1;
}

int InitOPTree(pOPTree tree, UINT_L csize) {
	tree->childSize = csize;
	return 1;
}

int SearchOfOPTree(pOPTree tree, pOPArray arr, int len, INT_V* output) {
	// TODO
	if (tree == NULL)
		return 0;
	pOPNode nowNode = tree;
	for (int i = 0; i < len; i++) {

	}
}
