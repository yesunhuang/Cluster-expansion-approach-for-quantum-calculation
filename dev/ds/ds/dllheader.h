/**
 * @ 文件名: dllheader.h
 * @ 功能: 用于导入函数
 * @ 作者: AyajiLin
 * @ 邮箱: 493987054@qq.com
 * @ github: https://github.com/leonardodalinky
 * @ 日期: 2020年2月25日
 *
 */
#pragma once
#ifndef _DLLHEADER_H_
#define _DLLHEADER_H_


typedef unsigned long long M_DATAPOINTER;

typedef int(*p_cedll_CalEvolution)(M_DATAPOINTER dataPtr, double* outputArr);
// 将ho_arr化为一维数组,并用ho_size_arr储存每个算符的长度
typedef M_DATAPOINTER(*p_cedll_DeriveAssign)(int* ho_arr, double* ho_coef, int* ho_size_arr, int ho_size, int* co_arr, double* co_coef, int* co_size_arr, int co_size, int* track_arr, int* track_size_arr, int track_size, int maxOPLen);

typedef int(*p_cedll_Destroy)(M_DATAPOINTER dataPtr);

typedef int(*p_cedll_GetCurrentValue)(M_DATAPOINTER dataPtr, double* outputArr, int arrSize);
typedef int(*p_cedll_GetHamiltonCoef)(M_DATAPOINTER dataPtr, double* outputArr, int arrSize);
typedef int(*p_cedll_GetCollapseCoef)(M_DATAPOINTER dataPtr, double* outputArr, int arrSize);
typedef int(*p_cedll_GetTrackingTreeSize)(M_DATAPOINTER dataPtr);
		   	 
typedef int(*p_cedll_SetCurrentValue)(M_DATAPOINTER dataPtr, double* inputArr, int arrSize);
typedef int(*p_cedll_SetHamiltonCoef)(M_DATAPOINTER dataPtr, double* inputArr, int arrSize);
typedef int(*p_cedll_SetCollapseCoef)(M_DATAPOINTER dataPtr, double* inputArr, int arrSize);
		   	 
typedef int(*p_cedll_UpdateInitialValue)(M_DATAPOINTER dataPtr, int* init_arr, int arrSize);

#endif // !_DLLHEADER_H_
