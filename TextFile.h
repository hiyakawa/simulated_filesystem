#pragma once

#include "AbstractFile.h"

class TextFile : public AbstractFile {
private:
    std::string       filename_;
    std::vector<char> contents_;

public:
    TextFile(std::string);
    ~TextFile() = default;

    unsigned int      getSize() override;
    std::string       getName() override;
    int               write(std::vector<char>) override;
    int               append(std::vector<char>) override;
    std::vector<char> read() override;
    void              accept(AbstractFileVisitor*) override;
//	virtual AbstractFile* clone(string) override;
};