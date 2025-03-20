#include "delfi/MultiFunction.h"
#include "MultiFunction.h"

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
    Variable MultiFunction::PartialDerivative(const Vector x, const size_t idx) const
    {
        Variable c_eps = eps;
        auto calc_d = [this, x, from](Variable c_eps) -> Variable
        {
            Vector l = x;
            l[idx] -= eps;
            Vector r = x;
            r[idx] += eps;
            return (this->_func(r) - this->_func(l)) / (2.0 * c_eps);
        };
    }
    Variable MultiFunction::Integral(Vector begin, const size_t idx, const Variable to) const
    {
        Function _part_function([this->_func, begin, idx](Variable x) -> Variable
                                {
            Vector X = begin;
            X[idx] = x;
            return this->_func(X); });
        return _part_function.Integral(begin[idx], to);
    }

    Function &operator*(const MultiFunction &mf, const Function &f)
    {
        return [mf, f](const Vector x) -> Variable
        {
            return f(mf(x));
        };
    }

}
