#pragma once

#include <string>
#include <vector>

using namespace std;

class AbstractParsingStrategy
{
public:
	virtual vector<string> parse(string) = 0;
	virtual void displayInfo() = 0;
};