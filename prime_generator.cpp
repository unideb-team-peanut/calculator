#include <iostream>
#include <vector>
#include <cmath>

#include "calculator.h"

int main(int c, char *argv[]) {
  std::cout << "#ifndef PRIMES_H_\n"
	    << "#define PRIMES_H_\n"
	    << "int _primes[" << MAX_PRIME_N_ << "] = {\n";
  
  std::vector<int> sieve{};
  for (size_t i = 2; i < MAX_PRIME_N_ * MAX_PRIME_N_; ++i) {
    sieve.push_back(i);
  };

  for (int p = 2; p <= (int)sqrt(MAX_PRIME_N_); ++p) {
    for (size_t multiplier = 2; p*multiplier < sieve.size(); ++multiplier) {
      sieve[p * multiplier] = 0;
    }
  }

  bool first = true;
  for (size_t i, c = 0; i < sieve.size() && c < MAX_PRIME_N_; ++i) {
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


