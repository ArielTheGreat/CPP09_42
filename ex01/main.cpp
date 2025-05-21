#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Wrong amount of arguments, program takes 2" << std::endl;
		return 0;
	}

	RPN rpn(argv[1]);
	
	rpn.calculate();
}