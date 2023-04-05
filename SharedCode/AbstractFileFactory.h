#pragma once

#include "AbstractFile.h"

#include <string>

using namespace std;

class AbstractFileFactory
{
public:
	virtual AbstractFile* createFile(string) = 0;
};