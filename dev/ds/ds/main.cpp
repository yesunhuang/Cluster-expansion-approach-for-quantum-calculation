#include "normalizer.h"
#include "position_tree.h"

UINT_L arr1[] = { 2,4,4,0,1,3,4,6 };
UINT_L arr2[] = { 2,0,4,4,6,0,2,4,4,6 };
UINT_L arr3[] = { 1,2 };
UINT_L arr4[] = { 2,1,2,4,3 };
UINT_L arr5[] = { 3,3,3 };
UINT_L arr6[] = { 2, 1 };

int main() {
	pOPArray buf = (UINT_L*)malloc(sizeof(UINT_L) * 100);
	/*
	pOPTree tree1;
	pOPTree tree2;
	CreateOPTree(6, &tree1);
	CreateOPTree(6, &tree2);
	InsertOfOPTree(tree1, arr1, 8, 1);
	InsertOfOPTree(tree1, arr2, 10, 2);
	InsertOfOPTree(tree2, arr3, 2, 3);
	pOPTree tree3;
	MultiplyOfOPTree_TT(tree1, tree1, &tree3);

	PrintOPTree(tree3);
	*/

	/*
	pOPTree tree;
	MONormalize(arr4, 5, &tree);
	PrintOPTree(tree);
	*/

	pPTree posTree = NULL;
	CreatePTree(3, &posTree);
	InsertOfPTree(posTree, arr3, 2, 1);
	//InsertOfPTree(posTree, arr5, 3, 1);
	InsertOfPTree(posTree, arr6, 2, -1);
	pOPTree tree;
	BuildFromPTree(posTree, arr5, 3, &tree);

	PrintOPTree(tree);

	while (1){
	

	}
	return 0;
}