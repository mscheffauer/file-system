#include "Node.h"

using namespace std;

Node::Node(Node* firstChild, Node* nextSibling) : firstChild(firstChild), nextSibling(nextSibling)
{
	// do nothing.
}

Node* Node::getFirstChild() const
{
	return 	this->firstChild;
}

Node* Node::getNextSibling() const
{
	return this->nextSibling;
}

void Node::setFirstChild(Node* n)
{
	this->firstChild = n;
}

void Node::setNextSibling(Node* n)
{
	this->nextSibling = n;
}

std::ostream& operator<<(std::ostream& os, const Node& n)
{
	n.print(os);
	return os;
}

