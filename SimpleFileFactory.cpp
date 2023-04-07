#include "SimpleFileFactory.h"
#include "TextFile.h"
#include "ImageFile.h"

AbstractFile* SimpleFileFactory::createFile(std::string filename) {
	std::string extension = filename.substr(filename.find('.'));
    AbstractFile* newFile;

	if (extension == ".txt") {
        newFile = new TextFile(filename);
	}
    else if (extension == ".img") {
        newFile = new ImageFile(filename);
	}
    else {
        return nullptr;
    }

	return newFile;
}