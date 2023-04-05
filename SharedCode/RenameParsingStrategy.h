#pragma once

#include "AbstractParsingStrategy.h"

#include <string>
#include <vector>

using namespace std;

class RenameParsingStrategy : public AbstractParsingStrategy
{
public:
	virtual vector<string> parse(string) override;
	virtual void displayInfo() override;
};