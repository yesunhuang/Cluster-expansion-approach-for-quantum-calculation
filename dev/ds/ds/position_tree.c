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
	// TODO
	int ret = 1;
	ret &= CreateOPTree(len, outputOPTree);
	ret &= _BuildFromPTree(posTree->root, posTree->childSize, *outputOPTree, len);
	ret &= _NormalizeOPTree(*outputOPTree);

	return ret;
}
