CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra

LIBRARY_NAME = libexpression.a

expression.o: expression.cpp expression.h token.h parser.h complex_f.h
	$(CXX) $(CXXFLAGS) expression.cpp -c -o expression.o

token.o: token.cpp token.h
	$(CXX) $(CXXFLAGS) token.cpp -c -o token.o

complex_f.o: complex_f.cpp complex_f.h
	$(CXX) $(CXXFLAGS) complex_f.cpp -c -o complex_f.o

catch2.o: catch_amalgamated.cpp catch_amalgamated.hpp
	$(CXX) $(CXXFLAGS) catch_amalgamated.cpp -c -o catch2.o

tests.o: tests.cpp expression.h token.h parser.h complex_f.h catch_amalgamated.hpp
	$(CXX) $(CXXFLAGS) tests.cpp -c -o tests.o

$(LIBRARY_NAME): token.o complex_f.o expression.o
	ar rcs $(LIBRARY_NAME) token.o complex_f.o expression.o

test: $(LIBRARY_NAME) catch2.o tests.o
	$(CXX) $(CXXFLAGS) catch2.o tests.o -L. -lexpression -o test_bin
	./test_bin

differentiator: expression.o token.o complex_f.o
	$(CXX) $(CXXFLAGS) expression.o token.o complex_f.o -o differentiator

clean:
	del /f /q *.o $(LIBRARY_NAME) test_bin.exe differentiator.exe