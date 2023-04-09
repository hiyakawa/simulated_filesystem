CXX= c++
CFLAGS= -std=c++11
HEADER= $(wildcard *.h)
CCSOURCE= $(wildcard *.cpp)

filesystem: main.o TextFile.o ImageFile.o SimpleFileSystem.o SimpleFileFactory.o BasicDisplayVisitor.o MetadataDisplayVisitor.o PasswordProxy.o CommandPrompt.o TouchCommand.o CommandTest.o
	c++ -std=c++11 -o filesystem $^

main.o: catch.h AbstractFile.h AbstractFileSystem.h AbstractFileFactory.h AbstractCommand.h main.cpp
	c++ -std=c++11 main.cpp -c

TextFile.o: TextFile.h TextFile.cpp
	c++ -c TextFile.cpp

ImageFile.o: ImageFile.h ImageFile.cpp
	c++ -c ImageFile.cpp

SimpleFileSystem.o: SimpleFileSystem.h SimpleFileSystem.cpp
	c++ -c SimpleFileSystem.cpp

SimpleFileFactory.o: SimpleFileFactory.h SimpleFileFactory.cpp
	c++ -c SimpleFileFactory.cpp

BasicDisplayVisitor.o: BasicDisplayVisitor.h BasicDisplayVisitor.cpp
	c++ -c BasicDisplayVisitor.cpp

MetadataDisplayVisitor.o: MetadataDisplayVisitor.h MetadataDisplayVisitor.cpp
	c++ -c MetadataDisplayVisitor.cpp

PasswordProxy.o: PasswordProxy.h PasswordProxy.cpp
	c++ -c PasswordProxy.cpp

CommandPrompt.o: CommandPrompt.h CommandPrompt.cpp
	c++ -c CommandPrompt.cpp

TouchCommand.o: TouchCommand.h TouchCommand.cpp
	c++ -c TouchCommand.cpp

CommandTest.o: CommandTest.h CommandTest.cpp
	c++ -c CommandTest.cpp

.PHONY: test
test: filesystem
	./filesystem --test

.PHONY : clean
clean:
	-rm *.o $(objects)
	# sudo make clean