#pragma once

#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractParsingStrategy.h"

#include <string>
#include <vector>

using namespace std;

class MacroCommand : public AbstractCommand
{
public:
	MacroCommand(AbstractFileSystem*);
	virtual ~MacroCommand() = default;

	virtual int execute(string) override;
	virtual void displayInfo() override;
	void addCommand(AbstractCommand*);
	void setParseStrategy(AbstractParsingStrategy*);

private:
	vector<AbstractCommand*> commands;
	AbstractParsingStrategy* aps;
	AbstractFileSystem* afs;
};