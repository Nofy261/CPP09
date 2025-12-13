/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:18:43 by nolecler          #+#    #+#             */
/*   Updated: 2025/12/13 13:32:23 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <stdexcept>
#include <set>

PmergeMe::PmergeMe() : _last(0), _oddList(false), _startVec(0), _startDeq(0), _endVec(0), _endDeq(0), _timeVec(0), _timeDeq(0)
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
        _pairs = other._pairs;
        _last = other._last;
        _oddList = other._oddList;
        _minVec = other._minVec;
        _maxVec = other._maxVec;
        _minDeq = other._minDeq;
        _maxDeq = other._maxDeq;
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
        throw std::runtime_error("Error: Empty string is not a valid number.");
    for (size_t i = 0; i < str.size(); i++)
    {
        if (!isdigit(str[i]))
            throw std::runtime_error("Error");
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

void PmergeMe::makePairs()
{
    for (size_t i = 0; i < _vec.size(); i += 2)
    {
        if (i + 1 < _vec.size())
        {
            int a = _vec[i];
            int b = _vec[i + 1];
            if (a > b)
            {
                int tmp = a;
                a = b;
                b = tmp;
            }
            _pairs.push_back(std::make_pair(a, b));
        }
        else
        {
            _last = _vec[i];
            _oddList = true;
        }
    }
}

void PmergeMe::extractMinsMaxs()
{
    for (size_t i = 0; i < _pairs.size(); i++)
    {
        _minVec.push_back(_pairs[i].first);
        _maxVec.push_back(_pairs[i].second);

        _minDeq.push_back(_pairs[i].first);
        _maxDeq.push_back(_pairs[i].second);
    }
    if (_oddList)
    {
        _minVec.push_back(_last);
        _minDeq.push_back(_last);
    }
}

void PmergeMe::sortMaxVec()
{
    _maxVec.clear();
    for (size_t i = 0; i < _pairs.size(); i++)
        _maxVec.push_back(_pairs[i].second);
    
    _startVec = clock();
    std::sort(_maxVec.begin(), _maxVec.end());

    std::vector<size_t> jacobIndices;
    if (_minVec.size() > 0) jacobIndices.push_back(0);
    if (_minVec.size() > 1) jacobIndices.push_back(1);

    size_t i = 2;
    while (i < _minVec.size())
    {
        size_t j = jacobIndices[i - 1] + 2 * jacobIndices[i - 2];
        if (j >= _minVec.size())
            break;
        jacobIndices.push_back(j);
        i++;
    }
    std::vector<bool> inserted(_minVec.size(), false);
    for (size_t k = 0; k < jacobIndices.size(); ++k)
    {
        size_t idx = jacobIndices[k];
        if (!inserted[idx]) 
        {
            int value = _minVec[idx];
            std::vector<int>::iterator pos = std::lower_bound(_maxVec.begin(), _maxVec.end(), value);
            _maxVec.insert(pos, value);
            inserted[idx] = true;
        }
    }
    for (size_t idx = 0; idx < _minVec.size(); ++idx)
    {
        if (!inserted[idx])
        {
            int value = _minVec[idx];
            std::vector<int>::iterator pos = std::lower_bound(_maxVec.begin(), _maxVec.end(), value);
            _maxVec.insert(pos, value);
            inserted[idx] = true;
        }
    }
    _endVec = clock();
    _timeVec = 1000000.0 * (_endVec - _startVec) / CLOCKS_PER_SEC;
}


void PmergeMe::sortMaxDeq()
{
    _maxDeq.clear();
    for (size_t i = 0; i < _pairs.size(); i++)
        _maxDeq.push_back(_pairs[i].second);
    
    _startDeq = clock();
    std::sort(_maxDeq.begin(), _maxDeq.end());

    std::deque<size_t> jacobIndices;
    if (_minDeq.size() > 0) jacobIndices.push_back(0);
    if (_minDeq.size() > 1) jacobIndices.push_back(1);

    size_t i = 2;
    while (i < _minDeq.size())
    {
        size_t j = jacobIndices[i - 1] + 2 * jacobIndices[i - 2];
        if (j >= _minDeq.size())
            break;
        jacobIndices.push_back(j);
        i++;
    }
    
    std::vector<bool> inserted(_minDeq.size(), false);
    for (size_t k = 0; k < jacobIndices.size(); ++k)
    {
        size_t idx = jacobIndices[k];
        if (!inserted[idx]) 
        {
            int value = _minDeq[idx];
            std::deque<int>::iterator pos = std::lower_bound(_maxDeq.begin(), _maxDeq.end(), value);
            _maxDeq.insert(pos, value);
            inserted[idx] = true;
        }
    }
    for (size_t idx = 0; idx < _minDeq.size(); ++idx)
    {
        if (!inserted[idx])
        {
            int value = _minDeq[idx];
            std::deque<int>::iterator pos = std::lower_bound(_maxDeq.begin(), _maxDeq.end(), value);
            _maxDeq.insert(pos, value);
            inserted[idx] = true;
        }
    }
    _endDeq = clock();
    _timeDeq = 1000000.0 * (_endDeq - _startDeq) / CLOCKS_PER_SEC;
}

void PmergeMe::printAfterSort() const
{
    std::cout << std::endl;
    std::cout << "vector AFTER : ";
    for (std::vector<int>::const_iterator it = _maxVec.begin(); it != _maxVec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "deque AFTER : ";
    for (std::deque<int>::const_iterator it = _maxDeq.begin(); it != _maxDeq.end(); ++it)
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