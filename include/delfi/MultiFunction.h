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

    public:
        MultiFunction(/* args */);
        MultiFunction(std::function<Variable(const Vector)> f);
        ~MultiFunction();
        // operator=
        const MultiFunction &operator=(const MultiFunction &mf);
        const MultiFunction &operator=(const std::function<Variable(const Vector)> &mf);
        Variable operator()(const Vector x) const;
        Variable PartialDerivative(const Vector x, const size_t idx) const;
        Variable Integral(Vector begin, const size_t idx, const Variable to) const;
    };
    MultiFunction operator*(const MultiFunction mf, const Function f);
} // namespace delfi

#endif // DELFI_MULTI_FUNCTION_H