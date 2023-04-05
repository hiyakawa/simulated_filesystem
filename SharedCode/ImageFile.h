#pragma once

#include "AbstractFile.h"

#include <string>
#include <vector>

using namespace std;

class ImageFile : public AbstractFile
{
public:
	ImageFile(string name);

	virtual vector <char> read() override;
	virtual int write(vector<char>) override;
	virtual int append(vector<char>) override;
	virtual unsigned int getSize() override;
	virtual string getName() override;
	virtual void accept(AbstractFileVisitor*) override;
	virtual AbstractFile* clone(string) override;

private:
	string name;
	vector<char> contents;
	char size;
}