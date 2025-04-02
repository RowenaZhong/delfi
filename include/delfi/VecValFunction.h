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
        class _SafeProvider
        {
        public:
            std::function<Vector(const Variable)>
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
            inline void CheckRet(const size_t idx) const
            {
                if (idx >= this->RetLen)
                    throw delfi::InvalidArgumentReporter(this->RetLen, x.size());
            }
            inline Vector operator()(const Variable x) const
            {
                this->CheckFunction();
                this->CheckArgs(x);
                auto result = this->func(x);
                this->CheckRet(result);
                return this->func(x);
            }
        } _sfunc;

    public:
        inline VecValFunction() {};
        inline VecValFunction(const std::function<Vector(const Variable)> &func, const size_t dim)
        {
            this->_sfunc.func = func;
            this->_sfunc.RetLen = dim;
        }
        VecValFunction(const VecValFunction &other) : _sfunc(other._sfunc) {}
        VecValFunction(const std::vector<Function> &funcs);
        const VecValFunction &operator=(const VecValFunction &other);
        const VecValFunction &operator=(const std::vector<Function> &funcs);
        Vector operator()(const Variable x) const;
        inline size_t GetDim() const { return _sfunc.RetLen; }
        Vector Derivative(const Variable x) const;
        Vector Integral(const Variable l, const Variable r) const;
    };
}
#endif // DELFI_VECTOR_VALUED_FUNCTION