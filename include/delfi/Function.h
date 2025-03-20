#pragma once
#ifndef DELFI_FUNCTION_H
#define DELFI_FUNCTION_H

#include <functional>
#include "delfi/constants.h"

namespace delfi
{
    class Function
    {
    private:
        std::function<Variable(const Variable)> _func;
        Variable _part_integral(const Variable l, const Variable r) const;

    public:
        Function(/* args */);
        Function(std::function<Variable(const Variable)> f);
        ~Function();
        Function(const Function &other);
        Function &operator=(const Function &other);
        Variable operator()(const Variable x) const;
        Variable Derivative(const Variable x) const;
        Variable Integral(const Variable l, const Variable r) const;
        Function operator*(const Function other) const;
        Function compount(const Function other) const;
    };

} // namespace delfi

#endif // DELFI_FUNCTION_H