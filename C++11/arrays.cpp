#include <iostream>
#include <array>

// Concepts:
// ---------------------------------------------------------------
//  array
//  array initialization methods
//  access elements of an array (indexes start at 0)
//  multidimensional arrays
//  passing arrays as parameters to functions
//  array template , standard container and size method
//  char arrays as strings
//
//
//

void workWithArray(int values[], int size)
{
	for(int i=0; i < size; i++)
		std::cout << "Called function:" << values[i] << std::endl;
}

void workWithArray(int values[][2], int size)
{
	for(int i=0; i < size; i++)
		for(int j=0; j < 2; j++)
			std::cout << "Called function:" << values[i][j] << std::endl;
}

void workWithArray(int values[2][2])
{
	for(int i=0; i < 2; i++)
		for(int j=0; j < 2; j++)
			std::cout << "Called function:" << values[i][j] << std::endl;
}

int main(int argc, char const *argv[])
{
	int values[] {1, 2, 3};
	int otherValues[5] {1, 2};

	for(int item : values)
		std::cout << item << std::endl;

	for(int item : otherValues)
		std::cout << item << std::endl;

	for(int i=0; i < 5; i++)
		std::cout << otherValues[i] << std::endl;


	// multidimensional - we must define the dimensions except the first
	// error: declaration of 'matrix' as multidimensional array must have bounds for all dimensions except the first
	// int matrix[][] {};

	int matrix[2][2] { {1, 2}, {1, 2}};

	for(int i=0; i < 2; i++)
		for(int j=0; j < 2; j++)
			std::cout << matrix[i][j] << std::endl;


	workWithArray(values, 3);

	workWithArray(matrix, 2);

	workWithArray(matrix);

	// using the container instead of the old fashioned C array
	std::array<int, 3> container {1, 2, 3};

	for(int item : container)
		std::cout << item << std::endl;

	for(int i=0; i < container.size(); i++)
		std::cout << container[i] << std::endl;

	char text[] = { 't', 'e', 'x', 't', '\0'};

	std::cout << text << std::endl;

	char otherText[] = "Hello";

	std::cout << otherText << std::endl;

	char message[10] {'H', 'e', 'l', 'l', 'o'};

	std::cout << message << std::endl;

	return 0;
}
