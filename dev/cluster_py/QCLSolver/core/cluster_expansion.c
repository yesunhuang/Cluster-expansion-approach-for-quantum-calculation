/**
 * @ 文件名: cluster_expansion.c
 * @ 功能: 定义与CE有关的函数
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 2020年1月30日
 *
 */

#include "cluster_expansion.h"

int DeltaTree(int N, pOPTree* outTree) {
	/* 加入静态数据 */
	if (N <= 0) {
		return 0;
	}
	if (N <= STANAMIC_DTREE_SIZE) {
		/* 从动态表中获取 */
		if (g_StanamicDTrees[N] != NULL) {
			return CopyCreateOPTree(g_StanamicDTrees[N], outTree);
		}
	}
	if (N <= STATIC_DTREE_SIZE) {
		// 从静态表中构造
		int ret = 1;
		ret &= CreateStaticDTree(N, outTree);
		ret &= FreeOPTree(g_StanamicDTrees[N]);
		ret &= CopyCreateOPTree(*outTree, &g_StanamicDTrees[N]);
		return ret;
	}
	int n = N - 1;
	/* 创建结果的树 */
	CreateOPTree(N, outTree);
	UINT_L buf[MAX_UINTL_BUFFER_SIZE];
	for (int i = 0; i <= n - 1; ++i) {
		_DT(i, N, 0, 0, buf, *outTree);
	}
	UINT_L temparr[MAX_UINTL_BUFFER_SIZE];
	for (int i = 0; i < N; ++i) {
		temparr[i] = i + 1;
	}
	INT_V tempv = { 1, 0 };
	InsertOfOPTree(*outTree, temparr, N, tempv);

	int ret = 1;
	if (N <= STANAMIC_DTREE_SIZE) {
		ret &= FreeOPTree(g_StanamicDTrees[N]);
		ret &= CopyCreateOPTree(*outTree, &g_StanamicDTrees[N]);
	}
	return ret;
}

int ClusterExpansion(pOPArray arr, int len, pOPTree* outTree) {
	pOPTree dtree = NULL;
	DeltaTree(len, &dtree);
	BuildFromPTree(dtree, arr, len, outTree);
	DTToBT(*outTree);
	BTToCEBT(*outTree);
	FreeOPTree(dtree);
	return 1;
}

int DTToBT(pOPTree tree) {
	for (int i = 0; i <= tree->childSize; ++i) {
		if (tree->root->children[i] != NULL)
			_DTToBT(tree->root->children[i], tree, 0);
	}
	return 1;
}

int BTToCEBT(pOPTree tree) {
	for (int i = 0; i <= tree->childSize; ++i) {
		if (tree->root->children[i] != NULL)
			_BTToCEBT(tree->root->children[i], tree);
	}
	return 1;
}

int _DT(int nowi, int N, int prevIndex, int alCount, UINT_L* buf, pOPTree outTree) {
	if (alCount == nowi) {
		UINT_L buf1[MAX_UINTL_BUFFER_SIZE];
		UINT_L buf2[MAX_UINTL_BUFFER_SIZE];
		memset(buf2, 0, MAX_UINTL_BUFFER_SIZE * sizeof(UINT_L));

		/* 构建{i}和<N-i> */
		for (int i = 0; i < nowi; ++i) {
			buf2[buf[i]] = 1;
		}
		int index = 0;
		for (int i = 1; i <= N - 1; ++i) {
			if (buf2[i] == 1) {
				buf1[index] = i;
				++index;
			}
		}
		index = 0;
		for (int i = 1; i <= N - 1; ++i) {
			if (buf2[i] == 0) {
				buf2[index] = i;
				++index;
			}
		}
		buf1[nowi] = N;

		INT_V tempv = { -1, 0 };
		InsertOfOPTree(outTree, buf2, N - nowi - 1, tempv);
		pOPNode tempNode = NULL;
		_SearchOfOPTree(outTree, buf2, N - nowi - 1, &tempNode);
		pOPTree newDeltaTree;
		DeltaTree(nowi + 1, &newDeltaTree);
		pOPTree newOPTree;
		BuildFromPTree(newDeltaTree, buf1, nowi + 1, &newOPTree);
		MultiplyOfOPTree_TO(newOPTree, tempNode, outTree);
		FreeOPTree(newDeltaTree);
		FreeOPTree(newOPTree);

		return 1;
	}
	else {
		for (int i = prevIndex + 1; i <= N - nowi + alCount; ++i) {
			buf[alCount] = i;
			_DT(nowi, N, i, alCount + 1, buf, outTree);
		}
		return 1;
	}
	return 1;
}

int _DTToBT(pOPNode node, pOPTree tree, int flag) {
	flag = (node->label == 0) ? 1 : flag;
	if (flag == 1)
		NegateOfComplex(node->value, &node->value);

	for (int i = 0; i <= tree->childSize; ++i) {
		if (node->children[i] != NULL)
			_DTToBT(node->children[i], tree, flag);
	}
	return 1;
}

int _BTToCEBT(pOPNode node, pOPTree tree) {
	if (_IsLeafNode(node, tree->childSize)) {
		_DeleteNode(node, tree);
		return 1;
	}
	int ret = 0;
	for (int i = 1; i <= tree->childSize; ++i) {
		if (node->children[i] != NULL) {
			ret |= _BTToCEBT(node->children[i], tree);
		}
		if (ret == 1)
			return 1;
	}
	return 1;
}
