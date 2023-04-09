#include "CommandTest.h"

CommandTest::CommandTest(AbstractFileSystem* _afs): afs(_afs) {}

int CommandTest::execute(std::string info) {
	if (info == "") {
        std::cout << "command-test-no-info" << std::endl;
	}
	else {
		replace(info.begin(), info.end(), ' ', ':');
        std::cout << "\n" << info << "\n" << std::endl;
	}

	return success;
}

void CommandTest::displayInfo() {
    std::cout << "aRandomStringz" << std::endl;
}
