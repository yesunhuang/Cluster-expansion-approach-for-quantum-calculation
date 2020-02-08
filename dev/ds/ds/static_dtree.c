/**
 * @ 文件名: static_dtree.c
 * @ 功能: delta树的静态存储
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 2020年2月9日
 *
 */
#include "static_dtree.h"

pOPTree g_StanamicDTrees[STANAMIC_DTREE_SIZE];

int g_StaticDTreesIndexList[STATIC_DTREE_SIZE] = { 0,0,0,0,0 };
/* TODO: 添加前五棵树的静态数组 */
UINT_L g_StaticDTreesList[] = {};