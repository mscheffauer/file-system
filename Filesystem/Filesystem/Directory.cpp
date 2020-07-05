#include "Directory.h"

Directory::Directory(FSNode* firstChild,FSNode* nextSibling) : FSNode(firstChild,nextSibling)
{
	//do nothing
}

void Directory::print(std::ostream& os) const
{
	FSNode::print(os);
}
