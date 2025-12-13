/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:22:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/12/13 19:54:58 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <set>

BitcoinExchange::BitcoinExchange(){};
    
BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
    *this = copy;
}
    
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        this->_btcData = other._btcData;
    return (*this);
}
    
BitcoinExchange::~BitcoinExchange(){};


static double stringToDouble(const std::string& str)
{
    std::stringstream ss(str);
    double value;
    ss >> value; 

    if (ss.fail() || !ss.eof())
        throw std::runtime_error("Invalid double format: " + str);
    return value;
}

void BitcoinExchange::trim(std::string &str)
{
    std::string::size_type start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos)
    {
        str.clear();
        return;
    }
    else
        str.erase(0, start);

    std::string::size_type end = str.find_last_not_of(" \t\n\r\f\v");
    if (end == std::string::npos)
		str.clear();
    else 
        str.erase(end + 1);
}

static bool isNumber(const std::string &str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if (!std::isdigit(str[i]))
            return false;
    }
    return true;
}

bool BitcoinExchange::IsValidDateCsv(const std::string &date)
{
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);

    if (!isNumber(yearStr) || !isNumber(monthStr) || !isNumber(dayStr))
        return false;

    int year = std::atoi(yearStr.c_str());
    int month = std::atoi(monthStr.c_str());
    int day = std::atoi(dayStr.c_str());

    if (month < 1 || month > 12)
        return false;
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1])
        return false;
    return true;
}

static bool IsValidDateMessage(const std::string &date)
{
    if (date.size() != 10)
    {
        std::cerr << "Error: Bad input => " << date << std::endl;
        return false;
    }
    if (date[4] != '-' || date[7] != '-')
    {
        std::cerr << "Error: Bad input => " << date << std::endl;
        return false;
    }

    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);

    if (!isNumber(yearStr) || !isNumber(monthStr) || !isNumber(dayStr))
    {
        std::cerr << "Error: Bad input => " << date << std::endl;
        return false;
    }

    int year = std::atoi(yearStr.c_str());
    int month = std::atoi(monthStr.c_str());
    int day = std::atoi(dayStr.c_str());

    if (month < 1 || month > 12)
    {
        std::cerr << "Error: Bad input => " << date << std::endl;
        return false;
    }
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1])
    {
        std::cerr << "Error: Bad input => " << date << std::endl;
        return false;
    }
    return true;
}

bool BitcoinExchange::IsValidRate(const std::string &rate)
{
    std::stringstream ss(rate);
    double rateValue;
    ss >> rateValue;

    if (ss.fail() || !ss.eof())
    {
        std::cerr << "Error: bad input => " << rate << std::endl;
        return false;
    }
    if (rateValue < 0)
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }
    if (rateValue > 1000)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

void BitcoinExchange::loadCsv(const std::string &csvFile)
{
    std::string line;
    std::string date;
    std::string rateStr;
    double rateValue;
    
    std::ifstream file(csvFile.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file");
    if (!std::getline(file, line))
        throw std::runtime_error("Error: empty CSV file");
    trim(line);
    if (line.empty())
        throw std::runtime_error("Error: empty header line");

    std::string expectedHeader = "date,exchange_rate";
    if (line != expectedHeader)
        throw std::runtime_error("Error: incorrect header of CSV file");
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        if ((!std::getline(ss, date, ',')) || (!std::getline(ss, rateStr)))
        {
            std::cerr << "Error: Invalid CSV line format => " << line << std::endl;
            continue;
        }
        trim(date);
        trim(rateStr);
        if (!IsValidDateCsv(date))
        {
            std::cerr << "Error: invalid date in CSV => " << date << std::endl;
            continue;
        }
        try
        {
            rateValue = stringToDouble(rateStr);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: invalid rate in CSV => " << rateStr << std::endl;
            continue;
        }
        if (_btcData.find(date) != _btcData.end())
        {
            std::cerr << "Error: duplicate date in CSV => " << date << std::endl;
            continue;
        }
        _btcData[date] = rateValue;
    }
    file.close();
}

static bool isPipe(const std::string &str)
{
    int countp = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '|')
            countp++;
    }
    if (countp != 1)
        return false;
    return true;
}

void BitcoinExchange::execute(const std::string &argvFile)
{
    std::string line;
    std::string date;
    std::string rate;
    
    std::set<std::string> processedLines;

    std::ifstream file(argvFile.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file");

    if (!std::getline(file, line))
        throw std::runtime_error("Error: empty input file");
    trim(line);
    if (line.empty())
        throw std::runtime_error("Error: empty header line");

    std::string expectedHeader = "date | value";
    if (line != expectedHeader)
        throw std::runtime_error("Error: incorrect header of input file");

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        trim(line);
        if (!isPipe(line) || line.size() < 14)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        size_t pipeIndex = line.find('|');
        if (pipeIndex != 11 || line[pipeIndex - 1] != ' ' || line[pipeIndex + 1] != ' ')
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::istringstream iss(line);
        if (!std::getline(iss, date, '|') || !std::getline(iss, rate)) 
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        trim(date);
        trim(rate);

        if (!IsValidDateMessage(date) || !IsValidRate(rate))
            continue;

        double rateValue = stringToDouble(rate);

        if (processedLines.find(line) != processedLines.end())
        {
            std::cerr << "Error: duplicate line => " << line << std::endl;
            continue;
        }
        processedLines.insert(line);

        std::map<std::string, double>::const_iterator it = _btcData.lower_bound(date);
        if (it == _btcData.end() || it->first != date)
        {
            if (it == _btcData.begin())
            {
                std::cerr << "Error: Date not found in database => " << date << std::endl;
                continue;
            }
            --it;
        }
        double btcPrice = it->second;
        double result = btcPrice * rateValue;
        std::cout << date << " => " << rateValue << " = " << result << std::endl;
    }
    file.close();
}
