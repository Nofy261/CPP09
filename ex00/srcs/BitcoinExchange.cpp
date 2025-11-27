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
    else str.erase(end + 1);
}

void BitcoinExchange::loadCsv(const std::string &csvFile)
{
    std::string line;
    std::string date;
    std::string rateStr;
    float rate; //taux
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
            std::cerr << "Error: Invalid line format => " << line << std::endl;
            continue;
        }
        trim(date);
        trim(rateStr);
        // convertir rateStr en float ou double ?
        // mettre la ligne dans la map
    }

    file.close();
}


