CXXFLAGS+=-std=c++17
CXX=g++

all: out out/main.o

run: out out/main.o
	./out/main.o
out/main.o: src/main.cpp
	$(CXX) $^ $(CXXFLAGS) -o out/main.o
pack:
	zip solution.zip -r Makefile src
out:
	mkdir -p out
clean:
	rm -rf out
