#pragma once

#include "Node.h"

class FSNode : public Node {
protected:
	std::string name;	
public:

	explicit FSNode(Node* firstChild=nullptr, Node* nextSibling=nullptr);
	virtual ~FSNode() = default;
	explicit FSNode(const FSNode& n) = default;

	void setName(std::string nm);
	std::string getName() const;

	FSNode* create() const   override    // Virtual constructor (creation) 
	{
		return new FSNode();
	}
	FSNode* clone() const  override      // Virtual constructor (copying) 
	{
		return new FSNode(*this);
	}

	FSNode& operator=(const FSNode& n) = default;

	virtual void print(std::ostream& os) const override; 

};


