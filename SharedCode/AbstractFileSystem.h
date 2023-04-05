#pragma once

#include "AbstractFile.h"

#include <string>
#include <vector>
#include <set>

using namespace std;

class AbstractFileSystem
{
public:
	virtual int addFile(string, AbstractFile*) = 0;
	virtual int createFile(string) = 0;
	virtual int deleteFile(string) = 0;
	virtual AbstractFile* openFile(string) = 0;
	virtual int closeFile(AbstractFile*) = 0;
	virtual set<string> getFileNames() = 0;
}