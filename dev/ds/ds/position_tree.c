/**
 * @文件名: position_tree.c
 * @功能: 实现operator tree的功能
 * @作者: AyajiLin & YesunHuang
 * @邮箱: 493987054@qq.com & 944812203@qq.com
 * @github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @日期: 2020年1月19日
 *
 */
#include "position_tree.h"


int BuildFromPTree(pPTree posTree, pOPArray arr, int len, pOPTree* outputOPTree) {
	int ret = 1;
	int opCsize = 0;
	for (int i = 0; i < len; ++i)
		opCsize = MAX(arr[i], opCsize);
	ret &= CreateOPTree(opCsize, outputOPTree);
	ret &= _BuildFromPTree(posTree->root, posTree->childSize, arr, len, (*outputOPTree)->root, opCsize);
	ret &= NormalizeOPTree(*outputOPTree);

	return ret;
}

int _BuildFromPTree(pPNode posNode, UINT_L posCsize, pOPArray arr, int len, pOPNode opNode, UINT_L opCsize) {
	int ret = 1;
	for (int i = 0; i <= posCsize; ++i) {
		if (posNode->children[i] != NULL) {
			/* 不允许位置树指向operator不存在的位置 */
			if (posNode->children[i]->label > len)
				return 0;
			UINT_L nextChild = (posNode->children[i]->label == 0) ? 0 : arr[posNode->children[i]->label - 1];
			/* 判断该子节点是否已经建立 */
			if (opNode->children[nextChild] == NULL)
				MallocOPNode(nextChild, 0, opCsize, opNode, &opNode->children[nextChild]);

			opNode->children[nextChild]->value += posNode->value;
			ret &= _BuildFromPTree(posNode->children[i], posCsize, arr, len, opNode->children[nextChild], opCsize);
		}
	}

	return ret;
}
