#include "SimpleFileFactory.h"
#include "TextFile.h"
#include "ImageFile.h"

using namespace std;

AbstractFile* SimpleFileFactory::createFile(string name)
{
	string extension = name.substr(name.find('.'));

	if (extension.compare(".txt") == 0)
	{
		AbstractFile* new_txt = (new TextFile(name));
		return new_txt;
	}
	else if (extension.compare(".img") == 0)
	{
		AbstractFile* new_img = (new ImageFile(name));
		return new_img;
	}
	return nullptr;
}