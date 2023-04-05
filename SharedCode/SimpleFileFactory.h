#pragma once

#include "AbstractFileFactory.h"

using namespace std;

class SimpleFileFactory : public AbstractFileFactory
{
public:
	virtual AbstractFile* createFile(string name) override;
};