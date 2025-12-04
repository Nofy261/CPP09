/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:18:50 by nolecler          #+#    #+#             */
/*   Updated: 2025/12/03 14:18:54 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <vector>
#include <deque>

class PmergeMe
{
    public :
        PmergeMe();
        PmergeMe(const PmergeMe& copy);
        PmergeMe &operator=(const PmergeMe& other);
        ~PmergeMe();

        void parseAndPush(int argc, char **argv);



    private :
        std::vector<int> _vec;
        std::deque<int> _deq;


};