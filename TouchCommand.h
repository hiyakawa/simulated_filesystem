#pragma once

#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
#include "AbstractFileSystem.h"

class TouchCommand : public AbstractCommand {
private:
    AbstractFileSystem*  afs_;
    AbstractFileFactory* aff_;

public:
    TouchCommand(AbstractFileSystem*, AbstractFileFactory*);

    int  execute(std::string) override;
	void displayInfo() override;
};