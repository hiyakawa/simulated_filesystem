#include "TextFile.h"

#include <iostream>

int main() {
	AbstractFile* new_file = new TextFile();

	cout << "Name: " << new_file->getName() << endl;
	cout << "Size: " << new_file->getSize() << endl;

	char word[] = { 'w', 'o', 'r', 'd' };
	vector<char> vec(word);

	new_file->append(vec);
	new_file->read();

	return 0;
}