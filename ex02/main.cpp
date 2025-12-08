/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:18:28 by nolecler          #+#    #+#             */
/*   Updated: 2025/12/03 14:18:31 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"

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
        pmm.printContainers();
        pmm.makePairs();
        pmm.extractMinsMaxs();
        pmm._sortMinVec();
        pmm._sortMinDeq();
        pmm.displayResults();
        pmm.displayTime();
       
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    return (0);
}