#pragma once

#include "AbstractCommand.h"
#include "AbstractFileSystem.h"

#include <string>

using namespace std;

class RemoveCommand : public AbstractCommand
{
public:
	RemoveCommand(AbstractFileSystem*);
	virtual ~RemoveCommand() = default;

	virtual int execute(string) override;
	virtual void displayInfo() override;

private:
	AbstractFileSystem* afs;
};