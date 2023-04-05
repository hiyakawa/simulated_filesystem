#include "TouchCommand.h"
#include "AbstractFile.h"
#include "AbstractFileFactory.h"
#include "LSCommand.h"
#include "MetadataDisplayVisitor.h"

#include <set>
#include <iostream>

using namespace std;

LSCommand::LSCommand(AbstractFileSystem* afs)
	: afs(afs) {}

int LSCommand::execute(string s)
{
	set<string> names = afs->getFileNames();
	set<string>::iterator iter;

	if (s.compare("-m") == 0)
	{
		for (iter = names.begin(); iter != names.end(); ++iter)
		{
			AbstractFileVisitor* visit = new MetadataDisplayVisitor();
			AbstractFile* file = afs->openFile(*iter);

			file->accept(visit);
			afs->closeFile(file);

			cout << endl;
		}
	}

	else if (s.compare("") == 0)
	{
		int i = 0;

		for (iter = names.begin(); iter != names.end(); ++iter)
		{
			cout << *iter;

			if (i % 2 == 0)
			{
				for (unsigned int j = 0; j < 20 - iter->size(); j++)
				{
					cout << " ";
				}
			}
			else
			{
				cout << endl;
			}

			++i;
		}
	}
	else
	{
		return ls_error;
	}

	cout << endl;

	return success;
}

void LSCommand::displayInfo()
{
	cout << "The LSCommand will be invoked by the user by typing 'ls' into the command prompt." << endl;
}