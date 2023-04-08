#include "TouchCommand.h"
#include "AbstractFile.h"
#include "PasswordProxy.h"

#include <iostream>
#include <sstream>

using namespace std;

TouchCommand::TouchCommand(AbstractFileSystem* afs, AbstractFileFactory* aff)
	: afs(afs), aff(aff) {}

int TouchCommand::execute(string s)
{
	istringstream iss(s);
	string file_name;
	string context;
	iss >> file_name;
	iss >> context;

	if (context.compare("-p") == 0)
	{
		string password;

		cout << "Please enter your password." << endl;

		getline(cin, password);

		AbstractFile* file = this->aff->createFile(file_name);
		PasswordProxy* pp = new PasswordProxy(file, password);

		if (file == nullptr)
		{
			delete file;
		}

		else
		{
			if (this->afs->addFile(file_name, pp) == 0)
			{
				return success;
			}
		}
	}

	else
	{
		AbstractFile* file = this->aff->createFile(s);

		if (file == nullptr)
		{
			delete file;
		}

		else
		{
			if (this->afs->addFile(s, file) == 0)
			{
				return success;
			}
		}
	}

	return touch_failed;
}

void TouchCommand::displayInfo()
{
	cout << "Touch creates a file, touch can be invoked with the command: touch <filename>." << endl;
}