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
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <stdexcept>
#include <set>

// PmergeMe::PmergeMe() : _last(0), _oddList(false), _startVec(0), _startDeq(0), _endVec(0), _endDeq(0), _timeVec(0), _timeDeq(0)
// {}

// PmergeMe::PmergeMe(const PmergeMe& copy)
// {
//     *this = copy;
// }

// PmergeMe& PmergeMe::operator=(const PmergeMe& other)
// {
//     if (this != &other)
//     {
//         _vec = other._vec;
//         _deq = other._deq;
//         _pairs = other._pairs;
//         _last = other._last;
//         _oddList = other._oddList;
//         _minVec = other._minVec;
//         _maxVec = other._maxVec;
//         _minDeq = other._minDeq;
//         _maxDeq = other._maxDeq;
//         _startVec = other._startVec;
//         _startDeq = other._startDeq;
//         _endVec = other._endVec;
//         _endDeq = other._endDeq;
//         _timeVec = other._timeVec;
//         _timeDeq = other._timeDeq;
//     }
//     return (*this);
// }

// PmergeMe::~PmergeMe()
// {}


// static bool isValidNumber(const std::string &str)
// {
//     if (str.empty())
//         throw std::runtime_error("Error: Empty string is not a valid number.");
//     for (size_t i = 0; i < str.size(); i++)
//     {
//         if (!isdigit(str[i]))
//             throw std::runtime_error("Error");
//     }
//     return true;
// }

// void PmergeMe::printContainers() const // affichage des tableaux avant
// {
//     std::cout << "vector BEFORE : ";
//     for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); ++it)
//         std::cout << *it << " ";
//     std::cout << std::endl;

//     std::cout << " deque BEFORE : ";
//     for (std::deque<int>::const_iterator it = _deq.begin(); it != _deq.end(); ++it)
//         std::cout << *it << " ";
//     std::cout << std::endl;

// }


// void PmergeMe::parseAndPush(int argc, char **argv)
// {
//     for(int i = 1; i < argc; i++)
//     {
//         std::string arg = argv[i];
//         if (isValidNumber(arg))
//         {
//             long value = std::atol(arg.c_str());
//             if (value > 2147483647)
//                 throw std::runtime_error("Error: Number too large");

//             if (std::find(_vec.begin(), _vec.end(), static_cast<int>(value)) != _vec.end())
//                 throw std::runtime_error("Error: Duplicate number detected");
//             _vec.push_back(static_cast<int>(value));
//             _deq.push_back(static_cast<int>(value));
//         }
//         else
//             throw std::runtime_error("Error");
//     }
// }

// // void PmergeMe::makePairs()
// // {
// //     for (size_t i = 0; i < _vec.size(); i += 2)
// //     {
// //         if (i + 1 < _vec.size())
// //         {
// //             int a = _vec[i];
// //             int b = _vec[i + 1];
// //             _pairs.push_back(std::make_pair(std::min(a, b), std::max(a, b)));
// //         }
// //         else
// //         {
// //             _last = _vec[i];
// //             _oddList = true;
// //         }
// //     }
// // }

// void PmergeMe::makePairs()
// {
//     for (size_t i = 0; i < _vec.size(); i += 2)
//     {
//         if (i + 1 < _vec.size())
//         {
//             int a = _vec[i];
//             int b = _vec[i + 1];
//             if (a > b)
//             {
//                 int tmp = a;
//                 a = b;
//                 b = tmp;
//             }
//             _pairs.push_back(std::make_pair(a, b));
//         }
//         else
//         {
//             _last = _vec[i];
//             _oddList = true;
//         }
//     }
    
//     // Tri simple des paires selon le deuxième élément (max)
//     for (size_t i = 0; i < _pairs.size(); i++)
//     {
//         for (size_t j = i + 1; j < _pairs.size(); j++)
//         {
//             if (_pairs[i].second > _pairs[j].second)
//             {
//                 std::pair<int, int> tmp = _pairs[i];
//                 _pairs[i] = _pairs[j];
//                 _pairs[j] = tmp;
//             }
//         }
//     }
//     std::cout << "DEBUG _oddList: " << (_oddList ? "true" : "false") << std::endl;
//     std::cout << "DEBUG _last: " << _last << std::endl;
//     std::cout << "DEBUG _pairs.size(): " << _pairs.size() << std::endl;
// }

// void PmergeMe::extractMinsMaxs()
// {
//     for (size_t i = 0; i < _pairs.size(); i++)
//     {
//         _minVec.push_back(_pairs[i].first);
//         _maxVec.push_back(_pairs[i].second);

//         _minDeq.push_back(_pairs[i].first);
//         _maxDeq.push_back(_pairs[i].second);
//     }
// }


// // void PmergeMe::sortMinVec() //  version 1
// // {
// //     _startVec = clock();

// //     std::sort(_minVec.begin(), _minVec.end()); // Tri du vecteur des mins

// //     // Insertion des max selon la suite de Jacobsthal
// //     std::vector<size_t> jacobIndices;
// //     jacobIndices.push_back(0);
// //     if (_maxVec.size() > 1)
// //         jacobIndices.push_back(1);

// //     size_t i = 2;// Construction de la suite de Jacobsthal
// //     while (true)
// //     {
// //         size_t j = jacobIndices[i - 1] + 2 * jacobIndices[i - 2];
// //         if (j >= _maxVec.size())
// //             break;
// //         jacobIndices.push_back(j);
// //         i++;
// //     }

// //     for (size_t k = 0; k < jacobIndices.size(); ++k)// Insertion des max selon Jacobsthal
// //     {
// //         size_t idx = jacobIndices[k];
// //         int value = _maxVec[idx];
// //         std::vector<int>::iterator pos = std::lower_bound(_minVec.begin(), _minVec.end(), value);
// //         _minVec.insert(pos, value);
// //     }

// //     for (size_t i = 0; i < _maxVec.size(); ++i)// Insertion des max restants
// //     {
// //         bool inserted = false;
// //         for (size_t j = 0; j < jacobIndices.size(); ++j)
// //         {
// //             if (jacobIndices[j] == i)
// //             {
// //                 inserted = true;
// //                 break;
// //             }
// //         }
// //         if (!inserted)
// //         {
// //             int value = _maxVec[i];
// //             std::vector<int>::iterator pos = std::lower_bound(_minVec.begin(), _minVec.end(), value);
// //             _minVec.insert(pos, value);
// //         }
// //     }
// //     if (_oddList)
// //     {
// //         std::vector<int>::iterator pos = std::lower_bound(_minVec.begin(), _minVec.end(), _last);
// //         _minVec.insert(pos, _last);
// //     }
// //     _endVec = clock();
// //     _timeVec = 1000000.0 * (_endVec - _startVec) / CLOCKS_PER_SEC;
// // }





// // void PmergeMe::sortMinDeq()
// // {
// //     _startDeq = clock();

// //     std::sort(_minDeq.begin(), _minDeq.end()); // Tri du vecteur des mins

// //     // Insertion des max selon la suite de Jacobsthal
// //     std::deque<size_t> jacobIndices;
// //     jacobIndices.push_back(0);
// //     if (_maxDeq.size() > 1)
// //         jacobIndices.push_back(1);

// //     size_t i = 2;// Construction de la suite de Jacobsthal
// //     while (true)
// //     {
// //         size_t j = jacobIndices[i - 1] + 2 * jacobIndices[i - 2];
// //         if (j >= _maxDeq.size())
// //             break;
// //         jacobIndices.push_back(j);
// //         i++;
// //     }

// //     for (size_t k = 0; k < jacobIndices.size(); ++k)// Insertion des max selon Jacobsthal
// //     {
// //         size_t idx = jacobIndices[k];
// //         int value = _maxDeq[idx];
// //         std::deque<int>::iterator pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), value);
// //         _minDeq.insert(pos, value);
// //     }

// //     for (size_t i = 0; i < _maxDeq.size(); ++i)// Insertion des max restants
// //     {
// //         bool inserted = false;
// //         for (size_t j = 0; j < jacobIndices.size(); ++j)
// //         {
// //             if (jacobIndices[j] == i)
// //             {
// //                 inserted = true;
// //                 break;
// //             }
// //         }
// //         if (!inserted)
// //         {
// //             int value = _maxDeq[i];
// //             std::deque<int>::iterator pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), value);
// //             _minDeq.insert(pos, value);
// //         }
// //     }
// //     if (_oddList)
// //     {
// //         std::deque<int>::iterator pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), _last);
// //         _minDeq.insert(pos, _last);
// //     }

// //     _endDeq = clock();
// //     _timeDeq = 1000000.0 * (_endDeq - _startDeq) / CLOCKS_PER_SEC;
// // }

// void PmergeMe::displayResults() const
// {
//     std::cout << "After sorted vector: ";
//     for (std::vector<int>::const_iterator it = _minVec.begin(); it != _minVec.end(); ++it)
//         std::cout << *it << " ";
//     std::cout << std::endl;

//     std::cout << "After sorted deque: ";
//     for (std::deque<int>::const_iterator it = _minDeq.begin(); it != _minDeq.end(); ++it)
//         std::cout << *it << " ";
//     std::cout << std::endl;
// }


// void PmergeMe::displayTime() const
// {
//     std::cout << "Vector time: " << _timeVec << " us" << std::endl;
//     std::cout << "Deque  time: " << _timeDeq << " us" << std::endl;
// }


// // void PmergeMe::sortMinVec()
// // {
// //     _startVec = clock();

// //     std::sort(_minVec.begin(), _minVec.end()); // Tri du vecteur des mins

// //     // Insertion des max selon la suite de Jacobsthal
// //     std::vector<size_t> jacobIndices;
// //     jacobIndices.push_back(0);
// //     if (_maxVec.size() > 1)
// //         jacobIndices.push_back(1);

// //     size_t i = 2;// Construction de la suite de Jacobsthal
// //     while (true)
// //     {
// //         size_t j = jacobIndices[i - 1] + 2 * jacobIndices[i - 2];
// //         if (j >= _maxVec.size())
// //             break;
// //         jacobIndices.push_back(j);
// //         i++;
// //     }

// //     // Insertion des max selon les intervalles de Jacobsthal
// //     std::set<size_t> insertedIndices;

// //     for (size_t k = 0; k < jacobIndices.size(); ++k) {
// //         insertedIndices.insert(jacobIndices[k]);
        
// //         size_t currentJacob = jacobIndices[k];
// //         size_t prevJacob = 0;
// //         if (k > 0)
// //             prevJacob = jacobIndices[k-1];
        
// //         // Insère l'élément à l'index de Jacobsthal
// //         int value = _maxVec[currentJacob];
// //         std::vector<int>::iterator pos = std::lower_bound(_minVec.begin(), _minVec.end(), value);
// //         _minVec.insert(pos, value);
        
// //         // Insère les éléments entre prevJacob et currentJacob en ordre décroissant
// //         if (currentJacob > prevJacob + 1) {
// //             for (size_t idx = currentJacob - 1; idx > prevJacob; --idx) {
// //                 insertedIndices.insert(idx);
// //                 value = _maxVec[idx];
// //                 pos = std::lower_bound(_minVec.begin(), _minVec.end(), value);
// //                 _minVec.insert(pos, value);
// //             }
// //         }
// //     }

// //     // Insère les éléments restants qui n'ont pas été insérés
// //     for (size_t idx = 0; idx < _maxVec.size(); ++idx) {
// //         if (insertedIndices.find(idx) == insertedIndices.end()) {
// //             int value = _maxVec[idx];
// //             std::vector<int>::iterator pos = std::lower_bound(_minVec.begin(), _minVec.end(), value);
// //             _minVec.insert(pos, value);
// //         }
// //     }

// //     if (_oddList)
// //     {
// //         std::vector<int>::iterator pos = std::lower_bound(_minVec.begin(), _minVec.end(), _last);
// //         _minVec.insert(pos, _last);
// //     }
// //     _endVec = clock();
// //     _timeVec = 1000000.0 * (_endVec - _startVec) / CLOCKS_PER_SEC;
// // }


// // void PmergeMe::sortMinDeq()
// // {
// //     _startDeq = clock();

// //     std::sort(_minDeq.begin(), _minDeq.end()); // Tri du deque des mins

// //     // Insertion des max selon la suite de Jacobsthal
// //     std::deque<size_t> jacobIndices;
// //     jacobIndices.push_back(0);
// //     if (_maxDeq.size() > 1)
// //         jacobIndices.push_back(1);

// //     size_t i = 2;// Construction de la suite de Jacobsthal
// //     while (true)
// //     {
// //         size_t j = jacobIndices[i - 1] + 2 * jacobIndices[i - 2];
// //         if (j >= _maxDeq.size())
// //             break;
// //         jacobIndices.push_back(j);
// //         i++;
// //     }

// //     // Insertion des max selon les intervalles de Jacobsthal
// //     std::set<size_t> insertedIndices;

// //     for (size_t k = 0; k < jacobIndices.size(); ++k) {
// //         insertedIndices.insert(jacobIndices[k]);
        
// //         size_t currentJacob = jacobIndices[k];
// //         size_t prevJacob = 0;
// //         if (k > 0)
// //             prevJacob = jacobIndices[k-1];
        
// //         // Insère l'élément à l'index de Jacobsthal
// //         int value = _maxDeq[currentJacob];
// //         std::deque<int>::iterator pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), value);
// //         _minDeq.insert(pos, value);
        
// //         // Insère les éléments entre prevJacob et currentJacob en ordre décroissant
// //         if (currentJacob > prevJacob + 1) {
// //             for (size_t idx = currentJacob - 1; idx > prevJacob; --idx) {
// //                 insertedIndices.insert(idx);
// //                 value = _maxDeq[idx];
// //                 pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), value);
// //                 _minDeq.insert(pos, value);
// //             }
// //         }
// //     }

// //     // Insère les éléments restants qui n'ont pas été insérés
// //     for (size_t idx = 0; idx < _maxDeq.size(); ++idx) {
// //         if (insertedIndices.find(idx) == insertedIndices.end()) {
// //             int value = _maxDeq[idx];
// //             std::deque<int>::iterator pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), value);
// //             _minDeq.insert(pos, value);
// //         }
// //     }

// //     if (_oddList)
// //     {
// //         std::deque<int>::iterator pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), _last);
// //         _minDeq.insert(pos, _last);
// //     }

// //     _endDeq = clock();
// //     _timeDeq = 1000000.0 * (_endDeq - _startDeq) / CLOCKS_PER_SEC;
// // }

// void PmergeMe::sortMinVec() // derniere versoin
// {
//     _startVec = clock();

//     std::sort(_minVec.begin(), _minVec.end()); // Tri du vecteur des mins

//     // Insertion des max selon la suite de Jacobsthal
//     std::vector<size_t> jacobIndices;
//     if (_maxVec.size() > 0)
//         jacobIndices.push_back(0);
//     if (_maxVec.size() > 1)
//         jacobIndices.push_back(1);

//     size_t i = 2;
//     while (true)
//     {
//         size_t j = jacobIndices[i - 1] + 2 * jacobIndices[i - 2];
//         if (j >= _maxVec.size())
//             break;
//         jacobIndices.push_back(j);
//         i++;
//     }

//     // Insertion des max selon les intervalles de Jacobsthal
//     std::set<size_t> insertedIndices;

//     for (size_t k = 0; k < jacobIndices.size(); ++k) {
//         size_t currentJacob = jacobIndices[k];
//         insertedIndices.insert(currentJacob);
        
//         size_t prevJacob = 0;
//         if (k > 0)
//             prevJacob = jacobIndices[k-1];
        
//         // Insère l'élément à l'index de Jacobsthal
//         int value = _maxVec[currentJacob];
//         std::vector<int>::iterator pos = std::lower_bound(_minVec.begin(), _minVec.end(), value);
//         _minVec.insert(pos, value);
        
//         // Insère les éléments entre prevJacob et currentJacob en ordre décroissant
//         for (size_t idx = currentJacob; idx > prevJacob; --idx) {
//             if (idx - 1 > prevJacob && insertedIndices.find(idx - 1) == insertedIndices.end()) {
//                 insertedIndices.insert(idx - 1);
//                 value = _maxVec[idx - 1];
//                 pos = std::lower_bound(_minVec.begin(), _minVec.end(), value);
//                 _minVec.insert(pos, value);
//             }
//         }
//     }

//     // Insère les éléments restants
//     for (size_t idx = 0; idx < _maxVec.size(); ++idx) {
//         if (insertedIndices.find(idx) == insertedIndices.end()) {
//             int value = _maxVec[idx];
//             std::vector<int>::iterator pos = std::lower_bound(_minVec.begin(), _minVec.end(), value);
//             _minVec.insert(pos, value);
//         }
//     }

//     if (_oddList)
//     {
//         std::vector<int>::iterator pos = std::lower_bound(_minVec.begin(), _minVec.end(), _last);
//         _minVec.insert(pos, _last);
//     }
//     _endVec = clock();
//     _timeVec = 1000000.0 * (_endVec - _startVec) / CLOCKS_PER_SEC;
// }

// void PmergeMe::sortMinDeq() // derniere version
// {
//     _startDeq = clock();

//     std::sort(_minDeq.begin(), _minDeq.end()); // Tri du deque des mins

//     // Insertion des max selon la suite de Jacobsthal
//     std::deque<size_t> jacobIndices;
//     if (_maxDeq.size() > 0)
//         jacobIndices.push_back(0);
//     if (_maxDeq.size() > 1)
//         jacobIndices.push_back(1);

//     size_t i = 2;
//     while (true)
//     {
//         size_t j = jacobIndices[i - 1] + 2 * jacobIndices[i - 2];
//         if (j >= _maxDeq.size())
//             break;
//         jacobIndices.push_back(j);
//         i++;
//     }

//     // Insertion des max selon les intervalles de Jacobsthal
//     std::set<size_t> insertedIndices;

//     for (size_t k = 0; k < jacobIndices.size(); ++k) {
//         size_t currentJacob = jacobIndices[k];
//         insertedIndices.insert(currentJacob);
        
//         size_t prevJacob = 0;
//         if (k > 0)
//             prevJacob = jacobIndices[k-1];
        
//         // Insère l'élément à l'index de Jacobsthal
//         int value = _maxDeq[currentJacob];
//         std::deque<int>::iterator pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), value);
//         _minDeq.insert(pos, value);
        
//         // Insère les éléments entre prevJacob et currentJacob en ordre décroissant
//         for (size_t idx = currentJacob; idx > prevJacob; --idx) {
//             if (idx - 1 > prevJacob && insertedIndices.find(idx - 1) == insertedIndices.end()) {
//                 insertedIndices.insert(idx - 1);
//                 value = _maxDeq[idx - 1];
//                 pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), value);
//                 _minDeq.insert(pos, value);
//             }
//         }
//     }

//     // Insère les éléments restants
//     for (size_t idx = 0; idx < _maxDeq.size(); ++idx) {
//         if (insertedIndices.find(idx) == insertedIndices.end()) {
//             int value = _maxDeq[idx];
//             std::deque<int>::iterator pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), value);
//             _minDeq.insert(pos, value);
//         }
//     }

//     if (_oddList)
//     {
//         std::deque<int>::iterator pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), _last);
//         _minDeq.insert(pos, _last);
//     }

//     _endDeq = clock();
//     _timeDeq = 1000000.0 * (_endDeq - _startDeq) / CLOCKS_PER_SEC;
// }

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

void PmergeMe::printContainers() const
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
    
    // Tri simple des paires selon le deuxième élément (max)
    for (size_t i = 0; i < _pairs.size(); i++)
    {
        for (size_t j = i + 1; j < _pairs.size(); j++)
        {
            if (_pairs[i].second > _pairs[j].second)
            {
                std::pair<int, int> tmp = _pairs[i];
                _pairs[i] = _pairs[j];
                _pairs[j] = tmp;
            }
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
    
    // Ajoute l'élément impair dans minVec/minDeq s'il existe
    if (_oddList)
    {
        _minVec.push_back(_last);
        _minDeq.push_back(_last);
    }
}


void PmergeMe::sortMinVec()
{
    _startVec = clock();

    std::sort(_minVec.begin(), _minVec.end());

    // Insertion des max selon la suite de Jacobsthal
    std::vector<size_t> jacobIndices;
    if (_maxVec.size() > 0)
        jacobIndices.push_back(0);
    if (_maxVec.size() > 1)
        jacobIndices.push_back(1);

    size_t i = 2;
    while (true)
    {
        size_t j = jacobIndices[i - 1] + 2 * jacobIndices[i - 2];
        if (j >= _maxVec.size())
            break;
        jacobIndices.push_back(j);
        i++;
    }

    // Insertion des max selon les intervalles de Jacobsthal
    std::set<size_t> insertedIndices;

    for (size_t k = 0; k < jacobIndices.size(); ++k) {
        size_t currentJacob = jacobIndices[k];
        insertedIndices.insert(currentJacob);
        
        size_t prevJacob = 0;
        if (k > 0)
            prevJacob = jacobIndices[k-1];
        
        // Insère l'élément à l'index de Jacobsthal
        int value = _maxVec[currentJacob];
        std::vector<int>::iterator pos = std::lower_bound(_minVec.begin(), _minVec.end(), value);
        _minVec.insert(pos, value);
        
        // Insère les éléments entre prevJacob et currentJacob en ordre décroissant
        for (size_t idx = currentJacob; idx > prevJacob; --idx) {
            if (idx - 1 > prevJacob && insertedIndices.find(idx - 1) == insertedIndices.end()) {
                insertedIndices.insert(idx - 1);
                value = _maxVec[idx - 1];
                pos = std::lower_bound(_minVec.begin(), _minVec.end(), value);
                _minVec.insert(pos, value);
            }
        }
    }

    // Insère les éléments restants
    for (size_t idx = 0; idx < _maxVec.size(); ++idx) {
        if (insertedIndices.find(idx) == insertedIndices.end()) {
            int value = _maxVec[idx];
            std::vector<int>::iterator pos = std::lower_bound(_minVec.begin(), _minVec.end(), value);
            _minVec.insert(pos, value);
        }
    }

    _endVec = clock();
    _timeVec = 1000000.0 * (_endVec - _startVec) / CLOCKS_PER_SEC;
}


void PmergeMe::sortMinDeq()
{
    _startDeq = clock();

    std::sort(_minDeq.begin(), _minDeq.end());

    // Insertion des max selon la suite de Jacobsthal
    std::deque<size_t> jacobIndices;
    if (_maxDeq.size() > 0)
        jacobIndices.push_back(0);
    if (_maxDeq.size() > 1)
        jacobIndices.push_back(1);

    size_t i = 2;
    while (true)
    {
        size_t j = jacobIndices[i - 1] + 2 * jacobIndices[i - 2];
        if (j >= _maxDeq.size())
            break;
        jacobIndices.push_back(j);
        i++;
    }

    // Insertion des max selon les intervalles de Jacobsthal
    std::set<size_t> insertedIndices;

    for (size_t k = 0; k < jacobIndices.size(); ++k) {
        size_t currentJacob = jacobIndices[k];
        insertedIndices.insert(currentJacob);
        
        size_t prevJacob = 0;
        if (k > 0)
            prevJacob = jacobIndices[k-1];
        
        // Insère l'élément à l'index de Jacobsthal
        int value = _maxDeq[currentJacob];
        std::deque<int>::iterator pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), value);
        _minDeq.insert(pos, value);
        
        // Insère les éléments entre prevJacob et currentJacob en ordre décroissant
        for (size_t idx = currentJacob; idx > prevJacob; --idx) {
            if (idx - 1 > prevJacob && insertedIndices.find(idx - 1) == insertedIndices.end()) {
                insertedIndices.insert(idx - 1);
                value = _maxDeq[idx - 1];
                pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), value);
                _minDeq.insert(pos, value);
            }
        }
    }

    // Insère les éléments restants
    for (size_t idx = 0; idx < _maxDeq.size(); ++idx) {
        if (insertedIndices.find(idx) == insertedIndices.end()) {
            int value = _maxDeq[idx];
            std::deque<int>::iterator pos = std::lower_bound(_minDeq.begin(), _minDeq.end(), value);
            _minDeq.insert(pos, value);
        }
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