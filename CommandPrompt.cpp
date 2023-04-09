#include "CommandPrompt.h"
#include <iostream>
#include <sstream>

CommandPrompt::CommandPrompt() {
    afs_ = nullptr;
    aff_ = nullptr;
}

void CommandPrompt::setFileSystem(AbstractFileSystem* afs) {
	afs_ = afs;
}

void CommandPrompt::setFileFactory(AbstractFileFactory* aff) {
	aff_ = aff;
}

int CommandPrompt::addCommand(std::string str, AbstractCommand* command) {
	auto i = command_.insert(std::pair<std::string, AbstractCommand*>(str, command));

	if (i.second) {
		return SUCCESS;
	}

    return INSERTION_FAILED;
}

void CommandPrompt::listCommands() {
	for (auto& i : command_) {
		std::cout << i.first << " ";
	}

	std::cout << std::endl;
}

std::string CommandPrompt::prompt() {
	std::cout << "Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command." << std::endl;
	std::cout << "$ ";

	std::string input;
	getline(std::cin, input);

	return input;
}

int CommandPrompt::run() {
    while (true) {
        std::string input = prompt();

        if (input == "q") {
            return USER_QUIT;
        }

        if (input == "help") {
            listCommands();

            return USER_HELP;
        }

        if (input.find(' ') == std::string::npos) {
            int count = 0;

            for (auto& i : command_) {
                if (i.first == input) {
                    count++;
                    i.second->execute("");
                }
            }

            if (count == 0) {
                std::cout << "Command does not exist." << std::endl;
            }
        }
        else {
            std::istringstream iss;
            std::string firstWord;
            iss.str(input);
            iss >> firstWord;

            if (firstWord == "help") {
                std::string secondWord;
                iss >> secondWord;

                int count = 0;

                for (auto& i : command_) {
                    if (i.first == secondWord) {
                        count++;
                        i.second->displayInfo();
                    }
                }

                if (count == 0) {
                    std::cout << "Command does not exist." << std::endl;
                }
            }

            int count = 0;

            for (auto& i : command_) {
                if (i.first == firstWord) {
                    count++;
                    i.second->execute(input.substr(input.find(' ') + 1));
                }
            }
            if (count == 0) {
                std::cout << "Command does not exist." << std::endl;
            }
        }
    }
}