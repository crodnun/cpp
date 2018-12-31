#include <iostream>

// we can represent also constants as pre-processor macros
#define MY_CONSTANT 12.6f

int main(int argc, char const *argv[])
{
	// We can define constants

	const float PI = 3.1416;

	std::cout << PI << std::endl;

	// constants can not be modified - the line:
	// PI += 1; 
	// generates error: assignment of read-only variable 'PI'

	// we can define string constants and concatenate multiple lines
	std::string longLine = "This is a long line with "
						   "more text at the end";

	std::cout << longLine << std::endl;

	// We can represent constants with suffixes
	std::cout << 100L << " " << 10.2f << " " << R"(This is a raw string \\\\)" << " " << MY_CONSTANT << std::endl; 

	return 0;
}
