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

        public:
            inline void CheckArgs(const Vector x) const
            {
                if (x.size() != this->ArgLen)
                    throw "wrong number of arguments"; // TODO rewrite
            }
            inline void CheckRet(const Vector x) const
            {
                if (x.size() != this->RetLen)
                    throw "wrong number of return values"; // TODO rewrite
            }
            inline void CheckFunction() const
            {
                if (this->func == nullptr)
                    throw "function do not exist"; // TODO rewrite
            }
            inline void CheckArgs(const size_t idx) const
            {
                if (idx >= this->ArgLen)
                    throw "wrong number of arguments"; // TODO rewrite
            }
            inline void CheckRet(const size_t idx) const
            {
                if (idx >= this->RetLen)
                    throw "wrong number of return values"; // TODO rewrite
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