FLAGS := -Wall -Wextra -ggdb

calculator: src/calculator.cpp
	g++ -o $@ $^ -g
