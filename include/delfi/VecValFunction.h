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
        size_t _dim;
        void _CheckResultDim(const Vector &result) const;

    public:
        inline VecValFunction() {};
        VecValFunction(const std::function<Vector(const Variable)> &func, const size_t dim) : _func(func), _dim(dim) {}
        VecValFunction(const VecValFunction &other) : _func(other._func), _dim(other._dim) {}
        VecValFunction(const std::vector<Function> &funcs);
        const VecValFunction &operator=(const VecValFunction &other);
        const VecValFunction &operator=(const std::vector<Function> &funcs);
        Vector operator()(const Variable x) const;
        inline size_t GetDim() const { return _dim; }
        Vector Derivative(const Variable x) const;
        Vector Integral(const Variable l, const Variable r) const;
    };
}
#endif // DELFI_VECTOR_VALUED_FUNCTION