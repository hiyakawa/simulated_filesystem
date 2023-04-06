#pragma once

#include "AbstractFile.h"

class TextFile : public AbstractFile {
private:
    std::string       filename_;
    std::vector<char> contents_;

public:
//    TextFile();
    TextFile(std::string);
//    TextFile(const TextFile&);
//    TextFile(TextFile&&);
    ~TextFile() = default;

    unsigned int getSize() override;
    std::string  getName() override;
    int          write(std::vector<char>) override;
    int          append(std::vector<char>) override;
    void         read() override;

//	virtual void accept(AbstractFileVisitor*) override;
//	virtual AbstractFile* clone(string) override;
};