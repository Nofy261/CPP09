/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:18:43 by nolecler          #+#    #+#             */
/*   Updated: 2025/12/16 10:51:18 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <stdexcept>
#include <sstream> 

PmergeMe::PmergeMe() : _startVec(0), _startDeq(0), _endVec(0), _endDeq(0), _timeVec(0), _timeDeq(0)
{}

PmergeMe::PmergeMe(const PmergeMe& copy)
{
    *this = copy;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _deq = other._deq;
        _startVec = other._startVec;
        _startDeq = other._startDeq;
        _endVec = other._endVec;
        _endDeq = other._endDeq;
        _timeVec = other._timeVec;
        _timeDeq = other._timeDeq;
    }
    return (*this);
}

PmergeMe::~PmergeMe()
{}

static bool isValidNumber(const std::string &str)
{
    if (str.empty())
        return false;

    size_t start = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');
    if (start == std::string::npos)
        return false;

    for (size_t i = start; i <= end; i++)
    {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

void PmergeMe::printBeforeSort() const
{
    std::cout << "vector BEFORE : ";
    for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "deque BEFORE : ";
    for (std::deque<int>::const_iterator it = _deq.begin(); it != _deq.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}


void PmergeMe::parseAndPush(int argc, char **argv)
{
    bool hasNumber = false;

    for (int i = 1; i < argc; ++i)
    {
        std::stringstream ss(argv[i]);
        std::string token;

        while (ss >> token)
        {
            if (!isValidNumber(token))
                throw std::runtime_error("Error");
            
            long value = std::atol(token.c_str());
            if (value > 2147483647)
                throw std::runtime_error("Error: Number too large");

            if (std::find(_vec.begin(), _vec.end(), static_cast<int>(value)) != _vec.end())
                throw std::runtime_error("Error: Duplicate number detected");

            _vec.push_back(static_cast<int>(value));
            _deq.push_back(static_cast<int>(value));
            hasNumber = true;
        }
    }
    if (!hasNumber)
        throw std::runtime_error("Error");
}

// void PmergeMe::buildOrder(std::vector<int>& jacob, std::vector<int>& order, int n)
// {
//     std::vector<bool> used(n, false);
//     order.push_back(0);
//     used[0] = true;
 
//     for (size_t i = 0; i < jacob.size(); ++i)
//     {
//         int j = jacob[i];
//         if (j - 1 < n && !used[j - 1])
//         {                 
//             order.push_back(j - 1);
//             used[j - 1] = true;
//         }
        
//         if (i > 0)
//         {
//             int prev = jacob[i - 1];
//             for (int k = j - 2; k >= prev; --k)
//             {
//                 if (k < n && !used[k])
//                 {
//                     order.push_back(k);
//                     used[k] = true;
//                 }
//             }
//         }
//     }
// }


void PmergeMe::printAfterSort() const
{
    std::cout << std::endl;
    std::cout << "vector AFTER : ";
    for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "deque AFTER : ";
    for (std::deque<int>::const_iterator it = _deq.begin(); it != _deq.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}


void PmergeMe::displayTime() const
{
    std::cout << std::endl;
    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << _timeVec << " us" << std::endl;

    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque : " << _timeDeq << " us" << std::endl;
}


// generer la suite jacostahl
// creer une fonction qui donne l ordre d insertion


std::vector<int> PmergeMe::fordJohnsonVec(const std::vector<int>& input)
{
    if (input.size() <= 1)
        return input;

    std::vector<int> mins;
    std::vector<int> maxs;
    bool oddList = false;
    int oddValue = 0;

    for (size_t i = 0; i + 1 < input.size(); i += 2)
    {
        int a = input[i];
        int b = input[i + 1];

        if (a < b)
        {
            mins.push_back(a);
            maxs.push_back(b);
        }
        else
        {
            mins.push_back(b);
            maxs.push_back(a);
        }
    }
    if (input.size() % 2 != 0)
    {
        oddList = true;
        oddValue = input.back();
    }
    
    maxs = fordJohnsonVec(maxs);

    std::vector<size_t> jacob;
    jacob.push_back(0);
    if (mins.size() > 1)
        jacob.push_back(1);

    size_t i = 2;
    while (i < mins.size())
    {
        size_t j = jacob[i - 1] + 2 * jacob[i - 2];
        if (j >= mins.size())
            break;
        jacob.push_back(j);
        i++;
    }

    std::vector<bool> inserted(mins.size(), false);
    for (size_t i = 0; i < jacob.size(); ++i)
    {
        size_t idx = jacob[i];
        if (!inserted[idx])
        {
            int value = mins[idx];
            std::vector<int>::iterator pos = std::lower_bound(maxs.begin(), maxs.end(), value);
            maxs.insert(pos, value);
            inserted[idx] = true;
        }
    }
    for (size_t i = 0; i < mins.size(); ++i)
    {
        if (!inserted[i])
        {
            int value = mins[i];
            std::vector<int>::iterator pos = std::lower_bound(maxs.begin(), maxs.end(), value);
            maxs.insert(pos, value);
        }
    }
    if (oddList)
    {
        std::vector<int>::iterator pos = std::lower_bound(maxs.begin(), maxs.end(), oddValue);
        maxs.insert(pos, oddValue);
    }
    return maxs;
}

std::deque<int> PmergeMe::fordJohnsonDeq(const std::deque<int>& input)
{
    if (input.size() <= 1)
        return input;

    std::deque<int> mins;
    std::deque<int> maxs;
    bool oddList = false;
    int oddValue = 0;

    for (size_t i = 0; i + 1 < input.size(); i += 2)
    {
        int a = input[i];
        int b = input[i + 1];

        if (a < b)
        {
            mins.push_back(a);
            maxs.push_back(b);
        }
        else
        {
            mins.push_back(b);
            maxs.push_back(a);
        }
    }
    if (input.size() % 2 != 0)
    {
        oddList = true;
        oddValue = input.back();
    }
    maxs = fordJohnsonDeq(maxs);

    std::deque<size_t> jacob;
    jacob.push_back(0);
    if (mins.size() > 1)
        jacob.push_back(1);

    size_t i = 2;
    while (i < mins.size())
    {
        size_t j = jacob[i - 1] + 2 * jacob[i - 2];
        if (j >= mins.size())
            break;
        jacob.push_back(j);
        i++;
    }

    std::vector<bool> inserted(mins.size(), false);

    for (size_t i = 0; i < jacob.size(); ++i)
    {
        size_t idx = jacob[i];
        if (!inserted[idx])
        {
            int value = mins[idx];
            std::deque<int>::iterator pos = std::lower_bound(maxs.begin(), maxs.end(), value);
            maxs.insert(pos, value);
            inserted[idx] = true;
        }
    }
    for (size_t i = 0; i < mins.size(); ++i)
    {
        if (!inserted[i])
        {
            int value = mins[i];
            std::deque<int>::iterator pos =
                std::lower_bound(maxs.begin(), maxs.end(), value);
            maxs.insert(pos, value);
        }
    }
    if (oddList)
    {
        std::deque<int>::iterator pos = std::lower_bound(maxs.begin(), maxs.end(), oddValue);
        maxs.insert(pos, oddValue);
    }
    return maxs;
}

void PmergeMe::sortMaxVec()
{
    _startVec = clock();
    _vec = fordJohnsonVec(_vec);
    _endVec = clock();
    _timeVec = 1000000.0 * (_endVec - _startVec) / CLOCKS_PER_SEC;
}

void PmergeMe::sortMaxDeq()
{
    _startDeq = clock();
    _deq = fordJohnsonDeq(_deq);
    _endDeq = clock();
    _timeDeq = 1000000.0 * (_endDeq - _startDeq) / CLOCKS_PER_SEC;
}