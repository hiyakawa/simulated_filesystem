#pragma once

#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
#include "AbstractFileSystem.h"

using namespace std;

class DisplayCommand : public AbstractCommand
{
public:
	DisplayCommand(AbstractFileSystem*);
	virtual ~DisplayCommand() = default;

	virtual int execute(string) override;
	virtual void displayInfo() override;

private:
	AbstractFileSystem* afs;
};