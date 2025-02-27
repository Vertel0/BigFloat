CXX = g++
big_decimal.o:
	$(CXX) big_decimal.cpp -c
big_decimal.a: big_decimal.o
	$(CXX) big_decimal.o -o big_decimal.a
