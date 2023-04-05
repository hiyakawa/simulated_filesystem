#define CATCH_CONFIG_RUNNER

#include "catch.h"
#include "TextFile.h"
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

TEST_CASE("contstructor") {
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
