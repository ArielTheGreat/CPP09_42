#include <iostream>
#include <stack>
#include <array>
#include <fstream>
#include <sstream>
#include <string>

using string = std::string;
using stack = std::stack<int>;
using array = std::array<string, 30>;

class RPN {
	private:
		stack _stack;
		array _input;
	public:
		RPN() = default;
		RPN(const string& input);
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		void calculate();
	};

bool isInputValid(const array& input);
array split(const string& str, char delimiter);
bool isNumeric(const std::string& str);