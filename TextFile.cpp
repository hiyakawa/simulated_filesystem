#include "TextFile.h"
#include <iostream>

//TextFile::TextFile()
//	: filename_(""), contents_(vector<char>()) {}

TextFile::TextFile(std::string filename) {
    filename_ = filename;
}

//TextFile::TextFile(const TextFile& c)
//	: filename_(c.filename_), contents_(c.contents_) {}
//
//TextFile::TextFile(TextFile&& c)
//	: filename_(c.filename_), contents_(c.contents_)
//{
//	c.filename_ = "";
//	c.contents_.resize(0);
//}

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

void TextFile::read() {
    for (std::size_t i = 0; i < contents_.size(); i++) {
		std::cout << contents_[i];
	}
}

//void TextFile::accept(AbstractFileVisitor* visit)
//{
//	visit->visit_TextFile(this);
//}
//
//AbstractFile* TextFile::clone(string new_name)
//{
//	AbstractFile* copy = new TextFile(new_name);
//	copy->write(this->read());
//
//	return copy;
//}