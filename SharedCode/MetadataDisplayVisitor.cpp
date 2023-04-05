#include "MetadataDisplayVisitor.h"
#include "TextFile.h"
#include "ImageFile.h"

#include <iostream>

using namespace std;

void MetadataDisplayVisitor::visit_TextFile(TextFile* txt_file)
{
	cout << txt_file->getName();

	for (unsigned int i = 0; i < 20 - txt_file->getName().size(); ++i)
	{
		cout << " ";
	}

	cout << "text " << txt_file->getSize();
}

void MetadataDisplayVisitor::visit_ImageFile(ImageFile* img_file)
{
	cout << img_file->getName();

	for (unsigned int i = 0; i < 20 - img_file->getName().size(); ++i)
	{
		cout << " ";
	}

	cout << "image" << img_file->getSize();
}
