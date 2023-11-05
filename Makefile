FLAGS := -Wall -Wextra -ggdb

calculator: calculator.cpp
	g++ -o $@ $^ -g
