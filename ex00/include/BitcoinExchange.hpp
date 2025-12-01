/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:23:05 by nolecler          #+#    #+#             */
/*   Updated: 2025/11/27 11:02:19 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <iostream>

class BitcoinExchange
{
    public :
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& copy);
        BitcoinExchange &operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        //fct pour charger la csv
        //fct de parsing : parse le fichier d'entree
        void trim(std::string &str);
        bool IsValidDateCsv(const std::string &date);
        bool IsValidRate(const std::string &rate);
        void loadCsv(const std::string &csvFile);
        void execute(const std::string &argvFile);
        // ouvrir le fichier : error si pb
        // parser la premiere ligne 
        //


    private :
        std::map<std::string, double> _btcData;
};
