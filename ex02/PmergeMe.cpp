/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:18:43 by nolecler          #+#    #+#             */
/*   Updated: 2025/12/17 10:35:24 by nolecler         ###   ########.fr       */
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
#include <utility>

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


static std::vector<size_t> buildJacobInsertionOrderV(size_t n)
{
    std::vector<size_t> jacob;
    std::vector<size_t> order;

    if (n == 0)
        return order;

    jacob.push_back(1);
    if (n > 1)
        jacob.push_back(3);

    while (jacob.back() < n)
        jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);

    size_t prev = 0;
    for (size_t i = 0; i < jacob.size(); ++i)
    {
        size_t cur = std::min(jacob[i], n);
        for (size_t j = cur; j > prev; --j)
            order.push_back(j - 1);
        prev = cur;
    }
    return order;
}

static std::deque<size_t> buildJacobInsertionOrderD(size_t n)
{
    std::deque<size_t> jacob;
    std::deque<size_t> order;

    if (n == 0)
        return order;

    jacob.push_back(1);
    if (n > 1)
        jacob.push_back(3);

    while (jacob.back() < n)
        jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);

    size_t prev = 0;
    for (size_t i = 0; i < jacob.size(); ++i)
    {
        size_t cur = std::min(jacob[i], n);
        for (size_t j = cur; j > prev; --j)
            order.push_back(j - 1);
        prev = cur;
    }
    return order;
}

static void insertOneVec(std::vector<int>& maxs, int minValue, int maxValue)
{
    std::vector<int>::iterator bound = std::find(maxs.begin(), maxs.end(), maxValue);
    std::vector<int>::iterator pos = std::lower_bound(maxs.begin(), bound, minValue);
    maxs.insert(pos, minValue);
}

static void insertOneDeq(std::deque<int>& maxs, int minValue, int maxValue)
{
    std::deque<int>::iterator bound = std::find(maxs.begin(), maxs.end(), maxValue);
    std::deque<int>::iterator pos = std::lower_bound(maxs.begin(), bound, minValue);
    maxs.insert(pos, minValue);
}

static void insertMinsWithJacobOrderV(std::vector<int>& maxs, const std::vector< std::pair<int,int> >& pairs)
{
    std::vector<size_t> jacobOrder = buildJacobInsertionOrderV(pairs.size());
    for (size_t i = 0; i < jacobOrder.size(); ++i)
    {
        size_t idx = jacobOrder[i];
        insertOneVec(maxs, pairs[idx].first, pairs[idx].second);
    }
}

static void insertMinsWithJacobOrderD(std::deque<int>& maxs, const std::deque< std::pair<int,int> >& pairs)
{
    std::deque<size_t> jacobOrder = buildJacobInsertionOrderD(pairs.size());
    for (size_t i = 0; i < jacobOrder.size(); ++i)
    {
        size_t idx = jacobOrder[i];
        insertOneDeq(maxs, pairs[idx].first, pairs[idx].second);
    }
}

std::vector<int> PmergeMe::fordJohnsonVec(const std::vector<int>& input)
{
    if (input.size() <= 1)
        return input;

    std::vector< std::pair<int,int> > pairs;
    std::vector<int> maxs;
    bool oddList = false;
    int oddValue = 0;

    size_t i;
    for (i = 0; i + 1 < input.size(); i += 2)
    {
        int a = input[i];
        int b = input[i + 1];
        if (a < b)
            pairs.push_back(std::make_pair(a,b));
        else
            pairs.push_back(std::make_pair(b,a));
        maxs.push_back(pairs.back().second);
    }

    if (input.size() % 2 != 0)
    {
        oddList = true;
        oddValue = input.back();
    }

    maxs = fordJohnsonVec(maxs);
    insertMinsWithJacobOrderV(maxs, pairs);

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

    std::deque< std::pair<int,int> > pairs;
    std::deque<int> maxs;
    bool oddList = false;
    int oddValue = 0;

    size_t i;
    for (i = 0; i + 1 < input.size(); i += 2)
    {
        int a = input[i];
        int b = input[i + 1];
        if (a < b)
            pairs.push_back(std::make_pair(a,b));
        else
            pairs.push_back(std::make_pair(b,a));
        maxs.push_back(pairs.back().second);
    }

    if (input.size() % 2 != 0)
    {
        oddList = true;
        oddValue = input.back();
    }

    maxs = fordJohnsonDeq(maxs);
    insertMinsWithJacobOrderD(maxs, pairs);
    
    std::deque<int>::iterator pos;
    if (oddList)
    {
        pos = std::lower_bound(maxs.begin(), maxs.end(), oddValue);
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