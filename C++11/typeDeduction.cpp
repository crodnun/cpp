#include <iostream>

int main(int argc, char const *argv[])
{
	// Usage of auto and decltype
	// compiler infers the type when the variable is initialized
	auto i = 1;
	decltype(i) j = 2;

	std::cout << "Auto values are: " << i << ", " << j << std::endl;

	return 0;
}
