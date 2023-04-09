#include "TouchCommand.h"
#include "PasswordProxy.h"
#include <iostream>

TouchCommand::TouchCommand(AbstractFileSystem* afs, AbstractFileFactory* aff) {
    afs_ = afs;
    aff_ = aff;
}

int TouchCommand::execute(std::string command) {
    if (command.find("-p") != std::string::npos) {
        std::string fileName = command.substr(0, command.find(" "));
        AbstractFile* newFile = aff_->createFile(fileName);
        std::cout << "Enter Password:" << std::endl;
        std::cout << "$ ";
        std::string input;
        getline(std::cin, input);
        AbstractFile* newFilePassword = new PasswordProxy(newFile, input);

        if (afs_->addFile(fileName, newFilePassword) != 0) {
            std::cout << "Couldn't add file" << std::endl;

            return ADD_FAILED;
        }

        return SUCCESS;
    }
    else {
        AbstractFile* af = aff_->createFile(command);
        if (af != nullptr) {
            int i = afs_->addFile(command, af);

            if (i != 0) {
                delete af;

                return ADD_FAILED;
            }

            return SUCCESS;
        }

        return TOUCH_FAILED;
    }
}

void TouchCommand::displayInfo() {
	std::cout << "Touch creates a file, touch can be invoked with the command: touch <filename>." << std::endl;
}