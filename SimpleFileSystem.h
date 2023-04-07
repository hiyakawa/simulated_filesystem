#pragma once

#include "AbstractFileSystem.h"
#include <map>

class SimpleFileSystem : public AbstractFileSystem {
private:
    std::map<std::string, AbstractFile*> allFiles_;
    std::set<AbstractFile*>              openFiles_;

public:
	int                   addFile(std::string, AbstractFile*) override;
    AbstractFile*         openFile(std::string) override;
    int                   closeFile(AbstractFile*) override;
    int                   deleteFile(std::string) override;
    std::set<std::string> getFileNames() override;
};