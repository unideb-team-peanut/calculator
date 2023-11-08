#include <iostream>
#include <vector>
#include <cmath>

#include "calculator.h"

int main() {
  std::cout << "#ifndef PRIMES_H_\n"
	    << "#define PRIMES_H_\n"
	    << "int _primes[" << MAX_PRIME_N << "] = {\n";
  
  std::vector<int> sieve{};
  for (size_t i = 2; i < MAX_PRIME_N * MAX_PRIME_N; ++i) {
    sieve.push_back(i);
  };

  for (int p = 2; p <= (int)sqrt(MAX_PRIME_N); ++p) {
    for (size_t multiplier = 2; p*multiplier < sieve.size(); ++multiplier) {
      sieve[p * multiplier - 2] = 0;
    }
  }

  bool first = true;
  size_t i = 0;
  size_t c = 0;
  for (; i < sieve.size() && c < MAX_PRIME_N; ++i) {
    if (sieve[i]) {
      if (!first) {
	std::cout << ",\n";
      }
      std::cout << sieve[i];
      first = false;
      ++c;
    }
  }

  std::cout << "\n};\n";

  std::cout << "#endif //PRIMES_H_\n";
  return 0;
}


