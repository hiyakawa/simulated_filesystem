#pragma once

#include "AbstractFileVisitor.h"

using namespace std;

class MetadataDisplayVisitor : public AbstractFileVisitor
{
public:
	virtual void visit_TextFile(TextFile*) override;
	virtual void visit_ImageFile(ImageFile*) override;
};