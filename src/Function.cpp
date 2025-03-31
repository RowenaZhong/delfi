#include "delfi/Function.h"

namespace delfi
{
    Function::Function()
    {
    }

    Function::Function(std::function<Variable(const Variable)> func)
    {
        this->_sfunc.func = func;
    }
    Function::~Function()
    {
    }
    Function::Function(const Function &other)
    {
        this->_sfunc = other._sfunc;
    }
    Function &Function::operator=(const Function &other)
    {
        this->_sfunc = other._sfunc;
        return *this;
    }

    Variable Function::operator()(const Variable x) const
    {
        return this->_sfunc(x);
    }

    Variable Function::Derivative(const Variable x) const
    {
        Variable dx = eps;
        auto calc_d = [this, x](Variable dx) -> Variable
        {
            return (this->_sfunc(x + dx) - this->_sfunc(x - dx)) / (2 * dx);
        };
        while (abs(calc_d(dx) - calc_d(dx / 2)) > eps)
            dx /= 2;
        return calc_d(dx);
    }
    Variable Function::_part_integral(const Variable l, const Variable r) const
    {
        auto calc_approximate_integral = [this](const Variable l, const Variable r) -> Variable
        {
            return (this->_sfunc(l) + 4 * this->_sfunc((l + r) / 2) + this->_sfunc(r)) * (r - l) / 6;
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
