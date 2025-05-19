#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>

using valueMap = std::map<std::string, float>;
using valueMultimap = std::multimap<std::string, float>;

class BitcoinExchange
{
    private:
        valueMap _dataBaseMap;
        valueMultimap _inputMap;
    public:
        //Orthodox canonical form
        BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

        void parseDataBase(const std::string& fileName);
        void parseInputFileTxt(const std::string& fileName);
        void parseLineInputFile(const std::string& line);
        void printMatch(const valueMultimap::value_type& pair);
        void calculateValues();
        void printStoredDatabase();
};

#endif