#include "normalizer.h"
#include "position_tree.h"
#include "cluster_expansion.h"
#include "solver.h"
#include "complex.h"
// #include <Python.h>

UINT_L arr1[] = { 2,4,4,0,1,3,4,6 };
UINT_L arr2[] = { 2,0,4,4,6,0,2,4,4,6 };
UINT_L arr3[] = { 1,3 };
UINT_L arr4[] = { 2,1,2,4,3 };
UINT_L arr5[] = { 3,0,3,3,0,3 };
UINT_L arr6[] = { 2, 1 };
UINT_L arr7[] = { 2,4,6,8 };
UINT_L arr8[] = { 1,1,2,2,5,5,5,6,6,6 };
UINT_L arr9[] = { 0,1 };
UINT_L arr10[] = { 1 };
UINT_L arr11[] = { 1,0,1,0,1 };
UINT_L arr12[] = { 1,1,2 };

Complex c_1 = { 1,0 };
Complex c_2 = { 2,0 };
Complex c_3 = { 0,1 };
int init_arr1[] = { 3,2,3,4 };
UINT_L ho_arr1[] = { 1,1 };
int ho_lens_arr1[] = { 2 };
Complex ho_coef_arr1[1];
pOPArray ho_arrs[1];
UINT_L co_arr1[] = { 3,4 };
int co_lens_arr1[] = { 2 };
Complex co_coef_arr1[1];
pOPArray co_arrs[1];
UINT_L track_arr1[] = { 1,2 };
int track_lens_arr1[] = { 2 };
pOPArray track_arrs[1];


int main() {
	ho_coef_arr1[0] = c_2;
	ho_arrs[0] = ho_arr1;

	co_coef_arr1[0] = c_2;
	co_arrs[0] = co_arr1;

	track_arrs[0] = track_arr1;

	pOPArray buf = (UINT_L*)malloc(sizeof(UINT_L) * 100);
	
	/*
	pOPTree tree1;
	pOPTree tree2;
	CreateOPTree(3, &tree1);
	CreateOPTree(3, &tree2);
	INT_V tempv = { 1, 0 };
	InsertOfOPTree(tree1, arr11, 5, tempv);
	// tempv.real = 2;
	// InsertOfOPTree(tree1, arr2, 10, tempv);
	// tempv.real = 1;
	//InsertOfOPTree(tree2, arr7, 4, tempv);
	InsertOfOPTree(tree2, arr5, 6, tempv);
	pOPTree tree3;
	//MultiplyOfOPTree_TT(tree1, tree2, &tree3);
	_DeleteAndCE(tree2, 1);
	

	PrintOPTree(tree2);
	printf("%lf", tree2->root->value.real);
	
	//*/
	/*
	pOPTree tree;
	MONormalize(arr12, 5, &tree);
	PrintOPTree(tree);
	//*/

	/*
	pPTree posTree = NULL;
	CreatePTree(3, &posTree);
	InsertOfPTree(posTree, arr3, 2, 1);
	//InsertOfPTree(posTree, arr5, 3, 1);
	InsertOfPTree(posTree, arr6, 2, -1);
	pOPTree tree;
	BuildFromPTree(posTree, arr5, 3, &tree);

	PrintOPTree(tree);
	*/
	
	/*
	pOPTree tempTree = NULL;
	//DeltaTree(5, &tempTree);
	ClusterExpansion(arr12, 3, &tempTree);

	PrintOPTree(tempTree);
	//*/

	/*
	double ans;
	int temparr[] = { 3,0,9 };
	InitialValue(arr9, 2, temparr, 3, &ans);

	printf("%lf", ans);
	*/
	
	/* Evolution()µÄ²âÊÔÓÃÀý
	pOPTree ho_output[1];
	pOPTree co_output[1];
	Evolution(ho_arrs, ho_lens_arr1, ho_coef_arr1, 1,
		co_arrs, co_lens_arr1, co_coef_arr1, 1,
		arr3, 2, 20, ho_output, co_output);

	PrintOPTree(ho_output[0]);
	//*/

	///*
	pDeriveData data = NULL;
	DeriveAssign(ho_arrs, ho_lens_arr1, ho_coef_arr1, 1,
		co_arrs, co_lens_arr1, co_coef_arr1, 1,
		init_arr1, 4, track_arrs, track_lens_arr1, 1, 10, &data);

	PrintOPTree(data->evoTrees_HO[0][0]);
	PrintOPTree(data->evoTrees_CO[0][0]);
	
	Complex* ans = NULL;
	CalEvolution(data, &ans);
	//*/



	while (1){
	

	}
	return 0;
}