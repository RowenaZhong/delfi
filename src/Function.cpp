#include "delfi/Function.h"

namespace Delfi
{
    Function::Function()
    {
    }

    Function::Function(std::function<Variable(const Variable)> func)
    {
        this->_func = func;
    }
    Function::~Function()
    {
    }

    Variable Function::operator()(const Variable x) const
    {
        return this->_func(x);
    }

    Variable Function::Derivative(const Variable x) const
    {
        Variable c_eps = eps;
        auto calc_d = [this, x](Variable c_eps) -> Variable
        {
            return (this->_func(x + c_eps) - this->_func(x - c_eps)) / (2 * c_eps);
        };
        while (abs(calc_d(c_eps) - calc_d(c_eps / 2)) > eps)
            c_eps /= 2;
        return calc_d(c_eps);
    }
    Variable Function::_part_integral(const Variable l, const Variable r) const
    {
        auto calc_approximate_integral = [this](const Variable l, const Variable r) -> Variable
        {
            return (this->_func(l) + 4 * this->_func((l + r) / 2) + this->_func(r)) * (r - l) / 6;
        };
        auto mid = (l + r) / 2;
        auto ans = calc_approximate_integral(l, r);
        if (abs(ans - calc_approximate_integral(l, mid) - calc_approximate_integral(mid, r)) > eps)
            return this->_part_integral(l, mid) + this->_part_integral(mid, r);
        return ans;
    }
    Variable Function::Integral(const Variable l, const Variable r) const
    {
        return this->_part_integral(l, r);
    }
}
