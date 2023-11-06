FLAGS := -Wall -Wextra -ggdb

calculator: obj/main.o obj/calculator.o
	g++ -o $@ $^ -g

obj: *.cpp
	mkdir -p obj

obj/calculator.o: calculator.cpp calculator.h primes.h obj
	g++ -o $@ $< -c -g

obj/main.o: main.cpp obj
	g++ -o $@ $< -c -g

primes.h: calculator.h prime_generator
	./prime_generator 1000 > primes.h

prime_generator: prime_generator.cpp
	g++ -o $@ $< -O2
