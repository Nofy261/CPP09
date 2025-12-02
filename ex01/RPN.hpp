
#pragma once
#include <stack>

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