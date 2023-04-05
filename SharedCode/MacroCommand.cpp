#include "MacroCommand.h"
#include "AbstractFileFactory.h"

#include <iostream>

using namespace std;

MacroCommand::MacroCommand(AbstractFileSystem* afs)
	: afs(afs), aps(nullptr) {}

int MacroCommand::execute(string s)
{
	vector<string> vec = aps->parse(s);

	for (unsigned int i = 0; i < commands.size(); i++)
	{
		string input = vec[i];
		int error = commands[i]->execute(input);

		if (error)
		{
			return error;
		}
	}

	return success;
}

void MacroCommand::displayInfo()
{
	if (aps != nullptr)
	{
		aps->displayInfo();
	}
	else
	{
		cout << "No macro commands." << endl;
	}
}

void MacroCommand::addCommand(AbstractCommand* ptr)
{
	commands.push_back(ptr);
}

void MacroCommand::setParseStrategy(AbstractParsingStrategy* ptr)
{
	this->aps = ptr;
}