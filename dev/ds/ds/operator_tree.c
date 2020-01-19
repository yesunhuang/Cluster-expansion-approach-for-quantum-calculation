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

int InitOPTree(pOPTree tree, UINT_L csize) {
	tree->childSize = csize;
	return MallocOPNode(0, 0, csize, NULL, &tree->root);
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
		*output = UINT_V_ERROR;
		return 0;
	}
	return nowNode->value;
}

int InsertOfOPTree(pOPTree tree, pOPArray arr, int len, int coef) {
	if (tree == NULL || len <= 0)
		return 0;
	pOPNode nowNode = tree->root;
	for (int i = 0; i < len; ++i) {
		if (nowNode->children[arr[i]] == NULL) {
			MallocOPNode(arr[i], 0, tree->childSize, nowNode, &nowNode->children[arr[i]]);
		}
		nowNode = nowNode->children[arr[i]];
	}

	/* 判断是否更新root的value */
	tree->root->value += ((nowNode->value == 0) ? 0 : 1);
	nowNode->value = coef;

	return 1;
}

int DeleteOfOPTree(pOPTree tree, pOPArray arr, int len) {
	if (tree == NULL || len <= 0)
		return 0;
	pOPNode nowNode = tree->root;
	_SearchOfOPTree(tree, arr, len, &nowNode);
	return _DeleteNode(nowNode, tree);
}

int MultiplyOfOPTree_TO(pOPTree tree, pOPNode node) {
	/* 获得另一个树的根节点和树指针 */
	pOPNode otherRoot;
	int depth = GetRoot(node, &otherRoot);
	pOPTree otherTree;
	ROOT_TO_TREE(otherRoot, otherTree);
	/* 获得另一个结点的数组表达 */
	pOPArray otherArray = (pOPArray)malloc(depth * sizeof(UINT_L));
	ArrayFromNode(node, depth, otherArray);
	/* 另一个树中删除该结点 */
	int coef = node->value;
	DeleteOfOPTree(otherTree, otherArray, depth);

	return _MultiplyOfOPTree_TO(tree, otherArray, depth, coef, otherTree);
}

int MultiplyOfOPTree_TT(pOPTree tree1, pOPTree tree2, pOPTree outputTree) {
	/* 定义一个简易的栈 */
	UINT_L tree2Stack[MAX_OPERATOR_LENGTH];
	int ret = 1;
	for (int i = 0; i <= tree2->childSize; ++i) {
		if (tree2->root->children[i] != NULL) {
			ret &= _MultiplyOfOPTree_TT(tree1, tree2->root->children[i], tree2->childSize, tree2Stack, 0, outputTree);
		}
	}
	return ret;
}

int ReserveChildSize(pOPTree tree, UINT_L newCsize) {
	if (newCsize <= 0)
		return 0;
	if (tree->childSize == newCsize)
		return 1;

	_ReserveChildSize(tree->root, tree->childSize, newCsize);

	tree->childSize = newCsize;

	/* 如果空间缩小,需要更新一下root->value */
	if (newCsize < tree->childSize)
		_AdjustRootValue(tree);

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

	tree->root->value = 0;

	return 1;
}

int _AddOfOPTree_TT(pOPNode node1, pOPNode node2, pOPTree tree1, pOPTree tree2) {
	/* 注意: 本函数不调整root中的value */
	for (int i = 0; i <= tree2->childSize; ++i) {
		if (node2->children[i] != NULL) {
			if (node1->children[i] != NULL) {
				/* node1中存在此子节点 */
				node1->children[i]->value += node2->children[i]->value;
			}
			else {
				/* node1中不存在此子节点 */
				MallocOPNode(node2->label, node2->value, tree1->childSize, node1, &node1->children[i]);
			}
		}
		_AddOfOPTree_TT(node1->children[i], node2->children[i], tree1, tree2);
	}
	/* 删除可能出现的"零"叶子结点 */
	for (int i = 0; i <= tree2->childSize; ++i) {
		if (node1->children[i]->value == 0 && _IsLeafNode(node1->children[i], tree1->childSize)) {
			free(node1->children[i]);
			node1->children[i] = NULL;
		}
	}
	return 1;
}

int _AdjustRootValue(pOPTree tree) {
	int sum = 0;
	for (int i = 0; i <= tree->childSize; ++i) {
		_AdjustRootValue_Sum(tree->root->children[i], tree->childSize, &sum);
	}
	tree->root->value = sum;
	return 1;
}

int _AdjustRootValue_Sum(pOPNode node, int csize, int* psum) {
	if (node->value != 0)
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

int _DeleteNode(pOPNode node, pOPTree tree) {
	if (tree == NULL)
		return 0;
	pOPNode nowNode = node;
	/* 无此结点 */
	if (nowNode == NULL)
		return 0;

	/* 有此结点 */
	if (nowNode->value == 0)
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

				if (!_IsLeafNode(nowNode, tree->childSize) || nowNode->value != 0)
					break;
				else if (nowNode == tree->root)
					break;
			}
			/* 更新root */
			tree->root->value--;
		}
		else {
			/* 非叶子节点 */
			nowNode->value = 0;
			/* 更新root */
			tree->root->value--;
		}
	}
	return 1;
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

	if (tree2node->value != 0) {
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
		ret &= MultiplyOfOPTree_TT(tree1, tree2node->children[i], tree2csize, tree2Stack, nextIndex + 1, outputTree);
	}

	return ret;
}

int _MultiplyNodeWithOP(pOPNode node, UINT_L csize, pOPArray arr, int len, INT_V coef, 
	UINT_L* lStack, int nextIndex, pOPTree otherTree) {
	if (nextIndex >= MAX_OPERATOR_LENGTH)
		return 0;
	lStack[nextIndex] = node->label;
	int ret = 1;
	if (node->value == 0) {
		for (int i = 0; i <= csize; ++i) {
			if (node->children[i] != NULL) {
				ret &= _MultiplyNodeWithOP(node->children[i], csize, arr, len, coef, lStack, nextIndex + 1, otherTree);
			}
		}
	}
	else {
		int newLen = ((nextIndex + 1) * len + 1);
		pOPArray ans = (pOPArray)malloc(newLen * sizeof(UINT_L));
		MultiplyOfOPArray(arr, len, lStack, nextIndex + 1, ans, NULL);
		InsertOfOPTree(otherTree, ans, newLen, coef * node->value);
		free(ans);
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
		for (int i = newChild + 1; i <= originCsize; ++i) {
			_FreeNode(node->children[i], originCsize);
		}
	}
	free(node->children);
	node->children = newChild;
	return 1;
}
