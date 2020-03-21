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

int InitOfComplex(Complex* c) {
	mpf_init2(c->real, FLOAT_PRECISION);
	mpf_init2(c->image, FLOAT_PRECISION);
	return 1;
}

int InitOfComplexs(Complex* c, int arrSize) {
	for (int i = 0;i < arrSize;++i){
		InitOfComplex(c + i);
	}
	return 1;
}

int InitOfComplexD(Complex* c, double real, double image) {
	mpf_init2(c->real, FLOAT_PRECISION);
	mpf_init2(c->image, FLOAT_PRECISION);
	mpf_set_d(c->real, real);
	mpf_set_d(c->image, image);
	return 1;
}

int ClearOfComplex(Complex* c) {
	mpf_clear(c->real);
	mpf_clear(c->image);
}

int ClearOfComplexs(Complex* c, int arrSize) {
	for (int i = 0;i < arrSize;++i){
		mpf_clear((c + i)->real);
		mpf_clear((c + i)->image);
	}
}

int FreeOfComplex(Complex* c) {
	mpf_clear(c->real);
	mpf_clear(c->image);
	free(c);
}

int FreeOfComplexs(Complex* c, int arrSize) {
	for (int i = 0;i < arrSize;++i){
		mpf_clear((c + i)->real);
		mpf_clear((c + i)->image);
	}
	free(c);
}

int AssignOfComplex(Complex* c, Complex* src) {
	mpf_set(c->real, src->real);
	mpf_set(c->image, src->image);
	return 1;
}

int SetRealOfComplex(Complex* c, double real) {
	mpf_set_d(c->real, real);
	return 1;
}

int SetImageOfComplex(Complex* c, double image) {
	mpf_set_d(c->image, image);
	return 1;
}

int SetOfComplex(Complex* c, double real, double image) {
	mpf_set_d(c->real, real);
	mpf_set_d(c->image, image);
	return 1;
}

int GetRealOfComplex(Complex* c, double* pnum) {
	if (pnum != NULL)
		*pnum = mpf_get_d(c->real);
	return 1;
}

int GetImageOfComplex(Complex* c, double* pnum) {
	if (pnum != NULL)
		*pnum = mpf_get_d(c->image);
	return 1;
}

int AddOfComplex(Complex* c1, Complex* c2, Complex* out) {
	if (out == NULL) return 0;
	mpf_add(out->real, c1->real, c2->real);
	mpf_add(out->image, c1->image, c2->image);
	return 1;
}

int SubtractOfComplex(Complex* c1, Complex* c2, Complex* out) {
	if (out == NULL) return 0;
	mpf_sub(out->real, c1->real, c2->real);
	mpf_sub(out->image, c1->image, c2->image);
	return 1;
}

int MultiplyOfComplex(Complex* c1, Complex* c2, Complex* out) {
	if (out == NULL) return 0;
	mpf_t tmp1, tmp2;
	mpf_inits(tmp1, tmp2, NULL);
	mpf_mul(tmp1, c1->real, c2->real);
	mpf_mul(tmp2, c1->image, c2->image);
	mpf_sub(out->real, tmp1, tmp2);
	mpf_mul(tmp1, c1->real, c2->image);
	mpf_mul(tmp2, c1->image, c2->real);
	mpf_add(out->image, tmp1, tmp2);

	mpf_clear(tmp1);
	mpf_clear(tmp2);
	return 1;
}

int DivideOfComplex(Complex* c1, Complex* c2, Complex* out) {
	if (out == NULL) return 0;
	else if (mpf_cmp_d(c2->real, 0) == 0 && mpf_cmp_d(c2->image, 0) == 0) return 0;
	mpf_t tmp1, tmp2;
	mpf_mul(tmp1, c2->real, c2->real);
	mpf_mul(tmp2, c2->image, c2->image);
	mpf_t temp;
	mpf_add(temp, tmp1, tmp2);
	mpf_ui_div(temp, 1, temp);

	mpf_mul(tmp1, c1->real, c2->real);
	mpf_mul(tmp2, c1->image, c2->image);
	mpf_add(tmp1, tmp1, tmp2);
	mpf_mul(out->real, tmp1, temp);

	mpf_mul(tmp1, c1->image, c2->real);
	mpf_mul(tmp2, c1->real, c2->image);
	mpf_sub(tmp1, tmp1, tmp2);
	mpf_mul(out->image, tmp1, temp);

	mpf_clear(tmp1);
	mpf_clear(tmp2);
	mpf_clear(temp);
	return 1;
}

int NegateOfComplex(Complex* c, Complex* out) {
	if (out == NULL) return 0;
	mpf_neg(out->real, c->real);
	mpf_neg(out->image, c->image);
	return 1;
}

int IncOfComplex(Complex* c) {
	mpf_add_ui(c->real, c->real, 1);
	return 1;
}

int DecOfComplex(Complex* c) {
	mpf_sub_ui(c->real, c->real, 1);
	return 1;
}

int SetZeroOfComplex(Complex* c) {
	mpf_set_d(c->real, 0);
	mpf_set_d(c->image, 0);
	return 1;
}

int IsZeroOfComplex(Complex* c) {
	return (mpf_cmp_d(c->real, EPISILON) < 0 && mpf_cmp_d(c->image, EPISILON) < 0) ? 1 : 0;
}
