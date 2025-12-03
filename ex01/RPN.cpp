/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:17:55 by nolecler          #+#    #+#             */
/*   Updated: 2025/12/03 14:18:13 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <exception>

RPN::RPN(){};

RPN::RPN(const RPN& copy)
{
    *this = copy;
}

RPN &RPN::operator=(const RPN& other)
{
    if (this != &other)
        this->_stack = other._stack;
    return (*this);
}

RPN::~RPN(){};

int RPN::applyOperator(int a, int b, const std::string &op)
{
    int result;
    if (op == "+")
        result = a + b;
    else if (op == "-")
        result = a - b;
    else if (op == "*")
        result = a * b;
    else if (op == "/")
    {
        if (b == 0)
            throw std::runtime_error("Error: Division by zero");
        result = a / b;
    }
    else
        throw std::runtime_error("Error: Invalid operator");
    return result;
}

int RPN::process(const std::string &str)
{
    std::istringstream iss(str);
    std::string s;
    int result;

    while (iss >> s)
    {
        if (s.size() == 1 && std::isdigit(s[0]))
            _stack.push(s[0] - '0');
        else if (s == "+" || s == "-" || s == "*" || s == "/")
        {
            if (_stack.size() < 2)
                throw std::runtime_error("Error: Not enough operands");
            int b = _stack.top();
            _stack.pop();
            int a = _stack.top();
            _stack.pop();
            result = applyOperator(a, b, s);
            _stack.push(result);
        }
        else
            throw std::runtime_error("Error: Invalid character");
    }
    if (_stack.size() != 1)
        throw std::runtime_error("Error: Invalid RPN expression");
        return _stack.top();
}

