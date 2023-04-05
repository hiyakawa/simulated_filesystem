#pragma once

#include "AbstractCommand.h"
#include "AbstractFileSystem.h"

#include <string>

using namespace std;

class CopyCommand : public AbstractCommand
{
public:
	CopyCommand(AbstractFileSystem*);
	virtual ~CopyCommand() = default;

	virtual int execute(string) override;
	virtual void displayInfo() override;

private:
	AbstractFileSystem* afs;
};