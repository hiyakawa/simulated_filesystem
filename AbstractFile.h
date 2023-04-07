#pragma once

#include "AbstractFileVisitor.h"
#include <string>
#include <vector>

class AbstractFile {
public:
	~AbstractFile() = default;

	virtual std::vector<char> read() = 0;
	virtual int               write(std::vector<char>) = 0;
	virtual int               append(std::vector<char>) = 0;
	virtual unsigned int      getSize() = 0;
	virtual std::string       getName() = 0;
	virtual void              accept(AbstractFileVisitor*) = 0;
//	virtual AbstractFile* clone(std::string) = 0;
};

enum results {
	SUCCESS,
    INVALID_SIZE,
    INVALID_SYMBOL,
    NO_APPEND_FOR_IMAGES,
    FILE_ALREADY_OPEN,
    FILE_FAILED_OPEN,
    FILE_ALREADY_EXIST,
    FILE_INEXIST,
    NULL_PTR_ERROR,


    l,
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
	ls_error,
	touch_failed
};