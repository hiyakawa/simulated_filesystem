#include "CommandPrompt.h"

#include <iostream>
#include <sstream> 

using namespace std;

CommandPrompt::CommandPrompt()
	: afs(nullptr), aff(nullptr) {}

void CommandPrompt::setFileSystem(AbstractFileSystem* fs)
{
	this->afs = fs;
}

void CommandPrompt::setFileFactory(AbstractFileFactory* ff)
{
	this->aff = ff;
}

int CommandPrompt::addCommand(string s, AbstractCommand* ptr)
{
	auto i = command.insert(pair<string, AbstractCommand*>(s, ptr));

	if (i.second)
	{
		return success;
	}
	else
	{
		return insertion_failed;
	}
}

void CommandPrompt::listCommands()
{
	map<string, AbstractCommand*>::iterator iter;

	for (iter = command.begin(); iter != command.end(); iter++)
	{
		cout << iter->first << " ";
	}

	cout << endl;
}

string CommandPrompt::prompt()
{
	cout << "Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command." << endl;
	cout << "$ " << flush;

	string s;
	getline(cin, s);

	return s;
}

int CommandPrompt::run()
{
	string input = prompt();

	if (input.compare("q") == 0)
	{
		return user_quit;
	}
	
	if (input.compare("help") == 0)
	{
		listCommands();

		return user_help;
	}

	bool only_one_word = true;

	for (unsigned int i = 0; i < input.size(); ++i)
	{
		if (input[i] == ' ')
		{
			only_one_word = false;
		}
	}

	if (only_one_word)
	{
		auto i = command.find(input);

		if (i != command.end())
		{
			int result = i->second->execute("");

			if (result == success)
			{
				return success;
			}
			else
			{
				cout << "The command returns an error." << endl;
			}
		}
		else
		{
			cout << "The command did not exist." << endl;
		}
		
		return command_error;
	}

	else
	{
		istringstream iss;
		iss.str(input);
		string first_word;
		iss >> first_word;

		if (first_word.compare("help") == 0)
		{
			string second_word;
			iss >> second_word;

			auto i = command.find(second_word);

			if (i != command.end())
			{
				i->second->displayInfo();

				return success;
			}

			cout << "The command did not exist." << endl;

			return command_error;
		}

		string command_context = input.substr(input.find(' ') + 1);

		auto i = command.find(first_word);

		if (i != command.end())
		{
			int result = i->second->execute(command_context);

			if (result == success)
			{
				return success;
			}
			else
			{
				cout << "The command returns an error." << endl;
			}
		}

		cout << "The command did not exist." << endl;

		return command_error;
	}
}