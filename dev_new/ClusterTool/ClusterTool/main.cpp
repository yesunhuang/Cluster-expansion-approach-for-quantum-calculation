#include <memory>
#include <iostream>
#include "operator_tree.h"
#include "deb.h"
#include "common.h"
#include "cluster_expansion.h"
#include "static_dtree.h"

#include <crtdbg.h>

using namespace ayaji;

int main() {
	{
		OPTree tree1;
		//tree1.insert(deb_generateLabelSeq(2, 1, 2));
		//tree1.insert(deb_generateLabelSeq(2, 1, 2), Complex(-1, 0));
		//tree1.search(deb_generateLabelSeq(2, 1, 2))->value = Complex();
		//tree1.normalize();
		//tree1 = ClusterExp::ClusterExpansion(deb_generateLabelSeq(4, 1, 2, 3, 4));
		tree1 = ClusterExp::DeltaTree(3);
		//tree1 = OPTree::BuildFromPTree(t, deb_generateLabelSeq(2, 1, 2));

		//OPTree tree2;
		//tree2.insert(deb_generateLabelSeq(5, 1, 2, 3, 4, 5));
		//tree2.insert(deb_generateLabelSeq(5, 0, 2, 3, 4, 5));

		//deb_printTree(tree1);
		deb_printTree(tree1);
		//_CrtDumpMemoryLeaks();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}