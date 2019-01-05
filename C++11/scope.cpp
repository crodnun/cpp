#include <iostream>

// Concepts:
// ---------------------------------------------------------------
//  Scope of variables
//  Global and local variables
//  Hidden variables using same name
//  Namespaces
//  using directive, avoids full qualifying an entity
//  namespace alias
//  std namespace and using namespace std;
//  initialization value depending on scope

namespace name1 
{
	int dummy()
	{
		return 11;
	}
}

namespace name2
{
	int dummy()
	{
		return 10;
	}
}

namespace test = name1;

int globalVar = 10;

int notInitializedGlobal;

int main(int argc, char const *argv[])
{
	std::cout << globalVar << std::endl;

	std::string local = "hello"; // local var

	std::cout << local << std::endl;

	if(true) {
		std::string local = "bye"; // hides the external one

		std::cout << local << std::endl;
	}

	// use namespaces qualifying
	std::cout << name1::dummy() << std::endl;
	std::cout << name2::dummy() << std::endl;

	using namespace name1;

	std::cout << dummy() << std::endl;

	using name2::dummy;

	std::cout << dummy() << std::endl;
	std::cout << name1::dummy() << std::endl;

	std::cout << test::dummy() << std::endl;


	int notInitializedLocal;

	// Local variables are not initialized by default, global are 
    std::cout << notInitializedGlobal << std::endl;
	std::cout << notInitializedLocal << std::endl;

	return 0;
}
