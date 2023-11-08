#include <iostream>
#include <cmath>

using namespace std;

int factorial(int f){
  int fact = 1;
  if (f < 0){
    cout <<"Use a positive number for factorial!";
  } else {
    for(int i = 1; i <= f; ++i) {
      fact *= i;
    }
    return fact;
  }
}

int my_combination(int n, int k){
	int result;
	result = factorial(n) / (factorial(k) * factorial(n-k));
	return result;
}




int main()
{
  int n, k;
  cin >> n;
  cin >> k;
  cout << my_combination(n, k) << endl;
  return 0;
}

