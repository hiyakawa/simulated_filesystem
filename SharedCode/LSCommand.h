#pragma once

#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
#include "AbstractFileSystem.h"

#include <string>

using namespace std;

class LSCommand : public AbstractCommand
{
public:
	LSCommand(AbstractFileSystem*);
	virtual ~LSCommand() = default;

	virtual int execute(string) override;
	virtual void displayInfo() override;

private:
	AbstractFileSystem* afs;
};