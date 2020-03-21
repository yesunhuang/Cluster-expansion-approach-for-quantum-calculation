
#include "dllwrapper.h"
/**
 * @ 文件名: dllwrapper.c
 * @ 功能: 封装为dll
 * @ 作者: AyajiLin
 * @ 邮箱: 493987054@qq.com
 * @ github: https://github.com/leonardodalinky
 * @ 日期: 2020年2月24日
 *
 */

int cedll_CalEvolution(M_DATAPOINTER dataPtr, double* outputArr)
{
	Complex* output = NULL;
	pDeriveData data = MPTR_TO(dataPtr, pDeriveData);

	CalEvolution(data, &output);
	for (int i = 0; i < data->size; ++i) {
		GetRealOfComplex(&output[i], &outputArr[i]);
	}
	for (int i = 0; i < data->size; ++i) {
		GetImageOfComplex(&output[i], &outputArr[i]);
	}
	free(output);
	return 1;
}

M_DATAPOINTER cedll_DeriveAssign(int* ho_arr, double* ho_coef, int* ho_size_arr, int ho_size, int* co_arr, double* co_coef, int* co_size_arr, int co_size, int* track_arr, int* track_size_arr, int track_size, int maxOPLen)
{
	pOPArray* inputArr_HO; int* inputArrLens_HO; Complex* inputArrCoef_HO; int inputArrLen_HO;
	pOPArray* inputArr_CO; int* inputArrLens_CO; Complex* inputArrCoef_CO; int inputArrLen_CO;
	int* inputArr_Init; int inputArrLen_Init;
	pOPArray* inputArr_Track; int* inputArrLens_Track; int inputArrLen_Track;

	// [Initial状态]
	inputArrLen_Init = 128;
	inputArr_Init = (int*)malloc(inputArrLen_Init * sizeof(int)); ASSERTNULL(inputArr_Init);
	memset(inputArr_Init, 0, inputArrLen_Init * sizeof(int));

	// [Hamiton算符...], [Hamilton算符系数...]
	inputArrLen_HO = ho_size;
	inputArr_HO = (pOPArray*)malloc(inputArrLen_HO * sizeof(pOPArray)); ASSERTNULL(inputArr_HO);
	inputArrLens_HO = (int*)malloc(inputArrLen_HO * sizeof(int)); ASSERTNULL(inputArrLens_HO);
	int indexSum = 0;
	for (int i = 0; i < inputArrLen_HO; ++i) {
		inputArrLens_HO[i] = ho_size_arr[i];
		inputArr_HO[i] = (pOPArray)malloc(inputArrLens_HO[i] * sizeof(UINT_L)); ASSERTNULL(inputArr_HO[i]);
		for (int j = 0; j < inputArrLens_HO[i]; ++j) {
			inputArr_HO[i][j] = ho_arr[indexSum + j];
		}
		indexSum += inputArrLens_HO[i];
	}
	inputArrCoef_HO = (Complex*)malloc(inputArrLen_HO * sizeof(Complex)); ASSERTNULL(inputArrCoef_HO);
	memset(inputArrCoef_HO, 0, inputArrLen_HO * sizeof(Complex));
	for (int i = 0; i < inputArrLen_HO; ++i) {
		SetRealOfComplex(&inputArrCoef_HO[i], ho_coef[i]);
		SetImageOfComplex(&inputArrCoef_HO[i], ho_coef[i + ho_size]);
	}

	// [Collapse算符...], [Collapse算符系数...]
	inputArrLen_CO = co_size;
	inputArr_CO = (pOPArray*)malloc(inputArrLen_CO * sizeof(pOPArray)); ASSERTNULL(inputArr_CO);
	inputArrLens_CO = (int*)malloc(inputArrLen_CO * sizeof(int)); ASSERTNULL(inputArrLens_CO);
	indexSum = 0;
	for (int i = 0; i < inputArrLen_CO; ++i) {
		inputArrLens_CO[i] = co_size_arr[i];
		inputArr_CO[i] = (pOPArray)malloc(inputArrLens_CO[i] * sizeof(UINT_L)); ASSERTNULL(inputArr_CO[i]);
		for (int j = 0; j < inputArrLens_CO[i]; ++j) {
			inputArr_CO[i][j] = co_arr[indexSum + j];
		}
		indexSum += inputArrLens_CO[i];
	}
	inputArrCoef_CO = (Complex*)malloc(inputArrLen_CO * sizeof(Complex)); ASSERTNULL(inputArrCoef_CO);
	memset(inputArrCoef_CO, 0, inputArrLen_CO * sizeof(Complex));
	for (int i = 0; i < inputArrLen_CO; ++i) {
		SetRealOfComplex(&inputArrCoef_CO[i], co_coef[i]);
		SetImageOfComplex(&inputArrCoef_CO[i], co_coef[i + co_size]);
	}

	// [Tracking算符...]
	inputArrLen_Track = track_size;
	inputArr_Track = (pOPArray*)malloc(inputArrLen_Track * sizeof(pOPArray)); ASSERTNULL(inputArr_Track);
	inputArrLens_Track = (int*)malloc(inputArrLen_Track * sizeof(int)); ASSERTNULL(inputArrLens_Track);
	indexSum = 0;
	for (int i = 0; i < inputArrLen_Track; ++i) {
		inputArrLens_Track[i] = track_size_arr[i];
		inputArr_Track[i] = (pOPArray)malloc(inputArrLens_Track[i] * sizeof(UINT_L)); ASSERTNULL(inputArr_Track[i]);
		for (int j = 0; j < inputArrLens_Track[i]; ++j) {
			inputArr_Track[i][j] = track_arr[indexSum + j];
		}
		indexSum += inputArrLens_Track[i];
	}

	// 生成data
	pDeriveData data = NULL;
	DeriveAssign(inputArr_HO, inputArrLens_HO, inputArrCoef_HO, inputArrLen_HO,
		inputArr_CO, inputArrLens_CO, inputArrCoef_CO, inputArrLen_CO,
		inputArr_Init, inputArrLen_Init, inputArr_Track, inputArrLens_Track, inputArrLen_Track, maxOPLen, &data);

	// 释放申请的内存
	for (int i = 0; i < inputArrLen_HO; ++i) {
		free(inputArr_HO[i]);
	}
	free(inputArrLens_HO);
	free(inputArrCoef_HO);
	for (int i = 0; i < inputArrLen_CO; ++i) {
		free(inputArr_CO[i]);
	}
	free(inputArrLens_CO);
	free(inputArrCoef_CO);
	free(inputArr_Init);
	for (int i = 0; i < inputArrLen_Track; ++i) {
		free(inputArr_Track[i]);
	}
	free(inputArrLens_Track);

	return (M_DATAPOINTER)data;
}


int cedll_Destroy(M_DATAPOINTER dataPtr)
{
	FreeOfDData(MPTR_TO(dataPtr, pDeriveData));
	return 1;
}

int cedll_GetCurrentValue(M_DATAPOINTER dataPtr, double* outputArr, int arrSize)
{
	pDeriveData data = MPTR_TO(dataPtr, pDeriveData);
	for (int i = 0; i < MIN(arrSize, data->size); ++i) {
		GetRealOfComplex(&data->curValues[i], &outputArr[i]);
	}
	for (int i = data->size; i < MIN(arrSize, 2 * data->size); ++i) {
		GetImageOfComplex(&data->curValues[i - data->size], &outputArr[i]);
	}
	return 1;
}

int cedll_GetHamiltonCoef(M_DATAPOINTER dataPtr, double* outputArr, int arrSize)
{
	pDeriveData data = MPTR_TO(dataPtr, pDeriveData);
	for (int i = 0; i < MIN(arrSize, data->hoSize); ++i) {
		GetRealOfComplex(&data->hoCoefs[i], &outputArr[i]);
	}
	for (int i = data->hoSize; i < MIN(arrSize, 2 * data->hoSize); ++i) {
		GetImageOfComplex(&data->hoCoefs[i - data->hoSize], &outputArr[i]);
	}
	return 1;
}

int cedll_GetCollapseCoef(M_DATAPOINTER dataPtr, double* outputArr, int arrSize)
{
	pDeriveData data = MPTR_TO(dataPtr, pDeriveData);
	mpf_t tmp;
	for (int i = 0; i < MIN(arrSize, data->coSize); ++i) {
		mpf_mul_ui(tmp, data->coCoefs[i].real, 2);
		outputArr[i] = mpf_get_d(tmp);
	}
	for (int i = data->coSize; i < MIN(arrSize, 2 * data->coSize); ++i) {
		mpf_mul_ui(tmp, data->coCoefs[i - data->coSize].image, 2);
		outputArr[i] = mpf_get_d(tmp);
	}
	mpf_clear(tmp);
	return 1;
}

int cedll_GetTrackingTreeSize(M_DATAPOINTER dataPtr)
{
	pDeriveData data = MPTR_TO(dataPtr, pDeriveData);
	return data->size;
}

int cedll_SetCurrentValue(M_DATAPOINTER dataPtr, double* inputArr, int arrSize)
{
	pDeriveData data = MPTR_TO(dataPtr, pDeriveData);
	Complex* temp = (Complex*)malloc(sizeof(Complex) * data->size); ASSERTNULL(temp);
	InitOfComplexs(temp, data->size);

	for (int i = 0; i < (arrSize / 2); ++i) {
		SetRealOfComplex(&temp[i], inputArr[i]);
	}
	for (int i = (arrSize / 2); i < arrSize; ++i) {
		SetImageOfComplex(&temp[i - (arrSize / 2)], inputArr[i]);
	}
	SetCurrentValueOfDData(data, temp, data->size);
	FreeOfComplexs(temp, data->size);
	return 1;
}

int cedll_SetHamiltonCoef(M_DATAPOINTER dataPtr, double* inputArr, int arrSize)
{
	pDeriveData data = MPTR_TO(dataPtr, pDeriveData);
	Complex* temp = (Complex*)malloc(sizeof(Complex) * data->hoSize); ASSERTNULL(temp);
	InitOfComplexs(temp, data->hoSize);

	for (int i = 0; i < MIN(arrSize, data->hoSize); ++i) {
		SetRealOfComplex(&temp[i], inputArr[i]);
	}
	for (int i = data->hoSize; i < MIN(arrSize, 2 * data->hoSize); ++i) {
		SetImageOfComplex(&temp[i - data->hoSize], inputArr[i]);
	}
	SetHOCoefOfDData(data, temp, data->hoSize);
	FreeOfComplexs(temp, data->hoSize);
	return 1;
}

int cedll_SetCollapseCoef(M_DATAPOINTER dataPtr, double* inputArr, int arrSize)
{
	pDeriveData data = MPTR_TO(dataPtr, pDeriveData);
	Complex* temp = (Complex*)malloc(sizeof(Complex) * data->coSize); ASSERTNULL(temp);
	InitOfComplexs(temp, data->coSize);

	for (int i = 0; i < MIN(arrSize, data->coSize); ++i) {
		SetRealOfComplex(&temp[i], inputArr[i]);
	}
	for (int i = data->coSize; i < MIN(arrSize, 2 * data->coSize); ++i) {
		SetImageOfComplex(&temp[i - data->coSize], inputArr[i]);
	}
	SetCOCoefOfDData(data, temp, data->coSize);
	FreeOfComplexs(temp, data->coSize);
	return 1;
}

int cedll_UpdateInitialValue(M_DATAPOINTER dataPtr, int* init_arr, int arrSize)
{
	pDeriveData data = MPTR_TO(dataPtr, pDeriveData);
	UINT_L trackBuf[MAX_OPERATOR_LENGTH];
	Complex* ans = (Complex*)malloc(data->size * sizeof(Complex)); ASSERTNULL(ans);
	InitOfComplexs(ans, data->size);
	for (int i = 0; i < data->size; ++i) {
		pOPNode nowTrack = data->trackNodes[i];
		int nowArrLen = GetRoot(data->trackNodes[i], NULL);
		ArrayFromNode(nowTrack, nowArrLen, trackBuf);
		double temp;
		InitialValue(trackBuf, nowArrLen, init_arr, arrSize, &temp);
		SetRealOfComplex(&ans[i], temp);
	}
	SetCurrentValueOfDData(data, ans, data->size);
	FreeOfComplexs(ans, data->size);
	return 0;
}
