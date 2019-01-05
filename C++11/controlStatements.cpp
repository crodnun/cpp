#include <iostream>

int main(int argc, char const *argv[])
{
	// Under C++ we have the following control statements
	bool isTrue = true;

	// if/else example
	if(isTrue) {
		std::cout << "It is true" << std::endl;
	} else {
		std::cout << "It is false" << std::endl;
	} 

	// Loops
	int i = 0;
	while(i) {
		std::cout << i-- << std::endl;
	}

	do {
		std::cout << i++ << std::endl;
	} while(i < 10);

	for(i=0; i < 10; i++) {
		std::cout << i << std::endl;
	}

	// range based loop
	std::string text = "Hello";

	for(char c : text)
		std::cout << c << std::endl;

	// break and continue
	for(i=0; i < 100; i++) {
		if(i > 78)
			break;

		if(i %2 )
			continue;

		std::cout << i << std::endl;
	}


	// switch-case statements

	int value = 10;

	switch(value) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			std::cout << "No match found" << std::endl;
			break;
	}

	return 0;
}
