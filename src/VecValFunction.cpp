#include "delfi/VecValFunction.h"
#include <stdexcept>

namespace delfi
{
    void VecValFunction::_CheckResultDim(const Vector &result) const
    {
        if (result.size() != this->_dim)
        {
            throw std::runtime_error("Dimension of result does not match dimension of function");
        }
    }
    const VecValFunction &VecValFunction::operator=(const VecValFunction &other)
    {
        this->_func = other._func;
        this->_dim = other._dim;
        return *this;
    }
    const VecValFunction &VecValFunction::operator=(const std::vector<Function> &funcs)
    {
        this->_func = [funcs](const Variable x) -> Vector
        {
            Vector result;
            for (const auto &func : funcs)
            {
                result.push_back(func(x));
            }
            return result;
        };
        this->_dim = funcs.size();
        return *this;
    }
    Vector VecValFunction::operator()(const Variable x) const
    {
        if (this->_func == nullptr)
        {
            throw std::runtime_error("VecValFunction not initialized");
        }
        Vector result = this->_func(x);
        this->_CheckResultDim(result);
        return result;
    }
    Vector VecValFunction::Derivative(const Variable x) const
    {
        Variable dx = eps;
        auto calc_d = [this, x](Variable c_eps) -> Vector
        {
            return (this->operator()(x + c_eps) - this->operator()(x - c_eps)) / (2 * c_eps);
        };
        auto calc_loss = [](Vector a, Vector b) -> Variable
        {
            Variable loss = 0;
            for (size_t i = 0; i < a.size(); ++i)
                loss = std::max(loss, std::abs(a[i] - b[i]));
            return loss;
        };
        while (calc_loss(calc_d(dx), calc_d(dx / 2)) > eps)
            dx /= 2;
        return calc_d(dx);
    }
    Vector VecValFunction::Integral(const Variable l, const Variable r) const
    {
        Vector result;
        for (size_t i = 0; i < this->_dim; ++i)
        {
            auto temp = Function([this, i](Variable x) -> Variable
                                 { return this->operator()(x)[i]; });
            result.push_back(temp.Integral(l, r));
        }
        return result;
    }
}
