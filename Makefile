CXX= c++
CFLAGS= -std=c++11
HEADER= $(wildcard *.h)
CCSOURCE= $(wildcard *.cpp)

filesystem: main.o TextFile.o ImageFile.o SimpleFileSystem.o SimpleFileFactory.o BasicDisplayVisitor.o MetadataDisplayVisitor.o
	$(CXX) $(CFLAGS) -o filesystem $^

main.o: catch.h AbstractFile.h AbstractFileSystem.h AbstractFileFactory.h main.cpp
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

.PHONY: test
test: filesystem
	./filesystem --test

.PHONY : clean
clean:
	-rm *.o $(objects)
	# sudo make clean