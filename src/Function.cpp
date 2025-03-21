#include "delfi/Function.h"

namespace delfi
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
    Function::Function(const Function &other)
    {
        this->_func = other._func;
    }
    Function &Function::operator=(const Function &other)
    {
        this->_func = other._func;
        return *this;
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
    Function Function::operator*(const Function other) const
    {
        return Function([f1 = this->_func, f2 = other._func](const Variable x) -> Variable
                        { return f2(f1(x)); });
    }
    Function Function::compount(const Function other) const
    {
        return Function([this, other](const Variable x) -> Variable
                        { return this->_func(other(x)); });
    }
}
