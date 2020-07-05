#pragma once

#include "FSNode.h"

class File : public FSNode {
protected:
public:

	explicit File(FSNode* firstChild = nullptr, FSNode* nextSibling = nullptr);
	virtual ~File() = default;
	explicit File(const File& n) = default;

	File* create() const   override    // Virtual constructor (creation) 
	{
		return new File();
	}
	File* clone() const  override      // Virtual constructor (copying) 
	{
		return new File(*this);
	}

	void print(std::ostream& os) const override;
};
