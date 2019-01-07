#include <iostream>

// Concepts:
// ---------------------------------------------------------------
//  address of a variable
//  Deference variables
//  Declaring a pointer
//  Pointers and arrays
//  Pointers and arithmetic operations: add & substract  (precedence of deference and ++ --)
//  const pointers
//  pointer to pointer
//  void pointer (uniform pointer for all types)
//  NULL,0, nullptr (issues with wrong an unitialized pointers)
//  Pointers to functions


void function1() {
	std::cout << "Callback invoked" << std::endl;
}

void function2(void (*cb)()) {
	cb();
}

int main(int argc, char const *argv[])
{
	int i = 10;

	// address of operator
	// deference operator
	int * add = &i;

	std::cout << "Content is " << *add << std::endl;

	// Multiple pointers definition
	int * add1, * add2;

	// Pointers and arrays
	int numbers[] { 1, 2, 3, 4, 5 };

	int * current = numbers;
	int max = sizeof(numbers) / sizeof(int);

	for(current; current != (numbers+max); current++)
		std::cout << "Number: " << *current << std::endl;

    current = numbers;

	for(current; current != (numbers+max); )
		std::cout << "Number: " << *current++ << std::endl;

	for(; current != (numbers-1); current--)
		std::cout << "Number: " << *current << std::endl;


	// With const pointers we can access but not modify
	const int * onlyReadPointer = numbers;

	const int ** pointerToPointer = &onlyReadPointer;

	for(; *pointerToPointer != (numbers+max); (*pointerToPointer)++)
		std::cout << "Pointer to pointer number: " << *(*pointerToPointer) << std::endl;


	// We have 3 ways to initialize the pointer
	int * nullP   = NULL;
	int * zeroP   = 0;
	int * nullPtr = nullptr;


	// Passing function pointers
	function2(function1);

	return 0;
}
