#include "solver.h"
/**
 * @ 文件名: solver.h
 * @ 功能: 声明有关solver的功能
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 2020年2月1日
 *
 */

int CreateOfDData(int capacity, int csize, int hoSize, int coSize, pDeriveData* outputpp) {
	if (capacity < 0 || hoSize < 0 || coSize < 0)
		return 0;
	pDeriveData p = *outputpp = (pDeriveData)malloc(sizeof(DeriveData));
	if (p == NULL) return 0;
	p->capacity = capacity;
	p->size = 0;
	p->hoSize = hoSize;
	p->coSize = coSize;
	p->curValues = (Complex*)malloc(capacity * sizeof(Complex)); ASSERTNULL(p->curValues);
	p->evoTrees_HO = (pOPTree**)malloc(capacity * sizeof(pOPTree*)); ASSERTNULL(p->evoTrees_HO);
	p->evoTrees_CO = (pOPTree**)malloc(capacity * sizeof(pOPTree*)); ASSERTNULL(p->evoTrees_CO);
	for (int i = 0; i < capacity; ++i) {
		p->evoTrees_HO[i] = (pOPTree*)malloc(hoSize * sizeof(pOPTree)); ASSERTNULL(p->evoTrees_HO[i]);
		p->evoTrees_CO[i] = (pOPTree*)malloc(coSize * sizeof(pOPTree)); ASSERTNULL(p->evoTrees_CO[i]);
		memset(p->evoTrees_HO[i], 0, hoSize * sizeof(pOPTree));
		memset(p->evoTrees_CO[i], 0, coSize * sizeof(pOPTree));
	}
	p->trackNodes = (pOPNode*)malloc(capacity * sizeof(pOPNode)); ASSERTNULL(p->trackNodes);
	if (CreateOPTree(csize, &p->trackTree) == 0) return 0;
	memset(p->curValues, 0, capacity * sizeof(Complex));
	for (int i = 0; i < capacity; ++i) {
		memset(p->evoTrees_HO[i], 0, hoSize * sizeof(pOPTree));
		memset(p->evoTrees_CO[i], 0, coSize * sizeof(pOPTree));
	}
	memset(p->trackNodes, 0, capacity * sizeof(pOPNode));
	return 1;
}

int InsertOfDData(pDeriveData data, Complex c, pOPArray arr, int arrLen) {
	pOPNode tempnode = NULL;
	_SearchOfOPTree(data->trackTree, arr, arrLen, &tempnode);
	if (tempnode != NULL && !IsZeroOfComplex(tempnode->value))
		return 1;
	if (data->size >= data->capacity) {
		ReserveOfDData(data, MAX(2 * data->capacity, data->size + 8));
	}
	data->curValues[data->size] = c;
	for (int i = 0; i < data->hoSize; ++i)
		data->evoTrees_HO[data->size][i] = NULL;
	for (int i = 0; i < data->coSize; ++i)
		data->evoTrees_CO[data->size][i] = NULL;
	Complex tempc = { 1, 0 };
	InsertOfOPTree(data->trackTree, arr, arrLen, tempc);
	// PrintOPTree(data->trackTree);
	// putchar('\n');
	_SearchOfOPTree(data->trackTree, arr, arrLen, &data->trackNodes[data->size]);
	++(data->size);
	
	return 1;
}

int FreeOfDData(pDeriveData data) {
	for (int i = 0; i < data->size; ++i) {
		if (data->trackNodes[i] != NULL)
			_DeleteNode(data->trackNodes[i], data->trackTree);
	}
	free(data->curValues);
	for (int i = 0; i < data->capacity; ++i) {
		for (int j = 0; j < data->hoSize; ++j) {
			FreeOPTree(data->evoTrees_HO[i][j]);
		}
		for (int j = 0; j < data->coSize; ++j) {
			FreeOPTree(data->evoTrees_CO[i][j]);
		}
		free(data->evoTrees_HO[i]);
		free(data->evoTrees_CO[i]);
	}
	free(data->evoTrees_HO);
	free(data->evoTrees_CO);
	free(data->trackNodes);
	FreeOPTree(data->trackTree);
	free(data);
	return 1;
}

int ReserveOfDData(pDeriveData data, int newCap) {
	if (newCap < 0)
		return 0;
	else if (newCap == data->capacity)
		return 1;
	else if (newCap > data->capacity) {
		void* tempp;
		tempp = realloc(data->curValues, newCap * sizeof(Complex)); ASSERTNULL(tempp);
		data->curValues = (Complex*)tempp;
		tempp = realloc(data->evoTrees_HO, newCap * sizeof(pOPTree*)); ASSERTNULL(tempp);
		data->evoTrees_HO = (pOPTree**)tempp;
		tempp = realloc(data->evoTrees_CO, newCap * sizeof(pOPTree*)); ASSERTNULL(tempp);
		data->evoTrees_CO = (pOPTree**)tempp;
		for (int i = data->capacity; i < newCap; ++i) {
			data->evoTrees_HO[i] = (pOPTree*)malloc(data->hoSize * sizeof(pOPTree)); ASSERTNULL(data->evoTrees_HO[i]);
			data->evoTrees_CO[i] = (pOPTree*)malloc(data->coSize * sizeof(pOPTree)); ASSERTNULL(data->evoTrees_CO[i]);
			memset(data->evoTrees_HO[i], 0, data->hoSize * sizeof(pOPTree));
			memset(data->evoTrees_CO[i], 0, data->coSize * sizeof(pOPTree));
		}
		tempp = realloc(data->trackNodes, newCap * sizeof(pOPNode)); ASSERTNULL(tempp);
		data->trackNodes = (pOPNode*)tempp;
		data->capacity = newCap;
	}
	else {
		/* newCap < data->capacity */
		for (int i = newCap; i < data->capacity; ++i) {
			if (data->trackNodes[i] != NULL)
				_DeleteNode(data->trackNodes[i], data->trackTree);
		}
		void* tempp;
		tempp = realloc(data->curValues, newCap * sizeof(Complex)); ASSERTNULL(tempp);
		data->curValues = (Complex*)tempp;

		for (int i = newCap; i < data->capacity; ++i) {
			for (int j = 0; j < data->hoSize; ++j) {
				FreeOPTree(data->evoTrees_HO[i][j]);
			}
			for (int j = 0; j < data->coSize; ++j) {
				FreeOPTree(data->evoTrees_CO[i][j]);
			}
			free(data->evoTrees_HO[i]);
			free(data->evoTrees_CO[i]);
		}
		tempp = realloc(data->evoTrees_HO, newCap * sizeof(pOPTree*)); ASSERTNULL(tempp);
		data->evoTrees_HO = (pOPTree**)tempp;
		tempp = realloc(data->evoTrees_CO, newCap * sizeof(pOPTree*)); ASSERTNULL(tempp);
		data->evoTrees_CO = (pOPTree**)tempp;
		tempp = realloc(data->trackNodes, newCap * sizeof(pOPNode)); ASSERTNULL(tempp);
		data->trackNodes = (pOPNode*)tempp;
		data->capacity = newCap;
	}
	return 1;
}

int InitialValue(pOPArray arr, int len, int* sArr, int sArrLen, double* output) {
	if (sArrLen <= 0 || len <= 0 || arr == NULL || sArr == NULL) {
		if (output != NULL)
			*output = 0;
		return 0;
	}
	if (arr[0] == 0) {
		if (output != NULL)
			*output = 1;
		return 1;
	}
	int maxn = -1;
	for (int i = 0; i < len; ++i) {
		maxn = MAX(maxn, arr[i]);
	}
	if ((maxn + 1) / 2 - 1 > sArrLen)
		return 0;

	int dagger = -1, normal = -1;
	int nextIndex = -1;
	/* n表示creation operator的数目,即dagger的数目 */
	/* m表示anihilation operator的数目,即normal的数目 */
	int n = 0, m = 0;
	double ans = 1;
	int state = 0;
	while (state != -1) {
		switch (state) {
		case -1:
			/* 状态-1: 退出状态 */
			break;
		case 0:
			/* 状态0: 初始化 */
			nextIndex = 0;
			state = 1;
			break;
		case 1:
			/* 状态1: 更改dagger和normal */
			n = m = 0;
			normal = ((arr[nextIndex] + 1) / 2) * 2;
			dagger = normal - 1;
			state = 2;
			break;
		case 2:
			/* 状态2: 开始遍历同一块 */
			if (nextIndex >= len) {
				state = 3;
			}
			else if (arr[nextIndex] == normal) {
				++m;
				++nextIndex;
			}
			else if (arr[nextIndex] == dagger) {
				++n;
				++nextIndex;
			}
			else {
				state = 3;
			}
			break;
		case 3:
			/* 状态3: 统计n和m,更新ans */
		{
			if (n != m) {
				ans = 0;
				state = -1;
				break;
			}
			else {
				int n_alpha = sArr[normal / 2 - 1];
				if (n > n_alpha) {
					ans = 0;
					state = -1;
				}
				else {
					for (int i = n_alpha; i >= n_alpha - n + 1; --i) {
						ans *= i;
					}
				}

				if (nextIndex >= len)
					state = -1;
				else
					state = 1;
			}
			break;
		}
		default:
			break;
		}
	}

	*output = ans;

	return 1;
}

int Evolution(pOPArray* inputArr_HO, int* inputArrLens_HO, Complex* inputArrCoef_HO, int inputArrLen_HO, 
	pOPArray* inputArr_CO, int* inputArrLens_CO, Complex* inputArrCoef_CO, int inputArrLen_CO, 
	pOPArray userArr, int userArrLen, int maxOPLen, pOPTree* ho_output, pOPTree* co_output) {
	int ret = 1;
	ret &= _Evolution_HO(inputArr_HO, inputArrLens_HO, inputArrCoef_HO, inputArrLen_HO,
		userArr, userArrLen, maxOPLen, ho_output);
	ret &= _Evolution_CO(inputArr_CO, inputArrLens_CO, inputArrCoef_CO, inputArrLen_CO,
		userArr, userArrLen, maxOPLen, co_output);
	return ret;
}

int DeriveAssign(pOPArray* inputArr_HO, int* inputArrLens_HO, Complex* inputArrCoef_HO, int inputArrLen_HO, 
	pOPArray* inputArr_CO, int* inputArrLens_CO, Complex* inputArrCoef_CO, int inputArrLen_CO, 
	int* inputArr_Init, int inputArrLen_Init, 
	pOPArray* inputArr_Track, int* inputArrLens_Track, int inputArrLen_Track, 
	int maxOPLen, 
	pDeriveData* outputpp){

	/* 首先确定csize,并创建data实体 */
	UINT_L maxInitTrackLabel = 0;
	for (int i = 0; i < inputArrLen_Track; ++i) {
		for (int j = 0; j < inputArrLens_Track[i]; ++j) {
			maxInitTrackLabel = MAX(maxInitTrackLabel, inputArr_Track[i][j]);
		}
	}
	CreateOfDData(2, maxInitTrackLabel, inputArrLen_HO, inputArrLen_CO, outputpp);
	pDeriveData outputData = *outputpp;

	/* 初始加入tracking operator, 并同时计算initial value */
	for (int i = 0; i < inputArrLen_Track; ++i) {
		Complex tempc = { 1,0 };
		InsertOfDData(outputData, tempc, inputArr_Track[i], inputArrLens_Track[i]);
		InitialValue(inputArr_Track[i], inputArrLens_Track[i], inputArr_Init, inputArrLen_Init, &tempc.real);
		outputData->curValues[i] = tempc;
	}

	/* derive的过程 */
	int index = 0;
	UINT_L nowIndexArr[MAX_OPERATOR_LENGTH];
	int nowIndexArrLen = 0;
	while (index < outputData->size) {
		if (outputData->evoTrees_HO[index] != NULL && outputData->evoTrees_CO[index] != NULL) {
			nowIndexArrLen = GetRoot(outputData->trackNodes[index], NULL);
			ArrayFromNode(outputData->trackNodes[index], nowIndexArrLen, nowIndexArr);
			Evolution(inputArr_HO, inputArrLens_HO, inputArrCoef_HO, inputArrLen_HO,
				inputArr_CO, inputArrLens_CO, inputArrCoef_CO, inputArrLen_CO,
				nowIndexArr, nowIndexArrLen, maxOPLen, outputData->evoTrees_HO[index], outputData->evoTrees_CO[index]);

			/* 添加未曾拥有的tracking operator, 并在插入新结点时算出initial value */
			for (int i = 0; i < inputArrLen_HO; ++i) {
				_DeriveAT(outputData->evoTrees_HO[index][i], inputArr_Init, inputArrLen_Init, outputData);
			}
			for (int i = 0; i < inputArrLen_CO; ++i) {
				_DeriveAT(outputData->evoTrees_CO[index][i], inputArr_Init, inputArrLen_Init, outputData);
			}
			++index;
		}
	}

	/* 把tracking tree中结点的value设为其current value */
	_UpdateDDTTreeValue(outputData);

	return 1;
}

int CalEvolution(pDeriveData data, Complex** outputpp) {
	/* 创建与data->size等长的复数数组 */
	Complex* outputp = *outputpp = (Complex*)malloc(data->size * sizeof(Complex)); ASSERTNULL(outputp);
	memset(outputp, 0, data->size * sizeof(Complex));

	UINT_L nowIndexArr[MAX_OPERATOR_LENGTH];
	int nowIndexArrLen = 0;
	for (int i = 0; i < data->size; ++i) {
		nowIndexArrLen = GetRoot(data->trackNodes[i], NULL);
		ArrayFromNode(data->trackNodes[i], nowIndexArrLen, nowIndexArr);
		for (int j = 0; j < data->hoSize; ++j) {
			_CalEvo(data->evoTrees_HO[i][j], data, &outputp[i]);
		}
		for (int j = 0; j < data->coSize; ++j) {
			_CalEvo(data->evoTrees_CO[i][j], data, &outputp[i]);
		}
	}

	return 1;
}

int SetCurrentValueOfDData(pDeriveData data, Complex* arr, int len) {
	ASSERTNULL(data);
	for (int i = 0; i < MIN(data->size, len); ++i) {
		data->curValues[i] = arr[i];
	}
	_UpdateDDTTreeValue(data);
	return 1;
}

int _CalEvo(pOPTree evoTree, pDeriveData data, Complex* psum) {
	UINT_L buf[MAX_OPERATOR_LENGTH];
	/* 零算符 */
	if (evoTree->root->children[0] != NULL) {
		AddOfComplex(*psum, evoTree->root->value, psum);
	}

	/* 其他算符 */
	for (int i = 1; i <= evoTree->childSize; ++i) {
		if (evoTree->root->children[i] != NULL) {
			__CalEvo(evoTree->root->children[i], evoTree, data, buf, 0, psum);
		}
	}
	return 1;
}

int __CalEvo(pOPNode node, pOPTree tree, pDeriveData data, UINT_L* buf, int nextIndex, Complex* psum) {
	buf[nextIndex] = node->label;
	if (!IsZeroOfComplex(node->value)) {
		int len = nextIndex + 1;
		int head = 0;
		int tail = 0;
		_GetNextCPIndexFromOPArray(buf, len, head, &tail);
		Complex tempc = { 1,0 };
		while (head < len) {
			Complex tempnodev = { 0,0 };
			pOPNode tempnode = NULL;
			if (tail == len) {
				_SearchOfOPTree(data->trackTree, buf + head, tail - head, &tempnode);
				if (tempnode != NULL) {
					tempnodev = tempnode->value;
				}
				else {
					/* dagger的共轭现象 */
					UINT_L dbuf[MAX_OPERATOR_LENGTH];
					for (int i = 0; i < tail - head; ++i) {
						dbuf[i] = (((*(buf + head + i)) - 1) ^ 1) + 1;
					}
					_SearchOfOPTree(data->trackTree, dbuf, tail - head, &tempnode);
					tempnodev = tempnode->value;
					tempnodev.image = -tempnodev.image;
				}
			}
			else {
				_SearchOfOPTree(data->trackTree, buf + head, tail - head - 1, &tempnode);
				if (tempnode != NULL) {
					tempnodev = tempnode->value;
				}
				else {
					/* dagger的共轭现象 */
					UINT_L dbuf[MAX_OPERATOR_LENGTH];
					for (int i = 0; i < tail - head - 1; ++i) {
						dbuf[i] = (((*(buf + head + i)) - 1) ^ 1) + 1;
					}
					_SearchOfOPTree(data->trackTree, dbuf, tail - head - 1, &tempnode);
					tempnodev = tempnode->value;
					tempnodev.image = -tempnodev.image;
				}
			}

			MultiplyOfComplex(tempc, tempnodev, &tempc);
			head = tail;
			_GetNextCPIndexFromOPArray(buf, len, head, &tail);
		}
		MultiplyOfComplex(tempc, tree->root->value, &tempc);
		MultiplyOfComplex(tempc, node->value, &tempc);
		AddOfComplex(tempc, *psum, psum);
	}
	for (int i = 0; i <= tree->childSize; ++i) {
		if (node->children[i] != NULL) {
			__CalEvo(node->children[i], tree, data, buf, nextIndex + 1, psum);
		}
	}
	return 1;
}

int _DeleteAndCE(pOPTree tree, int maxOPLen) {
	if (tree == NULL || maxOPLen <= 0)
		return 0;
	int ret = 0;
	for (int i = 1; i <= tree->childSize; ++i) {
		if (tree->root->children[i] != NULL)
			ret |= _DeleteAndCE_(tree->root->children[i], tree, maxOPLen, 1);
		if (ret)
			return 1;
	}
	return ret;
}

int _DeleteAndCE_(pOPNode node, pOPTree tree, int maxOPLen, int nextLen) {
	if (nextLen <= maxOPLen) {
		int ret = 0;
		for (int i = 0; i <= tree->childSize; ++i) {
			if (node->children[i] != NULL) {
				if (i == 0)
					ret |= _DeleteAndCE_(node->children[i], tree, maxOPLen, 0);
				else
					ret |= _DeleteAndCE_(node->children[i], tree, maxOPLen, nextLen + 1);
			}
			if (ret) {
				return 1;
			}
		}
		return ret;
	}
	else {
		if (!IsZeroOfComplex(node->value)) {
			UINT_L buf[MAX_OPERATOR_LENGTH];
			Complex originCoef = node->value;
			int totalLen = GetRoot(node, NULL);
			ArrayFromNode(node, totalLen, buf);
			_DeleteNode(node, tree);

			/* 将multi-op分拆为single-op,并Multiply_TT */
			pOPTree treeBuf[MAX_OPERATOR_TREE_LENGTH];
			memset(treeBuf, 0, MAX_OPERATOR_TREE_LENGTH * sizeof(pOPTree));
			int treeCount = 0;
			int nowIndex = 0;
			int nextIndex = 0;
			_GetNextCPIndexFromOPArray(buf, totalLen, nowIndex, &nextIndex);
			while (nowIndex < totalLen) {
				int singleLen;
				if (nextIndex == totalLen)
					singleLen = nextIndex - nowIndex;
				else
					singleLen = nextIndex - nowIndex - 1;
				

				if (singleLen > maxOPLen) {
					ClusterExpansion(buf + nowIndex, singleLen, &treeBuf[treeCount]);
				}
				else {
					CreateOPTree(tree->childSize, &treeBuf[treeCount]);
					Complex tempc = { 1, 0 };
					InsertOfOPTree(treeBuf[treeCount], buf + nowIndex, singleLen, tempc);
				}

				nowIndex = nextIndex;
				++treeCount;
				_GetNextCPIndexFromOPArray(buf, totalLen, nowIndex, &nextIndex);
			}

			pOPTree newTree = NULL;
			if (treeCount == 1) {
				newTree = treeBuf[0];
			}
			else {
				MultiplyOfOPTree_TT(treeBuf[0], treeBuf[1], &newTree);
				// PrintOPTree(newTree);
				for (int i = 2; i < treeCount; ++i) {
					pOPTree temp = NULL;
					MultiplyOfOPTree_TT(newTree, treeBuf[i], &temp);
					FreeOPTree(newTree);
					newTree = temp;
				}
			}

			/* TODO: 原系数需要乘上去 */
			EachNodeOfOPTree(newTree, &originCoef, _MultiplyNodeWithComplex);

			AddOfOPTree_TT(tree, newTree);
			FreeOPTree(newTree);
			return 1;
		}
		else {
			int ret = 0;
			for (int i = 0; i <= tree->childSize; ++i) {
				if (node->children[i] != NULL) {
					ret |= _DeleteAndCE_(node->children[i], tree, maxOPLen, maxOPLen + 1);
				}
				if (ret) {
					return 1;
				}
			}
			return ret;
		}
	}
}

int _DeriveAT(pOPTree evoTree, pOPArray inputArr_Init, int inputArrLen_Init, pDeriveData data) {
	UINT_L buf[MAX_OPERATOR_LENGTH];
	for (int i = 1; i <= evoTree->childSize; ++i) {
		if (evoTree->root->children[i] != NULL) {
			__DeriveAT(evoTree->root->children[i], evoTree->childSize, inputArr_Init, inputArrLen_Init, data, buf, 0);
		}
	}
	return 1;
}

int __DeriveAT(pOPNode node, int csize, pOPArray inputArr_Init, int inputArrLen_Init, pDeriveData data, UINT_L* buf, int nextIndex) {
	buf[nextIndex] = node->label;
	if (node->label == 0) {
		if (nextIndex == 0) {
			/* 0次项 */
			/* 先找正常项 */
			pOPNode tempnode = NULL;
			_SearchOfOPTree(data->trackTree, buf, 1, &tempnode);
			if (tempnode != NULL && !IsZeroOfComplex(tempnode->value))
				return 1;

			/* 最后可才插入 */
			Complex tempc = { 1, 0 };
			InsertOfDData(data, tempc, buf, 1);
			InitialValue(buf, 1, inputArr_Init, inputArrLen_Init, &tempc.real);
			data->curValues[data->size - 1] = tempc;
		}
		else {
			int prev = nextIndex - 1;
			for (; prev >= 0; --prev) {
				if (buf[prev] == 0)
					break;
			}
			int len = nextIndex - prev - 1;
			int isExist = 0;

			/* 先找正常项 */
			pOPNode tempnode = NULL;
			_SearchOfOPTree(data->trackTree, buf + prev + 1, len, &tempnode);
			if (tempnode != NULL && !IsZeroOfComplex(tempnode->value)) {
				isExist = 1;
			}

			/* 再找共轭项 */
			UINT_L dbuf[MAX_OPERATOR_LENGTH];
			for (int i = 0; i < len; ++i) {
				dbuf[i] = (((*(buf + prev + 1 + i)) - 1) ^ 1) + 1;
			}
			tempnode = NULL;
			_SearchOfOPTree(data->trackTree, dbuf, len, &tempnode);
			if (tempnode != NULL && !IsZeroOfComplex(tempnode->value)) {
				isExist = 1;
			}

			/* 最后可才插入 */
			if (!isExist) {
				Complex tempc = { 1, 0 };
				InsertOfDData(data, tempc, buf + prev + 1, len);
				InitialValue(buf, 1, inputArr_Init, inputArrLen_Init, &tempc.real);
				data->curValues[data->size - 1] = tempc;
			}
		}

		for (int i = 0; i <= csize; ++i) {
			if (node->children[i] != NULL) {
				__DeriveAT(node->children[i], csize, inputArr_Init, inputArrLen_Init, data, buf, nextIndex + 1);
			}
		}

		return 1;
	}
	else if (_IsLeafNode(node, csize)) {
		int prev = nextIndex - 1;
		for (; prev >= 0; --prev) {
			if (buf[prev] == 0)
				break;
		}
		int len = nextIndex - prev;
		int isExist = 0;

		/* 先找正常项 */
		pOPNode tempnode = NULL;
		_SearchOfOPTree(data->trackTree, buf + prev + 1, len, &tempnode);
		if (tempnode != NULL && !IsZeroOfComplex(tempnode->value)) {
			isExist = 1;
		}

		/* 再找共轭项 */
		UINT_L dbuf[MAX_OPERATOR_LENGTH];
		for (int i = 0; i < len; ++i) {
			dbuf[i] = (((*(buf + prev + 1 + i)) - 1) ^ 1) + 1;
		}
		tempnode = NULL;
		_SearchOfOPTree(data->trackTree, dbuf, len, &tempnode);
		if (tempnode != NULL && !IsZeroOfComplex(tempnode->value)) {
			isExist = 1;
		}

		/* 最后可才插入 */
		if (!isExist) {
			Complex tempc = { 1, 0 };
			InsertOfDData(data, tempc, buf + prev + 1, len);
			InitialValue(buf, 1, inputArr_Init, inputArrLen_Init, &tempc.real);
			data->curValues[data->size - 1] = tempc;
			return 1;
		}
	}
	else {
		for (int i = 0; i <= csize; ++i) {
			if (node->children[i] != NULL) {
				__DeriveAT(node->children[i], csize, inputArr_Init, inputArrLen_Init, data, buf, nextIndex + 1);
			}
		}
	}
	
	return 0;
}

int _Evolution_HO(pOPArray* inputArr, int* inputArrLens,
 Complex* inputArrCoef, int inputArrLen, pOPArray userArr, int userArrLen, int maxOPLen, pOPTree* ho_outputArr) {
	/* ho部分 */
	UINT_L buf[2 * MAX_OPERATOR_LENGTH];
	for (int i = 0; i < inputArrLen; ++i) {
		/* 先构造<O_j A_i> */
		memcpy(buf, inputArr[i], inputArrLens[i] * sizeof(UINT_L));
		memcpy(buf + inputArrLens[i], userArr, userArrLen * sizeof(UINT_L));
		pOPTree OA_Tree = NULL;
		MONormalize(buf, inputArrLens[i] + userArrLen, &OA_Tree);
		//PrintOPTree(OA_Tree);

		/* 再构造<A_i O_j> */
		memcpy(buf, userArr, userArrLen * sizeof(UINT_L));
		memcpy(buf + userArrLen, inputArr[i], inputArrLens[i] * sizeof(UINT_L));
		pOPTree AO_Tree = NULL;
		MONormalize(buf, inputArrLens[i] + userArrLen, &AO_Tree);
		//PrintOPTree(AO_Tree);

		/* 两树相减 */
		EachNodeOfOPTree(AO_Tree, NULL, _NegateNode);
		AddOfOPTree_TT(OA_Tree, AO_Tree);
		//PrintOPTree(OA_Tree);

		/* 去除长度超过范围的 */
		/* TODO: 这个方法很蠢,日后需要优化 */
		while (_DeleteAndCE(OA_Tree, maxOPLen) == 1) {}

		OA_Tree->root->value = inputArrCoef[i];
		Complex temp = { 0,1 };
		MultiplyOfComplex(OA_Tree->root->value, temp, &OA_Tree->root->value);

		FreeOPTree(AO_Tree);

		ho_outputArr[i] = OA_Tree;
	}
	return 1;
}

int _Evolution_CO(pOPArray* inputArr, int* inputArrLens,
	Complex* inputArrCoef, int inputArrLen, pOPArray userArr, int userArrLen, int maxOPLen, pOPTree* co_outputArr) {
	/* co部分 */
	UINT_L dagger[MAX_OPERATOR_LENGTH];
	UINT_L buf[3 * MAX_OPERATOR_LENGTH];
	for (int i = 0; i < inputArrLen; ++i) {
		/* 先构造O_n^{\dagger} */
		for (int j = 0; j < inputArrLens[i]; ++j) {
			dagger[j] = ((inputArr[i][j] - 1) ^ 1) + 1;
		}

		/* 先构造<O_n^{\dagger} A_i O_n> */
		memcpy(buf, dagger, inputArrLens[i] * sizeof(UINT_L));
		memcpy(buf + inputArrLens[i], userArr, userArrLen * sizeof(UINT_L));
		memcpy(buf + inputArrLens[i] + userArrLen, inputArr[i], inputArrLens[i] * sizeof(UINT_L));
		pOPTree OdAO_Tree = NULL;
		MONormalize(buf, 2 * inputArrLens[i] + userArrLen, &OdAO_Tree);
		Complex tempc = { 2,0 };
		EachNodeOfOPTree(OdAO_Tree, &tempc, _MultiplyNodeWithComplex);

		/* 再构造<O_n^{\dagger} O_n A_i> */
		memcpy(buf, dagger, inputArrLens[i] * sizeof(UINT_L));
		memcpy(buf + inputArrLens[i], inputArr[i], inputArrLens[i] * sizeof(UINT_L));
		memcpy(buf + 2 * inputArrLens[i], userArr, userArrLen * sizeof(UINT_L));
		pOPTree OdOA_Tree = NULL;
		MONormalize(buf, 2 * inputArrLens[i] + userArrLen, &OdOA_Tree);

		/* 再构造<A_i O_n^{\dagger} O_n> */
		memcpy(buf, userArr, userArrLen * sizeof(UINT_L));
		memcpy(buf + userArrLen, dagger, inputArrLens[i] * sizeof(UINT_L));
		memcpy(buf + userArrLen + inputArrLens[i], inputArr[i], inputArrLens[i] * sizeof(UINT_L));
		pOPTree AOdO_Tree = NULL;
		MONormalize(buf, 2 * inputArrLens[i] + userArrLen, &AOdO_Tree);

		/* 三树相减 */
		EachNodeOfOPTree(OdOA_Tree, NULL, _NegateNode);
		EachNodeOfOPTree(AOdO_Tree, NULL, _NegateNode);
		AddOfOPTree_TT(OdAO_Tree, OdOA_Tree);
		AddOfOPTree_TT(OdAO_Tree, AOdO_Tree);

		/* 去除长度超过范围的 */
		/* TODO: 这个方法很蠢,日后需要优化 */
		while (_DeleteAndCE(OdAO_Tree, maxOPLen) == 1) {}

		Complex temp = { (double)0.5, 0 };
		MultiplyOfComplex(temp, inputArrCoef[i], &temp);
		OdAO_Tree->root->value = temp;

		FreeOPTree(OdOA_Tree);
		FreeOPTree(AOdO_Tree);

		co_outputArr[i] = OdAO_Tree;
	}
	return 1;
}

int _MultiplyNodeWithComplex(pOPNode node, void* sth) {
	if (sth == NULL)
		return 0;
	Complex* c = (Complex*)sth;
	MultiplyOfComplex(node->value, *c, &node->value);
	return 1;
}

int _NegateNode(pOPNode node, void* sth) {
	NegateOfComplex(node->value, &node->value);
	return 1;
}

int _UpdateDDTTreeValue(pDeriveData data) {
	ASSERTNULL(data);
	for (int i = 0; i < data->size; ++i) {
		ASSERTNULL(data->trackNodes[i]);
		data->trackNodes[i]->value = data->curValues[i];
	}
	return 1;
}
