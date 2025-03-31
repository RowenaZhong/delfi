#include "delfi/MultiFunction.h"
#include <stdexcept>

namespace delfi
{

    MultiFunction::MultiFunction()
    {
    }

    MultiFunction::MultiFunction(std::function<Variable(const Vector)> func, const size_t dim)
    {
        this->_sfunc.func = func;
        this->_sfunc.ArgLen = dim;
    }

    MultiFunction::~MultiFunction()
    {
    }

    const size_t MultiFunction::GetDim() const
    {
        return size_t(this->_sfunc.ArgLen);
    }
    Variable MultiFunction::operator()(const Vector x) const
    {
        return this->_sfunc(x);
    }
    const MultiFunction &MultiFunction::operator=(const MultiFunction &mf)
    {
        this->_sfunc = mf._sfunc;
        return *this;
    }
    Variable MultiFunction::Derivative(const Vector x, const size_t idx) const
    {
        this->_sfunc.CheckArgs(x);
        this->_sfunc.CheckArgs(idx);
        Variable c_eps = eps;
        auto calc_d = [this, x, idx](Variable c_eps) -> Variable
        {
            Vector l = x;
            l[idx] -= c_eps;
            Vector r = x;
            r[idx] += c_eps;
            return (this->_sfunc(r) - this->_sfunc(l)) / (2.0 * c_eps);
        };
        while (abs(calc_d(c_eps) - calc_d(c_eps / 2.0)) > eps)
            c_eps /= 2;
        return calc_d(c_eps);
    }
    Vector MultiFunction::Gradient(const Vector x) const
    {
        this->_sfunc.CheckArgs(x);
        Vector grad;
        for (size_t i = 0; i < x.size(); i++)
            grad.push_back(this->Derivative(x, i));
        return grad;
    }
    Variable MultiFunction::Integral(Vector begin, const size_t idx, const Variable to) const
    {
        this->_sfunc.CheckArgs(begin);
        this->_sfunc.CheckArgs(idx);
        Function _part_function([this, begin, idx](Variable x) -> Variable
                                {
            Vector X = begin;
            X[idx] = x;
            return this->_sfunc(X); });
        return _part_function.Integral(begin[idx], to);
    }

}
