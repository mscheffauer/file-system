#pragma once

#include "FSNode.h"

class Directory : public FSNode {
protected:

public:

	explicit Directory(FSNode* firstChild = nullptr, FSNode* nextSibling = nullptr);
	virtual ~Directory() = default;
	explicit Directory(const Directory& n) = default;

	Directory* create() const   override    // Virtual constructor (creation) 
	{
		return new Directory();
	}
	Directory* clone() const  override      // Virtual constructor (copying) 
	{
		return new Directory(*this);
	}

	void print(std::ostream& os) const override;

};