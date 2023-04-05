#include "BasicDisplayVisitor.h"
#include "TextFile.h"
#include "ImageFile.h"

#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

void BasicDisplayVisitor::visit_TextFile(TextFile* txt_file)
{
	vector<char> vec = txt_file->read();

	for (unsigned int i = 0; i < vec.size(); ++i)
	{
		cout << vec[i];
	}

	cout << endl;
}

void BasicDisplayVisitor::visit_ImageFile(ImageFile* img_file)
{
	vector<char> vec = img_file->read();

	int i = (int)sqrt(img_file->getSize());

	for (int y = i - 1; y < i; --y)
	{
		for (int x = 0; x < i; ++x)
		{
			cout << (vec[(y * i) + x]);
		}

		cout << endl;
	}
}