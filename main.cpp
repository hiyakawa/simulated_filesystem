#define CATCH_CONFIG_RUNNER

#include "catch.h"
#include "TextFile.h"
#include "ImageFile.h"
#include "SimpleFileSystem.h"
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
    // ASSIGN COUT BACK TO STDOUT
    std::cout.rdbuf(backup);
    CHECK(wordShouldBe == word);
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
    // ASSIGN COUT BACK TO STDOUT
    std::cout.rdbuf(backup);
    CHECK(wordShouldBe == word);
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
    // ASSIGN COUT BACK TO STDOUT
    std::cout.rdbuf(backup);
    CHECK(wordShouldBe == word);
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
    // ASSIGN COUT BACK TO STDOUT
    std::cout.rdbuf(backup);
    CHECK(wordShouldBe == word);
}

TEST_CASE("contstructor") {
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

//TEST_CASE("read3") {
//    std::string fileName = "FileName.img";
//    ImageFile t(fileName);
//    std::vector<char> v = {'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', '3'};
//    CHECK(0 == t.write(v));
//    // REDIRECT STD STREAM
//    std::streambuf *backup;
//    backup = std::cout.rdbuf();
//    std::stringstream ss;
//    std::cout.rdbuf(ss.rdbuf());
//    t.read();
//    std::string outputShouldBe = "X";
//    std::string word;
//    int count = 0;
//    while (ss >> word) {
//        CHECK(outputShouldBe == word);
//        ++count;
//    }
//    // ASSIGN COUT BACK TO STDOUT
//    std::cout.rdbuf(backup);
//    CHECK(5 == count);
//}

TEST_CASE("createFileValid") {
    SimpleFileSystem sfs;
    CHECK(0 == sfs.createFile("FileName.img"));
    CHECK(0 == sfs.createFile("FileName.txt"));
}

TEST_CASE("createFileAlreadyExists") {
    SimpleFileSystem sfs;
    CHECK(0 == sfs.createFile("FileName.img"));
    CHECK(0 != sfs.createFile("FileName.img")); // accepts any non-zero value
}

TEST_CASE("createUnknownExtension") {
    SimpleFileSystem sfs;
    CHECK(0 != sfs.createFile("FileName.bla"));
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

    // check using create -- a quick check to see that create adds successfully and open finds the file by returning a pointer that  is not null
    CHECK(0 == sfs.createFile("FileName.txt"));
    AbstractFile* res2 = sfs.openFile("FileName.txt");
    bool nullCheck = res2 == nullptr;
    CHECK_FALSE(nullCheck);
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
