#include "TextFile.h"

TextFile::TextFile(std::string filename) {
    filename_ = filename;
}

unsigned int TextFile::getSize() {
    return contents_.size();
}

std::string TextFile::getName() {
    return filename_;
}

int TextFile::write(std::vector<char> input) {
    contents_ = input;

    return SUCCESS;
}

int TextFile::append(std::vector<char> input) {
    for (std::size_t i = 0; i < input.size(); i++) {
        contents_.push_back(input[i]);
    }

    return SUCCESS;
}

std::vector<char> TextFile::read() {
    return contents_;
}

void TextFile::accept(AbstractFileVisitor* visit) {
	visit->visitTextFile(this);
}

//AbstractFile* TextFile::clone(string new_name)
//{
//	AbstractFile* copy = new TextFile(new_name);
//	copy->write(this->read());
//
//	return copy;
//}