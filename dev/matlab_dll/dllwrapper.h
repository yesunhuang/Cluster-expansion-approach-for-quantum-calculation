/**
 * @ 文件名: dllwrapper.h
 * @ 功能: 封装为dll
 * @ 作者: AyajiLin
 * @ 邮箱: 493987054@qq.com
 * @ github: https://github.com/leonardodalinky
 * @ 日期: 2020年2月24日
 *
 */

#ifdef DSDLL_EXPORTS   //定义在 工程->属性->c/c++ 预处理器定义 为工程宏定义
#define DSDLL_API __declspec(dllexport) //在dll项目中 为dllexport
#else
#define DSDLL_API __declspec(dllimport)  //在使用该dll的项目中为 dllimport
#endif


#define MPTR_TO(mptr, type) ((type)(mptr))

typedef unsigned long long M_DATAPOINTER;

#include <stdlib.h>
#include "solver.h"
#include "dllheader.h"

#ifdef __cplusplus
extern "C" {
#endif
	DSDLL_API int cedll_CalEvolution(M_DATAPOINTER dataPtr, double* outputArr);
	/* 将二维转为一维数组的操作 */
	DSDLL_API M_DATAPOINTER cedll_DeriveAssign(int* ho_arr, double* ho_coef, int* ho_size_arr, int ho_size, int* co_arr, double* co_coef, int* co_size_arr, int co_size, int* track_arr, int* track_size_arr, int track_size, int maxOPLen);

	DSDLL_API int cedll_Destroy(M_DATAPOINTER dataPtr);

	DSDLL_API int cedll_GetCurrentValue(M_DATAPOINTER dataPtr, double* outputArr, int arrSize);
	DSDLL_API int cedll_GetHamiltonCoef(M_DATAPOINTER dataPtr, double* outputArr, int arrSize);
	DSDLL_API int cedll_GetCollapseCoef(M_DATAPOINTER dataPtr, double* outputArr, int arrSize);
	DSDLL_API int cedll_GetTrackingTreeSize(M_DATAPOINTER dataPtr);

	DSDLL_API int cedll_SetCurrentValue(M_DATAPOINTER dataPtr, double* inputArr, int arrSize);
	DSDLL_API int cedll_SetHamiltonCoef(M_DATAPOINTER dataPtr, double* inputArr, int arrSize);
	DSDLL_API int cedll_SetCollapseCoef(M_DATAPOINTER dataPtr, double* inputArr, int arrSize);

	DSDLL_API int cedll_UpdateInitialValue(M_DATAPOINTER dataPtr, int* init_arr, int arrSize);

#ifdef __cplusplus
}
#endif