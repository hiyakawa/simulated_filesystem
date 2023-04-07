#define CATCH_CONFIG_RUNNER

#include "catch.h"
#include "TextFile.h"
#include "ImageFile.h"
#include "SimpleFileSystem.h"
#include "SimpleFileFactory.h"
#include "BasicDisplayVisitor.h"
#include "MetadataDisplayVisitor.h"
#include <iostream>

bool run_tests() {
    const char *argv[] = {"arith"};
    return (Catch::Session().run(1, argv) == 0);
}

int use_arguments(int argc, const char * argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            std::string cur_cmd = argv[i];

            if (cur_cmd == "--test") {
                if (! run_tests()) {
                    exit(1);
                }
            }
            else {
                std::cerr << "Error: Invalid command." << std::endl;
                exit(1);
            }
        }
    }
    else {
        std::cerr << "Error: At least two arguments are required. "
                  << "Please use --help for the options." << std::endl;
        exit(1);
    }

    exit(0);
}

int main(int argc, const char * argv[]) {
    try {
        use_arguments(argc, argv);

        return 0;
    }
    catch (std::runtime_error exn) {
        std::cerr << exn.what() << std::endl;
        return 1;
    }
}

TEST_CASE("constructor") {
    std::string fileName = "FileName.txt";
    unsigned int fileSize = 0;
    TextFile t(fileName);
    CHECK(fileName == t.getName());
    CHECK(fileSize == t.getSize());
}

TEST_CASE("write") {
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    CHECK(0 == t.write(v));
    CHECK(static_cast<unsigned int>(v.size()) == t.getSize());
}

TEST_CASE("append") {
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    CHECK(0 == t.write(v));
    unsigned int fileSize = t.getSize();
    CHECK(0 == t.append(v));
    CHECK(static_cast<unsigned int>(fileSize + v.size()) == t.getSize());
}

TEST_CASE("read") {
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    int resWrite = t.write(v);
    // REDIRECT STD STREAM
    std::streambuf* backup;
    backup = std::cout.rdbuf();
    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    t.read();
    std::string wordShouldBe = "hi";
    std::string word;
    ss >> word;
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup);
    CHECK(0 == resWrite);
}

TEST_CASE("readWithAppend") {
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    CHECK(0 == t.write(v));
    unsigned int fileSize = t.getSize();
    CHECK(0 == t.append(v));
    CHECK(static_cast<unsigned int>(fileSize + v.size()) == t.getSize());
    // REDIRECT STD STREAM
    std::streambuf* backup;
    backup = std::cout.rdbuf();
    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    t.read();
    std::string wordShouldBe = "hihi";
    std::string word;
    ss >> word;
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup);
}

TEST_CASE("constructor2") {
    std::string fileName = "FileName.txt";
    unsigned int fileSize = 0;
    TextFile t(fileName);
    CHECK(fileName == t.getName());
    CHECK(fileSize == t.getSize());
}

TEST_CASE("write2") {
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    CHECK(0 == t.write(v));
    CHECK(static_cast<unsigned int>(v.size()) == t.getSize());
}

TEST_CASE("append2") {
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    CHECK(0 == t.write(v));
    unsigned int fileSize = t.getSize();
    CHECK(0 == t.append(v));
    CHECK(static_cast<unsigned int>(fileSize + v.size()) == t.getSize());
}

TEST_CASE("read2") {
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    int resWrite = t.write(v);
    // REDIRECT STD STREAM
    std::streambuf* backup;
    backup = std::cout.rdbuf();
    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    t.read();
    std::string wordShouldBe = "hi";
    std::string word;
    ss >> word;
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup);
    CHECK(0 == resWrite);
}

TEST_CASE("readWithAppend2") {
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    CHECK(0 == t.write(v));
    unsigned int fileSize = t.getSize();
    CHECK(0 == t.append(v));
    CHECK(static_cast<unsigned int>(fileSize + v.size()) == t.getSize());
    // REDIRECT STD STREAM
    std::streambuf* backup;
    backup = std::cout.rdbuf();
    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    t.read();
    std::string wordShouldBe = "hihi";
    std::string word;
    ss >> word;
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup);
}

TEST_CASE("constructor3") {
    std::string fileName = "FileName.img";
    unsigned int fileSize = 0;
    ImageFile t(fileName);
    CHECK(fileName == t.getName());
    CHECK(fileSize == t.getSize());
}

TEST_CASE("writeValid") {
    std::string fileName = "FileName.img";
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
    CHECK(0 == t.write(v));
    CHECK(static_cast<unsigned int>(v.size() - 1) == t.getSize());
}

TEST_CASE("writeSizeMismatch") {
    std::string fileName = "FileName.img";
    unsigned int fileSize = 0;
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '4' };
    CHECK(0 != t.write(v)); // non-zero error returned
    CHECK(fileSize == t.getSize()); // contents not added
}

TEST_CASE("writeInvalidPixel") {
    std::string fileName = "FileName.img";
    unsigned int fileSize = 0;
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'Y', ' ', 'X',' ', 'X', '3' };
    CHECK(0 != t.write(v));
    CHECK(fileSize == t.getSize()); // contents not added
}
TEST_CASE("appendInvalid") {
    std::string fileName = "FileName.img";
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'Y', ' ', 'X',' ', 'X', '3' };
    CHECK(0 != t.append(v)); // can't append to image
}

TEST_CASE("addValid") {
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    TextFile* txt = new TextFile("FileName.txt");
    CHECK(0 == sfs.addFile(img->getName(), img));
    CHECK(0 == sfs.addFile(txt->getName(), txt));
}

TEST_CASE("addNullFile") {
    SimpleFileSystem sfs;
    ImageFile* img = nullptr;
    CHECK(0 != sfs.addFile("FileName.img", img));
}

TEST_CASE("addFileAlreadyExists") {
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    CHECK(0 == sfs.addFile(img->getName(), img));
    CHECK(0 != sfs.addFile(img->getName(), img));
}

TEST_CASE("deleteValid") {
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    CHECK(0 == sfs.addFile(img->getName(), img));
    CHECK(0 == sfs.deleteFile(img->getName()));
}

TEST_CASE("deleteFileDoesNotExist") {
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    CHECK(0 != sfs.deleteFile(img->getName()));
}

TEST_CASE("openValid") {
    SimpleFileSystem sfs;
    // check using add -- expect to see the same file returned
    AbstractFile* img = new ImageFile("FileName.img");
    CHECK(0 == sfs.addFile(img->getName(), img));
    AbstractFile* res1 = sfs.openFile(img->getName());
    bool sameAddress = &(*img) == &(*res1);
    CHECK(sameAddress);
}

TEST_CASE("openFileNotAdded") {
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    AbstractFile* res1 = sfs.openFile(img->getName());
    bool isNull = res1 == nullptr;
    CHECK(isNull);
}

TEST_CASE("openAlreadyOpenedFile") {
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    CHECK(0 == sfs.addFile(img->getName(), img));
    AbstractFile* firstOpen = sfs.openFile(img->getName());
    bool sameAddress = &(*img) == &(*firstOpen);
    CHECK(sameAddress);
    AbstractFile* secondOpen = sfs.openFile(img->getName());
    bool isNull = secondOpen == nullptr;
    CHECK(isNull);
}

TEST_CASE("closeValid") {
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    sfs.addFile(img->getName(), img);
    sfs.openFile(img->getName());
    int res1 = sfs.closeFile(img);
    CHECK(0 == res1);
}

TEST_CASE("closeNotOpen") {
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    CHECK(0 == sfs.addFile(img->getName(), img));
    CHECK(0 != sfs.closeFile(img));
}

TEST_CASE("closeNotAdded") {
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    CHECK(0 != sfs.closeFile(img));
}

TEST_CASE("createFileValid2") {
    SimpleFileFactory sff;
    AbstractFile* res1 = sff.createFile("FileName.img");
    bool isNull1 = res1 == nullptr;
    CHECK(! isNull1);
    AbstractFile* res2 = sff.createFile("FileName.txt");
    bool isNull2 = res2 == nullptr;
    CHECK(! isNull2);
}

TEST_CASE("createUnknownExtension2") {
    SimpleFileFactory sfs;
    AbstractFile* res1 = sfs.createFile("FileName.bla");
    bool isNull = res1 == nullptr;
    CHECK(isNull);
}

TEST_CASE("visitTextFile") {
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    int resWrite = t.write(v);
    // REDIRECT STD STREAM
    std::streambuf* backup;
    backup = std::cout.rdbuf();
    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    AbstractFileVisitor* bdv = new BasicDisplayVisitor;
    t.accept(bdv);
    std::string wordShouldBe = "hi";
    std::string word;
    ss >> word;
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup);
    CHECK(wordShouldBe == word);
    CHECK(0 == resWrite);
}

TEST_CASE("visitImageFile") {
    std::string fileName = "FileName.img";
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
    CHECK(0 == t.write(v));
    // REDIRECT STD STREAM
    std::streambuf* backup;
    backup = std::cout.rdbuf();
    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    AbstractFileVisitor* bdv = new BasicDisplayVisitor;
    t.accept(bdv);
    std::string outputShouldBe = "X";
    std::string word;
    int count = 0;
    while (ss >> word) { // no skip ws -- wont skip white space! would have to extract one character at a time
        CHECK(outputShouldBe == word);
        ++count;
    }
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup);
    CHECK(5 == count);
}

TEST_CASE("visitTextFile2") { // tests the output of the metadata display visitor for a text file, expects the filename, type and size to be included in the print statement
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    CHECK(0 == t.write(v));
    // REDIRECT STD STREAM
    std::streambuf* backup;
    backup = std::cout.rdbuf();
    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    AbstractFileVisitor* bdv = new MetadataDisplayVisitor;
    t.accept(bdv);
    std::string word;
    std::vector<std::string> printedWords;
    while (ss >> word) {
        printedWords.push_back(word);
    }
    std::vector<std::string>::iterator it1;
    std::vector<std::string>::iterator it2;
    std::vector<std::string>::iterator it3;
    it1 = std::find(printedWords.begin(), printedWords.end(), fileName);
    bool notEqual1 = it1 == printedWords.end();
    CHECK(! notEqual1);
    it2 = std::find(printedWords.begin(), printedWords.end(), std::to_string(t.getSize()));
    bool notEqual2 = it2 == printedWords.end();
    CHECK(! notEqual2);
    it3 = std::find(printedWords.begin(), printedWords.end(), "text");
    bool notEqual3 = it3 == printedWords.end();
    CHECK(! notEqual3);
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup);
}
TEST_CASE("visitImageFile2") {
    std::string fileName = "FileName.img";
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
    CHECK(0 == t.write(v));
    // REDIRECT STD STREAM
    std::streambuf* backup;
    backup = std::cout.rdbuf();
    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    AbstractFileVisitor* bdv = new MetadataDisplayVisitor;
    t.accept(bdv);
    std::string word;
    std::vector<std::string> printedWords;
    while (ss >> word) {
        printedWords.push_back(word);
    }
    std::vector<std::string>::iterator it1;
    std::vector<std::string>::iterator it2;
    std::vector<std::string>::iterator it3;
    it1 = std::find(printedWords.begin(), printedWords.end(), fileName);
    bool notEqual1 = it1 == printedWords.end();
    CHECK(! notEqual1);
    it2 = std::find(printedWords.begin(), printedWords.end(), std::to_string(t.getSize()));
    bool notEqual2 = it2 == printedWords.end();
    CHECK(! notEqual2);
    it3 = std::find(printedWords.begin(), printedWords.end(), "image");
    bool notEqual3 = it3 == printedWords.end();
    CHECK(! notEqual3);
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup);
}