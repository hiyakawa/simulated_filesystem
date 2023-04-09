cmake_minimum_required(VERSION 3.24)
project(simulated_filesystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(simulated_filesystem
        main.cpp catch.h
        AbstractFile.h
        TextFile.h TextFile.cpp
        ImageFile.h ImageFile.cpp
        AbstractFileSystem.h
        SimpleFileSystem.h SimpleFileSystem.cpp
        AbstractFileFactory.h
        SimpleFileFactory.h SimpleFileFactory.cpp
        AbstractFileVisitor.h
        BasicDisplayVisitor.h BasicDisplayVisitor.cpp
        MetadataDisplayVisitor.h MetadataDisplayVisitor.cpp
        PasswordProxy.h PasswordProxy.cpp
        AbstractCommand.h
        CommandPrompt.h CommandPrompt.cpp
        TouchCommand.h TouchCommand.cpp
        CommandTest.h CommandTest.cpp)
