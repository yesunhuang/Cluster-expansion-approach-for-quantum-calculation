#include "normalizer.h"
#include "position_tree.h"
#include "cluster_expansion.h"
#include "solver.h"
#include "complex.h"
#include <crtdbg.h>
// #include <Python.h>

UINT_L arr1[] = { 2,4,4,0,1,3,4,6 };
UINT_L arr2[] = { 2,0,4,4,6,0,2,4,4,6 };
UINT_L arr3[] = { 1,3 };
UINT_L arr4[] = { 2,1,2,4,3 };
UINT_L arr5[] = { 3,0,3,3,0,3 };
UINT_L arr6[] = { 2, 1 };
UINT_L arr7[] = { 2,2,3,1 };
UINT_L arr8[] = { 1,1,2,2,5,5,5,6,6,6 };
UINT_L arr9[] = { 0,1 };
UINT_L arr10[] = { 1 };
UINT_L arr11[] = { 1,0,1,0,1 };
UINT_L arr12[] = { 1,1,2 };

Complex c_1 = { 0.8,0 };
Complex c_2 = { 1.6,0 };
Complex c_3 = { 0.3,0 };
Complex c_4 = { 0.3,0 };
Complex c_5 = { 0.106,0 };
Complex c_6 = { 0.106,0 };
Complex c_7 = { 2,0 };
Complex c_8 = { 4,0 };
int init_arr1[] = { 1,1 };
UINT_L ho_arr1[] = { 1,2 };
UINT_L ho_arr2[] = { 3,4 };
UINT_L ho_arr3[] = { 1,1,4 };
UINT_L ho_arr4[] = { 2,2,3 };
UINT_L ho_arr5[] = { 1 };
UINT_L ho_arr6[] = { 2 };
int ho_lens_arr1[] = { 2,2,3,3,1,1 };
Complex ho_coef_arr1[6];
pOPArray ho_arrs[6];
UINT_L co_arr1[] = { 2 };
UINT_L co_arr2[] = { 4 };
int co_lens_arr1[] = { 1,1 };
Complex co_coef_arr1[2];
pOPArray co_arrs[2];
UINT_L track_arr1[] = { 1,2 };
UINT_L track_arr2[] = { 3,4 };
int track_lens_arr1[] = { 2,2 };
pOPArray track_arrs[2];


int main() {
	ho_coef_arr1[0] = c_1;
	ho_coef_arr1[1] = c_2;
	ho_coef_arr1[2] = c_3;
	ho_coef_arr1[3] = c_4;
	ho_coef_arr1[4] = c_5;
	ho_coef_arr1[5] = c_6;
	ho_arrs[0] = ho_arr1;
	ho_arrs[1] = ho_arr2;
	ho_arrs[2] = ho_arr3;
	ho_arrs[3] = ho_arr4;
	ho_arrs[4] = ho_arr5;
	ho_arrs[5] = ho_arr6;

	co_coef_arr1[0] = c_7;
	co_coef_arr1[1] = c_8;
	co_arrs[0] = co_arr1;
	co_arrs[1] = co_arr2;

	track_arrs[0] = track_arr1;
	track_arrs[1] = track_arr2;

	pOPArray buf = (UINT_L*)malloc(sizeof(UINT_L) * 100);
	
	/*
	pOPTree tree1;
	pOPTree tree2;
	
	CreateOPTree(3, &tree1);
	// CreateOPTree(3, &tree2);
	INT_V tempv = { 1, 0 };
	InsertOfOPTree(tree1, arr11, 5, tempv);
	// tempv.real = 2;
	// InsertOfOPTree(tree1, arr2, 10, tempv);
	// tempv.real = 1;
	//InsertOfOPTree(tree2, arr7, 4, tempv);
	InsertOfOPTree(tree1, arr5, 6, tempv);
	FreeOPTree(tree1);
	pOPTree tree3;
	// CopyCreateOPTree(tree1, &tree3);
	//MultiplyOfOPTree_TT(tree1, tree2, &tree3);
	//_DeleteAndCE(tree2, 1);
	
	PrintOPTree(tree1);
	printf("%lf", tree3->root->value.real);
	
	//*/
	/*
	pOPTree tree;
	MONormalize(arr7, 4, &tree);
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
	DeltaTree(10, &tempTree);
	//ClusterExpansion(arr12, 3, &tempTree);

	// PrintOPTree(tempTree);
	//*/

	/*
	double ans;
	int temparr[] = { 3,0,9 };
	InitialValue(arr9, 2, temparr, 3, &ans);

	printf("%lf", ans);
	*/
	
	/* Evolution()的测试用例
	pOPTree ho_output[1];
	pOPTree co_output[1];
	Evolution(ho_arrs, ho_lens_arr1, ho_coef_arr1, 6,
		co_arrs, co_lens_arr1, co_coef_arr1, 2,
		track_arr1, 2, 22, ho_output, co_output);

	PrintOPTree(ho_output[0]);
	//*/

	///* CalEvolution()的测试过程
	pDeriveData data = NULL;
	DeriveAssign(ho_arrs, ho_lens_arr1, ho_coef_arr1, 6,
		co_arrs, co_lens_arr1, co_coef_arr1, 2,
		init_arr1, 2, track_arrs, track_lens_arr1, 2, 2, &data);

	//PrintOPTree(data->evoTrees_HO[0][0]);
	//PrintOPTree(data->evoTrees_CO[0][0]);
	for (int i = 0; i < data->size; ++i) {
		int len;
		len = GetRoot(data->trackNodes[i], NULL);
		ArrayFromNode(data->trackNodes[i], len, buf);
		printf("TrackNodes[%d]:{", i);
		for (int j = 0; j < len; ++j) {
			printf("%d, ", buf[j]);
		}
		printf("}\n");
	}
	for (int i = 0; i < data->hoSize; ++i) {
		printf("Tree_HO %d\n", i);
		PrintOPTree(data->evoTrees_HO[4][i]);
		putchar('\n');
	}
	for (int i = 0; i < data->coSize; ++i) {
		printf("Tree_CO %d\n", i);
		PrintOPTree(data->evoTrees_CO[4][i]);
		putchar('\n');
	}
	//PrintOPTree(data->trackTree);
	
	Complex* ans = NULL;
	CalEvolution(data, &ans);
	//*/

	/* 静态Delta树创建过程
	UINT_L output1[1024];
	int output2[1024];
	int output1_len, output2_len;
	pOPTree tree;
	DeltaTree(5, &tree);
	PrintOrderOPTree(tree, output1, output2, &output1_len, &output2_len);
	printf("Output1:\n");
	for (int i = 0; i < output1_len; ++i) {
		printf("%d, ", (int)output1[i]);
	}
	printf("\nOutput1_Len: %d\n\n", output1_len);
	printf("Output2:\n");
	for (int i = 0; i < output2_len; ++i) {
		printf("%d, ", (int)output2[i]);
	}
	printf("\nOutput2_Len: %d\n", output2_len);
	//*/

	/* 内存泄漏检验
	{
	for (int i = 0; i < 100; ++i) {
		pOPTree tempTree = NULL;
		DeltaTree(5, &tempTree);
		FreeOPTree(tempTree);
	}
	}
	
	//*/
	while (1){
	

	}
	return 0;
}