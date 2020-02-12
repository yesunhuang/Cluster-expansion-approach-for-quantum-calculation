/**
 * @ �ļ���: datafile.h
 * @ ����: �ṩdata�����ݴ洢�Ľӿ�
 * @ ����: AyajiLin
 * @ ����: 493987054@qq.com
 * @ github: https://github.com/leonardodalinky
 * @ ����: 2020��2��12��
 *
 */
#pragma once
#ifndef __DATAFILE_H__
#define __DATAFILE_H__

#pragma region �궨����
#define _TREESTARTID ((uint32_t)0x3a74f19d)
#define _TREEENDID ((uint32_t)0x4b74f87d)
#define _DATASTARTID ((uint32_t)0xd2743671)
#define _DATAENDID ((uint32_t)0xe5742189)
#pragma endregion

#pragma region ͷ�ļ���
#include "solver.h"
#pragma endregion

#pragma region �ṹ�弰typedef������

#pragma endregion

#pragma region ����������
/**
 * @ ����: int DataFromFile(const char* filePath, pDeriveData* outputpp)
 *
 * @ ����: ���ļ�ָ�뵱ǰ��λ��ָ�뿪ʼ, ��ȡdata. �����ƶ�λ��ָ��.
 *
 * @ param{filePath}: �ļ�·��
 *
 * @ param{outputpp}: ����һ����data
 *
 * @ ����ֵ: �ɹ�ʱ,����ֵΪ1; ����,����ֵΪ0.
 */
int DataFromFile(const char* filePath, pDeriveData* outputpp);

/**
 * @ ����: int32_t TreeToFile(FILE* fp, pOPTree tree)
 *
 * @ ����: ���ļ�ָ�뵱ǰ��λ��ָ�뿪ʼ, д��һ����. �����ƶ�λ��ָ��.
 *
 * @ param{data}: �������data
 *
 * @ param{filePath}: ����ļ���·��
 *
 * @ ����ֵ: �ɹ�ʱ,����ֵΪд����ֽ���; ����,����ֵΪ-1.
 */
int32_t DataToFile(pDeriveData data, const char* filePath);

/**
 * @ ����: int TreeFromFile(FILE* fp, size_t size, pOPTree* outputpp)
 *
 * @ ����: ���ļ�ָ�뵱ǰ��λ��ָ�뿪ʼ, ��ȡһ����. �����ƶ�λ��ָ��.
 *
 * @ param{fp}: �ļ�ָ��, ������ɶ�
 *
 * @ param{size}: �����ݼ��Ĵ�С, ��λΪ�ֽ�
 *
 * @ param{outputpp}: ����һ������
 *
 * @ ����ֵ: �ɹ�ʱ,����ֵΪ1; ����,����ֵΪ0.
 */
int TreeFromFile(FILE* fp, size_t size, pOPTree* outputpp);

/**
 * @ ����: int32_t TreeToFile(FILE* fp, pOPTree tree)
 *
 * @ ����: ���ļ�ָ�뵱ǰ��λ��ָ�뿪ʼ, д��һ����. �����ƶ�λ��ָ��.
 *
 * @ param{fp}: �ļ�ָ��, �������д
 *
 * @ param{tree}: ���������
 *
 * @ ����ֵ: �ɹ�ʱ,����ֵΪд����ֽ���; ����,����ֵΪ-1.
 */
int32_t TreeToFile(FILE* fp, pOPTree tree);
#pragma endregion
#endif // !__DATAFILE_H__
