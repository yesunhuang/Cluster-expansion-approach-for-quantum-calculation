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
	*output = nowNode;
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
	// TODO: 注意用_DeleteNode(nowNode, tree)
	/* 获得另一个树的根节点和树指针 */
	pOPNode otherRoot;
	int depth = GetRoot(node, &otherRoot);
	pOPTree otherTree;
	ROOT_TO_TREE(otherRoot, otherTree);
	/* 获得另一个结点的数组表达 */
	pOPArray otherArray = (pOPArray)malloc(depth * sizeof(UINT_L));
	ArrayFromNode(node, depth, otherArray);
	/* 另一个树中删除该结点 */
	DeleteOfOPTree(otherTree, otherArray, depth);

	return _MultiplyOfOPTree_TO(tree, otherArray, depth, otherTree);
}

int ClearOfOPTree(pOPTree tree) {
	if (tree == NULL)
		return 0;

	for (int i = 0; i < tree->childSize; ++i) {
		if (tree->root->children[i] != NULL) {
			_FreeNode(tree->root->children[i], tree->childSize);
			tree->root->children[i] = NULL;
		}
	}

	tree->root->value = 0;

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
	pOPNode nowNode = tree->root;
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

	for (int i = 0; i < csize; ++i) {
		if (node->children[i] != NULL) {
			_FreeNode(node->children[i], csize);
		}
	}
	
	/* 释放自己的内存 */
	free(node->children);
	free(node);
	return;
}

int _MultiplyOfOPTree_TO(pOPTree tree, pOPArray arr, int len, pOPTree otherTree) {
	/* 定义一个简易的栈 */
	UINT_L lStack[MAX_OPERATOR_LENGTH];
	return _MultiplyNodeWithOP(tree->root, arr, len, lStack, 0, otherTree);
}

int _MultiplyNodeWithOP(pOPNode node, pOPArray arr, int len, UINT_L* lStack, int nextIndex, pOPTree otherTree) {

	return 0;
}
