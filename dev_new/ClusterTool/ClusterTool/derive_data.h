/**
 * @ 文件名: derive_data.h
 * @ 功能: 声明有关DeriveData的功能
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 06/24/2020
 *
 */
#pragma once
#ifndef _DERIVE_DATA_H_
#define _DERIVE_DATA_H_

#include "operator_tree.h"
#include "cluster_expansion.h"
#include "deb.h"

namespace ayaji {
	class DeriveData {
	public:
		// constant
		static const int MAX_OPERATOR_LENGTH = 128;

		// member
		int size;
		int capacity;
		int hoSize;
		int coSize;
		OPTree trackTree;
		OPTree trackValueTree;
		std::vector<Complex> curValues;
		std::vector<Complex> hoCoefs;
		std::vector<Complex> coCoefs;
		std::vector<std::vector<OPTree>> evoTrees_HO;
		std::vector<std::vector<OPTree>> evoTrees_CO;
		std::vector<pNode> trackNodes;

		// constructor
		DeriveData(int capacity, int csize, int hoSize, int coSize);
		DeriveData(DeriveData&& other) noexcept;
		~DeriveData();

		// basic method
		int insert(LabelSeq seq, Complex c);
		int reserve(int newCapacity);

		// imperative method
		/// <summary>
		/// 对应第四章的InitialValue操作。默认输入为合法。零次项输出1。
		/// sArr[0]对应{1,2}的初值,sArr[1]对应{3,4}的初值......以此类推。
		/// </summary>
		/// <param name="seq">operator数组表达</param>
		/// <param name="sseq">初态数组</param>
		/// <returns></returns>
		static Complex initialValue(LabelSeq seq, LabelSeq sseq);
		/// <summary>
		/// 对应第四章的Evolution操作, 但是root->value不变, 根中的系数由外部改变。
		/// </summary>
		/// <param name="inputSeq_HO">用户输入的hamilton operator的列表</param>
		/// <param name="inputSeqCoef_HO">用户输入的hamilton operator的列表对应的系数</param>
		/// <param name="inputSeq_CO">用户输入的hamilton operator的列表</param>
		/// <param name="inputSeqCoef_CO">用户输入的hamilton operator的列表对应的系数</param>
		/// <param name="userSeq">用户特定的op</param>
		/// <param name="maxOPLen">最大operator长度</param>
		/// <returns>输出的ho树和co树数组</returns>
		static std::pair<std::vector<OPTree>, std::vector<OPTree>>
			evolution(const std::vector<LabelSeq>& inputSeq_HO, const std::vector<Complex>& inputSeqCoef_HO,
				const std::vector<LabelSeq>& inputSeq_CO, const std::vector<Complex>& inputSeqCoef_CO,
				const LabelSeq& userSeq, int maxOPLen);
		/// <summary>
		/// 对应第四章中的Derive And Assign过程
		/// </summary>
		/// <param name="inputSeq_HO"></param>
		/// <param name="inputSeqCoef_HO"></param>
		/// <param name="inputSeq_CO"></param>
		/// <param name="inputSeqCoef_CO"></param>
		/// <param name="inputSeq_Init"></param>
		/// <param name="inputSeq_Track"></param>
		/// <param name="maxOPLen"></param>
		/// <returns>生成一个新的data</returns>
		static DeriveData deriveAssign(const std::vector<LabelSeq>& inputSeq_HO, const std::vector<Complex>& inputSeqCoef_HO,
			const std::vector<LabelSeq>& inputSeq_CO, const std::vector<Complex>& inputSeqCoef_CO,
			const LabelSeq& inputSeq_Init, const std::vector<LabelSeq>& inputSeq_Track,
			int maxOPLen);
		/// <summary>
		/// 对应第四章中的Calculate Evolution过程
		/// </summary>
		/// <returns></returns>
		std::vector<Complex> calEvolution();

		// other

		/// <summary>
		/// multiply node's value with sth
		/// </summary>
		/// <param name="node"></param>
		/// <param name="sth"></param>
		static void _multiplyNodeWithComplex(pNode node, void* sth);

	private:
		static std::vector<OPTree> _evolution_HO(const std::vector<LabelSeq>& inputSeq_HO, const std::vector<Complex>& inputSeqCoef_HO,
			const LabelSeq& userSeq, int maxOPLen);
		static std::vector<OPTree> _evolution_CO(const std::vector<LabelSeq>& inputSeq_CO, const std::vector<Complex>& inputSeqCoef_CO,
			const LabelSeq& userSeq, int maxOPLen);

		/// <summary>
		/// 删除树中第一个遇到的长度大于maxOPLen的operator
		/// TODO: 此处的乘法，可以分成更大一块的Operator再进行相乘，以加快
		/// </summary>
		/// <param name="tree">operator tree</param>
		/// <param name="maxOPLen">operator最大长度</param>
		/// <returns>若存在删除并成功时,返回值为1; 否则,返回值为0.</returns>
		static int _DeleteAndCE(OPTree& tree, int maxOPLen);
		/// <summary>
		/// 获得长度大于maxOPLen的operator的起始index
		/// </summary>
		/// <param name="seq"></param>
		/// <param name="maxOPLen"></param>
		/// <returns></returns>
		static std::vector<std::pair<int, int>> _getOverLengthIndex(const LabelSeq& seq, int maxOPLen);
	};
}

#endif // !_DERIVE_DATA_H_
