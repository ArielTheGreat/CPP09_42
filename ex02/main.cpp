#include "PmergeMe.hpp"
#include <cstddef>
#include <iostream>
#include <sys/_pthread/_pthread_rwlock_t.h>

int main (int argc, char **argv) {
	int i = 1;
	int value;
	PmergeMe program;

	if (argc < 2)
		return 0;

	while (argv[i] != NULL)
	{
		if (!isNumeric(argv[i]))
		{
			std::cout << "Invalid arguments" << std::endl;
			return 1;
		}

		value = std::stoi(argv[i]);
		program.insertValue(value);
		i++;
	}

	program.printMainChain("Before");
	program.setVecInit();
	program.algorithmVec(program._mainChainVec);
	program.setVecFinish();
	program.printMainChain("After");

	program.setDequeInit();
	program.algorithmDeque(program._mainChainDeque);
	program.setDequeFinish();

	std::cout << "It took for Vector " << program.calculateDurationVec() << " us"<< std::endl;
	std::cout << "It took for Deque " << program.calculateDurationDeque() << " us"<< std::endl;

}