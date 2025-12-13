/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:18:28 by nolecler          #+#    #+#             */
/*   Updated: 2025/12/13 19:56:24 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }
    PmergeMe pmm;
    try
    {
        pmm.parseAndPush(argc, argv);
        pmm.printBeforeSort();
        pmm.makePairs();
        pmm.extractMinsMaxs();
        pmm.sortMaxVec();
        pmm.sortMaxDeq();
        pmm.printAfterSort();
        pmm.displayTime();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    return (0);
}

// faire des pairs - extraire min et max - trier max avec fordjohnson - 
// creer une fonction fordjohnson qui fait les etapes de fordjonhson

