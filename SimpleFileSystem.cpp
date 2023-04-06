#include "SimpleFileSystem.h"
#include "TextFile.h"
#include "ImageFile.h"
#include <iostream>
#include <fstream>

int SimpleFileSystem::addFile(std::string filename, AbstractFile* file) {
	if (allFiles_.find(filename) != allFiles_.end()) {
		return FILE_ALREADY_EXIST;
	}

    if (file == nullptr) {
        return NULL_PTR_ERROR;
    }

    std::pair<std::string, AbstractFile*> p = make_pair(filename, file);
    allFiles_.insert(p);

    return SUCCESS;
}

int SimpleFileSystem::createFile(std::string name) {
    std::string extension = name.substr(name.find('.'));

	if (allFiles_.find(name) != allFiles_.end()) {
		return FILE_ALREADY_EXIST;
	}

    AbstractFile* newFile;

    if (extension == ".txt") {
        newFile = new TextFile(name);
    }
    else if (extension == ".img") {
        newFile = new ImageFile(name);
    }
    else {
        return INVALID_EXTENSION;
    }

    std::pair<std::string, AbstractFile*> p = make_pair(newFile->getName(), newFile);
    allFiles_.insert(p);

	return SUCCESS;
}

AbstractFile* SimpleFileSystem::openFile(std::string filename) {
    std::ifstream ifs(filename);
    
	if (allFiles_.find(filename) != allFiles_.end()) {
		if (openFiles_.find(allFiles_[filename]) == openFiles_.end()) {
			openFiles_.insert(allFiles_[filename]);
            
			return allFiles_[filename];
		}
	}

	return nullptr;
}

int SimpleFileSystem::closeFile(AbstractFile* file) {
	if (openFiles_.find(file) != openFiles_.end()) {
		openFiles_.erase(file);

		return SUCCESS;
	}

	return FILE_FAILED_OPEN;
}

int SimpleFileSystem::deleteFile(std::string filename) {
	if (allFiles_.find(filename) != allFiles_.end()) {
		auto file = allFiles_.find(filename);

		if (openFiles_.find(file->second) != openFiles_.end()) {
			return FILE_ALREADY_OPEN;
		}

        allFiles_.erase(file);

        return SUCCESS;
	}

    return FILE_INEXIST;
}

std::set<std::string> SimpleFileSystem::getFileNames() {
    std::set<std::string> fileNames;

	for (auto i = allFiles_.begin(); i != allFiles_.end(); i++) {
		fileNames.insert(i->first);
	}

	return fileNames;
}
