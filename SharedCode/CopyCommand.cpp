#include "CopyCommand.h"
#include "AbstractFileFactory.h"

#include <iostream>
#include <sstream>

using namespace std;

CopyCommand::CopyCommand(AbstractFileSystem* afs)
	: afs(afs) {}

int CopyCommand::execute(string s)
{
	string file_name;
	string new_name;
	istringstream iss(s);
	iss >> file_name;
	iss >> new_name;

	set<string> files;
	files = afs->getFileNames();

	if (files.find(file_name) == files.end())
	{
		return copy_failed;
	}

	string full_name = new_name + file_name.substr(file_name.find('.'));

	if (files.find(full_name) != files.end())
	{
		return copy_failed;
	}

	AbstractFile* file = afs->openFile(file_name);
	AbstractFile* copy = file->clone(full_name);
	afs->closeFile(file);

	return afs->addFile(copy->getName(), copy);
}

void CopyCommand::displayInfo()
{
	cout << "The copy command is invoked with 'cp <file_to_copy> <new_name_with_no_extension>'." << endl;
}