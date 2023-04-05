#pragma once

using namespace std;

class TextFile;
class ImageFile;

class AbstractFileVisitor
{
public:
	virtual void visit_TextFile(TextFile*) = 0;
	virtual void visit_ImageFile(ImageFile*) = 0;
};