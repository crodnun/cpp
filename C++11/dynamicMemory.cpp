#include <iostream>
//#include <new>

// Concepts:
// ---------------------------------------------------------------
//  new and delete
//  nothrow
//  new[] delete[]
//  

int main(int argc, char const *argv[])
{
	int * numbers = new int[5]{};

	for(int i=0; i < 5; i++)
		std::cout << numbers[i] << std::endl;


	// deallocate
	delete[] numbers;

	// allocate single item
	float * f = new float;

	delete f;


	// usage of nothrow to skip exceptions and just return null when allocating memory with new

	int * values = new (std::nothrow) int[10000000000000000000];

	if(!values) {
		std::cout << "Unable to allocate memory" << std::endl;
	}

	// If we remove nothrow, we get the exception
	// terminate called after throwing an instance of 'std::bad_alloc'
    // what():  std::bad_alloc

	values = new int[10000000000000000000];

	if(!values) {
		std::cout << "Unable to allocate memory" << std::endl;
	}

	return 0;
}
