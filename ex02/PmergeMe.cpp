/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:18:43 by nolecler          #+#    #+#             */
/*   Updated: 2025/12/03 14:18:47 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"



bool isValidNumber(const std::string &str)
{
    if (str.empty())
        throw std::runtime_error("Error: Empty string is not a valid number.");
    for (size_t i = 0; i < str.size(); i++)
    {
        if (!isdigit(str[i]))
            throw std::runtime_error("Error");
    }
    return true;
}

void PmergeMe::printContainers() const // affichage des tableaux avant
{
    std::cout << "vector BEFORE : ";
    for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << " deque BEFORE : ";
    for (std::deque<int>::const_iterator it = _deq.begin(); it != _deq.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

}



void PmergeMe::parseAndPush(int argc, char **argv)
{
    for(int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (isValidNumber(arg))
        {
            long value = std::atol(arg.c_str());
            if (value > 2147483647)
                throw std::runtime_error("Error: Number too large");

            if (std::find(_vec.begin(), _vec.end(), static_cast<int>(value)) != _vec.end())
                throw std::runtime_error("Error: Duplicate number detected");
            _vec.push_back(static_cast<int>(value));
            _deq.push_back(static_cast<int>(value));
        }
        else
            throw std::runtime_error("Error");
    }
}