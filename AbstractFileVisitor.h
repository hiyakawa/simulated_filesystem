#pragma once

class TextFile;
class ImageFile;

class AbstractFileVisitor {
public:
	virtual void visitTextFile(TextFile*) = 0;
	virtual void visitImageFile(ImageFile*) = 0;
};