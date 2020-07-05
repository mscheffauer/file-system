#include "FSNode.h"

using namespace std;

FSNode::FSNode(Node* firstChild, Node* nextSibling) : Node(firstChild,nextSibling)
{
	//do nothing
}

void FSNode::setName(std::string nm)
{
	name = nm;
}

std::string FSNode::getName() const
{
	return name;
}

void FSNode::print(std::ostream& os) const
{
	os << name << endl;
}
