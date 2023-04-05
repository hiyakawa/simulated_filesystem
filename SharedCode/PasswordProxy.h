#pragma once

#include "AbstractFile.h"

class PasswordProxy : public AbstractFile
{
public:
	PasswordProxy(AbstractFile*, string);
	~PasswordProxy();

	virtual vector<char> read() override;
	int write(vector<char>) override;
	int append(vector<char>) override;
	unsigned int getSize() override;
	string getName() override;
	void accept(AbstractFileVisitor*) override;

protected:
	string passwordPrompt();
	bool matchPassword(string);

private:
	AbstractFile* file;
	string password;
};