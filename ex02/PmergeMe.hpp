/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:18:50 by nolecler          #+#    #+#             */
/*   Updated: 2025/12/16 09:30:50 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <deque>
#include <ctime>

class PmergeMe
{
    public :
        PmergeMe();
        PmergeMe(const PmergeMe& copy);
        PmergeMe &operator=(const PmergeMe& other);
        ~PmergeMe();

        void parseAndPush(int argc, char **argv);
        void printBeforeSort() const;
        void sortMaxVec();
        void sortMaxDeq();
        void printAfterSort() const;
        void displayTime() const;

    private :
        std::vector<int> _vec;
        std::deque<int> _deq;

        clock_t _startVec;
        clock_t _startDeq;
        clock_t _endVec;
        clock_t _endDeq;

        double _timeVec;
        double _timeDeq;

        std::deque<int> fordJohnsonDeq(const std::deque<int>& input);
        std::vector<int> fordJohnsonVec(const std::vector<int>& input);
};