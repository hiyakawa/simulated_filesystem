#pragma once

#include "AbstractFile.h"

class TextFile : public AbstractFile {
private:
    std::vector<char> contents_;
    std::string       filename_;

public:
//    TextFile();
    TextFile(std::string);
//    TextFile(const TextFile&);
//    TextFile(TextFile&&);
    ~TextFile() = default;

    virtual unsigned int getSize() override;
    virtual std::string  getName() override;
    virtual int          write(std::vector<char>) override;
    virtual int          append(std::vector<char>) override;
    virtual void         read() override;

//	virtual void accept(AbstractFileVisitor*) override;
//	virtual AbstractFile* clone(string) override;
};