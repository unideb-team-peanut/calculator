ifdef DEBUG
	OPTIMIZATION := -ggdb
else
	OPTIMIZATION := -O2
endif

FLAGS := -Wall -Wextra $(OPTIMIZATION)

calculator: obj/main.o obj/calculator.o
	g++ -o $@ $^ $(FLAGS)

obj: *.cpp
	mkdir -p obj

obj/calculator.o: calculator.cpp calculator.h primes.h obj
	g++ -o $@ $< -c $(FLAGS)

obj/main.o: main.cpp obj
	g++ -o $@ $< -c $(FLAGS)

primes.h: calculator.h prime_generator
	./prime_generator > primes.h

prime_generator: prime_generator.cpp
	g++ -o $@ $< $(FLAGS)

.PHONY: clean
clean:
	rm calculator prime_generator primes.h
