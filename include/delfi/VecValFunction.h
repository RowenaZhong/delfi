#pragma once
#ifndef DELFI_VECTOR_VALUED_FUNCTION
#include "delfi/Vector.h"
#include "delfi/Function.h"
#include <functional>
namespace delfi
{

    class VecValFunction
    {
    private:
        std::function<Vector(const Variable)> _func;

    public:
        inline VecValFunction() {};
        VecValFunction(const std::function<Vector(const Variable)> &func) : _func(func) {}
        VecValFunction(const VecValFunction &other) : _func(other._func) {}
        const VecValFunction &operator=(const VecValFunction &other);
        const VecValFunction &operator=(const std::function<Vector(const Variable)> &func);
        const VecValFunction &operator=(const std::vector<Function> &funcs);
        Vector operator()(const Variable x) const;
    };
}
#endif // DELFI_VECTOR_VALUED_FUNCTION