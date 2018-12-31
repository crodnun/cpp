#include <iostream>
#include <sstream>

int main(int argc, char const *argv[])
{
	// In c++ we can interact with the user by means of streams
	// stream is just a source or destination of characters where we read/write characters

	// standard ones are cout , cin, cerr, clog

	std::cout << "This is an output" << std::endl;

	// We can read input

	std::cout << "Enter a number: " << std::endl;
	int number = 0;
	std::cin >> number;
	// if we want to reuse it - we need to clear current buffer to start again
	std::cin.clear();
	fflush(stdin);

	// we can read a whole line
	std::cout << "Enter a text: " << std::endl;
	std::string text;
	std::getline(std::cin, text);

	std::cout << "Text read: " << text << std::endl;

	// We can treat also an string as stream and extract fields from there
	std::string input = "This is the input: 213213";
	std::stringstream ss(input);
	// Parse the content of the input into text + number
	std::string text1;

	ss >> text1;

	std::cout << text1 << std::endl;

	return 0;
}
