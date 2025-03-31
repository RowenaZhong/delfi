#include "delfi/VecValFunction.h"
#include <stdexcept>

namespace delfi
{
    VecValFunction::VecValFunction(const std::vector<Function> &funcs)
    {
        this->_sfunc.func = [funcs](const Variable x) -> Vector
        {
            Vector result;
            for (const auto &func : funcs)
            {
                result.push_back(func(x));
            }
            return result;
        };
        this->_sfunc.RetLen = funcs.size();
    }
    const VecValFunction &VecValFunction::operator=(const VecValFunction &other)
    {
        this->_sfunc = other._sfunc;
        return *this;
    }
    const VecValFunction &VecValFunction::operator=(const std::vector<Function> &funcs)
    {
        this->_sfunc.func = [funcs](const Variable x) -> Vector
        {
            Vector result;
            for (const auto &func : funcs)
            {
                result.push_back(func(x));
            }
            return result;
        };
        this->_sfunc.RetLen = funcs.size();
        return *this;
    }
    Vector VecValFunction::operator()(const Variable x) const
    {
        return this->_sfunc(x);
    }
    Vector VecValFunction::Derivative(const Variable x) const
    {
        Vector result;
        for (size_t i = 0; i < this->_sfunc.RetLen; ++i)
        {
            auto temp = Function([this, i](Variable x) -> Variable
                                 { return this->_sfunc(x)[i]; });
            result.push_back(temp.Derivative(x));
        }
        return result;
    }
    Vector VecValFunction::Integral(const Variable l, const Variable r) const
    {
        Vector result;
        for (size_t i = 0; i < this->_sfunc.RetLen; ++i)
        {
            auto temp = Function([this, i](Variable x) -> Variable
                                 { return this->_sfunc(x)[i]; });
            result.push_back(temp.Integral(l, r));
        }
        return result;
    }
}
