#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>

using valueMap = std::multimap<std::string, float>;
using valuePair = std::pair<std::string, float>;

class BitcoinExchange
{
    private:
        valueMap _dataBaseMap;
        valueMap _inputMap;
    public:
        //Orthodox canonical form
        BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

        void parseDataBase(const std::string& fileName);
        void parseInputFile(const std::string& fileName);
        void calculateValues();
        void findClosest();
};

#endif