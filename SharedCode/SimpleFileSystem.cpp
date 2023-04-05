#include "SimpleFileSystem.h"
#include "TextFile.h"
#include "ImageFile.h"

#include <iostream>

using namespace std;

int SimpleFileSystem::addFile(string name, AbstractFile* file_ptr)
{
	if (allFiles.find(name) != allFiles.end())
	{
		return file_already_exist;
	}
	else
	{
		if (file_ptr == nullptr)
		{
			return null_ptr;
		}
		else
		{
			allFiles.insert(pair<string, AbstractFile*>(name, file_ptr));
			return success;
		}
	}
}

int SimpleFileSystem::createFile(string name)
{
	string extension = name.substr(name.find('.'));

	if (allFiles.find(name) != allFiles.end())
	{
		return file_already_exist;
	}
	else
	{
		if (extension.compare(".txt") == 0)
		{
			AbstractFile* new_txt = (new TextFile(name));
		}
		else if (extension.compare(".img") == 0)
		{
			AbstractFile* new_img = (new ImageFile(name));
		}
		else
		{
			return invalid_extension;
		}
	}

	return success;
}

AbstractFile* SimpleFileSystem::openFile(string name)
{
	if (allFiles.find(name) != allFiles.end())
	{
		AbstractFile* file = allFiles.find(name);

		if (openedFiles.find(file) == openedFiles.end())
		{
			openedFiles.insert(file);

			return file;
		}
	}

	return nullptr;
}

int SimpleFileSystem::closeFile(AbstractFile* file)
{
	if (openedFiles.find(file) != openedFiles.end())
	{
		openedFiles.erase(file);

		return success;
	}

	return file_open_failed;
}

int SimpleFileSystem::deleteFile(string name)
{
	if (allFiles.find(name) == allFiles.end())
	{
		AbstractFile* file = allFiles.find(name);

		if (openedFiles.find(file) != openedFiles.end())
		{
			return file_already_open;
		}
		else
		{
			allFiles.erase(name);
			delete file;

			return success;
		}
	}
	else
	{
		return file_doesnot_exist;
	}
}

set<string> SimpleFileSystem::getFileNames()
{
	set<string> file_name;

	map<string, AbstractFile*>::iterator iter;

	for (iter = allFiles.begin(); iter != allFiles.end(); ++iter)
	{
		file_name.insert(iter->first);
	}

	return file_name;
}