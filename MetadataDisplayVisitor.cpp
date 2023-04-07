#include "MetadataDisplayVisitor.h"
#include "TextFile.h"
#include "ImageFile.h"

#include <iostream>

void MetadataDisplayVisitor::visitTextFile(TextFile* txtfile) {
	std::cout << txtfile->getName();

	for (std::size_t i = 0; i < 20 - txtfile->getName().size(); ++i) {
		std::cout << " ";
	}

	std::cout << "text " << txtfile->getSize() << std::endl;
}

void MetadataDisplayVisitor::visitImageFile(ImageFile* imgfile) {
	std::cout << imgfile->getName();

	for (std::size_t i = 0; i < 20 - imgfile->getName().size(); ++i) {
		std::cout << " ";
	}

	std::cout << "image " << imgfile->getSize() << std::endl;
}
