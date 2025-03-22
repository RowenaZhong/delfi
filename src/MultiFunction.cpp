#include "delfi/MultiFunction.h"

namespace delfi
{

    MultiFunction::MultiFunction()
    {
    }

    MultiFunction::MultiFunction(std::function<Variable(const Vector)> func)
    {
        this->_func = func;
    }
    MultiFunction::~MultiFunction()
    {
    }

    Variable MultiFunction::operator()(const Vector x) const
    {
        return this->_func(x);
    }
    const MultiFunction &MultiFunction::operator=(const MultiFunction &mf)
    {
        this->_func = mf._func;
        return *this;
    }
    const MultiFunction &MultiFunction::operator=(const std::function<Variable(const Vector)> &mf)
    {
        this->_func = mf;
        return *this;
    }
    Variable MultiFunction::PartialDerivative(const Vector x, const size_t idx) const
    {
        Variable c_eps = eps;
        auto calc_d = [this, x, idx](Variable c_eps) -> Variable
        {
            Vector l = x;
            l[idx] -= c_eps;
            Vector r = x;
            r[idx] += c_eps;
            return (this->_func(r) - this->_func(l)) / (2.0 * c_eps);
        };
        while (abs(calc_d(c_eps) - calc_d(c_eps / 2.0)) > eps)
            c_eps /= 2;
        return calc_d(c_eps);
    }
    Variable MultiFunction::Integral(Vector begin, const size_t idx, const Variable to) const
    {
        Function _part_function([this, begin, idx](Variable x) -> Variable
                                {
            Vector X = begin;
            X[idx] = x;
            return this->_func(X); });
        return _part_function.Integral(begin[idx], to);
    }

    MultiFunction operator*(const MultiFunction mf, const Function f)
    {
        return MultiFunction([mf, f](const Vector x) -> Variable
                             { return f(mf(x)); });
    }

}
