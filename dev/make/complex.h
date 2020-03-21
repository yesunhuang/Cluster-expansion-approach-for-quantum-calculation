/**
 * @ 文件名: complex.h
 * @ 功能: 声明复数的功能
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 2020年2月1日
 *
 */
#pragma once
#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#pragma region 头文件区
#include <gmp.h>
#include <stdlib.h>
#pragma endregion

#pragma region 宏定义区
//#define NULL ((void*)0)
#define SQUARE(x) ((x) * (x))
#define ABS(x) ((x < 0)? -x : x )

#define FLOAT_PRECISION 256

#define EPISILON ((double)10e-10)
#pragma endregion

#pragma region 结构体及typedef定义区
/* 复数域扩展 */
typedef struct _Complexmy {
	mpf_t real;
	mpf_t image;
} Complex;
#pragma endregion

#pragma region 函数声明区
int InitOfComplex(Complex* c);
int InitOfComplexs(Complex* c, int arrSize);
int InitOfComplexD(Complex* c, double real, double image);
int ClearOfComplex(Complex* c);
int ClearOfComplexs(Complex* c, int arrSize);
int FreeOfComplex(Complex* c);
int FreeOfComplexs(Complex* c, int arrSize);
int AssignOfComplex(Complex* c, Complex* src);

int SetRealOfComplex(Complex* c, double real);
int SetImageOfComplex(Complex* c, double image);
int SetOfComplex(Complex* c, double real, double image);
int GetRealOfComplex(Complex* c, double* real);
int GetImageOfComplex(Complex* c, double* image);

int AddOfComplex(Complex* c1, Complex* c2, Complex* out);
int SubtractOfComplex(Complex* c1, Complex* c2, Complex* out);
int MultiplyOfComplex(Complex* c1, Complex* c2, Complex* out);
int DivideOfComplex(Complex* c1, Complex* c2, Complex* out);
int NegateOfComplex(Complex* c, Complex* out);

int IncOfComplex(Complex* c);
int DecOfComplex(Complex* c);
int SetZeroOfComplex(Complex* c);
int IsZeroOfComplex(Complex* c);
#pragma endregion

#endif // !_COMPLEX_H_
