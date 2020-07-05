#include "Tree.h"

using namespace std;

Tree::Tree() : root(root),count(count)
{
	cout << "construct tree..."<<endl;
}

Tree::~Tree()
{
	cout << "destruct tree..." << endl;
	deleteElements();
}

Node* Tree::getRoot() const
{
	return root;
}

void Tree::insertChild(Node* parent, Node* child)
{
	if (child != nullptr)
	{

		if (parent == nullptr)
		{
			this->root = child;
			count++;
		}
		else
		{ 
			if (parent != nullptr)
			{
				if (parent->getFirstChild() == nullptr)
				{
					parent->setFirstChild(child);
					count++;
				}
				else
				{
					Node* curr = parent->getFirstChild();
					while (curr->getNextSibling() != nullptr)
					{
						curr = curr->getNextSibling();

					} 
					if (curr != nullptr)
					{
						curr->setNextSibling(child);
					}
					count++;

				}
			}

		}

	}

}

void Tree::deleteSingleChild(Node* parent, Node* node)
{
	if ((node != nullptr) && (parent != nullptr))
	{

		Node* curr = parent->getFirstChild();
		if (node == curr)
		{
			parent->setFirstChild(curr->getNextSibling());
			delete node;
			if (count > 1)
			{
				count--;
			}
		}
		else {
			if (curr != nullptr)
			{
				while (curr->getNextSibling() != nullptr)
				{
					if (curr->getNextSibling() == node)
					{
						curr->setNextSibling(curr->getNextSibling()->getNextSibling());
						delete node;
						if (count > 1)
						{
							count--;
						}
					}
					curr = curr->getNextSibling();
					if (curr == nullptr)
					{
						break;
					}
				}
			}
		
		}
	}

}

//delete all under the given element
void Tree::deleteSubtree(Node* node)
{
	if ((node != nullptr) && (count > 0))
	{

		Node* traverse = node;
		while ((node->getFirstChild() != nullptr) || (node->getNextSibling() != nullptr))
		{
			if (traverse->getFirstChild() == nullptr)
			{

				if (traverse->getNextSibling() == nullptr)
				{
					break;
				}
				else {
					if ((traverse->getNextSibling()->getFirstChild() == nullptr) && (traverse->getNextSibling()->getNextSibling() == nullptr))
					{
						cout << "delete node " << (int)traverse->getNextSibling()<< endl;
						delete traverse->getNextSibling();

						traverse->setNextSibling(nullptr);
						traverse = node;
						if (count > 1)
						{
							count--;
						}
					}
					else
					{
						traverse = traverse->getNextSibling();
					}
				}

			}
			else
			{

				if ((traverse->getFirstChild()->getFirstChild() == nullptr) && (traverse->getFirstChild()->getNextSibling() == nullptr))
				{
					cout << "delete node " << (int)traverse->getFirstChild() << endl;
					delete traverse->getFirstChild();

					traverse->setFirstChild(nullptr);

					traverse = node;
					if (count > 0)
					{
						count--;
					}

				}
				else
				{
					traverse = traverse->getFirstChild();
				}


			}
		}
		node->setFirstChild(nullptr);
		node->setNextSibling(nullptr);

	}

}


int Tree::getSize() const
{
	return count;
}

void Tree::clear()
{
	deleteSubtree(this->root);
}

void Tree::deleteElements()
{
	if ((this->root != nullptr) && (count > 0))
	{
		deleteSubtree(this->root);

		cout << "delete root node " << (int)this->root << endl;
		delete(this->root);

		count = 0;
	}

}

void SubPrint(std::ostream& os, Node* start)
{
	if (start != nullptr)
	{
		if (start->getFirstChild() != nullptr)
		{
			start->getFirstChild()->print(os);

			Node* traverseSib = start->getFirstChild()->getNextSibling();
			while (traverseSib != nullptr)
			{
				traverseSib->print(os);
				SubPrint(os, traverseSib);

				traverseSib = traverseSib->getNextSibling();
			}
			SubPrint(os, start->getFirstChild());
		
		}
	}

}


void SubCopy(Node* dest, Node* start)
{
	if ((start != nullptr) && (dest != nullptr))
	{
		if ((start->getFirstChild() != nullptr))
		{

			dest->setFirstChild(start->getFirstChild()->clone());

			Node* traverseSib = start->getFirstChild()->getNextSibling();
			Node* traverseSibDest = dest->getFirstChild();

			while ((traverseSib != nullptr) && (traverseSibDest != nullptr))
			{
				traverseSibDest->setNextSibling(traverseSib->clone());

				SubCopy(traverseSibDest->getNextSibling(), traverseSib);

				traverseSib = traverseSib->getNextSibling();

				traverseSibDest = traverseSibDest->getNextSibling();
			}
			SubCopy(dest->getFirstChild() , start->getFirstChild());

		}
	}

}


void Tree::print(std::ostream& os) const
{
	if ((root != nullptr) && (count > 0))
	{
		root->print(os);
		SubPrint(os, root);
	}
}


Tree::Tree(const Tree& t) : root(t.root), count(t.count)
{
	if (t.root != nullptr)
	{
		root = t.root->clone();
		SubCopy(root, t.root);
	}
	
}

std::ostream& operator<<(std::ostream& os, const Tree& t)
{
	t.print(os);
	return os;
}
