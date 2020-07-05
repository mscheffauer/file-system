#pragma once

#include "File.h"
#include "Directory.h"
#include "Tree.h"

class FileSystem : public Tree {
protected:
	FSNode* root = nullptr;
	int count = 0;
public:

	explicit FileSystem() = default;
	explicit FileSystem(int count, FSNode* root);
	virtual ~FileSystem();
	explicit FileSystem(const FileSystem& n) = default;

	void touch(const std::string& path, const std::string& fileName); // create new file
	void mkdir(const std::string& path, const std::string& dirName); // create new directory
	void rm(const std::string& path, const std::string& fileName); // remove file
	void rmdir(const std::string& path, const std::string& dirName); // remove directory
	void ls() const; // list contents of file system = print tree

	FileSystem& operator=(const FileSystem& n) = default;

};

