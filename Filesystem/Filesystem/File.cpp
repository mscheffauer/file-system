#include "File.h"

File::File(FSNode* firstChild, FSNode* nextSibling) : FSNode(nullptr,nextSibling)
{
	//do nothing else
}

void File::print(std::ostream& os) const
{
	FSNode::print(os);
}
