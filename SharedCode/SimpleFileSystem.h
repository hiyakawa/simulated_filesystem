#pragma once

#include "AbstractFileSystem.h"

#include <map>
#include <set>

using namespace std;

class SimpleFileSystem : public AbstractFileSystem
{
public:
	virtual int addFile(string, AbstractFile*) override;
	virtual int createFile(string) override;
	virtual int deleteFile(string) override;
	virtual AbstractFile* openFile(string) override;
	virtual int closeFile(AbstractFile*) override;
	virtual set<string> getFileNames() override;

private:
	map<string, AbstractFile*> allFiles;
	set<AbstractFile*> openedFiles;
};