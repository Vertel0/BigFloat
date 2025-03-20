CXX = g++
big_decimal.o: big_decimal.cpp
	$(CXX) big_decimal.cpp -c -o big_decimal.o
big_decimal.a: big_decimal.o
	$(CXX) big_decimal.o -o big_decimal.a
catch2.o: catch_amalgamated.cpp
	$(CXX) catch_amalgamated.cpp  -c -o catch2.o
test_case.o: test_case.cpp
	$(CXX) test_case.cpp -c -o test_case.o

test: catch2.o test_case.o big_decimal.o
	$(CXX) catch2.o test_case.o big_decimal.o -o test_bin
	./test_bin

CallPi.o: CallPi.cpp
	$(CXX) CallPi.cpp -c -o CallPi.o


pi: CallPi.o big_decimal.o
	$(CXX) CallPi.o big_decimal.o -o pi
	./pi
