#pragma once
#ifndef DELFI_FUNCTION_H
#define DELFI_FUNCTION_H

#include <functional>
#include "delfi/constants.h"

namespace Delfi
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
        Variable operator()(const Variable x) const;
        Variable Derivative(const Variable x) const;
        Variable Integral(const Variable l, const Variable r) const;
    };

} // namespace Delfi

#endif // DELFI_FUNCTION_H