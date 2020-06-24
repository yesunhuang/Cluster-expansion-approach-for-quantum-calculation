#include "deb.h"

namespace ayaji {
	LabelSeq deb_generateLabelSeq(unsigned size, ...) {
		va_list valist;
		va_start(valist, size);
		LabelSeq seq;
		for (unsigned i = 0; i < size; ++i) {
			int value = va_arg(valist, int);
			seq.push_back((Label)value);
		}
		va_end(valist);
		return seq;
	}

	void deb_printTree(const OPTree& tree) {
		LabelSeq seqBuf;
		for (int i = 0; i <= tree.childSize; ++i) {
			pNode node;
			if ((node = tree.root->children[i]) != nullptr) {
				deb_printTree_(node, seqBuf, tree.childSize);
			}
		}
	}

	void deb_printTree_(pNode& node, LabelSeq& seqBuf, int cSize) {
		if (node == nullptr) return;
		seqBuf.push_back(node->label);
		if (!node->value.isZero()) {
			std::string coef = node->value.getString();
			std::cout << "Coef: " << coef << "  Struct: [";
			for (auto it = seqBuf.cbegin(); it != seqBuf.cend(); ++it) {
				std::cout << *it << ", ";
			}
			std::cout << "]" << std::endl;
		}
		for (int i = 0; i <= cSize; ++i) {
			pNode tnode;
			if ((tnode = node->children[i]) != nullptr) {
				deb_printTree_(tnode, seqBuf, cSize);
			}
		}
		seqBuf.pop_back();
	}

}