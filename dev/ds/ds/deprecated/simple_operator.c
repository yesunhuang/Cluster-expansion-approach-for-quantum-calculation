#include "simple_operator.h"
/**
 * @ 文件名: simple_operator.c
 * @ 功能: 实现单模式operator
 * @ 作者: AyajiLin
 * @ 邮箱: 493987054@qq.com
 * @ github: https://github.com/leonardodalinky
 * @ 日期: 2020年1月20日
 *
 */

int InitSimpleOperator(SimpleOperator* so, int dagger, int normal) {
	so->dagger = dagger;
	so->normal = normal;
	return 1;
}
