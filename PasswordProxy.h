#pragma once

#include "AbstractFile.h"

class PasswordProxy : public AbstractFile {
private:
    AbstractFile* file_;
    std::string   password_;

protected:
    std::string passwordPrompt();

public:
	PasswordProxy(AbstractFile*, std::string);
	~PasswordProxy();

	std::vector<char> read() override;
	int write(std::vector<char>) override;
	int append(std::vector<char>) override;
	unsigned int getSize() override;
    std::string getName() override;
	void accept(AbstractFileVisitor*) override;
//    AbstractFile* clone(std::string) override;
};