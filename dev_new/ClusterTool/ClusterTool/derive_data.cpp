/**
 * @ 文件名: derive_data.cpp
 * @ 功能: 实现有关DeriveData的功能
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 06/24/2020
 *
 */
#include "derive_data.h"

namespace ayaji {
	DeriveData::DeriveData(int capacity, int csize, int hoSize, int coSize) 
		: capacity(capacity), size(0), hoSize(hoSize), coSize(coSize)
	{
		curValues.resize(capacity);
		hoCoefs.resize(hoSize);
		coCoefs.resize(coSize);
		evoTrees_HO.resize(capacity);
		evoTrees_CO.resize(capacity);
		for (int i = 0; i < capacity; ++i) {
			evoTrees_HO[i].resize(hoSize);
			evoTrees_CO[i].resize(coSize);
		}
		trackNodes.resize(capacity);
		trackTree.setChildSize(csize);
		trackValueTree.setChildSize(csize);
	}

	DeriveData::DeriveData(DeriveData&& other) noexcept
		: capacity(other.capacity), size(other.size), hoSize(other.hoSize), coSize(other.coSize)
	{
		curValues.swap(other.curValues);
		hoCoefs.swap(other.hoCoefs);
		coCoefs.swap(other.coCoefs);
		evoTrees_HO.swap(other.evoTrees_HO);
		evoTrees_CO.swap(other.evoTrees_CO);
		trackNodes.swap(other.trackNodes);
		trackTree.shallowCopy(other.trackTree);
		trackValueTree.shallowCopy(other.trackValueTree);
	}

	DeriveData::~DeriveData() {

	}

	int DeriveData::insert(LabelSeq seq, Complex c) {
		pNode tmpNode = trackTree.search(seq);
		if (tmpNode != nullptr && !tmpNode->isZero())
			return 0;
		else if (size >= capacity) {
			reserve(__max(2 * capacity, size + 8));
		}

		curValues[size] = c;
		// 此处注意
		//for (int i = 0; i < data->hoSize; ++i)
		//	data->evoTrees_HO[data->size][i] = NULL;
		//for (int i = 0; i < data->coSize; ++i)
		//	data->evoTrees_CO[data->size][i] = NULL;
		trackTree.insert(seq);
		trackValueTree.insert(seq);
		trackNodes[size] = trackTree.search(seq);
		size += 1;
		return 0;
	}

	int DeriveData::reserve(int newCapacity) {
		newCapacity = __max(0, newCapacity);
		if (newCapacity == capacity)
			return 0;
		else {
			curValues.resize(capacity);
			evoTrees_HO.resize(capacity);
			evoTrees_CO.resize(capacity);
			for (int i = capacity; i < newCapacity; ++i) {
				evoTrees_HO[i].resize(hoSize);
				evoTrees_CO[i].resize(coSize);
			}
			trackNodes.resize(capacity);
			return 0;
		}
	}

	Complex DeriveData::initialValue(LabelSeq seq, LabelSeq sseq) {
		int len = seq.size();
		int slen = sseq.size();
		if (len == 0 || slen == 0) {
			return Complex(0, 0);
		}
		else if (seq[0] == 0) {
			return Complex(1, 0);
		}

		int maxn = -1;
		for (int i = 0; i < len; ++i) {
			maxn = __max(maxn, seq[i]);
		}
		if ((maxn + 1) / 2 - 1 > slen)
			return Complex(0, 0);

		int dagger = -1, normal = -1;
		int nextIndex = -1;
		/* n表示creation operator的数目,即dagger的数目 */
		/* m表示anihilation operator的数目,即normal的数目 */
		int n = 0, m = 0;
		double ans = 1;
		int state = 0;
		while (state != -1) {
			switch (state) {
			case -1:
				/* 状态-1: 退出状态 */
				break;
			case 0:
				/* 状态0: 初始化 */
				nextIndex = 0;
				state = 1;
				break;
			case 1:
				/* 状态1: 更改dagger和normal */
				n = m = 0;
				normal = ((seq[nextIndex] + 1) / 2) * 2;
				dagger = normal - 1;
				state = 2;
				break;
			case 2:
				/* 状态2: 开始遍历同一块 */
				if (nextIndex >= len) {
					state = 3;
				}
				else if (seq[nextIndex] == normal) {
					++m;
					++nextIndex;
				}
				else if (seq[nextIndex] == dagger) {
					++n;
					++nextIndex;
				}
				else {
					state = 3;
				}
				break;
			case 3:
				/* 状态3: 统计n和m,更新ans */
			{
				if (n != m) {
					ans = 0;
					state = -1;
					break;
				}
				else {
					int n_alpha = sseq[normal / 2 - 1];
					if (n > n_alpha) {
						ans = 0;
						state = -1;
					}
					else {
						for (int i = n_alpha; i >= n_alpha - n + 1; --i) {
							ans *= i;
						}
					}

					if (nextIndex >= len)
						state = -1;
					else
						state = 1;
				}
				break;
			}
			default:
				break;
			}
		}

		return Complex(ans, 0);
	}

	std::pair<std::vector<OPTree>, std::vector<OPTree>> DeriveData::evolution(const std::vector<LabelSeq>& inputSeq_HO, const std::vector<Complex>& inputSeqCoef_HO, 
		const std::vector<LabelSeq>& inputSeq_CO, const std::vector<Complex>& inputSeqCoef_CO, 
		const LabelSeq& userSeq, int maxOPLen)
	{
		std::pair<std::vector<OPTree>, std::vector<OPTree>> ret;
		ret.first = _evolution_HO(inputSeq_HO, inputSeqCoef_HO, userSeq, maxOPLen);
		ret.first = _evolution_CO(inputSeq_CO, inputSeqCoef_CO, userSeq, maxOPLen);
		return ret;
	}

	void DeriveData::_multiplyNodeWithComplex(pNode node, void* sth) {
		node->value *= *((Complex*)sth);
	}

	std::vector<OPTree> DeriveData::_evolution_HO(const std::vector<LabelSeq>& inputSeq_HO,
		const std::vector<Complex>& inputSeqCoef_HO, 
		const LabelSeq& userSeq, int maxOPLen) 
	{
		/* ho部分 */

		LabelSeq buf;
		int inputSeqLen = inputSeq_HO.size();
		int userSeqLen = userSeq.size();
		std::vector<OPTree> ret;
		ret.resize(inputSeqLen);
		for (int i = 0; i < inputSeqLen; ++i) {
			/* 先构造<O_j A_i> */
			buf.clear();
			buf.insert(buf.cend(), inputSeq_HO[i].cbegin(), inputSeq_HO[i].cend());
			buf.insert(buf.cend(), userSeq.cbegin(), userSeq.cend());
			OPTree OA_Tree = OPTree::MONormalize(buf);
			//PrintOPTree(OA_Tree);

			/* 再构造<A_i O_j> */
			buf.clear();
			buf.insert(buf.cend(), userSeq.cbegin(), userSeq.cend());
			buf.insert(buf.cend(), inputSeq_HO[i].cbegin(), inputSeq_HO[i].cend());
			OPTree AO_Tree = OPTree::MONormalize(buf);
			//PrintOPTree(AO_Tree);

			/* 两树相减 */
			AO_Tree.eachNode(nullptr, ClusterExp::_NegateNode);
			OA_Tree.add(AO_Tree);
			//PrintOPTree(OA_Tree);

			/* 去除长度超过范围的 */
			/* TODO: 这个方法很蠢,日后需要优化 */
			while (_DeleteAndCE(OA_Tree, maxOPLen) == 1) {}

			ret[i] = OA_Tree;
		}
		return ret;
	}

	std::vector<OPTree> DeriveData::_evolution_CO(const std::vector<LabelSeq>& inputSeq_CO, 
		const std::vector<Complex>& inputSeqCoef_CO, 
		const LabelSeq& userSeq, int maxOPLen)
	{
		/* co部分 */
		//UINT_L dagger[MAX_OPERATOR_LENGTH];
		//UINT_L buf[3 * MAX_OPERATOR_LENGTH];
		LabelSeq dagger;
		LabelSeq buf;

		Complex tempc(2, 0);

		int inputSeqLen = inputSeq_CO.size();
		std::vector<OPTree> ret;
		ret.resize(inputSeqLen);
		for (int i = 0; i < inputSeqLen; ++i) {
			/* 先构造O_n^{\dagger} */
			dagger.clear();
			int inputSeqLens = inputSeq_CO[i].size();
			for (int j = 0; j < inputSeqLens; ++j) {
				Label t = ((inputSeq_CO[i][j] - 1) ^ 1) + 1;
				dagger.push_back(t);
			}

			/* 先构造<O_n^{\dagger} A_i O_n> */
			buf.clear();
			buf.insert(buf.cend(), dagger.cbegin(), dagger.cend());
			buf.insert(buf.cend(), userSeq.cbegin(), userSeq.cend());
			buf.insert(buf.cend(), inputSeq_CO[i].cbegin(), inputSeq_CO[i].cend());
			OPTree OdAO_Tree = OPTree::MONormalize(buf);
			OdAO_Tree.eachNode(&tempc, _multiplyNodeWithComplex);

			/* 再构造<O_n^{\dagger} O_n A_i> */
			buf.clear();
			buf.insert(buf.cend(), dagger.cbegin(), dagger.cend());
			buf.insert(buf.cend(), inputSeq_CO[i].cbegin(), inputSeq_CO[i].cend());
			buf.insert(buf.cend(), userSeq.cbegin(), userSeq.cend());
			OPTree OdOA_Tree = OPTree::MONormalize(buf);

			/* 再构造<A_i O_n^{\dagger} O_n> */
			buf.clear();
			buf.insert(buf.cend(), userSeq.cbegin(), userSeq.cend());
			buf.insert(buf.cend(), dagger.cbegin(), dagger.cend());
			buf.insert(buf.cend(), inputSeq_CO[i].cbegin(), inputSeq_CO[i].cend());
			OPTree AOdO_Tree = OPTree::MONormalize(buf);

			/* 三树相减 */
			OdOA_Tree.eachNode(nullptr, ClusterExp::_NegateNode);
			AOdO_Tree.eachNode(nullptr, ClusterExp::_NegateNode);
			OdAO_Tree.add(OdOA_Tree);
			OdAO_Tree.add(AOdO_Tree);

			/* 去除长度超过范围的 */
			/* TODO: 这个方法很蠢,日后需要优化 */
			while (_DeleteAndCE(OdAO_Tree, maxOPLen) == 1) {}

			ret[i] = OdAO_Tree;
		}

		return ret;
	}

	int DeriveData::_DeleteAndCE(OPTree& tree, int maxOPLen) {
		for (auto it = tree.getIterator(); *it != nullptr; it.next()) {
			LabelSeq seq = it.getCurLabelSeq();
			int len = seq.size();
			int nowIndex = 0, nextIndex = Common::_GetNextCPIndexFromOPArray(seq, 0);
			OPTree tmpAddToNow;
			tmpAddToNow.setChildSize(tree.getChildSize());
			std::vector<std::pair<int, int>> overs = _getOverLengthIndex(seq, maxOPLen);
			int overLen = overs.size();
			int prevTailIndex = 0;
			if (overLen != 0) {
				for (int i = 0; i < overLen; ++i) {
					std::pair<int, int>& pair = overs[i];
					if (prevTailIndex < pair.first) {
						// need to multiply other ops
						tmpAddToNow = tmpAddToNow.mul_TO(LabelSeq(seq.cbegin() + prevTailIndex, seq.cbegin() + pair.first - 1), Complex(1,0));
					}

					if (pair.second >= len) {
						tmpAddToNow = tmpAddToNow.mul_TT(ClusterExp::ClusterExpansion(LabelSeq(seq.cbegin() + pair.first, seq.cbegin() + pair.second)));
					}
					else {
						tmpAddToNow = tmpAddToNow.mul_TT(ClusterExp::ClusterExpansion(LabelSeq(seq.cbegin() + pair.first, seq.cbegin() + pair.second - 1)));
						if (i == overLen - 1) {
							// the last one
							tmpAddToNow = tmpAddToNow.mul_TO(LabelSeq(seq.cbegin() + pair.second, seq.cend()), Complex(1, 0));
						}
					}
					prevTailIndex = pair.second;
				}
				// multiply the origin coef
				Complex originCoef = it.getNode()->value;
				tmpAddToNow.eachNode(&originCoef, _multiplyNodeWithComplex);

				tree.remove(seq);
				tree.add(tmpAddToNow);
				return 1;
			}
		}
		return 0;
	}

	std::vector<std::pair<int, int>> DeriveData::_getOverLengthIndex(const LabelSeq& seq, int maxOPLen) {
		int len = seq.size();
		int nowIndex = 0, nextIndex = Common::_GetNextCPIndexFromOPArray(seq, 0);
		std::vector<std::pair<int, int>> ret;
		while (nowIndex < len) {
			if (nextIndex >= len) {
				// reach tail
				if (nextIndex - nowIndex > maxOPLen) {
					ret.push_back(std::pair<int, int>(nowIndex, nextIndex));
				}
			}
			else {
				// reach middle
				if (nextIndex - nowIndex - 1 > maxOPLen) {
					ret.push_back(std::pair<int, int>(nowIndex, nextIndex));
				}
			}
			nowIndex = nextIndex;
			nextIndex = Common::_GetNextCPIndexFromOPArray(seq, nowIndex);
		}
		return std::move(ret);
	}

}