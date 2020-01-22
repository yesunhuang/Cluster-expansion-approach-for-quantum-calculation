// Deprecated. Yesun nmsl.
/**
 * @ 文件名: simple_operator.h
 * @ 功能: 声明单模式operator
 * @ 作者: AyajiLin
 * @ 邮箱: 493987054@qq.com
 * @ github: https://github.com/leonardodalinky
 * @ 日期: 2020年1月20日
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
