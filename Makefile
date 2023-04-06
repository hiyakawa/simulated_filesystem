CXX= c++
CFLAGS= -std=c++11
HEADER= $(wildcard *.h)
CCSOURCE= $(wildcard *.cpp)

filesystem: main.o TextFile.o ImageFile.o SimpleFileSystem.o
	$(CXX) $(CFLAGS) -o filesystem $^

main.o: catch.h AbstractFile.h AbstractFileSystem.h main.cpp
	c++ -std=c++17 main.cpp -c

TextFile.o: TextFile.h TextFile.cpp
	c++ -c TextFile.cpp

ImageFile.o: ImageFile.h ImageFile.cpp
	c++ -c ImageFile.cpp

SimpleFileSystem.o: SimpleFileSystem.h SimpleFileSystem.cpp
	c++ -c SimpleFileSystem.cpp

.PHONY: test
test: msdscript
	./msdscript --test

.PHONY : clean
clean:
	-rm *.o $(objects)
	# sudo make clean