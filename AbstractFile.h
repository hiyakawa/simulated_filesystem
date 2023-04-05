#pragma once

//#include "AbstractFileVisitor.h"
#include <string>
#include <vector>

class AbstractFile {
public:
	~AbstractFile() = default;

	virtual void          read() = 0;
	virtual int           write(std::vector<char>) = 0;
	virtual int           append(std::vector<char>) = 0;
	virtual unsigned int  getSize() = 0;
	virtual std::string   getName() = 0;
//	virtual void          accept(AbstractFileVisitor*) = 0;
//	virtual AbstractFile* clone(std::string) = 0;
};

enum results {
	SUCCESS,
	no_append_for_image,
	file_already_exist,
	null_ptr,
	invalid_extension,
	l,
	file_open_failed,
	file_already_open,
	file_doesnot_exist,
	invalid_password,
	insertion_failed,
	user_quit,
	user_help,
	command_error,
	cat_failed,
	cat_save,
	cat_quit,
	copy_failed,
	display_failed,
	write_failed,
	ls_error,
	touch_failed
};