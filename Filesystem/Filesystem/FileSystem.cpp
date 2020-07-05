#include "FileSystem.h"
#include <fstream>
#include <filesystem>

using namespace std;

FileSystem::FileSystem(int count, FSNode* root) : count(count), root(root)
{
	//do nothing
}

FileSystem::~FileSystem()
{
	if (count > 0)
	{
		deleteElements();
	}
}

Node* FindChild(Node* parent, const string realFilePath, FileSystem* f) {

	Node* curr = f->getRoot();
	Node* found = f->getRoot();

	if (parent != nullptr)
	{
		curr = parent->getFirstChild();

		if (curr != nullptr)
		{
			do
			{
				FSNode* temp;
				temp = dynamic_cast<FSNode*>(curr);
			
				FSNode* comp;
				comp = dynamic_cast<FSNode*>(parent);
			
				if ((temp != nullptr) && (comp != nullptr))
				{
					string compstr = realFilePath;
					if (comp->getName() != "")
					{
						compstr = comp->getName() + "/" + realFilePath;
					}

					if (temp->getName() == compstr)
					{
						found = curr;
					}
				}
					
				curr = curr->getNextSibling();
				
				if (curr == nullptr)
				{
					break;
				}
			} while (curr != nullptr);

		}
	}
	
	return found;
}

Node* FindParent(const string path, FileSystem* f)
{

	//path is root
	if (path == "")
	{
		return nullptr;
	}
	else {
		Node* prevChild = nullptr;
		Node* lastChild = nullptr;

		char* writable = new char[path.size() + 1];
	

		std::copy(path.begin(), path.end(), writable);
		writable[path.size()] = '\0';

		uint32_t tokennum;
		char* tokenptr;

		for (tokennum = 1; (tokenptr = strtok(writable, "/")) != nullptr; writable = nullptr, tokennum++) {
			lastChild = FindChild(prevChild, tokenptr, f);
			prevChild = lastChild;
		}

		delete[] writable;

		if (lastChild == nullptr)
		{
			//parent not found 
			cout << "specified path not found!" << endl;
			return nullptr;
		}
		return lastChild;
	}
}

void FileSystem::touch(const std::string& path, const std::string& fileName)
{
	const string realFilePath = path + "/" + fileName;

	cout << "      making file " << realFilePath << " ..." << endl;
	//handle tree
	//find parent through path
	Node* parent = FindParent(path,this);
	//insert at parent
	File* myNewNode = new File(nullptr,nullptr);
	
	myNewNode->setName(realFilePath);

	if (parent == nullptr)
	{
		Directory* myEmptyRoot = new Directory(nullptr,nullptr);
		
		myEmptyRoot->setName("");
		root = myNewNode;
	}

	insertChild(parent, myNewNode);
	std::ofstream file{ realFilePath };
}

void FileSystem::mkdir(const std::string& path, const std::string& dirName)
{
	string realFilePath = path;

	if (path != "")
	{
		realFilePath = path + "/" + dirName;
	}
	else
	{
		realFilePath = dirName;
	}

	cout << "      making dir " << realFilePath << " ..." << endl;
	//handle tree
	Node* parent = nullptr;
		
	if (path != "")
	{
		 parent = FindParent(path,this);
	}
	 //insert at parent
	 Directory* myNewNode = new Directory(nullptr,nullptr);
	 if (myNewNode == nullptr)
	 {
		 cout << "mem exhausted" << endl;
		 throw std::exception();

	 }

	 myNewNode->setName(realFilePath);

	 if (parent == nullptr)
	 {
		 root = myNewNode;
	 }
	insertChild(parent, myNewNode);
	filesystem::create_directory(realFilePath);	
}

void FileSystem::rm(const std::string& path, const std::string& fileName)
{
	string realFilePath = path;

	if (path != "")
	{
		realFilePath = path + "/" + fileName;
	}
	else
	{
		realFilePath = fileName;
	}
	cout << "      removing file " << realFilePath << " ..." << endl;
	//handle tree
	if (path == "")
	{
		Node* myFoundNode = FindChild(getRoot(), realFilePath,this);

		if (myFoundNode == getRoot())
		{
			delete getRoot();
			count = 0;
			Tree::count = 0;
		}
		else
		{
			deleteSingleChild(getRoot(), myFoundNode);
		}
	}
	else {
		Node* parent = FindParent(path, this);
		Node* myFoundNode = FindChild(parent,fileName, this);	
		deleteSingleChild(parent, myFoundNode);
	}

	filesystem::remove(realFilePath);
}

void FileSystem::rmdir(const std::string& path, const std::string& dirName)
{
	string realFilePath = path;

	if (path != "")
	{
		realFilePath = path + "/" + dirName;
	}
	else
	{
		realFilePath = dirName;
	}

	cout << "      removing dir " << realFilePath << " ..." << endl;
	//handle tree
	if (path == "")
	{
		Node* myFoundNode = FindChild(getRoot(), realFilePath, this);

		if (myFoundNode != nullptr)
		{
			if (myFoundNode->getFirstChild() != nullptr)
			{
				cout << "ERROR: cannot delete folder that is not empty!" << endl;
			}
			else {

				if (myFoundNode == getRoot())
				{
					delete getRoot();
					count = 0;
					Tree::count = 0;
				}
				else
				{
					deleteSingleChild(getRoot(), myFoundNode);
				}
				filesystem::remove_all(realFilePath);
			}
		}
	
	}
	else {
		Node* parent = FindParent(path, this);
		Node* myFoundNode = FindChild(parent, dirName, this);

		if (myFoundNode != nullptr)
		{
			if (myFoundNode->getFirstChild() != nullptr)
			{
				cout << "ERROR: cannot delete folder that is not empty!" << endl;
			}
			else {
				deleteSingleChild(parent, myFoundNode);
				filesystem::remove_all(realFilePath);
			}
		}

	}
}

void FileSystem::ls() const
{
	print(cout);
}

