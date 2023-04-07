#include "BasicDisplayVisitor.h"
#include "TextFile.h"
#include "ImageFile.h"
#include <cmath>
#include <iostream>

void BasicDisplayVisitor::visitTextFile(TextFile* txtfile) {
	std::vector<char> contents = txtfile->read();

	for (std::size_t i = 0; i < contents.size(); i++) {
		std::cout << contents[i];
	}

	std::cout << std::endl;
}

void BasicDisplayVisitor::visitImageFile(ImageFile* imgfile) {
	std::vector<char> contents = imgfile->read();
	int i = (int)sqrt(imgfile->getSize());

	for (std::size_t y = i - 1; y < i; --y) {
		for (int x = 0; x < i; ++x) {
			std::cout << (contents[(y * i) + x]);
		}

		std::cout << std::endl;
	}
}