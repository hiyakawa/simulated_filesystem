#include "DisplayCommand.h"
#include "AbstractFileFactory.h"
#include "BasicDisplayVisitor.h"

#include <iostream>
#include <sstream>

using namespace std;

DisplayCommand::DisplayCommand(AbstractFileSystem* afs)
	: afs(afs) {}

int DisplayCommand::execute(string s)
{
	string file_name;
	string context;
	istringstream iss(s);
	iss >> file_name;
	iss >> context;

	set<string> files;
	files = afs->getFileNames();

	if (files.find(file_name) == files.end())
	{
		return display_failed;
	}

	AbstractFile* file = afs->openFile(file_name);

	if (file == nullptr)
	{
		return null_ptr;
	}

	if (context.compare("-d") == 0)
	{
		vector<char> contents = file->read();

		for (unsigned int i = 0; i < contents.size(); ++i)
		{
			if (contents[i] == '\n')
			{
				cout << endl;
			}
			else
			{
				cout << contents[i];
			}
		}
		cout << endl;

		afs->closeFile(file);

		return success;
	}

	else
	{
		AbstractFileVisitor* visit = new BasicDisplayVisitor();
		file->accept(visit);
		afs->closeFile(file);

		return success;
	}
}

void DisplayCommand::displayInfo()
{
	cout << "Display is invoked with 'ds'." << endl;
}