#define CATCH_CONFIG_RUNNER

#include "catch.h"
#include "TextFile.h"
#include "ImageFile.h"
#include "SimpleFileSystem.h"
#include "SimpleFileFactory.h"
#include "BasicDisplayVisitor.h"
#include "MetadataDisplayVisitor.h"
#include "PasswordProxy.h"
#include "CommandPrompt.h"
#include "CommandTest.h"
#include "TouchCommand.h"
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
                std::cerr << "Error: Invalid command_." << std::endl;
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

TEST_CASE("constructor4") {
    // REDIRECT std::cout STREAM -- TO PROTECT AGAINST ERRORS
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    std::string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    unsigned int fileSize = 0;
    // EXPECTATIONS FOR CONSTRUCTION
    CHECK(fileName == pp->getName());
    CHECK(fileSize == pp->getSize());
    CHECK(fileName == realfile->getName());
    CHECK(fileSize == realfile->getSize());
}
TEST_CASE("writeValidPassword") {
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    std::string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    std::vector<char> v = { 'h', 'i' };
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    ss_in << password;
    // EXPECTATIONS FOR FUNCTION -- VALID PASSWORD
    CHECK(0 == pp->write(v));
    CHECK(static_cast<unsigned int>(v.size()) == pp->getSize());
    CHECK(static_cast<unsigned int>(v.size()) == realfile->getSize());
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("writeInvalidPassword") {
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    std::string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    std::vector<char> v = { 'h', 'i' };
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    std::string wrongPassword = "s9K3qL";
    ss_in << wrongPassword;
    // EXPECTATIONS FOR FUNCTION -- INVALID PASSWORD
    CHECK(0 != pp->write(v));
    CHECK(static_cast<unsigned int>(0) == pp->getSize());
    CHECK(static_cast<unsigned int>(0) == realfile->getSize());
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("appendValidPassword") {
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    std::string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    std::vector<char> v = { 'h', 'i' };
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    ss_in << password + '\n' + password;
    // EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
    CHECK(0 == pp->write(v));
    CHECK(static_cast<unsigned int>(v.size()) == pp->getSize());
    CHECK(static_cast<unsigned int>(v.size()) == realfile->getSize());
    unsigned int fileSize = pp->getSize();
    // EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
    CHECK(0 == pp->append(v));
    CHECK(static_cast<unsigned int>(fileSize + v.size()) == pp->getSize());
    CHECK(static_cast<unsigned int>(fileSize + v.size()) == realfile->getSize());
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("appendInvalidPassword") {
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    std::string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    std::vector<char> v = { 'h', 'i' };
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    std::string wrongPassword = "a5lsdIK3";
    ss_in << password + '\n' + wrongPassword;
    // EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
    CHECK(0 == pp->write(v));
    CHECK(static_cast<unsigned int>(v.size()) == pp->getSize());
    CHECK(static_cast<unsigned int>(v.size()) == realfile->getSize());
    unsigned int fileSize = pp->getSize();
    // EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
    CHECK(0 != pp->append(v));
    CHECK(static_cast<unsigned int>(fileSize) == pp->getSize());
    CHECK(static_cast<unsigned int>(fileSize) == realfile->getSize());
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("readValidPassword") {
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    std::string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    std::vector<char> v = { 'h', 'i' };
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    ss_in << password + '\n' + password;
    // EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
    CHECK(0 == pp->write(v));
    CHECK(static_cast<unsigned int>(v.size()) == pp->getSize());
    CHECK(static_cast<unsigned int>(v.size()) == realfile->getSize());
    // EXPECTATIONS FOR SECOND FUNCTION -- VALID PASSWORD
    std::vector<char> contentsPP = pp->read();
    CHECK(v.size() == contentsPP.size());
    for (size_t i = 0; i < contentsPP.size(); ++i) {
        CHECK(contentsPP[i] == v[i]);
    }
    std::vector<char> contentsRF = realfile->read();
    CHECK(v.size() == contentsRF.size());
    for (size_t i = 0; i < contentsRF.size(); ++i) {
        CHECK(contentsRF[i] == v[i]);
    }
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("readInvalidPassword") {
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    std::string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    std::vector<char> v = { 'h', 'i' };
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    std::string wrongPassword = "a5lsdIK3";
    ss_in << password + '\n' + wrongPassword;
    // EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
    CHECK(0 == pp->write(v));
    CHECK(static_cast<unsigned int>(v.size()) == pp->getSize());
    CHECK(static_cast<unsigned int>(v.size()) == realfile->getSize());
    // EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
    std::vector<char> contentsPP = pp->read();
    CHECK(static_cast<size_t>(0) == contentsPP.size());
    std::vector<char> contentsRF = realfile->read();
    CHECK(static_cast<size_t>(v.size()) == contentsRF.size());
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("acceptValidPassword") {
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    std::string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    std::vector<char> v = { 'h', 'i' };
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    ss_in << password + '\n' + password;
    // EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
    CHECK(0 == pp->write(v));
    CHECK(static_cast<unsigned int>(v.size()) == pp->getSize());
    CHECK(static_cast<unsigned int>(v.size()) == realfile->getSize());
    // EXPECTATIONS FOR SECOND FUNCTION -- VALID PASSWORD
    BasicDisplayVisitor* bdv = new BasicDisplayVisitor;
    pp->accept(bdv);
    std::string wordShouldBe = "hi";
    std::string word;
    std::vector<std::string> printedWords;
    while (ss_out >> word) {
        printedWords.push_back(word);
    }
    std::vector<std::string>::iterator it1;
    it1 = std::find(printedWords.begin(), printedWords.end(), wordShouldBe);
    bool isEqual = it1 == printedWords.end();
    CHECK(! isEqual);
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("acceptInvalidPassword") {
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    std::string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    std::vector<char> v = { 'h', 'i' };
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    std::string wrongPassword = "a5lsdIK3";
    ss_in << password + '\n' + wrongPassword;
    // EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
    CHECK(0 == pp->write(v));
    CHECK(static_cast<unsigned int>(v.size()) == pp->getSize());
    CHECK(static_cast<unsigned int>(v.size()) == realfile->getSize());
    // EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
    BasicDisplayVisitor* bdv = new BasicDisplayVisitor;
    pp->accept(bdv);
    std::string wordShouldBe = "hi";
    std::string word;
    std::vector<std::string> printedWords;
    while (ss_out >> word) {
        printedWords.push_back(word);
    }
    std::vector<std::string>::iterator it1;
    it1 = std::find(printedWords.begin(), printedWords.end(), wordShouldBe);
    bool isEqual = it1 == printedWords.end();
    CHECK(isEqual);
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("addAndListCommands") {
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    CommandPrompt cp;
    cp.setFileSystem(sfs);
    cp.setFileFactory(sff);
    // ADD COMMAND -- TEST COMMAND
    CommandTest* ct = new CommandTest(sfs);
    std::string commandname = "test";
    CHECK(0 == cp.addCommand(commandname, ct));
    // REDIRECT STD STREAM
    std::streambuf* backup;
    backup = std::cout.rdbuf();
    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    // LIST COMMANDS
    cp.listCommands();
    std::string word;
    std::vector<std::string> printedWords;
    while (ss >> word) {
        printedWords.push_back(word);
    }
    // EXPECTATION -- COMMAND NAME SHOULD BE PRINTED TO std::cout
    CHECK(1 == static_cast<int>(printedWords.size()));
    CHECK(commandname == printedWords[0]);
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup);
}

TEST_CASE("prompt") {
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    CommandPrompt* cp = new CommandPrompt;
    cp->setFileSystem(sfs);
    cp->setFileFactory(sff);
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // MIMIC USER INPUT -- SAMPLE COMMAND FOR TOUCH
    std::string input = "touch file.txt";
    ss_in << input;
    // EXPECTATION -- PROMPT SHOULD RETURN THE USER INPUT
    std::string promptResponse = cp->prompt();
    CHECK(input == promptResponse);
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("runQuit") {
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    CommandPrompt* cp = new CommandPrompt;
    cp->setFileSystem(sfs);
    cp->setFileFactory(sff);
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // MIMC USER INPUT -- QUITTING COMMAND -- 'Q'
    std::string input = "q";
    ss_in << input;
    // CAPUTRE RETURN VALUE -- Q SHOULD END THE RUN LOOP
    int response = cp->run();
    CHECK(0 != response);
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("runHelp") {
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    CommandPrompt* cp = new CommandPrompt;
    cp->setFileSystem(sfs);
    cp->setFileFactory(sff);
    // ADD COMMAND -- COMMAND TEST
    CommandTest* ct = new CommandTest(sfs);
    std::string commandname = "test";
    CHECK(0 == cp->addCommand(commandname, ct));
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // MIMIC USER INPUT -- HELP & QUIT -- USE QUIT TO END RUN
    std::string input = "help\nq";
    ss_in << input;
    int response = cp->run();
    CHECK(0 != response);
    // CAPTURE std::cout DATA
    std::string word;
    std::vector<std::string> printedWords;
    while (ss_out >> word) {
        printedWords.push_back(word);
    }
    // EXPECTATION -- PROGRAM SHOULD PRINT ALL COMMANDS
    std::vector<std::string>::iterator it1;
    it1 = std::find(printedWords.begin(), printedWords.end(), commandname);
    bool notEqual1 = it1 == printedWords.end();
    CHECK(! notEqual1);
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("commandDisplayInfo") {
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    CommandPrompt* cp = new CommandPrompt;
    cp->setFileSystem(sfs);
    cp->setFileFactory(sff);
    // ADD COMMAND -- COMMAND TEST
    CommandTest* ct = new CommandTest(sfs);
    std::string commandname = "test";
    CHECK(0 == cp->addCommand(commandname, ct));
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // MIMIC USER INPUT -- SPECIFIC HELP COMMAND
    std::string input = "help test\nq\n";
    ss_in << input;
    int response = cp->run();
    CHECK(0 != response);
    std::string word;
    std::vector<std::string> printedWords;
    while (ss_out >> word) {
        printedWords.push_back(word);
    }
    /// EXPECTATION -- DISPLAY INFO OF OUR COMMAND TEST SHOULD BE PRINTED TO std::cout
    std::vector<std::string>::iterator it1;
    std::string expectedString = "aRandomstd::stringz"; // MATCHES GIVEN COMMAND TEST FILE
    it1 = std::find(printedWords.begin(), printedWords.end(), expectedString);
    bool notEqual1 = it1 != printedWords.end();
    CHECK(! notEqual1);
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("commandExecuteNoInfo") {
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    CommandPrompt* cp = new CommandPrompt;
    cp->setFileSystem(sfs);
    cp->setFileFactory(sff);
    // ADD COMMAND
    CommandTest* ct = new CommandTest(sfs);
    std::string commandname = "test";
    CHECK(0 == cp->addCommand(commandname, ct));
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // MIMIC USER INPUT -- COMMAND TEST EXECUTE 
    std::string input = "test\nq\n";
    ss_in << input;
    // CAPTURE RUN OUTPUT
    int response = cp->run();
    CHECK(0 != response);
    std::string word;
    std::vector<std::string> printedWords;
    while (ss_out >> word) {
        printedWords.push_back(word);
    }
    // EXPECTATION -- NOTHING SHOULD BE PASSED TO THE FUNCTION
    std::vector<std::string>::iterator it1;
    std::string expectedOutput = "command-test-no-info";
    it1 = std::find(printedWords.begin(), printedWords.end(), expectedOutput);
    bool notEqual1 = it1 == printedWords.end();
    CHECK(! notEqual1);
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("commandExecuteOneInput") {
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    CommandPrompt* cp = new CommandPrompt;
    cp->setFileSystem(sfs);
    cp->setFileFactory(sff);
    // ADD COMMAND
    CommandTest* ct = new CommandTest(sfs);
    std::string commandname = "test";
    CHECK(0 == cp->addCommand(commandname, ct));
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // MIMIC USER INPUT
    std::string input = "test foo\nq\n";
    ss_in << input;
    int response = cp->run();
    CHECK(0 != response);
    std::string word;
    std::vector<std::string> printedWords;
    while (ss_out >> word) {
        printedWords.push_back(word);
    }
    // EXPECTATION -- THE SECOND PARAMETER SHOULD BE PRINTED TO std::cout
    std::vector<std::string>::iterator it1;
    std::string expectedOutput = "foo";
    it1 = std::find(printedWords.begin(), printedWords.end(), expectedOutput);
    bool notEqual1 = it1 == printedWords.end();
    CHECK(! notEqual1);
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("commandExecuteMoreInputs") {
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    CommandPrompt* cp = new CommandPrompt;
    cp->setFileSystem(sfs);
    cp->setFileFactory(sff);
    // ADD COMMAND
    CommandTest* ct = new CommandTest(sfs);
    std::string commandname = "test";
    CHECK(0 == cp->addCommand(commandname, ct));
    // REDIRECT std::cout STREAM
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // REDIRECT std::cin STREAM
    std::streambuf* backup_in;
    backup_in = std::cin.rdbuf();
    std::stringstream ss_in;
    std::cin.rdbuf(ss_in.rdbuf());
    // MIMIC USER INPUT
    std::string input = "test foo moo\nq\n";
    ss_in << input;
    int response = cp->run();
    CHECK(0 != response);
    std::string word;
    std::vector<std::string> printedWords;
    while (ss_out >> word) {
        printedWords.push_back(word);
    }
    // EXPECTATION -- ALL PARAMETERS SHOULD BE PRINTED TO std::cout
    std::vector<std::string>::iterator it1;
    std::string expectedOutput = "foo:moo";
    it1 = std::find(printedWords.begin(), printedWords.end(), expectedOutput);
    bool notEqual1 = it1 == printedWords.end();
    CHECK(! notEqual1);
    // ASSIGN std::cout BACK TO STDOUT
    std::cout.rdbuf(backup_out);
    // ASSIGN std::cin BACK TO STDIN
    std::cin.rdbuf(backup_in);
}

TEST_CASE("execute") {
    // REDIRECT std::cout STREAM -- TO PROTECT AGAINST ERRORS
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    // CREATE COMMAND
    TouchCommand* tc = new TouchCommand(sfs, sff);
    // CALL EXECUTE ON TOUCH COMMAND
    std::string filename = "file.txt";
    CHECK(0 == tc->execute(filename));
    // EXPECTATION -- FILE EXISTS IN THE FILE SYSTEM
    AbstractFile* file = sfs->openFile(filename);
    bool isNull = file == nullptr;
    CHECK(! isNull);
    CHECK(file->getName() == filename);
}
TEST_CASE("executeInvalidExtension") {
    // REDIRECT std::cout STREAM -- TO PROTECT AGAINST ERRORS
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    // CREATE COMMAND
    TouchCommand* tc = new TouchCommand(sfs, sff);
    // CALL EXECUTE ON TOUCH COMMAND
    std::string filename = "file.foo";
    CHECK(0 != tc->execute(filename));
    // EXPECTATION -- FILE DOES NOT EXISTS IN THE FILE SYSTEM
    AbstractFile* file = sfs->openFile(filename);
    bool isNull = file == nullptr;
    CHECK(isNull);
}

TEST_CASE("executeFileAlreadyExists") {
    // REDIRECT std::cout STREAM -- TO PROTECT AGAINST ERRORS
    std::streambuf* backup_out;
    backup_out = std::cout.rdbuf();
    std::stringstream ss_out;
    std::cout.rdbuf(ss_out.rdbuf());
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    // CREATE COMMAND
    TouchCommand* tc = new TouchCommand(sfs, sff);
    // CALL EXECUTE ON TOUCH COMMAND
    std::string filename = "file.txt";
    CHECK(0 == tc->execute(filename));
    CHECK(0 != tc->execute(filename));
    // EXPECTATION -- FILE DOES EXISTS IN THE FILE SYSTEM - FIRST EXECUTION
    AbstractFile* file = sfs->openFile(filename);
    bool isNull = file == nullptr;
    CHECK(! isNull);
}
