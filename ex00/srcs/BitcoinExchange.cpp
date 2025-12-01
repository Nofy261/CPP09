/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:22:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/11/27 11:02:06 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <algorithm>
#include <sstream>

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
    std::string::size_type start = str.find_first_not_of(" \t\n\r\f\v"); // cherche le premier caractere qui n'est pas un espace ...
    if (start == std::string::npos) // n'a pas trouve ce qu'on cherche (carcatere qui n est pas espace , tab etc...)
    {
        str.clear(); // tout est espace ou tab etc... aucun carcatere alphabetique par exemple 
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

static bool isNumber(const std::string &str) //pour les verif de date
{
    for (size_t i = 0; i < str.size(), i++)
    {
        if (!std::isdigit(str[i]))
            return false;
    }
    return true;
}

//2009-01-02,0  <-- .csv
//2023-06-01 | 2.5  <-- file,txt
//2009-01-02
bool BitcoinExchange::IsValidDate(const std::string &date)
{
    if (date.size() != 10)
        return false;
    if (date[4] != '-' && date[7] != '-')
        return false;
    // on decoupe l annee 
    // substr(index de ce qu'on veut prendre, le nombre de caracatere a prendre a partir de cet index)
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

    // Si znnée bissextile 
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1]) // month - 1 = index du mois Ex : janvier = index 0 car (1 - 1)
        return false;

    return true;
}

void BitcoinExchange::loadCsv(const std::string &csvFile)
{
    std::string line;
    std::string date;
    std::string rateStr;
    double rateValue; //taux
    // ouvrir le fihcier csv
    std::ifstream file(csvFile.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file");
        
    std::getline(file, line); // on recupere la premiere ligne et on n'en fait rien(on ignore)
    while (std::getline(file, line))
    {
        // YYYY-MM-DD,0.545  date-taux
        // chercher la virgule
    
        std::istringstream ss(line); //rendre line lisible avec getline
        if ((!std::getline(ss, date, ',')) || (!std::getline(ss, rateStr)))
        {
            std::cerr << "Error: Invalid CSV line format => " << line << std::endl;
            continue;
        }
        trim(date);
        trim(rateStr);
        // parser la date IsvalidateDate()?? 
        if (!IsvalidateDate(date))
        {
            std::cerr << "Error: invalid date in CSV => " << date << std::endl;
            continue; // on ignore la ligne
        }
        // convertir rateStr en double ?
        try
        {
            rateValue = stringToDouble(rateStr);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: invalid rate in CSV => " << rateStr << std::endl;
            continue;
        }
        // mettre la ligne dans la map cad _btcData["2025-01-01"] = 46850.23f;
        _btcData[date] = rateValue;
    }
    file.close();
}