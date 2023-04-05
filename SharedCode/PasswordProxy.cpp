#include "PasswordProxy.h"

#include <iostream>

using namespace std;

PasswordProxy::PasswordProxy(AbstractFile* file, string password)
	: file(file), password(password) {}

PasswordProxy::~PasswordProxy()
{
	delete file;
}

string PasswordProxy::passwordPrompt()
{
	cout << "Please enter your password:" << endl;

	string s;
	getline(cin, s);

	return s;
}

bool PasswordProxy::matchPassword(string s)
{
	return !(s.compare(password));
}

vector<char> PasswordProxy::read()
{
	if (matchPassword(passwordPrompt()))
	{
		return file->read();
	}
	else
	{
		vector<char> vec;
		return vec;
	}
}

int PasswordProxy::write(vector<char> vec)
{
	if (matchPassword(passwordPrompt()))
	{
		return file->write(vec);
	}
	else
	{
		return invalid_password;
	}
}

int PasswordProxy::append(vector<char> vec)
{
	if (matchPassword(passwordPrompt()))
	{
		return file->append(vec);
	}
	else
	{
		return invalid_password;
	}
}

unsigned int PasswordProxy::getSize()
{
	return file->getSize();
}

string PasswordProxy::getName()
{
	return file->getName();
}

void PasswordProxy::accept(AbstractFileVisitor* visit)
{
	if (matchPassword(passwordPrompt()))
	{
		file->accept(visit);
	}
}