#include "delfi/MultiFunction.h"
#include <stdexcept>

namespace delfi
{

    MultiFunction::MultiFunction()
    {
    }

    MultiFunction::MultiFunction(std::function<Variable(const Vector)> func, size_t dim)
    {
        this->_func = func;
        this->_dim = dim;
    }

    MultiFunction::~MultiFunction()
    {
    }

    const size_t MultiFunction::GetDim() const
    {
        return size_t(this->_dim);
    }
    void MultiFunction::_CheckArgDim(const Vector x) const
    {
        if (x.size() != this->_dim)
            throw std::invalid_argument("Dimension of input vector does not match the dimension of the function");
    }
    Variable MultiFunction::operator()(const Vector x) const
    {
        this->_CheckArgDim(x);
        return this->_func(x);
    }
    const MultiFunction &MultiFunction::operator=(const MultiFunction &mf)
    {
        this->_func = mf._func;
        this->_dim = mf._dim;
        return *this;
    }
    Variable MultiFunction::PartialDerivative(const Vector x, const size_t idx) const
    {
        this->_CheckArgDim(x);
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
    Vector MultiFunction::Gradient(const Vector x) const
    {
        this->_CheckArgDim(x);
        Vector grad;
        for (size_t i = 0; i < x.size(); i++)
            grad.push_back(this->PartialDerivative(x, i));
        return grad;
    }
    Variable MultiFunction::Integral(Vector begin, const size_t idx, const Variable to) const
    {
        this->_CheckArgDim(begin);
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
                             { return f(mf(x)); }, mf.GetDim());
    }

}
