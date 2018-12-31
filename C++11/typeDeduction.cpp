#include <iostream>

int main(int argc, char const *argv[])
{
	// Usage of auto and decltype
	// compiler infers the type when the variable is initialized if we use the "auto" reserved word
	auto i = 1;

	// decltype operator obtains the type of a given variable
	decltype(i) j = 2;

	std::cout << "Auto values are: " << i << ", " << j << std::endl;

	return 0;
}
