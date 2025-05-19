#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other){
    _dataBaseMap = other._dataBaseMap;
	_inputMap = other._inputMap;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other)
    {
        _dataBaseMap = other._dataBaseMap;
	    _inputMap = other._inputMap;
    }
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

std::list<std::string> split(const std::string &s, char delimiter) {
    std::list<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        // Trim whitespace from tokens
        token.erase(token.find_last_not_of(" \t\n\r\f\v") + 1);
        token.erase(0, token.find_first_not_of(" \t\n\r\f\v"));
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

void BitcoinExchange::parseDataBase(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    std::string line;
    while(std::getline(file, line))
    {
        if (line.empty()) continue;
        std::list<std::string> row = split(line, ',');
        auto it = row.begin();
        std::string key = *it;
        *it++;
        std::string valueStr = *it;
        try{
            size_t pos;
            float value = std::stof(valueStr, &pos);
            if (pos != valueStr.length()) {
                throw std::invalid_argument("Invalid characters in value");
            }
            _dataBaseMap[key] = value;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error parsing value for date " << key << ": " << valueStr << " " << e.what() << std::endl;
        }
    }
    file.close();
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

void BitcoinExchange::parseLineInputFile(const std::string& line) {
	size_t commaPos = line.find('|');

	std::string date = trim(line.substr(0, commaPos));
	std::string value = trim(line.substr(commaPos + 1));
	float fValue = std::stof(value);

	_inputMap.insert(std::make_pair(date, fValue));
}

void BitcoinExchange::parseInputFileTxt(const std::string& fileName)
{
    std::ifstream	file(fileName);
	std::string			line;

	if (!file.is_open()) {
		std::cout << "Input file could not be opened" << std::endl;
		return;
	}

	std::getline(file, line);

	while (std::getline(file, line))
	{
		// Might to a try catch here an throw and error for bad formating
		parseLineInputFile(line);
	}
}

bool isNumeric(const std::string& str) {
	int i = 0;
	int len = str.length();
	for (char ch : str)
	{
		if (ch == '.' && i != 0 && i != len -1)
		continue;
	if (!std::isdigit(ch))
		{
			// std::cout << ch << std::endl;
			return false;
		}
		i++;
	}
	return true;
}

bool isDateValid(const std::string& date)
{
	std::list<std::string> strList;
    strList = split(date, '-');

    if (strList.size() != 3) {
        return false;
    }

    auto it = strList.begin();
    std::string yearStr = *it++;  // First element (year)
    std::string monthStr = *it++; // Second element (month)
    std::string dayStr = *it; 

	if (std::stoi(yearStr) > 2025 || std::stoi(monthStr) > 12 || std::stoi(dayStr) > 31)
		return false;

	for (auto& word : strList)
	{
		// std::cout << word << std::endl;
		if (!isNumeric(word))
			return false;
	}
	return true;
}

bool isValidFormat(const std::string& value)
{
	int count = std::count(value.begin(), value.end(), '.');
	if (count > 1)
		return false;
	return true;
}

bool isValueValid(const std::string& value) {
	if (!isNumeric(value) || !isValidFormat(value))
		return false;
	return true;
}

void BitcoinExchange::printMatch(const valueMultimap::value_type& pair) {
    std::string inputDate = pair.first;
	float inputValue = pair.second;

    if (!isValueValid(std::to_string(inputValue))) {
		std::cout << "Error: Bad Input (Input file) => " << inputValue << std::endl;
		return;
    }
    else if (!isDateValid(inputDate))
	{
		std::cout << "Error: Date is Invalid (Input file) => " << inputDate << std::endl;
		return;
	} else if ( inputValue > 1000) {
		std::cout << "Error: too large a number (Input file) => " << inputValue << std::endl;
		return;
	}

	valueMap::iterator it =  _dataBaseMap.find(inputDate);
	if ((it != _dataBaseMap.end()))
	{
		// std::cout << it->second  << " * " << inputValue << std::endl;
		std::cout << inputDate << " => " << inputValue << " = " << it->second * inputValue << std::endl;
	}
	else
	{
		valueMultimap::value_type pairCopy = pair;
		_dataBaseMap.insert(pairCopy);
		it =  _dataBaseMap.find(inputDate);
		if (it != _dataBaseMap.begin())
			it--;
		else
			it++;

		// std::cout << it->second  << " * " << inputValue << std::endl;
		std::cout << inputDate << " => " << inputValue << " = " << inputValue * it->second << std::endl;
		_dataBaseMap.erase(pairCopy.first);
	}
}

void BitcoinExchange::calculateValues()
{
    std::string inputDate;

	if (_dataBaseMap.empty() || _inputMap.empty())
		return;
    
    for (const auto& pair : _inputMap)
    {
        printMatch(pair);
    }
}

void BitcoinExchange::printStoredDatabase()
{
    if (_dataBaseMap.size() == 0)
    {
        std::cout << "Size of container not enough to iterate through!" << std::endl;
    }
    else
    {
        for (const auto& [key, value] : _dataBaseMap)
        {
            std::cout << key << " => " << value << std::endl;
        }
    }
}