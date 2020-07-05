#pragma once

#include <iostream>

class Node { // abstract class
protected:
	Node* firstChild, * nextSibling;
	// value of any type later in derived, concrete classes
public:
	explicit Node(Node* firstChild = nullptr, Node* nextSibling = nullptr);
	virtual ~Node() = default;
	explicit Node(const Node& n) = default;

	virtual Node* create() const = 0; // Virtual constructor (creation) 
	virtual Node* clone() const = 0;  // Virtual constructor (copying) 

	Node* getFirstChild() const;
	Node* getNextSibling() const;
	void setFirstChild(Node* n);
	void setNextSibling(Node* n);

	virtual void print(std::ostream& os) const = 0; 
	Node& operator=(const Node& n) = default; 
											
	friend std::ostream& operator <<(std::ostream& os, const Node& n); 

};


