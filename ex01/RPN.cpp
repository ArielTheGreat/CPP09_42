#include "RPN.hpp"
#include <string>

void printStringArray(const array& vec) {
	for (const auto& str : vec) {
		std::cout << str << std::endl;
		if (str == "")
			break;
	}
}

void printStack(std::stack<int> stk) {
	std::stack<int> tempStack;

	while (!stk.empty()) {
		tempStack.push(stk.top());
		stk.pop();
	}

	std::cout << "Stack contents: ";
	while (!tempStack.empty()) {
		std::cout << tempStack.top() << " ";
		tempStack.pop();
	}

	std::cout << std::endl;
}

RPN::RPN(const string& input){

	_input = split(input, ' ');
	// printStringArray(_input);
}

RPN::RPN(const RPN& other){
	_input = other._input;
	_stack = other._stack;
}

RPN& RPN::operator=(const RPN& other){
	_input = other._input;
	_stack = other._stack;

	return(*this);
}

RPN::~RPN() {}


void RPN::calculate() {
	int a;
	int b;

	if (!isInputValid(_input))
	{
		std::cout << "Error" << std::endl;
		return;
	}

	for (int i = 0; _input[i] != ""; i++) {
		if (isNumeric(_input[i])) {

			_stack.push(std::stoi(_input[i]));
			// std::cout << _input[i] << std::endl;
		}
		else if (_input[i] == "+" && _stack.size() >= 2) {
			// std::cout << "Operation + " << std::endl;
			a = _stack.top();
			_stack.pop();
			b = _stack.top();
			_stack.pop();
			_stack.push( b + a);
		}
		else if (_input[i] == "-" && _stack.size() >= 2){

			// std::cout << "Operation -" << std::endl;
			a = _stack.top();
			_stack.pop();
			b = _stack.top();
			_stack.pop();
			_stack.push( b - a);
		}
		else if (_input[i] == "*" && _stack.size() >= 2) {
			// std::cout << "Operation *" << std::endl;

			a = _stack.top();
			_stack.pop();
			b = _stack.top();
			_stack.pop();
			_stack.push( b * a);
		}
		else if (_input[i] == "/" && _stack.size() >= 2) {
			// std::cout << "Operation /" << std::endl;

			a = _stack.top();
			_stack.pop();
			b = _stack.top();
			_stack.pop();
			_stack.push( b / a);
		}
		else {
			std::cout << "Error" << std::endl;
		}
		// printStack(_stack);
	}
	if (_stack.size() == 1)
		std::cout << "Result: " << _stack.top() << std::endl;
	else
		std::cout << "Expression is incomplete" << std::endl;

}

array split(const string& str, char delimiter) {
	array result = {};
	std::stringstream ss(str);
	string item;
	size_t index = 0;

	while (std::getline(ss, item, delimiter) && index < result.size()) {
		result[index++] = item;
	}

	return result;
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


bool isValidChar(char ch) {
	return std::isdigit(ch) || ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool isInputValid(const array& inputArray) {
	int numCount = 0;

	for (const string& word : inputArray) {
		if (isNumeric(word) && word != "")
		{
			// std::cout << word << std::endl;
			numCount++;
		}

		for (char ch : word) {
			if (!isValidChar(ch))
				return false;

		}
	}

	if (numCount > 10)
	{
		// std::cout << numCount << std::endl;
		return false;
	}

	return true;
}