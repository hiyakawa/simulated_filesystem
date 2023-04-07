#pragma once

#include "AbstractFile.h"

class ImageFile : public AbstractFile {
private:
    std::string       filename_;
    std::vector<char> contents_;
    char              imgsize_;

public:
	ImageFile(std::string filename);

    unsigned int      getSize() override;
    std::string       getName() override;
    int               write(std::vector<char>) override;
    int               append(std::vector<char>) override;
    std::vector<char> read() override;
    void              accept(AbstractFileVisitor*) override;
//	virtual AbstractFile* clone(std::string) override;
};