#include "RemoveCommand.h"

#include <iostream>

using namespace std;

RemoveCommand::RemoveCommand(AbstractFileSystem* afs)
	: afs(afs) {}

int RemoveCommand::execute(string file_name)
{
	set<string> files;
	files = afs->getFileNames();

	if (files.find(file_name) == files.end())
	{
		return file_doesnot_exist;
	}

	return afs->deleteFile(file_name);
}

void RemoveCommand::displayInfo()
{
	cout << "The command should be invoked by the user with 'rm < filename>'." << endl;
}