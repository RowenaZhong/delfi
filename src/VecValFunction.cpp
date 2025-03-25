#include "delfi/VecValFunction.h"

namespace delfi
{
    const VecValFunction &VecValFunction::operator=(const VecValFunction &other)
    {
        this->_func = other._func;
        return *this;
    }
    const VecValFunction &VecValFunction::operator=(const std::function<Vector(const Variable)> &func)
    {
        this->_func = func;
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
        return *this;
    }
    Vector delfi::VecValFunction::operator()(const Variable x) const
    {
        return Vector();
    }
}
