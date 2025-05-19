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
/*
void BitcoinExchange::calculateValues()
{

}

void BitcoinExchange::findClosest()
{

}
*/
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