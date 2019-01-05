#include <iostream>

// Concepts:
// ---------------------------------------------------------------
//  Function templates
//  Template definition and instantiation (with or without types)
//  Non type template arguments
//  

template <class T>
T addNumbers(T a, T b)
{
	return a+b;
}

template <class T>
T concatenate(T a, T b)
{
	return a+b;
}

template <class T, int N>
T multiply(T a)
{
	return a * N;
}

template <class T>
T multiply(T a, int N)
{
	return a * N;
}

int main(int argc, char const *argv[])
{
	std::cout << concatenate<std::string>("a", "b") << std::endl;

	std::cout << addNumbers<int>(5, 8) << std::endl;

	std::cout << multiply<int, 2>(5) << std::endl;

	std::cout << multiply<int>(5, 2) << std::endl;

	return 0;
}
