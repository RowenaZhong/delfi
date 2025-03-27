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
    VecValFunction::VecValFunction(const std::vector<Function> &funcs)
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
        Vector result;
        for (size_t i = 0; i < this->_dim; ++i)
        {
            auto temp = Function([this, i](Variable x) -> Variable
                                 { return this->operator()(x)[i]; });
            result.push_back(temp.Derivative(x));
        }
        return result;
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
