#include "ImageFile.h"
#include <iostream>

ImageFile::ImageFile(std::string filename) {
    filename_ = filename;
    imgsize_ = 0;
}

unsigned int ImageFile::getSize() {
	return contents_.size();
}

std::string ImageFile::getName() {
	return filename_;
}

int ImageFile::write(std::vector<char> vec) {
	unsigned int inputsize = vec.size();
	imgsize_ = vec[inputsize - 1];
	size_t imgsize = imgsize_ - '0';

	if (imgsize * imgsize != inputsize - 1) {
		contents_.clear();
		imgsize_ = '0';

		return INVALID_SIZE;
	}

    for (unsigned int i = 0; i < imgsize * imgsize; i++) {
        if (vec[i] != 'X' && vec[i] != ' ') {
            contents_.clear();
            imgsize_ = '0';

            return INVALID_SYMBOL;
        }
        else {
            contents_.push_back(vec[i]);
        }
    }

	return SUCCESS;
}

int ImageFile::append(std::vector<char> vec) {
	return NO_APPEND_FOR_IMAGES;
}

std::vector<char> ImageFile::read() {
    return contents_;
}

void ImageFile::accept(AbstractFileVisitor* visit) {
	visit->visitImageFile(this);
}

//AbstractFile* ImageFile::clone(string new_name)
//{
//	AbstractFile* copy = new ImageFile(new_name);
//	copy->write(this->read());
//
//	return copy;
//}