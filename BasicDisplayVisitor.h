#pragma once

#include "AbstractFileVisitor.h"

class BasicDisplayVisitor : public AbstractFileVisitor {
public:
    void visitTextFile(TextFile*) override;
    void visitImageFile(ImageFile*) override;
};