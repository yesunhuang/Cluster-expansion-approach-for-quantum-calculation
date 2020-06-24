/**
 * @ �ļ���: derive_data.h
 * @ ����: �����й�DeriveData�Ĺ���
 * @ ����: AyajiLin & YesunHuang
 * @ ����: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ ����: 06/24/2020
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
		/// ��Ӧ�����µ�InitialValue������Ĭ������Ϊ�Ϸ�����������1��
		/// sArr[0]��Ӧ{1,2}�ĳ�ֵ,sArr[1]��Ӧ{3,4}�ĳ�ֵ......�Դ����ơ�
		/// </summary>
		/// <param name="seq">operator������</param>
		/// <param name="sseq">��̬����</param>
		/// <returns></returns>
		static Complex initialValue(LabelSeq seq, LabelSeq sseq);
		/// <summary>
		/// ��Ӧ�����µ�Evolution����, ����root->value����, ���е�ϵ�����ⲿ�ı䡣
		/// </summary>
		/// <param name="inputSeq_HO">�û������hamilton operator���б�</param>
		/// <param name="inputSeqCoef_HO">�û������hamilton operator���б��Ӧ��ϵ��</param>
		/// <param name="inputSeq_CO">�û������hamilton operator���б�</param>
		/// <param name="inputSeqCoef_CO">�û������hamilton operator���б��Ӧ��ϵ��</param>
		/// <param name="userSeq">�û��ض���op</param>
		/// <param name="maxOPLen">���operator����</param>
		/// <returns>�����ho����co������</returns>
		static std::pair<std::vector<OPTree>, std::vector<OPTree>>
			evolution(const std::vector<LabelSeq>& inputSeq_HO, const std::vector<Complex>& inputSeqCoef_HO,
				const std::vector<LabelSeq>& inputSeq_CO, const std::vector<Complex>& inputSeqCoef_CO,
				const LabelSeq& userSeq, int maxOPLen);
		/// <summary>
		/// ��Ӧ�������е�Derive And Assign����
		/// </summary>
		/// <param name="inputSeq_HO"></param>
		/// <param name="inputSeqCoef_HO"></param>
		/// <param name="inputSeq_CO"></param>
		/// <param name="inputSeqCoef_CO"></param>
		/// <param name="inputSeq_Init"></param>
		/// <param name="inputSeq_Track"></param>
		/// <param name="maxOPLen"></param>
		/// <returns>����һ���µ�data</returns>
		static DeriveData deriveAssign(const std::vector<LabelSeq>& inputSeq_HO, const std::vector<Complex>& inputSeqCoef_HO,
			const std::vector<LabelSeq>& inputSeq_CO, const std::vector<Complex>& inputSeqCoef_CO,
			const LabelSeq& inputSeq_Init, const std::vector<LabelSeq>& inputSeq_Track,
			int maxOPLen);
		/// <summary>
		/// ��Ӧ�������е�Calculate Evolution����
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
		/// ɾ�����е�һ�������ĳ��ȴ���maxOPLen��operator
		/// TODO: �˴��ĳ˷������Էֳɸ���һ���Operator�ٽ�����ˣ��Լӿ�
		/// </summary>
		/// <param name="tree">operator tree</param>
		/// <param name="maxOPLen">operator��󳤶�</param>
		/// <returns>������ɾ�����ɹ�ʱ,����ֵΪ1; ����,����ֵΪ0.</returns>
		static int _DeleteAndCE(OPTree& tree, int maxOPLen);
		/// <summary>
		/// ��ó��ȴ���maxOPLen��operator����ʼindex
		/// </summary>
		/// <param name="seq"></param>
		/// <param name="maxOPLen"></param>
		/// <returns></returns>
		static std::vector<std::pair<int, int>> _getOverLengthIndex(const LabelSeq& seq, int maxOPLen);
	};
}

#endif // !_DERIVE_DATA_H_
