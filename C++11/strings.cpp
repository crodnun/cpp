#include <iostream>

// Concepts:
// ---------------------------------------------------------------
// strings
// access C chars of string
//
//

int main(int argc, char const *argv[])
{
	// string type is a powerful type provided by C++
	std::string myString{"Test string2"};

	std::cout << myString << std::endl;

	// get c-chars (char*)
	std::cout << "Get string char* : " << myString.c_str() << std::endl;

	return 0;
}
