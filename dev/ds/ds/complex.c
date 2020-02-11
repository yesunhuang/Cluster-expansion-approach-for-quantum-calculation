#include "complex.h"
/**
 * @ 文件名: complex.c
 * @ 功能: 定义复数的功能
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 2020年2月1日
 *
 */

int AddOfComplex(Complex c1, Complex c2, Complex* out) {
	if (out == NULL) return 0;
	out->real = c1.real + c2.real;
	out->image = c1.image + c2.image;
	return 1;
}

int SubtractOfComplex(Complex c1, Complex c2, Complex* out) {
	if (out == NULL) return 0;
	out->real = c1.real - c2.real;
	out->image = c1.image - c2.image;
	return 1;
}

int MultiplyOfComplex(Complex c1, Complex c2, Complex* out) {
	if (out == NULL) return 0;
	out->real = c1.real * c2.real - c1.image * c2.image;
	out->image = c1.real * c2.image + c1.image * c2.real;
	return 1;
}

int DivideOfComplex(Complex c1, Complex c2, Complex* out) {
	if (out == NULL) return 0;
	else if (c2.real == 0 && c2.image == 0) return 0;
	double temp = 1.0 / (SQUARE(c2.real) + SQUARE(c2.image));
	out->real = (c1.real * c2.real + c1.image * c2.image) * temp;
	out->image = (c1.image * c2.real - c1.real * c2.image) * temp;
	return 1;
}

int NegateOfComplex(Complex c, Complex* out) {
	if (out == NULL) return 0;
	out->real = -c.real;
	out->image = -c.image;
	return 1;
}

int IsZeroOfComplex(Complex c) {
	return (ABS(c.real) < EPISILON && ABS(c.image) < EPISILON) ? 1 : 0;
}
