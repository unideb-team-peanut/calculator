
/*
  calculator08buggy.cpp
  Helpful comments removed.
  We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include "calculator.h"
#include "primes.h"
#include "std_lib_facilities.h"
#include <cmath>
#include <limits.h>

// define constansok
constexpr char let = '#';
constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char root = 'S';
constexpr char pows = 'P';
constexpr char fact = 'F';
constexpr char prime = 'p';
constexpr char sinus = 's';
constexpr char cosinus = 'f';
constexpr char tangent = 't';
constexpr char nthroot = 'n';
constexpr char combination = 'c';


//function declarations
double expression();
double primary();
double term();
double declaration();
double statement();



//sin function
double my_sin(double n){
	double x, result;
	x = n * 3.14159 / 180;
  	result = sin(x);
  	return result;
}


//cos function
double my_cos(double n){
	double x, result;
	x = n * 3.14159 / 180;
  	result = cos(x);
  	return result;
}


//tan function
double my_tan(double n){
	double x, result;
	x = n * 3.14159 / 180;
  	result = tan(x);
  	return result;
}

// nth root function
double nthRoot(int A, int N)
{
    double xPre = rand() % 10;
    double eps = 1e-3;
    double delX = INT_MAX;
    double xK;
 
    //  loop until we reach desired accuracy
    while (delX > eps)
    {
        //  calculating current value from previous value by newton's method
        xK = ((N - 1.0) * xPre +
              (double)A/pow(xPre, N-1)) / (double)N;
        delX = abs(xK - xPre);
        xPre = xK;
    }
    return xK;
}

// factorial definition extra function
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

// combination function
int my_combination(int n, int k){
	int result;
	result = factorial(n) / (factorial(k) * factorial(n-k));
	return result;
}

// variation
int my_variation(int n, int k){
	int result;
	result = factorial(n) / (factorial(n-k));
	return result;
}

// permutation
int my_permutation(int n, int k){
	int result;
	result = factorial(n);
	return result;
}

int nth_prime(int n) {
  if (n >= sizeof(_primes) / sizeof(int)) {
  char err_str[64];
  snprintf(err_str, 64, "Max N for primes: %d\n", MAX_PRIME_N - 1);
  error(err_str);
  }
  if (n <= 0) error("Argument for prime() must be positive\n");
  return _primes[n-1];
}

// define what Token is
struct Token {
  char kind;
  double value;
  string name;
  Token(char ch) :kind(ch), value(0) { }
  Token(char ch, double val) :kind(ch), value(val) { }
  Token(char ch, string val) :kind(ch), name(val) { }
};

// define what Token_stream is
class Token_stream {
  bool full;
  Token buffer;
public:
  Token_stream() :full(0), buffer(0) { }

  Token get();
  void unget(Token t) { buffer = t; full = true; }

  void ignore(char);
};


// define get inside token_stream
Token Token_stream::get()
{
  if (full) { full = false; return buffer; }
  char ch;
  cin >> ch;
  switch (ch) {
  case quit:
  case print:
  case ',':
  case '!':
  case '(':
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
  case let:
  case '=':
    return Token(ch);
  case '.':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    {	cin.unget();
      double val;
      cin >> val;
      return Token(number, val);
    }
  case 'k': {
    return Token(number,1000);
  }

    // works with texts
  default:
    if (isalpha(ch)) {
      string s;
      s += ch;
      while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
      cin.unget();
      if (s == "#") return Token(let);
      if (s == "exit") return Token(quit);
      if (s == "sqrt") return Token(root);
      if (s == "pow") return Token(pows);
      if (s == "fact") return Token(fact);
      if (s == "prime") return Token(prime);
      if (s == "sinus") return Token(sinus);
      if (s == "cosinus") return Token(cosinus);
      if (s == "tangent") return Token(tangent);
      if (s == "nthroot") return Token(nthroot);
      if (s == "combination") return Token(combination);

      return Token(name, s);
    }
    error("Bad token");
  }
}

// define ignore in Token_stream
void Token_stream::ignore(char c)
{
  if (full && c == buffer.kind) {
    full = false;
    return;
  }
  full = false;

  char ch;
  while (cin >> ch)
    if (ch == c) return;
}

//define variable that can be definied in calculator
struct Variable {
  string name;
  double value;
  Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)
{
  for (int i = 0; i < names.size(); ++i)
    if (names[i].name == s) return names[i].value;
  error("get: undefined name ", s);
}

void set_value(string s, double d)
{
  for (int i = 0; i <= names.size(); ++i)
    if (names[i].name == s) {
      names[i].value = d;
      return;
    }
  error("set: undefined name ", s);
}

bool is_declared(string s)
{
  for (int i = 0; i < names.size(); ++i)
    if (names[i].name == s) return true;
  return false;
}

Token_stream ts;

// define function for grammar 
double expression();

// define primary for grammar works with () and negative numbers and sqrt and pow and factorial
double primary()
{
  Token t = ts.get();
  switch (t.kind) {
  case '(':
    {	double d = expression();
      t = ts.get();
      if (t.kind != ')') error("'(' expected");
    }
  case '-':
    return -primary();
  case '+':
    return primary();
  case number:
    return t.value;
  case name:
    return get_value(t.name);
  case '=':
    return primary();

    // for square root
  case root: {
    t= ts.get();
    double d = expression();
    t= ts.get();
    if(d<0)error("Square root can not be negative");
    else{
      double sqr_root = sqrt(d);
      return sqr_root;
	
    }
  }
  
  
    // for power of a number
  case pows:{
    t=ts.get();
    if (t.kind != '(') error("'(' expected");
    double d=expression();
    t=ts.get();
    //if (t.kind!=',') error("',' expected");
    double i=expression();
    t=ts.get();
    if (t.kind != ')') error("')' expected");
    return pow(d,i);
  }
    // for a factorial
  case fact:{
    t=ts.get();
    double dd=expression();
    t=ts.get();
    return factorial(dd);
  }
	
	//for primes
  case prime: {
    t=ts.get();
    double dd=expression();
    t=ts.get();
    return nth_prime(dd);
  }
  
  // for sinus
  case sinus:{
    t=ts.get();
    double dd=expression();
    t=ts.get();
    return my_sin(dd);
  }
  
  // for cosinus
  case cosinus:{
    t=ts.get();
    double dd=expression();
    t=ts.get();
    return my_cos(dd);
  }
  
  // for tangent
  case tangent:{
    t=ts.get();
    double dd=expression();
    t=ts.get();
    return my_tan(dd);
  }
  
  // for nth root
  case nthroot:{
    t=ts.get();
    if (t.kind != '(') error("'(' expected");
    double d=expression();
    t=ts.get();
    //if (t.kind!=',') error("',' expected");
    double i=expression();
    t=ts.get();
    if (t.kind != ')') error("')' expected");
    return nthRoot(d,i);
  }
  
  // for combination
  case combination:{
    t=ts.get();
    if (t.kind != '(') error("'(' expected");
    double d=expression();
    t=ts.get();
    //if (t.kind!=',') error("',' expected");
    double i=expression();
    t=ts.get();
    if (t.kind != ')') error("')' expected");
    return my_combination(d,i);
  }

  default:
    error("primary expected");
  }
	
}

// define term for gramamr handle * /
double term()
{
  double left = primary();
  while (true) {
    Token t = ts.get();
    switch (t.kind) {
    case '*':
      left *= primary();
      break;
    case '/':
      {	double d = primary();
	if (d == 0) error("divide by zero");
	left /= d;
	break;
      }
    default:
      ts.unget(t);
      return left;
    }
  }
}

// define expression for grammar handle + - 
double expression()
{
  double left = term();
  while (true) {
    Token t = ts.get();
    switch (t.kind) {
    case '+':
      left += term();
      break;
    case '-':
      left -= term();
      break;
    default:
      ts.unget(t);
      return left;
    }
  }
}

// define variable declaration
double declaration()
{
  Token t = ts.get();
  if (t.kind != 'a') error("name expected in declaration");
  string name = t.name;
  if (is_declared(name)) error(name, " declared twice");
  Token t2 = ts.get();
  if (t2.kind != '=') error("= missing in declaration of ", name);
  double d = expression();
  names.push_back(Variable(name, d));
  return d;
}

double statement()
{
  Token t = ts.get();
  switch (t.kind) {
  case let:
    return declaration();
  default:
    ts.unget(t);
    return expression();
  }
}

void clean_up_mess()
{
  ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

// define calculator as a function 
void calculate()
{
  while (true) try {
      cout << prompt;
      Token t = ts.get();
      while (t.kind == print) t = ts.get();
      if (t.kind == quit) return;
      ts.unget(t);
      cout << result << statement() << endl;
    }
    catch (runtime_error& e) {
      cerr << e.what() << endl;
      clean_up_mess();
    }
}
