/**
 * @ FileName: node.c
 * @ Function: implement the function of node
 * @ Author: AyajiLin & YesunHuang
 * @ Mail: 493987054@qq.com & 944812203@qq.com
 * @ Github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ Date: 04/03/2020
 *
 */

#include "node.h"

namespace ayaji {
	Node::Node()
		: label(0)
	{
		parent.reset();
	}

	Node::Node(int childSize)
		: label(0)
	{
		this->children.resize(childSize + 1, nullptr);
		parent.reset();
	}

	Node::Node(int childSize, Label l, Complex v)
		: label(l)
	{
		this->children.resize(childSize + 1, nullptr);
		this->value = v;
		parent.reset();
	}

	Node::Node(int childSize, Label l, Complex v, const std::shared_ptr<Node>& p)
		: label(l)
	{
		this->children.resize(childSize + 1, nullptr);
		this->value = v;
		parent = p;
	}

	Node::~Node()
	{
	}

	std::shared_ptr<Node> Node::createNode() {
		return std::move(std::make_shared<Node>());
	}

	std::shared_ptr<Node> Node::createNode(int childSize) {
		return std::move(std::make_shared<Node>(childSize));
	}

	std::shared_ptr<Node> Node::createNode(int childSize, Label l, Complex v) {
		return std::move(std::make_shared<Node>(childSize, l, v));
	}

	std::shared_ptr<Node> Node::createNode(int childSize, Label l, Complex v, const std::shared_ptr<Node>& parent) {
		return std::move(std::make_shared<Node>(childSize, l, v, parent));
	}

	std::shared_ptr<Node> Node::getPtr() {
		return std::move(shared_from_this());
	}

	void Node::clear() {
		parent.reset();
		children.clear();
	}

	void Node::clear_r() {
		parent.reset();
		for (auto it = children.begin(); it != children.end(); ++it) {
			if ((*it) != nullptr)
				(*it)->clear_r();
		}
		children.clear();
	}

	bool Node::hasChild(int childLabel) const {
		return children[childLabel] != nullptr;
	}

	bool Node::hasChildren() const {
		for (auto it = children.cbegin(); it != children.cend(); ++it) {
			if (*it != nullptr)
				return true;
		}
		return false;
	}

	bool Node::isZero() const {
		return this->value.isZero();
	}

	void Node::resize_r(int newSize) {
		if (newSize < 0)
			throw std::out_of_range("New size is out of range");
		int nowSize = children.size() - 1;
		if (nowSize == newSize) return;
		else if (nowSize < newSize) {
			children.insert(children.cend(), newSize - nowSize, nullptr);
			for (auto it = children.begin(); it != children.end(); ++it) {
				if ((*it) != nullptr)
					(*it)->resize_r(newSize);
			}
		}
		else {
			// nowSize > newSize
			for (int i = newSize + 1; i < nowSize; ++i) {
				children[i]->clear_r();
			}
			children.resize(newSize + 1);
		}
	}

	pNode Node::getRoot() {
		pNode nowNode = this->getPtr();
		while (nowNode->parent.lock() != nullptr)
			nowNode = nowNode->parent.lock();
		return std::move(nowNode);
	}

	LabelSeq Node::seqFromRoot() {
		LabelSeq s;
		pNode nowNode = this->getPtr();
		while (nowNode != nullptr && nowNode->parent.lock() != nullptr) {
			s.push_back((*nowNode).label);
			nowNode = nowNode->parent.lock();
		}
		std::reverse(s.begin(), s.end());
		return std::move(s);
	}

	int Node::getFirstNonEmptyChildIndex(void) {
		int t = 0;
		int size = children.size();
		for (; t < size; ++t) {
			if (children.at(t) != nullptr)
				return t;
		}
		return -1;
	}

	pNode Node::getFirstNonEmptyChild(void) {
		int t = getFirstNonEmptyChildIndex();
		return (t == -1) ? nullptr : children.at(t);
	}

	int Node::getLastNonEmptyChildIndex(void) {
		int size = children.size();
		int t = size - 1;
		for (; t >= 0; --t) {
			if (children.at(t) != nullptr)
				return t;
		}
		return -1;
	}

	pNode Node::getLastNonEmptyChild(void) {
		int t = getLastNonEmptyChildIndex();
		return (t == -1) ? nullptr : children.at(t);
	}
}