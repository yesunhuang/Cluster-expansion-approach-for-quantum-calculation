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

#pragma endregion

#pragma region 宏定义区
#define NULL ((void*)0)
#define SQUARE(x) ((x) * (x))
#define ABS(x) ((x < 0)? -x : x )

#define EPISILON ((double)10e-10)
#pragma endregion

#pragma region 结构体及typedef定义区
/* 复数域扩展 */
typedef struct _Complex {
	long double real;
	long double image;
} Complex;
#pragma endregion

#pragma region 函数声明区
int AddOfComplex(Complex c1, Complex c2, Complex* out);
int SubtractOfComplex(Complex c1, Complex c2, Complex* out);
int MultiplyOfComplex(Complex c1, Complex c2, Complex* out);
int DivideOfComplex(Complex c1, Complex c2, Complex* out);
int NegateOfComplex(Complex c, Complex* out);

int IsZeroOfComplex(Complex c);
#pragma endregion

#endif // !_COMPLEX_H_
