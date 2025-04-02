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
        class _SafeProvider
        {
        public:
            std::function<Variable(const Vector)>
                func;
            size_t ArgLen;
            size_t RetLen;

        private:
            inline void CheckArgs(const Variable x) const {};
            inline void CheckRet(const Variable x) const {};
            inline void CheckRet(const Vector x) const
            {
                if (x.size() != this->RetLen)
                    throw delfi::InvalidArgumentReporter("in return value, expected for " + std::to_string(this->ArgLen) + ", but " + std::to_string(x.size()));
            }
            inline void CheckRet(const size_t idx) const
            {
                if (idx >= this->RetLen)
                    throw delfi::InvalidArgumentReporter(this->RetLen, x.size());
            }

            inline void CheckArgs(const Vector x) const
            {
                if (x.size() != this->ArgLen)
                    throw delfi::InvalidArgumentReporter(this->ArgLen, x.size());
            }
            inline void CheckFunction() const
            {
                if (this->func == nullptr)
                    throw delfi::FunctionUndefinedReporter();
            }

        public:
            inline void CheckArgs(const size_t idx) const
            {
                if (idx >= this->ArgLen)
                    throw delfi::InvalidArgumentReporter(this->ArgLen, x.size());
            }

            inline Variable operator()(const Vector x) const
            {
                this->CheckFunction();
                this->CheckArgs(x);
                auto result = this->func(x);
                this->CheckRet(result);
                return this->func(x);
            }
        } _sfunc;
        void _CheckArgDim(const Vector x) const;

    public:
        MultiFunction(/* args */);
        MultiFunction(std::function<Variable(const Vector)> f, const size_t dim);
        MultiFunction(const MultiFunction &mf) : _sfunc(mf._sfunc) {};
        ~MultiFunction();
        const size_t GetDim() const;
        // operator=
        const MultiFunction &operator=(const MultiFunction &mf);

        Variable operator()(const Vector x) const;
        Variable Derivative(const Vector x, const size_t idx) const;
        Vector Gradient(const Vector x) const;
        Variable Integral(Vector begin, const size_t idx, const Variable to) const;
    };
} // namespace delfi

#endif // DELFI_MULTI_FUNCTION_H