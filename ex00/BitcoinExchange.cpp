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

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
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
        std::vector<std::string> row = split(line, ',');

        for (const auto &cell : row) {
            std::cout << cell << "\t";
        }
        std::cout << std::endl;
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
