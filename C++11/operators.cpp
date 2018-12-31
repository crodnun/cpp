#include <iostream>

int main(int argc, char const *argv[])
{
	// Operators 
	// Arithmetic
	// +, -, *, /, % 
	int x(0);
	int y = ((2 + (x = 5)) * 10 % 3) - 4;
	
	std::cout << y << std::endl; 


	// Compound assignment (+=, -=, *=, /=, %=, >>=, <<=, &=, ^=, |=)
	y += 1;
	y >>= 1;
	y &= 3;

	std::cout << y << std::endl; 

	// Increment and decrement (++, --)

	std::cout << y++ << " " << ++y << " " << y-- << " " << --y << std::endl; 


	// Relational and comparison operators ( ==, !=, >, <, >=, <= )

	std::cout << (y == x) << " " << (y != x)  << " " << (y >= x)  << " " << (y <= x)  << std::endl; 


	// Logical operators ( !, &&, || )

	std::cout << (y && x) << " " << (y || x)  << " " << (!y)  << " " << (y && x || y)  << std::endl; 

	// Conditional ternary operator

	std::cout << ((y && x)?"AND":"NOT AND") << std::endl;

	// Comma operator ( , )
	y = (x=3, x+1);
	std::cout << y << std::endl;

	// Bitwise operators ( &, |, ^, ~, <<, >> )
	std::cout << (y & x) << " " << (y | x)  << " " << (~y)  << " " << (y && x || y)  << std::endl; 

	// Explicit type casting operator
	float value = 1.67;
	std::cout << (int) value << std::endl;

	// sizeof
	std::cout << sizeof(y) << std::endl;


	return 0;
}
