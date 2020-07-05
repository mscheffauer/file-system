#pragma once

#include "Node.h"

class Tree {
protected:
	Node* root = nullptr;
	int count = 0;

public:
	Tree();
	virtual ~Tree();
	Tree(const Tree& t);

	virtual Node* getRoot() const;
	void insertChild(Node* parent, Node* child);

	void deleteSubtree(Node* node);

	int getSize() const;
	void clear();
	void deleteElements();
	void print(std::ostream& os) const;
	void deleteSingleChild(Node* parent, Node* node);
	Tree& operator=(Tree t)noexcept
	{
		swap(*this, t);
		return *this;
	}
											
	friend std::ostream& operator <<(std::ostream& os, const Tree& t);

	friend void swap(Tree& t1, Tree& t2) noexcept { 
		using std::swap; 
		swap(t1.root, t2.root); 
		swap(t1.count, t2.count); 
	}
};

