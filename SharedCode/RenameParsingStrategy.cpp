#include "RenameParsingStrategy.h"

#include <sstream>
#include <iostream>

using namespace std;

vector<string> RenameParsingStrategy::parse(string s)
{
	string first_word;
	string second_word;

	istringstream iss(s);

	iss >> first_word;
	iss >> second_word;

	vector<string> vec;
	vec.push_back(first_word + " " + second_word);
	vec.push_back(first_word);

	return vec;
}

void RenameParsingStrategy::displayInfo()
{
	cout << "Rename can be invoked by the user with 'rn' as '$ rn <existing_file> <new_name_with_no_extension>'." << endl;
}