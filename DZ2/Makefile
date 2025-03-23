CXX = g++
expression.o: expression.cpp
	$(CXX) expression.cpp -c -o expression.o
expression.a: expression.o
	$(CXX) expression.o -o expression.a
catch2.o: catch_amalgamated.cpp
	$(CXX) catch_amalgamated.cpp  -c -o catch2.o
tests.o: tests.cpp
	$(CXX) tests.cpp -c -o tests.o

test: catch2.o tests.o expression.o
	$(CXX) catch2.o tests.o expression.o -o test_bin
	./test_bin