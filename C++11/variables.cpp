#include <iostream>

int main(int argc, char const *argv[])
{
	// Initialize variables
	// classic initialization
	float value1 = 2.1;
	// constructor initializer
	float value2(2.4);
	// C++11 added the uniform initializer
	float value3{1.2};

	std::cout << "Float values are: " << value1 << ", " << value2 << ", " << value3 << std::endl;

	return 0;
}
