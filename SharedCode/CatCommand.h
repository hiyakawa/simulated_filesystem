#pragma once

#include "AbstractCommand.h"
#include "AbstractFileSystem.h"

#include <string>

using namespace std;

class CatCommand : public AbstractCommand
{
public:
	CatCommand(AbstractFileSystem*);
	virtual ~CatCommand() = default;

	virtual int execute(string) override;
	virtual void displayInfo() override;

private:
	AbstractFileSystem* afs;
};