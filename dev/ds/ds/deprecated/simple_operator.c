#include "simple_operator.h"
/**
 * @ �ļ���: simple_operator.c
 * @ ����: ʵ�ֵ�ģʽoperator
 * @ ����: AyajiLin
 * @ ����: 493987054@qq.com
 * @ github: https://github.com/leonardodalinky
 * @ ����: 2020��1��20��
 *
 */

int InitSimpleOperator(SimpleOperator* so, int dagger, int normal) {
	so->dagger = dagger;
	so->normal = normal;
	return 1;
}
