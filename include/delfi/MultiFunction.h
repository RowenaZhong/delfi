#pragma once
#ifndef DELFI_MULTI_FUNCTION_H
#define DELFI_MULTI_FUNCTION_H

#include <functional>
#include "delfi/constants.h"
#include "delfi/Vector.h"
#include "delfi/Function.h"

namespace delfi
{
    class MultiFunction
    {
    private:
        std::function<Variable(const Vector)> _func;
        size_t _dim;
        void _Check_Dim(const Vector x) const;

    public:
        MultiFunction(/* args */);
        MultiFunction(std::function<Variable(const Vector)> f, size_t dim);
        ~MultiFunction();
        const size_t GetDim() const;
        // operator=
        const MultiFunction &operator=(const MultiFunction &mf);

        Variable operator()(const Vector x) const;
        Variable PartialDerivative(const Vector x, const size_t idx) const;
        Vector Gradient(const Vector x) const;
        Variable Integral(Vector begin, const size_t idx, const Variable to) const;
    };
    MultiFunction operator*(const MultiFunction mf, const Function f);
} // namespace delfi

#endif // DELFI_MULTI_FUNCTION_H