#include <iostream>
#include "calculator.h"
#include "std_lib_facilities.h"

int main()
	
  try {
    std::cout << "This calculator can handle + - * /"<< std::endl;
    std::cout<< "Use ; to print result"<< std::endl;
    std::cout<< "k = 1000 as constans" << std::endl;
    std::cout<< "Use sqrt(number) to calculate square root of a number"<< std::endl;
    std::cout<< "Use pow(num1 ,num2) to calculate num2 power of a num1"<< std::endl;
    std::cout<< "Use fact(number) to calculate factorial of a number"<< std::endl;
    std::cout<< "Use prime(number) to calculate n th prime number"<< std::endl;
    std::cout<< "Use sinus(number) to calculate sinus of an angle"<< std::endl;
    std::cout<< "Use cosinus(number) to calculate cosinus of an angle"<< std::endl;
    std::cout<< "Use tangent(number) to calculate tangent of an angle"<< std::endl;
    std::cout<< "Use nthroot(n, m) to calculate m th root of n"<< std::endl;
    std::cout<< "Use combination(n, m) to calculate under n the k"<< std::endl;    
    std::cout<< "Use # to define a variable like # x= 1;"<< std::endl;
    std::cout<< "Type in exit to exit"<< std::endl;
	
    calculate();
    return 0;
  }
  catch (exception& e) {
    cerr << "exception: " << e.what() << std::endl;
    char c;
    while (cin >> c && c != ';');
    return 1;
  }
  catch (...) {
    cerr << "exception\n";
    char c;
    while (cin >> c && c != ';');
    return 2;
  }
