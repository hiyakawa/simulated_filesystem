#pragma once

#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"
#include <map>

class CommandPrompt {
private:
    std::map<std::string, AbstractCommand*> command_;
    AbstractFileSystem* afs_;
    AbstractFileFactory* aff_;

public:
    CommandPrompt();
    ~CommandPrompt() = default;

    std::string prompt();
	void        setFileSystem(AbstractFileSystem*);
	void        setFileFactory(AbstractFileFactory*);
	int         addCommand(std::string, AbstractCommand*);
	int         run();
    void        listCommands();
};