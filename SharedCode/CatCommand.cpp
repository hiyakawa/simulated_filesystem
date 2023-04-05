#include "CatCommand.h"
#include "AbstractFile.h"
#include "AbstractFileFactory.h"
#include "BasicDisplayVisitor.h"
#include "LSCommand.h"

#include <iostream>
#include <sstream>

using namespace std;

CatCommand::CatCommand(AbstractFileSystem* afs)
	: afs(afs) {}

int CatCommand::execute(string s)
{
	istringstream iss(s);
	string file_name;
	string context;
	iss >> file_name;
	iss >> context;

	AbstractFile* file = afs->openFile(file_name);

	if (file == nullptr)
	{
		afs->closeFile(file);

		return cat_failed;
	}

	if (context.compare("-a") == 0)
	{
		AbstractFileVisitor* visit = new BasicDisplayVisitor();
		file->accept(visit);

		cout << endl;
		cout << "Please input data to append to the file, \":wq\" to save and quit, or \":q\" to quit without saving." << endl;

		string input;
		string line;
		unsigned int result = success;

		while (result == success)
		{
			getline(cin, line);

			if (line.compare(":wq") == 0)
			{
				result = cat_save;
			}

			if (line.compare(":q") == 0)
			{
				result = cat_quit;
			}

			input += line + "\n";
			line = "";
		}

		if (result == cat_quit)
		{
			afs->closeFile(file);

			return success;
		}

		if (result == cat_save)
		{
			string extension = file_name.substr(file_name.find("."));

			if (extension.compare(".img") == 0)
			{
				afs->closeFile(file);

				return cat_failed;
			}

			if (input.size() > l)
			{
				vector<char> vec(input.length() - l);
				copy(input.begin(), input.end() - l, vec.begin());
				file->append(vec);
			}

			afs->closeFile(file);

			return success;
		}
	}

	else
	{
		cout << "Please input data to write to the file, \":wq\" to save and quit, or \":q\" to quit without saving." << endl;

		string input;
		string line;
		unsigned int result = success;

		while (result == success)
		{
			getline(cin, line);

			if (line.compare(":wq") == 0)
			{
				result = cat_save;
			}
			if (line.compare(":q") == 0)
			{
				result = cat_quit;
			}

			input += line + "\n";
			line = "";
		}

		if (result == cat_quit)
		{
			afs->closeFile(file);

			return success;
		}

		if (result == cat_save)
		{
			if (input.size() > l)
			{
				vector<char> vec(input.length() - l);
				copy(input.begin(), input.end() - l, vec.begin());
				file->write(vec);
			}

			afs->closeFile(file);

			return success;
		}
	}

	afs->closeFile(file);

	return cat_failed;
}

void CatCommand::displayInfo()
{
	cout << "Cat can be invoked from the command prompt as '$ cat <filename>[-a]'." << endl;
}