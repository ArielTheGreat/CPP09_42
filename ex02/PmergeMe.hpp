#include <iostream>
#include <vector>
#include <deque>
#include <chrono>

using TimePoint = std::chrono::high_resolution_clock::time_point;
using string = std::string;
using vector = std::vector<int>;
using sizetVector = std::vector<size_t>;
using sizetDeque = std::deque<size_t>;
using deque = std::deque<int>;

class PmergeMe {
	private:
	vector _finalMain;
	deque _finalMainDeque;

	TimePoint _vectorStart;
	TimePoint _vectorEnd;

	TimePoint _dequeStart;
	TimePoint _dequeEnd;

	public:
		vector _mainChainVec;
		deque _mainChainDeque;

		PmergeMe() = default;
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe() = default;

		// Experiment Vector
		void algorithmVec(vector& mainChain);
		void separatePairsVec(vector& mainChain, vector& secChain, vector& newMain);
		void binaryInsertionVec(vector& mainChain, vector& secChain);
		sizetVector generateJacobsthalInsertionOrder(vector& secChain);
		void insertSingleElementVec(int value, vector& mainChain);

		// Experiment Deque
		void algorithmDeque(deque& mainChain);
		void separatePairsDeque(deque& mainChain, deque& secChain, deque& newMain);
		void binaryInsertionDeque(deque& mainChain, deque& secChain);
		void insertSingleElementDeque(int value, deque& mainChain);
		sizetDeque generateJacobsthalInsertionOrder(deque& secChain);

		void setDequeInit();
		void setDequeFinish();
		long long calculateDurationDeque();
		void setVecInit();
		void setVecFinish();
		long long calculateDurationVec();

		void printMainChain(const string& message);
		void insertValue(int value);

	};

	TimePoint getTime();
	sizetVector generateJacobsthalSequence(size_t n);
	void printVector(const vector& vec);
	void printVector(const sizetVector& vec);
	bool isNumeric(const std::string& str);