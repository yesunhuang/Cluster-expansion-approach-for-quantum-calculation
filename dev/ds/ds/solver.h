/**
 * @ 文件名: solver.h
 * @ 功能: 声明有关solver的功能
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 2020年2月1日
 *
 */
#pragma once
#ifndef _SOLVER_H_
#define _SOLVER_H_

#pragma region 头文件区
#include "operator_tree.h"
#include "normalizer.h"
#include "cluster_expansion.h"
#pragma endregion

#pragma region 宏定义区

#define ASSERTNULL(x) do{ if ((x) == NULL){ return 0; } }while(0)

#pragma endregion

#pragma region 结构体及typedef定义区
struct _DeriveData {
	int size;
	int capacity;
	int hoSize;
	int coSize;
	pOPTree trackTree;
	Complex* curValues;
	pOPTree** evoTrees_HO;
	pOPTree** evoTrees_CO;
	pOPNode* trackNodes;
};
typedef struct _DeriveData DeriveData;
typedef DeriveData* pDeriveData;
#pragma endregion

#pragma region 结构体函数声明区

int CreateOfDData(int capacity, int csize, int hoSize, int coSize, pDeriveData* outputpp);

int InsertOfDData(pDeriveData data, Complex c, pOPArray arr, int arrLen);

int FreeOfDData(pDeriveData data);

int ReserveOfDData(pDeriveData data, int newCap);
#pragma endregion

#pragma region 函数声明区

/**
 * @ 函数: int InitialValue(pOPArray arr, int len, int* sArr, int sArrLen, double* output)
 *
 * @ 功能: 对应第四章的InitialValue操作。默认输入为合法。
 *
 * @ 说明: sArr[0]对应{1,2}的初值,sArr[1]对应{3,4}的初值......以此类推.
 *
 * @ param{arr}: operator数组表达
 *
 * @ param{len}: operator数组表达长度
 *
 * @ param{sArr}: 初态数组
 *
 * @ param{sArrLen}: 初态数组长度
 *
 * @ param{output}: 栈顶的第一个空闲空间的索引号
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int InitialValue(pOPArray arr, int len, int* sArr, int sArrLen, double* output);

/**
 * @ 函数: int _Evolution_HO(pOPArray* inputArr, int* intputArrCoef, int inputArrLen, pOPArray userArr, int userArrLen,
	pOPTree* ho_outputArr)
 *
 * @ 功能: 对应第四章的Evolution操作。
 *
 * @ 说明: 默认输入为合法。输出的数组需要拥有足够的空间(不小于inputArrLen个pOPTree元素的空间).
 *
 * @ param{inputArr_HO}: 用户输入的hamilton operator的列表
 *
 * @ param{inputArrLen_HO}: 用户输入的hamilton operator的列表的各个项的长度
 *
 * @ param{intputArrCoef_HO}: 用户输入的hamilton operator的列表对应的系数
 *
 * @ param{inputArrLen_HO}: 用户输入的hamilton operator的列表的系数
 *
 * @ param{inputArr_CO}: 用户输入的hamilton operator的列表
 *
 * @ param{inputArrLen_CO}: 用户输入的hamilton operator的列表的各个项的长度
 *
 * @ param{intputArrCoef_CO}: 用户输入的hamilton operator的列表对应的系数
 *
 * @ param{inputArrLen_CO}: 用户输入的hamilton operator的列表的系数
 *
 * @ param{userArr}: 用户特定的op
 *
 * @ param{maxOPLen}: 最大operator长度
 *
 * @ param{userArrLen}: 用户特定的op的长度
 *
 * @ param{ho_outputArr}: 输出的ho树数组,需要拥有足够的空间
 *
 * @ param{co_outputArr}: 输出的co树数组,需要拥有足够的空间
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int Evolution(pOPArray* inputArr_HO, int* inputArrLens_HO, Complex* inputArrCoef_HO, int inputArrLen_HO, 
	pOPArray* inputArr_CO, int* inputArrLens_CO, Complex* inputArrCoef_CO, int inputArrLen_CO,
	pOPArray userArr, int userArrLen, int maxOPLen, pOPTree* ho_outputArr, pOPTree* co_outputArr);

/**
 * @ 函数: int DeriveAssign(..., pDeriveData* outputpp)
 *
 * @ 功能: 对应第四章中的Derive And Assign过程
 *
 * @ param{outputpp}: 生成一个新的data, 内存交由调用者管理
 *
 * @ 返回值: 若成功时,返回值为1; 否则,返回值为0.
 */
int DeriveAssign(int* sArr, int sArrLen,
	pOPArray* inputArr_HO, int* inputArrLens_HO, Complex* inputArrCoef_HO, int inputArrLen_HO,
	pOPArray* inputArr_CO, int* inputArrLens_CO, Complex* inputArrCoef_CO, int inputArrLen_CO,
	pOPArray inputArr_Init, int inputArrLen_Init,
	pOPArray* inputArr_Track, int* inputArrLens_Track, int inputArrLen_Track,
	int maxOPLen,
	pDeriveData* outputpp);

/**
 * @ 函数: int CalEvolution(pDeriveData data, Complex** outputpp)
 *
 * @ 功能: 对应第四章中的Calculate Evolution过程
 *
 * @ param{data}: 生成一个新的data, 内存交由调用者管理
 *
 * @ param{outputpp}: 生成一个新的data, 内存交由调用者管理
 *
 * @ 返回值: 若成功时,返回值为1; 否则,返回值为0.
 */
int CalEvolution(pDeriveData data, Complex** outputpp);

int SetCurrentValueOfDData(pDeriveData data, Complex* arr, int len);

int _CalEvo(pOPTree evoTree, pDeriveData data, Complex* psum);

int __CalEvo(pOPNode node, pOPTree tree, pDeriveData data, UINT_L* buf, int nextIndex, Complex* psum);

/**
 * @ 函数: int _DeleteAndCE(pOPTree tree, int maxOPLen)
 *
 * @ 功能: 删除树中第一个遇到的长度大于maxOPLen的operator
 *
 * @ param{tree}: operator tree
 *
 * @ param{maxOPLen}: operator最大长度
 *
 * @ 返回值: 若存在删除并成功时,返回值为1; 否则,返回值为0.
 */
int _DeleteAndCE(pOPTree tree, int maxOPLen);

/**
 * @ 函数: int _DeleteAndCE_(pOPNode node, int maxOPLen, int nextLen)
 *
 * @ 功能: 删除树中第一个遇到的长度大于maxOPLen的operator
 *
 * @ param{node}: operator tree
 *
 * @ param{csize}: csize
 *
 * @ param{maxOPLen}: operator最大长度
 *
 * @ param{nextLen}: 下一个被调用的operator长度
 *
 * @ 返回值: 若存在删除并成功时,返回值为1; 否则,返回值为0.
 */
int _DeleteAndCE_(pOPNode node, pOPTree tree, int maxOPLen, int nextLen);

/**
 * @ 函数: int _DeriveAT(pOPTree evoTree, pDeriveData data)
 *
 * @ 功能: 拆分树中的single operator,并加入data
 *
 * @ param{evoTree}: 待拆分的evolution树
 *
 * @ param{data}: 类型为pDeriveData
 *
 * @ 返回值: 若存在删除并成功时,返回值为1; 否则,返回值为0.
 */
int _DeriveAT(pOPTree evoTree, pOPArray inputArr_Init, int inputArrLen_Init, pDeriveData data);

/**
 * @ 函数: int __DeriveAT(pOPTree evoTree, pDeriveData data)
 *
 * @ 功能: 拆分树中的single operator,并加入data
 *
 * @ param{evoTree}: 待拆分的evolution树
 *
 * @ param{data}: 类型为pDeriveData
 *
 * @ 返回值: 若存在删除并成功时,返回值为1; 否则,返回值为0.
 */
int __DeriveAT(pOPNode node, int csize, pOPArray inputArr_Init, int inputArrLen_Init, pDeriveData data, 
	UINT_L* buf, int nextIndex);

/**
 * @ 函数: int _Evolution_HO(pOPArray* inputArr, int* intputArrCoef, int inputArrLen, pOPArray userArr, int userArrLen,
	pOPTree* ho_outputArr)
 *
 * @ 功能: 对应第四章的Evolution操作。
 *
 * @ 说明: 默认输入为合法。输出的数组需要拥有足够的空间(不小于inputArrLen个pOPTree元素的空间).
 *
 * @ param{inputArr}: 用户输入的hamilton operator的列表
 *
 * @ param{inputArrLen}: 用户输入的hamilton operator的列表的各个项的长度
 *
 * @ param{intputArrCoef}: 用户输入的hamilton operator的列表对应的系数
 *
 * @ param{inputArrLen}: 用户输入的hamilton operator的列表的系数
 *
 * @ param{userArr}: 用户特定的op
 *
 * @ param{userArrLen}: 用户特定的op的长度
 *
 * @ param{ho_outputArr}: 输出的ho树数组,需要拥有足够的空间
 *
 * @ param{co_outputArr}: 输出的co树数组,需要拥有足够的空间
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _Evolution_HO(pOPArray* inputArr, int* inputArrLens, Complex* inputArrCoef,
 int inputArrLen, pOPArray userArr, int userArrLen, int maxOPLen, pOPTree* ho_outputArr);

/**
 * @ 函数: int _Evolution_CO(pOPArray* inputArr, int* intputArrCoef, int inputArrLen, pOPArray userArr, int userArrLen,
	pOPTree* co_outputArr)
 *
 * @ 功能: 对应第四章的Evolution操作。
 *
 * @ 说明: 默认输入为合法。输出的数组需要拥有足够的空间(不小于inputArrLen个pOPTree元素的空间).
 *
 * @ param{inputArr}: 用户输入的hamilton operator的列表
 *
 * @ param{inputArrLen}: 用户输入的hamilton operator的列表的各个项的长度
 *
 * @ param{intputArrCoef}: 用户输入的hamilton operator的列表对应的系数
 *
 * @ param{inputArrLen}: 用户输入的hamilton operator的列表的系数
 *
 * @ param{userArr}: 用户特定的op
 *
 * @ param{userArrLen}: 用户特定的op的长度
 *
 * @ param{co_outputArr}: 输出的co树数组,需要拥有足够的空间
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _Evolution_CO(pOPArray* inputArr, int* inputArrLens, Complex* inputArrCoef,
	int inputArrLen, pOPArray userArr, int userArrLen, int maxOPLen, pOPTree* co_outputArr);

/**
 * @ 函数: int _MultiplyNodeWithComplex(pOPNode node, void* sth)
 *
 * @ 功能: 将每个结点的value乘某个复数
 *
 * @ param{node}: 结点
 *
 * @ param{sth}: 某个复数的地址
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _MultiplyNodeWithComplex(pOPNode node, void* sth);


/**
 * @ 函数: int _NegateNode(pOPNode node, void* sth)
 *
 * @ 功能: 将每个结点的value取反
 *
 * @ 说明: sth函数传入值无效(可为NULL)
 *
 * @ param{node}: 结点
 *
 * @ param{sth}: 无效
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _NegateNode(pOPNode node, void* sth);

/**
 * @ 函数: int _UpdateDDTTreeValue(pDeriveData data)
 *
 * @ 功能: 把tracking tree中结点的value设为其current value
 *
 * @ param{data}: 类型为pDeriveData
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int _UpdateDDTTreeValue(pDeriveData data);

#pragma endregion
#endif // !_SOLVER_H_
