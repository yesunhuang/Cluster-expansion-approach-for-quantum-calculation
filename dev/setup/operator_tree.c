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
#include "normalizer.h"

int InitOPNode(struct _Node* node, UINT_L l, INT_V v, int csize, struct _Node* p)
{
	node->label = l;
	node->value = v;
	node->parent = p;
	node->children = (struct _Node**)malloc((csize + 1) * sizeof(struct _Node*));
	if (node->children == NULL) return 0;
	memset(node->children, 0, (csize + 1) * sizeof(struct _Node*));
	return 1;
}

int MallocOPNode(UINT_L l, INT_V v, int csize, struct _Node* p, struct _Node** output)
{
	*output = (struct _Node*)malloc(sizeof(struct _Node));
	return (*output == NULL) ? 0 : InitOPNode(*output, l, v, csize, p);
}

int GetRoot(struct _Node* node,struct _Node** output) {
	int cnt = 0;
	struct _Node* nowNode = node;
	while (nowNode->parent != NULL) {
		++cnt;
		nowNode = nowNode->parent;
	}
	if (output != NULL) *output = nowNode;
	return cnt;
}

int ArrayFromNode(pOPNode node, int depth, pOPArray outputArr) {
	/* 默认outputArr空间足够 */
	pOPNode nowNode = node;
	for (int i = depth - 1; i >= 0; --i) {
		outputArr[i] = nowNode->label;
		nowNode = nowNode->parent;
	}
	return 1;
}

int CreateOPTree(UINT_L csize, pOPTree* outputTree) {
	(*outputTree) = (pOPTree)malloc(sizeof(OPTree));
	return _InitOPTree(*outputTree, csize);
}

int CopyCreateOPTree(pOPTree origin, pOPTree* outputTree) {
	if (origin == NULL || outputTree == NULL) return 0;
	CreateOPTree(origin->childSize, outputTree);
	_CopyOPTree(origin->root, (*outputTree)->root, origin->childSize);
	return 1;
}

int _InitOPTree(pOPTree tree, UINT_L csize) {
	tree->childSize = csize;
	INT_V v = { 0,0 };
	return MallocOPNode(0, v, csize, NULL, &tree->root);
}

int AddOfOPTree_TT(pOPTree tree1, pOPTree tree2)
{
	if (tree1 == NULL || tree2 == NULL)
		return 0;
	/* 调整tree1的大小 */
	if (tree2->childSize > tree1->childSize)
		ReserveChildSize(tree1, tree2->childSize);

	_AddOfOPTree_TT(tree1->root, tree2->root, tree1, tree2);
	_AdjustRootValue(tree1);
	return 1;
}

int SearchOfOPTree(pOPTree tree, pOPArray arr, int len, INT_V* output) {
	if (tree == NULL || len <= 0)
		return 0;
	pOPNode nowNode = tree->root;
	_SearchOfOPTree(tree, arr, len, &nowNode);
	if (nowNode == NULL) {
		// 不存在此节点的情况

		return 0;
	}

	/* 成功查询 */
	if (output != NULL) *output = nowNode->value;
	return 1;
}

int InsertOfOPTree(pOPTree tree, pOPArray arr, int len, INT_V coef) {
	if (tree == NULL || len <= 0)
		return 0;
	else if (IsZeroOfComplex(coef))
		return 0;

	/* 判断是否增大容量 */
	UINT_L maxLabel = 0;
	for (int i = 0; i < len; ++i)
		maxLabel = MAX(maxLabel, arr[i]);
	if (maxLabel > tree->childSize)
		ReserveChildSize(tree, maxLabel);

	if (arr[0] == 0) {
		/* 0次项插入 */
		if (tree->root->children[0] == NULL) {
			if (IsZeroOfComplex(coef)) return 0;
			INT_V tempv = { 0,0 };
			MallocOPNode(0, tempv, tree->childSize, tree->root, &tree->root->children[0]);
		}

		/* 判断是否更新root的value */
		if (tree->root->children[0]->value.real == 0) {
			++tree->root->value.real;
		}
		AddOfComplex(coef, tree->root->children[0]->value, &tree->root->children[0]->value);
		/* 删除0结点 */
		if (IsZeroOfComplex(tree->root->children[0]->value)) {
			_DeleteNode(tree->root->children[0], tree);
		}

		return 1;
	}
	pOPNode nowNode = tree->root;
	for (int i = 0; i < len; ++i) {
		if (nowNode->children[arr[i]] == NULL) {
			if (IsZeroOfComplex(coef)) return 0;
			INT_V tempv = { 0,0 };
			MallocOPNode(arr[i], tempv, tree->childSize, nowNode, &nowNode->children[arr[i]]);
		}
		nowNode = nowNode->children[arr[i]];
	}

	/* 判断是否更新root的value */
	if (IsZeroOfComplex(nowNode->value)) {
		++tree->root->value.real;
	}
	AddOfComplex(coef, nowNode->value, &nowNode->value);
	if (IsZeroOfComplex(nowNode->value))
		_DeleteNode(nowNode, tree);
	
	return 1;
}

int DeleteOfOPTree(pOPTree tree, pOPArray arr, int len) {
	if (tree == NULL || len <= 0)
		return 0;
	pOPNode nowNode = tree->root;
	_SearchOfOPTree(tree, arr, len, &nowNode);
	return _DeleteNode(nowNode, tree);
}

int EachNodeOfOPTree(pOPTree tree, void* sth, int(*func)(pOPNode, void*)) {
	if (tree == NULL || func == NULL)
		return 0;
	int ret = 1;
	for (int i = 0; i <= tree->childSize; ++i) {
		if (tree->root->children[i] != NULL)
			ret &= _EachNodeOfOPTree(tree->root->children[i], tree->childSize, sth, func);
	}

	return ret;
}

int ExchangeOfOPTree(pOPTree tree1, pOPTree tree2) {
	SWAP(tree1->childSize, tree2->childSize, UINT_L);
	SWAP(tree1->root, tree2->root, pOPNode);
	return 1;
}

int MultiplyOfOPTree_TO(pOPTree tree, pOPNode otherNode, pOPTree otherTree) {
	/* 获得另一个树的根节点和树指针 */
	pOPNode otherRoot;
	int depth = GetRoot(otherNode, &otherRoot);
	/* 获得另一个结点的数组表达 */
	pOPArray otherArray = (pOPArray)malloc(depth * sizeof(UINT_L));
	ArrayFromNode(otherNode, depth, otherArray);
	/* 另一个树中删除该结点 */
	INT_V coef = otherNode->value;
	DeleteOfOPTree(otherTree, otherArray, depth);

	return _MultiplyOfOPTree_TO(tree, otherArray, depth, coef, otherTree);
}

int MultiplyOfOPTree_TT(pOPTree tree1, pOPTree tree2, pOPTree* outputTree) {
	/* 定义一个简易的栈 */
	UINT_L tree2Stack[MAX_OPERATOR_LENGTH];
	CreateOPTree(MAX(tree1->childSize, tree2->childSize), outputTree);
	if (*outputTree == NULL) return 0;
	int ret = 1;
	for (int i = 0; i <= tree2->childSize; ++i) {
		if (tree2->root->children[i] != NULL) {
			ret &= _MultiplyOfOPTree_TT(tree1, tree2->root->children[i], tree2->childSize, tree2Stack, 0, *outputTree);
		}
	}
	return ret;
}

int NormalizeOPTree(pOPTree tree) {
	tree->root->value.real = 0;
	int ret = 1;
	for (int i = 0; i <= tree->childSize; ++i) {
		if (tree->root->children[i] != NULL) {
			ret &= _NormalizeOPTree(tree->root->children[i], tree);
		}
	}
	return ret;
}

int ReserveChildSize(pOPTree tree, UINT_L newCsize) {
	if (newCsize <= 0)
		return 0;
	if (tree->childSize == newCsize)
		return 1;

	int oldCSize = tree->childSize;

	_ReserveChildSize(tree->root, tree->childSize, newCsize);

	tree->childSize = newCsize;

	/* 如果空间缩小,需要更新一下树和root->value */
	if (newCsize < oldCSize) {
		NormalizeOPTree(tree);
		_AdjustRootValue(tree);
	}

	return 1;
}

int ClearOfOPTree(pOPTree tree) {
	if (tree == NULL)
		return 0;

	for (int i = 0; i <= tree->childSize; ++i) {
		if (tree->root->children[i] != NULL) {
			_FreeNode(tree->root->children[i], tree->childSize);
			tree->root->children[i] = NULL;
		}
	}

	tree->root->value.real = 0;

	return 1;
}

int FreeOPTree(pOPTree tree) {
	if (tree == NULL) return 0;
	ClearOfOPTree(tree);
	_FreeNode(tree->root, tree->childSize);
	free(tree);
	return 1;
}

int _AddOfOPTree_TT(pOPNode node1, pOPNode node2, pOPTree tree1, pOPTree tree2) {
	/* 注意: 本函数不调整root中的value */
	for (int i = 0; i <= tree2->childSize; ++i) {
		if (node2->children[i] != NULL) {
			if (node1->children[i] != NULL) {
				/* node1中存在此子节点 */
				AddOfComplex(node1->children[i]->value, node2->children[i]->value, &node1->children[i]->value);
			}
			else {
				/* node1中不存在此子节点 */
				MallocOPNode(node2->children[i]->label, node2->children[i]->value, tree1->childSize, node1, &node1->children[i]);
			}
			_AddOfOPTree_TT(node1->children[i], node2->children[i], tree1, tree2);
		}
	}
	/* 删除可能出现的"零"叶子结点 */
	for (int i = 0; i <= tree2->childSize; ++i) {
		if (node1->children[i] != NULL && 
			IsZeroOfComplex(node1->children[i]->value) && _IsLeafNode(node1->children[i], tree1->childSize)) {
			free(node1->children[i]);
			node1->children[i] = NULL;
		}
	}
	return 1;
}

int _AdjustRootValue(pOPTree tree) {
	int sum = 0;
	for (int i = 0; i <= tree->childSize; ++i) {
		if (tree->root->children[i] != NULL)
			_AdjustRootValue_Sum(tree->root->children[i], tree->childSize, &sum);
	}
	tree->root->value.real = sum;
	return 1;
}

int _AdjustRootValue_Sum(pOPNode node, int csize, int* psum) {
	if (node == NULL)
		return 0;
	else if (!IsZeroOfComplex(node->value))
		++(*psum);

	for (int i = 0; i <= csize; ++i) {
		if (node->children[i] != NULL)
			_AdjustRootValue_Sum(node->children[i], csize, psum);
	}
	return 1;
}

int _SearchOfOPTree(pOPTree tree, pOPArray arr, int len, pOPNode* output) {
	pOPNode nowNode = tree->root;
	for (int i = 0; i < len; ++i) {
		nowNode = nowNode->children[arr[i]];
		if (nowNode == NULL) {
			// 不存在此节点的情况
			*output = NULL;
			return 0;
		}
	}
	*output = nowNode;
	return 1;
}

int _IsLeafNode(struct _Node* node, int csize) {
	for (int i = 0; i <= csize; ++i) {
		if (node->children[i] != NULL)
			return 0;
	}
	return 1;
}

int _CopyOPTree(pOPNode origin, pOPNode output, int csize) {
	if (origin == NULL || output == NULL) return 0;
	output->label = origin->label;
	output->value = origin->value;
	for (int i = 0; i <= csize; ++i) {
		if (origin->children[i] != NULL) {
			if (output->children[i] == NULL) {
				Complex temp = { 0,0 };
				MallocOPNode(0, temp, csize, output, &output->children[i]);
			}
			_CopyOPTree(origin->children[i], output->children[i], csize);
		}
	}
	return 1;
}

int _DeleteNode(pOPNode node, pOPTree tree) {
	if (tree == NULL)
		return 0;
	pOPNode nowNode = node;
	/* 无此结点 */
	if (nowNode == NULL)
		return 0;

	/* 有此结点 */
	if (IsZeroOfComplex(nowNode->value))
		/* 但value为0 */
		return 1;
	else {
		/* value不为0 */
		if (_IsLeafNode(nowNode, tree->childSize)) {
			/* 叶子节点 */
			pOPNode parent = nowNode->parent;
			while (1) {
				parent->children[nowNode->label] = NULL;
				free(nowNode->children);
				free(nowNode);
				nowNode = parent;
				parent = parent->parent;

				if (!_IsLeafNode(nowNode, tree->childSize) || !IsZeroOfComplex(nowNode->value))
					break;
				else if (nowNode == tree->root)
					break;
			}
			/* 更新root */
			tree->root->value.real--;
		}
		else {
			/* 非叶子节点 */
			INT_V tempv = { 0,0 };
			nowNode->value = tempv;
			/* 更新root */
			tree->root->value.real--;
		}
	}
	return 1;
}

int _EachNodeOfOPTree(pOPNode node, int csize, void* sth, int(*func)(pOPNode, void*)) {
	if (node == NULL)
		return 0;
	int ret = func(node, sth);
	for (int i = 0; i <= csize; ++i) {
		if (node->children[i] != NULL)
			ret &= _EachNodeOfOPTree(node->children[i], csize, sth, func);
	}
	return ret;
}

void _FreeNode(struct _Node* node, int csize) {
	if (node == NULL)
		return;

	for (int i = 0; i <= csize; ++i) {
		if (node->children[i] != NULL) {
			_FreeNode(node->children[i], csize);
		}
	}
	
	/* 释放自己的内存 */
	free(node->children);
	free(node);
	return;
}

int _MultiplyOfOPTree_TO(pOPTree tree, pOPArray arr, int len, INT_V coef, pOPTree otherTree) {
	/* 定义一个简易的栈 */
	UINT_L lStack[MAX_OPERATOR_LENGTH];
	int ret = 1;
	for (int i = 0; i <= tree->childSize; ++i) {
		if (tree->root->children[i] != NULL) {
			ret &= _MultiplyNodeWithOP(tree->root->children[i], tree->childSize, arr, len, coef, lStack, 0, otherTree);
		}
	}
	return ret;
}

int _MultiplyOfOPTree_TT(pOPTree tree1, pOPNode tree2node, int tree2csize,
	UINT_L* tree2Stack, int nextIndex, pOPTree outputTree) {
	if (nextIndex >= MAX_OPERATOR_LENGTH)
		return 0;
	tree2Stack[nextIndex] = tree2node->label;
	int ret = 1;

	if (!IsZeroOfComplex(tree2node->value)) {
		/* 定义一个简易的栈 */
		UINT_L tree1Stack[MAX_OPERATOR_LENGTH];
		for (int i = 0; i <= tree1->childSize; ++i) {
			if (tree1->root->children[i] != NULL) {
				ret &= _MultiplyNodeWithOP(tree1->root->children[i], tree1->childSize, 
					tree2Stack, nextIndex + 1, tree2node->value, tree1Stack, 0, outputTree);
			}
		}
	}

	for (int i = 0; i <= tree2csize; ++i) {
		if (tree2node->children[i] != NULL)
			ret &= _MultiplyOfOPTree_TT(tree1, tree2node->children[i], tree2csize, tree2Stack, nextIndex + 1, outputTree);
	}

	return ret;
}

int _MultiplyNodeWithOP(pOPNode node, UINT_L csize, pOPArray arr, int len, INT_V coef, 
	UINT_L* lStack, int nextIndex, pOPTree otherTree) {
	if (nextIndex >= MAX_OPERATOR_LENGTH)
		return 0;
	lStack[nextIndex] = node->label;
	int ret = 1;
	if (IsZeroOfComplex(node->value)) {
		for (int i = 0; i <= csize; ++i) {
			if (node->children[i] != NULL) {
				ret &= _MultiplyNodeWithOP(node->children[i], csize, arr, len, coef, lStack, nextIndex + 1, otherTree);
			}
		}
	}
	else {
		int newLen = ((nextIndex + 1) + len + 1);
		pOPArray ans = (pOPArray)malloc(newLen * sizeof(UINT_L));
		MultiplyOfOPArray(arr, len, lStack, nextIndex + 1, ans, &newLen);
		INT_V tempv;
		MultiplyOfComplex(coef, node->value, &tempv);
		InsertOfOPTree(otherTree, ans, newLen, tempv);
		free(ans);
	}
	return ret;
}

int _NormalizeOPTree(pOPNode node, pOPTree tree) {
	if (node == NULL)
		return 0;
	if (!IsZeroOfComplex(node->value))
		++(tree->root->value.real);

	int ret = 1;
	for (int i = 0; i <= tree->childSize; ++i) {
		if (node->children[i] != NULL) {
			ret &= _NormalizeOPTree(node->children[i], tree);
		}
	}

	if (_IsLeafNode(node, tree->childSize) && IsZeroOfComplex(node->value)) {
		pOPNode p = node->parent;
		p->children[node->label] = NULL;
		free(node);
	}

	return ret;
}

int _ReserveChildSize(pOPNode node, UINT_L originCsize, UINT_L newCsize) {
	struct _Node** newChild = (struct _Node**)malloc((newCsize + 1) * sizeof(struct _Node*));
	if (newChild == NULL) 
		return 0;
	for (int i = 0; i <= MIN(originCsize, newCsize); ++i) {
		newChild[i] = node->children[i];
	}
	/* 空间缩小时,需要释放原来的截断空间 */
	if (newCsize < originCsize) {
		for (int i = newCsize + 1; i <= originCsize; ++i) {
			_FreeNode(node->children[i], originCsize);
		}
	}
	free(node->children);
	node->children = newChild;
	/* 向下遍历所有结点 */
	for (int i = 0; i <= newCsize; ++i) {
		if (node->children[i] != NULL) 
			_ReserveChildSize(node->children[i], originCsize, newCsize);
	}
	return 1;
}

#ifdef __DEBUG__


int PrintOPTree(pOPTree tree) {
	UINT_L* buf = (UINT_L*)malloc(sizeof(UINT_L) * 128);
	if (buf == NULL) return 0;
	for (int i = 0; i <= tree->childSize; ++i) {
		if (tree->root->children[i] != NULL)
			_PrintOPTree(tree->root->children[i], tree->childSize, 0, buf);
	}
	free(buf);
	return 1;
}

int PrintOrderOPTree(pOPTree tree, UINT_L* output1, int* output2, int* output1_len, int* output2_len) {
	int o1cnt = 0;
	int o2cnt = 0;
	for (int i = 0; i <= tree->childSize; ++i) {
		if (tree->root->children[i] != NULL) {
			output1[o1cnt++] = tree->root->children[i]->label;
			output2[o2cnt++] = tree->root->children[i]->value.real;
			_PrintOrderOPTree(tree->root->children[i], tree->childSize, output1, output2, &o1cnt, &o2cnt);
		}
	}
	if (output1_len != NULL)
		*output1_len = o1cnt;
	if (output2_len != NULL)
		*output2_len = o2cnt;
	return 1;
}

int _PrintOPTree(pOPNode node, UINT_L csize, int nextIndex, pOPArray buf) {
	buf[nextIndex] = node->label;
	if (!IsZeroOfComplex(node->value)) {
		printf("%lf  ", node->value.real);
		putchar('{');
		printf("%d", buf[0]);
		for (int i = 1; i <= nextIndex; ++i) {
			printf(", %d", buf[i]);
		}
		putchar('}');
		putchar('\n');
	}
	for (int i = 0; i <= csize; ++i) {
		if (node->children[i] != NULL)
			_PrintOPTree(node->children[i], csize, nextIndex + 1, buf);
	}
	return 1;
}

int _PrintOrderOPTree(pOPNode node, UINT_L csize, UINT_L* output1, int* output2, 
	int* output1_cnt, int* output2_cnt) {
	for (int i = 0; i <= csize; ++i) {
		if (node->children[i] != NULL) {
			output1[*output1_cnt] = node->children[i]->label;
			output2[*output2_cnt] = node->children[i]->value.real;
			++(*output1_cnt);
			++(*output2_cnt);
			_PrintOrderOPTree(node->children[i], csize, output1, output2, output1_cnt, output2_cnt);
		}
	}
	output1[*output1_cnt] = MAX_UINT_L;
	++(*output1_cnt);
	return 1;
}

#endif // __DEBUG__