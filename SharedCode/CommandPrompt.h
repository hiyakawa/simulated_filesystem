#pragma once

#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"

#include <map>

class CommandPrompt
{
public:
	CommandPrompt();

	void setFileSystem(AbstractFileSystem*);
	void setFileFactory(AbstractFileFactory*);
	int addCommand(string, AbstractCommand*);
	int run();

protected:
	void listCommands();
	string prompt();

private:
	map<string, AbstractCommand*> command;
	AbstractFileSystem* afs;
	AbstractFileFactory* aff;
};