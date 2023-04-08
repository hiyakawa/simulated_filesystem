#include "PasswordProxy.h"
#include <iostream>

PasswordProxy::PasswordProxy(AbstractFile* file, std::string password) {
    file_ = file;
    password_ = password;
}

PasswordProxy::~PasswordProxy() {
	delete file_;
}

std::string PasswordProxy::passwordPrompt() {
    std::cout << "Please enter your password: " << std::endl;

    std::string input;
	getline(std::cin, input);

	return input;
}

std::vector<char> PasswordProxy::read() {
	if (passwordPrompt() == password_) {
		return file_->read();
	}

    std::vector<char> emptyVec;

    return emptyVec;
}

int PasswordProxy::write(std::vector<char> vec) {
	if (passwordPrompt() == password_) {
		return file_->write(vec);
	}

    return INVALID_PASSWORD;
}

int PasswordProxy::append(std::vector<char> vec) {
	if (passwordPrompt() == password_) {
		return file_->append(vec);
	}

    return INVALID_PASSWORD;
}

unsigned int PasswordProxy::getSize() {
	return file_->getSize();
}

std::string PasswordProxy::getName() {
	return file_->getName();
}

void PasswordProxy::accept(AbstractFileVisitor* visit) {
	if (passwordPrompt() == password_) {
		file_->accept(visit);
	}
}