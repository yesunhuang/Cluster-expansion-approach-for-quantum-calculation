// Deprecated. Yesun nmsl.
/**
 * @ �ļ���: simple_operator.h
 * @ ����: ������ģʽoperator
 * @ ����: AyajiLin
 * @ ����: 493987054@qq.com
 * @ github: https://github.com/leonardodalinky
 * @ ����: 2020��1��20��
 *
 */
#pragma once
#ifndef _SIMPLE_OPERATOR_H_
#define _SIMPLE_OPERATOR_H_

struct _SimpleOperator {
	int dagger;
	int normal;
};

typedef struct _SimpleOperator SimpleOperator;

int InitSimpleOperator(SimpleOperator* so, int dagger, int normal);

#endif // !_SIMPLE_OPERATOR_H_
