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
#include <algorithm>

//a implementer la forme canonique

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

PmergeMe::PmergeMe() : _last(0), _oddList(false)
{}

void PmergeMe::makePairs()
{
    for (size_t i = 0; i < _vec.size(); i += 2)
    {
        if (i + 1 < _vec.size())
        {
            int a = _vec[i];
            int b = _vec[i + 1];
            _pairs.push_back(std::make_pair(std::min(a, b), std::max(a, b)));
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
}


// void PmergeMe::sortMinVec()
// {
//     _startVec = clock();
//     std::sort(_minVec.begin(), _minVec.end());
//     // insertion des max selon Jacobsthal 
//     _endVec = clock();
//     _timeVec = 1000000.0 * (_endVec - _startVec) / CLOCKS_PER_SEC;
// }

void PmergeMe::sortMinVec()
{
    _startVec = clock();

    std::sort(_minVec.begin(), _minVec.end()); // Tri du vecteur des mins

    std::vector<int> jacobIndices; // Insertion des max selon la suite de Jacobsthal
    jacobIndices.push_back(0);
    if (_maxVec.size() > 1)
        jacobIndices.push_back(1);

    int i = 2;// Construction de la suite de Jacobsthal
    while (true)
    {
        int j = jacobIndices[i - 1] + 2 * jacobIndices[i - 2];
        if (j >= static_cast<int>(_maxVec.size()))
            break;
        jacobIndices.push_back(j);
        i++;
    }

    for (size_t k = 0; k < jacobIndices.size(); ++k)// Insertion des max selon Jacobsthal
    {
        int idx = jacobIndices[k];
        int value = _maxVec[idx];
        std::vector<int>::iterator pos = std::lower_bound(_minVec.begin(), _minVec.end(), value);
        _minVec.insert(pos, value);
    }

    for (size_t i = 0; i < _maxVec.size(); ++i)// Insertion des max restants
    {
        bool inserted = false;
        for (size_t j = 0; j < jacobIndices.size(); ++j)
        {
            if (jacobIndices[j] == i)
            {
                inserted = true;
                break;
            }
        }
        if (!inserted)
        {
            int value = _maxVec[i];
            std::vector<int>::iterator pos = std::lower_bound(_minVec.begin(), _minVec.end(), value);
            _minVec.insert(pos, value);
        }
    }
    if (_oddList)
    {
        std::vector<int>::iterator pos = std::lower_bound(_minVec.begin(), _minVec.end(), _last);
        _minVec.insert(pos, _last);
    }
    _endVec = clock();
    _timeVec = 1000000.0 * (_endVec - _startVec) / CLOCKS_PER_SEC;
}



// void PmergeMe::sortMinDeq()
// {
//     _startDeq = clock();
//     std::sort(_minDeq.begin(), _minDeq.end());
//     // insertion des max selon Jacobsthal 
//     _endDeq = clock();
//     _timeDeq = 1000000.0 * (_endDeq - _startDeq) / CLOCKS_PER_SEC;
// }

void PmergeMe::sortMinDeq()
{
    _startDeq = clock();

    std::sort(_minDeq.begin(), _minDeq.end()); // Tri du vecteur des mins

    std::deque<int> jacobIndices; // Insertion des max selon la suite de Jacobsthal
    jacobIndices.push_back(0);
    if (_maxDeq.size() > 1)
        jacobIndices.push_back(1);

    int i = 2;// Construction de la suite de Jacobsthal
    while (true)
    {
        int j = jacobIndices[i - 1] + 2 * jacobIndices[i - 2];
        if (j >= static_cast<int>(_maxDeq.size()))
            break;
        jacobIndices.push_back(j);
        i++;
    }

    for (size_t k = 0; k < jacobIndices.size(); ++k)// Insertion des max selon Jacobsthal
    {
        int idx = jacobIndices[k];
        int value = _maxDeq[idx];
        std::deque<int>::iterator pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), value);
        _minDeq.insert(pos, value);
    }

    for (size_t i = 0; i < _maxDeq.size(); ++i)// Insertion des max restants
    {
        bool inserted = false;
        for (size_t j = 0; j < jacobIndices.size(); ++j)
        {
            if (jacobIndices[j] == i)
            {
                inserted = true;
                break;
            }
        }
        if (!inserted)
        {
            int value = _maxDeq[i];
            std::deque<int>::iterator pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), value);
            _minDeq.insert(pos, value);
        }
    }
    if (_oddList)
    {
        std::deque<int>::iterator pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), _last);
        _minDeq.insert(pos, _last);
    }

    _endDeq = clock();
    _timeDeq = 1000000.0 * (_endDeq - _startDeq) / CLOCKS_PER_SEC;
}

void PmergeMe::displayResults() const
{
    std::cout << "After sorted vector: ";
    for (std::vector<int>::const_iterator it = _minVec.begin(); it != _minVec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "After sorted deque: ";
    for (std::deque<int>::const_iterator it = _minDeq.begin(); it != _minDeq.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}


void PmergeMe::displayTime() const
{
    std::cout << "Vector time: " << _timeVec << " us" << std::endl;
    std::cout << "Deque  time: " << _timeDeq << " us" << std::endl;
}
