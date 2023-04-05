#include "ImageFile.h"

#include<iostream>

using namespace std;

ImageFile::ImageFile(string name)
	: name(name), size(0) {}

unsigned int ImageFile::getSize()
{
	unsigned int size_ = (unsigned int)contents.size();
	return size_;
}

string ImageFile::getName()
{
	return name;
}

int ImageFile::write(vector<char> vec)
{
	unsigned int size_i = (unsigned int)vec.size();
	char size_c = vec[size_i - 1];
	size_t ctoi = (size_t)size_c - '0';

	vector<char> vec_(contents);
	vec_.resize((ctoi ^ 2), 0);

	if (size_i - 1 != vec_.size()) {
		vec.clear();
		vec.resize(0, 0);

		return write_failed;
	}

	else
	{
		for (unsigned int i = 0; i < vec.size() - 1; i++)
		{
			if (vec[i] != 'X' && vec[i] != ' ')
			{
				vec.clear();
				vec.resize(0, 0);

				return write_failed;
			}
		}

		for (int i = 0; i < vec_.size(); i++)
		{
			if (vec_[i] != ' ' || vec_[i] != 'X')
			{
				vec_[i] = vec[i];
			}
			else
			{
				vec.clear();
				vec.resize(0, 0);

				return write_failed;
			}
		}
	}

	contents = vec_;
	this->size = ctoi;

	return success;
}

int ImageFile::append(vector<char> vec)
{
	return no_append_for_image;
}

vector <char> ImageFile::read()
{
	vector<char> vec;
	int size_ = (int)size;

	for (int y = size_ - 1; y < size_; --y)
	{
		for (int x = 0; x < size_; ++x)
		{
			int index = y * size_ + x;
			vec.push_back(contents[index]);
		}
	}

	return vec;
}

void ImageFile::accept(AbstractFileVisitor* visit)
{
	visit->visit_ImageFile(this);
}

AbstractFile* ImageFile::clone(string new_name)
{
	AbstractFile* copy = new ImageFile(new_name);
	copy->write(this->read());

	return copy;
}