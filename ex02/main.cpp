/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:18:28 by nolecler          #+#    #+#             */
/*   Updated: 2025/12/11 15:56:11 by nolecler         ###   ########.fr       */
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

Étapes concrètes pour le faire :
Construire la suite de Jacobsthal jusqu’à la taille de maxVec.
La suite commence par : 0, 1, 3, 5, 11, 21, …
Formule récursive : J(n) = J(n-1) + 2*J(n-2)
Parcourir maxVec dans l’ordre donné par la suite de Jacobsthal.
Pour chaque élément de maxVec :
Trouver sa position dans le minVec trié avec std::lower_bound.
L’insérer à cette position.


makePairs():
Crée des paires de nombres dans _vec.
Chaque paire est triée en interne (petit, grand).
Si le nombre total est impair, garde le dernier dans _last.
Trie ensuite les paires selon le maximum de chaque paire (croissant).
Ex : _pairs = [(2,5), (1,4), (3,6)] devient _pairs = [(1,4),(2,5),(3,6)] Les max sont dans l ordre croissant

extractMinsMaxs():
Sépare les paires en deux listes :
_minVec / _minDeq → les plus petits de chaque paire
_maxVec / _maxDeq → les plus grands de chaque paire
Si la liste initiale est impaire, ajoute _last aux listes des minimums.
Trie _maxVec et _maxDeq pour commencer avec les maximums déjà triés


sortMaxVec():
On commence à mesurer le temps d’exécution du tri pour le vector.

Préparation : _maxVec contient déjà les max triés, _minVec contient les min non triés
Cette étape est conceptuelle : les éléments maximum des paires sont déjà triés (après extractMinsMaxs()), et _minVec contient les plus petits éléments à insérer dans _maxVec.

Génération des indices de la suite de Jacobsthal
On calcule une suite d’indices selon Jacobsthal pour déterminer l’ordre d’insertion des minimums.
Cette suite permet d’optimiser le tri en limitant le nombre de comparaisons lors des insertions dans _maxVec.

Marquer quels éléments(indices) ont été insérés
On initialise un vecteur booléen pour savoir si chaque élément de _minVec a déjà été inséré dans _maxVec.
Évite de réinsérer plusieurs fois le même élément.

Insertion des minimums selon la suite de Jacobsthal
On parcourt les indices de Jacobsthal.
Pour chaque indice, on insère l’élément correspondant de _minVec dans _maxVec à la bonne position grâce à std::lower_bound.
On marque ensuite l’élément comme inséré.

Insertion des minimums restants
Après Jacobsthal, certains éléments peuvent rester non insérés (parce que la suite n’a pas couvert tous les indices).
On les insère maintenant dans l’ordre naturel pour compléter le tri.

Arrêt du chronomètre et calcul du temps
On calcule le temps total pour trier _vec.
Le résultat est en microsecondes.


sortMaxDeq():
Générer les indices de Jacobsthal
Marquer quels éléments sont insérés
Insérer d’abord selon Jacobsthal
Insérer ensuite les restants
Calculer le temps écoulé

Resume Algo FordJohnson
Création des paires 
Tri des max 
Insertion des min selon la suite de Jacobsthal
Insertion des min restants :Certains min peuvent ne pas être couverts par la suite de Jacobsthal.On les insère ensuite à leur position correcte dans le vecteur max.
Insertion de l’élément impair
Résultat final.