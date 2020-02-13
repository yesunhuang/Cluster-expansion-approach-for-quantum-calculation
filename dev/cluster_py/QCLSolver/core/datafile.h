/**
 * @ 文件名: datafile.h
 * @ 功能: 提供data中数据存储的接口
 * @ 作者: AyajiLin
 * @ 邮箱: 493987054@qq.com
 * @ github: https://github.com/leonardodalinky
 * @ 日期: 2020年2月12日
 *
 */
#pragma once
#ifndef __DATAFILE_H__
#define __DATAFILE_H__

#pragma region 宏定义区
#define _TREESTARTID ((uint32_t)0x3a74f19d)
#define _TREEENDID ((uint32_t)0x4b74f87d)
#define _DATASTARTID ((uint32_t)0xd2743671)
#define _DATAENDID ((uint32_t)0xe5742189)
#pragma endregion

#pragma region 头文件区
#include "solver.h"
#pragma endregion

#pragma region 结构体及typedef定义区

#pragma endregion

#pragma region 函数声明区
/**
 * @ 函数: int DataFromFile(const char* filePath, pDeriveData* outputpp)
 *
 * @ 功能: 从文件指针当前的位置指针开始, 读取data. 并会移动位置指针.
 *
 * @ param{filePath}: 文件路径
 *
 * @ param{outputpp}: 生成一个新data
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int DataFromFile(const char* filePath, pDeriveData* outputpp);

/**
 * @ 函数: int32_t TreeToFile(FILE* fp, pOPTree tree)
 *
 * @ 功能: 从文件指针当前的位置指针开始, 写入一棵树. 并会移动位置指针.
 *
 * @ param{data}: 待输出的data
 *
 * @ param{filePath}: 输出文件的路径
 *
 * @ 返回值: 成功时,返回值为写入的字节数; 否则,返回值为-1.
 */
int32_t DataToFile(pDeriveData data, const char* filePath);

/**
 * @ 函数: int TreeFromFile(FILE* fp, size_t size, pOPTree* outputpp)
 *
 * @ 功能: 从文件指针当前的位置指针开始, 读取一棵树. 并会移动位置指针.
 *
 * @ param{fp}: 文件指针, 属性需可读
 *
 * @ param{size}: 树数据集的大小, 单位为字节
 *
 * @ param{outputpp}: 生成一颗新树
 *
 * @ 返回值: 成功时,返回值为1; 否则,返回值为0.
 */
int TreeFromFile(FILE* fp, size_t size, pOPTree* outputpp);

/**
 * @ 函数: int32_t TreeToFile(FILE* fp, pOPTree tree)
 *
 * @ 功能: 从文件指针当前的位置指针开始, 写入一棵树. 并会移动位置指针.
 *
 * @ param{fp}: 文件指针, 属性需可写
 *
 * @ param{tree}: 待输出的树
 *
 * @ 返回值: 成功时,返回值为写入的字节数; 否则,返回值为-1.
 */
int32_t TreeToFile(FILE* fp, pOPTree tree);
#pragma endregion
#endif // !__DATAFILE_H__
