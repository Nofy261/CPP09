/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:18:01 by nolecler          #+#    #+#             */
/*   Updated: 2025/12/13 11:31:09 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <stack>
#include <iostream>

class RPN
{
    public :
        RPN();
        RPN(const RPN& copy);
        RPN &operator=(const RPN& other);
        ~RPN();

        int process(const std::string &str);

    private :
        std::stack<int> _stack;
        int applyOperator(int a, int b, const std::string &op);
};