/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:18:50 by nolecler          #+#    #+#             */
/*   Updated: 2025/12/11 15:38:06 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <deque>
#include <ctime>
#include <utility>

class PmergeMe
{
    public :
        PmergeMe();
        PmergeMe(const PmergeMe& copy);
        PmergeMe &operator=(const PmergeMe& other);
        ~PmergeMe();

        void parseAndPush(int argc, char **argv);
        void printBeforeSort() const;
        void makePairs();
        void extractMinsMaxs();
        void sortMaxVec();
        void sortMaxDeq();
        void printAfterSort() const;
        void displayTime() const;

    private :
        std::vector<int> _vec;
        std::deque<int> _deq;
        std::vector<std::pair<int,int> > _pairs;
        int _last;
        bool _oddList; 

        std::vector<int> _minVec;
        std::vector<int> _maxVec;
        std::deque<int> _minDeq;
        std::deque<int> _maxDeq;

        clock_t _startVec;
        clock_t _startDeq;
        clock_t _endVec;
        clock_t _endDeq;

        double _timeVec;
        double _timeDeq;
};