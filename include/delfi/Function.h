#pragma once
#ifndef DELFI_FUNCTION_H
#define DELFI_FUNCTION_H

#include <functional>
#include "delfi/reporter.h"
#include "delfi/constants.h"
#include "delfi/Vector.h"

namespace delfi
{
    class Function
    {
    private:
        class _SafeProvider
        {
        public:
            std::function<Variable(const Variable)>
                func;
            size_t ArgLen;
            size_t RetLen;

        private:
            inline void CheckArgs(const Variable x) const {};
            inline void CheckRet(const Variable x) const {};
            inline void CheckArgs(const Vector x) const
            {
                if (x.size() != this->ArgLen)
                    throw delfi::InvalidArgumentReporter(this->ArgLen, x.size());
            }
            inline void CheckRet(const Vector x) const
            {
                if (x.size() != this->RetLen)
                    throw delfi::InvalidArgumentReporter("in return value, expected for " + std::to_string(this->ArgLen) + ", but " + std::to_string(x.size()));
            }
            inline void CheckFunction() const
            {
                if (this->func == nullptr)
                    throw delfi::FunctionUndefinedReporter();
            }
            inline void CheckArgs(const size_t idx) const
            {
                if (idx >= this->ArgLen)
                    throw delfi::InvalidArgumentReporter(this->ArgLen, x.size());
            }
            inline void CheckRet(const size_t idx) const
            {
                if (idx >= this->RetLen)
                    throw delfi::InvalidArgumentReporter(this->RetLen, x.size());
            }

        public:
            inline Variable operator()(const Variable x) const
            {
                this->CheckFunction();
                this->CheckArgs(x);
                auto result = this->func(x);
                this->CheckRet(result);
                return this->func(x);
            }
        } _sfunc;
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
    };

} // namespace delfi

#endif // DELFI_FUNCTION_H