#pragma once

#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
#include "AbstractFileSystem.h"

using namespace std;

class TouchCommand : public AbstractCommand
{
public:
	TouchCommand(AbstractFileSystem*, AbstractFileFactory*);
	virtual ~TouchCommand() = default;

	virtual int execute(string) override;
	virtual void displayInfo() override;

private:
	AbstractFileSystem* afs;
	AbstractFileFactory* aff;
};