#include <iostream>

// Concepts:
// ---------------------------------------------------------------
//  Function, parameters, return value
//  void
//  passing arguments by value, by reference, by const reference (efficiency when doing the copy)
//  inline functions
//  default parameters
//  declaration and definition of functions (declare before using it)
//  recursivity, a function calls itself
//  overloaded functions


void functionByReference(std::string& text);  // function declaration

void functionByReference(std::string& text, int value);  // overload previous function



void functionByValue(int value) 
{
	std::cout << value << std::endl;

	// We need function declaration before calling it, otherwise we obtain
	// error: 'functionByReference' was not declared in this scope
	std::string text;
	functionByReference(text);

	// We can not modify the input value
	value = 10;
}

void functionByReference(std::string& text) 
{
	std::cout << text << std::endl;

	// We can modify the variable here
	text = "Bye";
}

void functionByReferenceConst(const std::string& text) 
{
	std::cout << text << std::endl;

	// We can NOT modify the variable here
	// If we un-comment this line we obtain the following error:
	// error: passing 'const string {aka const std::basic_string<char>}' as 'this' argument of 'std::basic_string<_CharT, _Traits, _Alloc>& std::basic_string<_CharT, _Traits, _Alloc>::operator=(const _CharT*) [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]' discards qualifiers [-fpermissive]
	// text = "Bye";
}

int functionReturnValue(int value) 
{
	std::cout << value << std::endl;

	return (value*2);
}

int functionWithDefaults(int value, int other=2) 
{
	return (value*other);
}

inline std::string inlineConcatenate(const std::string& a, const std::string& b)
{
	return a+b;
}

int factorial (int value)
{
	int result = 1;

	if(value > 1) {
		result = value * factorial(value-1);
		std::cout << result << std::endl;
		return result;
	}

    std::cout << result << std::endl;
  	return 1;
}

int main(int argc, char const *argv[])
{
	int value = 5;
	functionByValue(value);
	std::cout << value << std::endl;

	std::string text = "Hello";

	functionByReference(text);
	std::cout << text << std::endl;

	std::cout << functionReturnValue(20) << std::endl;

	std::cout << inlineConcatenate("Hello ", "World") << std::endl;

	std::cout << functionWithDefaults(2) << std::endl;

	std::cout << std::endl << "Running factorial: " << std::endl;
	factorial(9);

	return 0;
}
