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
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    std::string line;
    while(std::getline(file, line))
    {
        if (line.empty()) continue;
        std::list<std::string> row = split(line, ',');
        auto it = row.begin();
        std::string key = *it++;
        float valueStr = *it;
        try{
            size_t pos;
            float value = std::stof(valueStr, &pos);
            _dataBaseMap[key] = valueStr;
        }
    }
    file.close();
}

void BitcoinExchange::parseInputFile(const std::string& fileName)
{
    std::ifstream file(fileName);
}

void BitcoinExchange::calculateValues()
{

}

void BitcoinExchange::findClosest()
{

}

void BitcoinExchange::printStoredDatabase()
{
    if (_dataBaseMap.size() == 0)
        std::cout << "Size of container not enough to iterate through!" << std::endl;
    else
    {
        for (const auto& [key, value] : _dataBaseMap) {
            std::cout << key << " => " << value << std::endl;
        }
    }
}