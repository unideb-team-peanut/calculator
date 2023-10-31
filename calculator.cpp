
/*
	calculator08buggy.cpp
	Helpful comments removed.
	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include "std_lib_facilities.h"

// define constansok
constexpr char let = '#';
constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char root = 'S';
constexpr char pows = 'P';
constexpr char fact = 'F';

//function declarations
double expression();
double primary();
double term();
double declaration();
double statement();

// factorial definition extra function
int factorial(int f){
	int fact = 1;
	if(f < 0){
		cout <<"Use a positive number for factorial!";
	}
	else{
        for(int i = 1; i <= f; ++i) {
            fact *= i;
        }
    
    return fact;
	}
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

int main()
	
try {
	cout << "This calculator can handle + - * /"<< endl;
	cout<< "Use ; to print result"<< endl;
	cout<< "k = 1000 as constans" << endl;
	cout<< "Use sqrt(number) to calculate square root of a number"<< endl;
	cout<< "Use pow(num1 ,num2) to calculate num2 power of a num1"<< endl;
	cout<< "Use fact(number) to calculate factorial of a number"<< endl;
	cout<< "Use # to define a variable like # x= 1;"<< endl;
	cout<< "Type in exit to exit"<< endl;
	
	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
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
