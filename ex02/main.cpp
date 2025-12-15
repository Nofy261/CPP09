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

// int main(int argc, char **argv)
// {
//     if (argc < 2)
//     {
//         std::cerr << "Error" << std::endl;
//         return (1);
//     }
//     PmergeMe pmm;
//     try
//     {
//         pmm.parseAndPush(argc, argv);
//         pmm.printBeforeSort();
//         pmm.makePairs();
//         pmm.extractMinsMaxs();
//         pmm.sortMaxVec();
//         pmm.sortMaxDeq();
//         pmm.printAfterSort();
//         pmm.displayTime();
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//         return (1);
//     }
//     return (0);
// }



int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }
    try
    {
        PmergeMe pmm;

        pmm.parseAndPush(argc, argv);
        pmm.printBeforeSort();

        // Tri Ford–Johnson + timing
        //pmm.sortWithFordJohnson();
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

//void fordjohnson()
//{
    //1-parseAndPush()
    //2-print juste pour tester (a enlever apres test)
    //3-makePairs()
    //4-extractMinsMaxs()
    //5- sortMax(); // avec sort ou fordjohnson? :
    //6- suite de jacobsthal pour min
    //7- inserer min dans max avec la suite de jacob
    //8- s'occuper des nombres restants
//}

//void fordjohnson(container)
//{
    // if (container.size() <= 1)
    //     return container;
    //1-parseAndPush()
    //2-print juste pour tester (a enlever apres test)
    //3-makePairs()
    //4-extractMinsMaxs()
    //5- trier max avec fordjohnson :
        //a)->sortMax() = fordjohnson(max);
        // appel recursif a fordjohnson jusqu a ce que la liste soit de taille 1 ou 0
    //6- suite de jacobsthal pour min
    //7- inserer min dans sortMax 
    //8- s'occuper des nombres restants
//}

// fordJohnson(list)
// {
//     if (list.size() <= 1)
//         return list;   // STOP

//     faire des paires
//     séparer min / max

//     maxTrié = fordJohnson(max)   // 🔁 APPEL RÉCURSIF

//     insérer min dans maxTrié
//     retourner le résultat
// }

// std::vector<int> fordJohnsonVec(const std::vector<int>& input);
// std::deque<int>  fordJohnsonDeq(const std::deque<int>& input);

// pmm.parseAndPush(argc, argv);
// pmm.printBeforeSort();

// _startVec = clock();
// _resultVec = fordJohnsonVec(_vec);
// _endVec = clock();

// _startDeq = clock();
// _resultDeq = fordJohnsonDeq(_deq);
// _endDeq = clock();

// pmm.printAfterSort();
// pmm.displayTime();