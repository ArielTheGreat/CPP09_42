#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const PmergeMe& other) {
	_mainChainVec = other._mainChainVec;
	_mainChainDeque = other._mainChainDeque;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	_mainChainVec = other._mainChainVec;
	_mainChainDeque = other._mainChainDeque;
	return (*this);
}

void PmergeMe::setVecInit() {
	_vectorStart = getTime();
}

void PmergeMe::setVecFinish() {
	_vectorEnd = getTime();
}

void PmergeMe::setDequeInit() {
	_dequeStart = getTime();
}

void PmergeMe::setDequeFinish() {
	_dequeEnd= getTime();
}

sizetVector PmergeMe::generateJacobsthalInsertionOrder(vector& secChain) {
	sizetVector order;
	sizetVector jacob = generateJacobsthalSequence(secChain.size());

	// printVector(jacob);

	// Add all missing indices between Jacobsthal numbers in reverse
	for (size_t j = 1; j < jacob.size(); ++j) {
		for (size_t i = std::min(jacob[j], secChain.size() - 1); i > jacob[j - 1]; --i) {
			order.push_back(i);
		}
	}

	// printVector(order);
	return order;
}

void PmergeMe::insertSingleElementVec(int value, vector& mainChain) {
	auto insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), value);
	mainChain.insert(insertPos, value);
}

void PmergeMe::binaryInsertionVec(vector& mainChain, vector& secChain) {
	if (secChain.empty()) return;

	// Insert first pend element
	insertSingleElementVec(secChain[0], mainChain);
	// printVector(mainChain);

	// gen Jacobsthal sequence
	std::vector<size_t> insertionOrder = generateJacobsthalInsertionOrder(secChain);

	// insert remaining elements in optimized order
	for (size_t index : insertionOrder) {
		if (index < secChain.size()) {
			insertSingleElementVec(secChain[index], mainChain);
		}
	}

	secChain.clear();
}

void PmergeMe::separatePairsVec(vector& mainChain, vector& secChain, vector& newMain) {
	int a;
	int b;

	for (size_t i = 0; i < mainChain.size(); i += 2)
	{
		if (i + 1 >= mainChain.size()) {
			secChain.push_back(mainChain[i]);
		} else {
			a = mainChain[i];
			b = mainChain[i + 1];
			newMain.push_back(a > b ? a : b);
			secChain.push_back(a > b ? b : a);
		}
	}
}

void PmergeMe::algorithmVec(vector& mainChain) {
	if (mainChain.size() <= 1) {
		_finalMain = mainChain;
		return;
	}

	vector newMain;
	vector secChain;

	separatePairsVec(mainChain, secChain, newMain);
	algorithmVec(newMain);
	binaryInsertionVec(newMain, secChain);
	mainChain = newMain;
	_finalMain = newMain;
}

void PmergeMe::insertSingleElementDeque(int value, deque& mainChain) {
	auto insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), value);
	mainChain.insert(insertPos, value);
}

sizetDeque PmergeMe::generateJacobsthalInsertionOrder(deque& secChain) {
	sizetDeque order;
	sizetVector jacob = generateJacobsthalSequence(secChain.size());

	for (size_t j = 1; j < jacob.size(); ++j) {
		size_t start = jacob[j - 1] + 1;
		size_t end = std::min(jacob[j], secChain.size() - 1);

		for (size_t i = end + 1; i-- > start;) {
			order.push_back(i);
		}
	}

	return order;
}

void PmergeMe::binaryInsertionDeque(deque& mainChain, deque& secChain) {
	if (secChain.empty()) return;

	// Insert first pend element
	insertSingleElementDeque(secChain[0], mainChain);

	// gen Jacobsthal sequence
	sizetDeque insertionOrder = generateJacobsthalInsertionOrder(secChain);

	// insert remaining elements in optimized order
	for (size_t index : insertionOrder) {
		if (index < secChain.size()) {
			insertSingleElementDeque(secChain[index], mainChain);
		}
	}

	secChain.clear();
}

void PmergeMe::separatePairsDeque(deque& mainChain, deque& secChain, deque& newMain) {
	int a;
	int b;

	for (size_t i = 0; i < mainChain.size(); i += 2)
	{
		if (i + 1 >= mainChain.size()) {
			secChain.push_back(mainChain[i]);
		} else {
			a = mainChain[i];
			b = mainChain[i + 1];
			newMain.push_back(a > b ? a : b);
			secChain.push_back(a > b ? b : a);
		}
	}
}

void PmergeMe::algorithmDeque(deque& mainChain) {
	if (mainChain.size() <= 1) {
		_finalMainDeque = mainChain;
		return;
	}

	deque newMain;
	deque secChain;

	separatePairsDeque(mainChain, secChain, newMain);
	algorithmDeque(newMain);
	binaryInsertionDeque(newMain, secChain);
	mainChain = newMain;
	_finalMainDeque = newMain;
}

bool isNumeric(const std::string& str) {
	int i = 0;
	for (char ch : str)
	{
		if (ch == '-' && i == 0 && str.length() != 1)
			continue;
		if (!std::isdigit(ch))
			return false;
		i++;
	}
	return true;
}

TimePoint getTime() {
	return std::chrono::high_resolution_clock::now();
}

long long PmergeMe::calculateDurationVec() {
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(_vectorEnd - _vectorStart);
	return duration.count();
}

long long PmergeMe::calculateDurationDeque() {
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(_dequeEnd - _dequeStart);
	return duration.count();
}

void printVector(const std::vector<int>& vec) {
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i];
		if (i != vec.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}

void printVector(const std::vector<size_t>& vec) {
	std::cout << "Jacob vector\n";
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i];
		if (i != vec.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printMainChain(const string& message) {
	std::cout << message << ": ";
	for (size_t i = 0; i < _mainChainVec.size(); ++i) {
		std::cout << _mainChainVec[i];
		if (i != _mainChainVec.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::insertValue(int value) {
	_mainChainVec.push_back(value);
	_mainChainDeque.push_back(value);
}

sizetVector generateJacobsthalSequence(size_t n)
{
	sizetVector sequence = {0, 1};
	while (sequence.back() < n)
	{
		size_t next = sequence[sequence.size() - 1] + 2 * sequence[sequence.size() - 2];
		sequence.push_back(next);
	}
	return sequence;
}