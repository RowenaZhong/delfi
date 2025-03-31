#pragma once
#ifndef DELFI_FIELD_H
#define DELFI_FIELD_H

#include "Function.h"
#include "MultiFunction.h"
#include <functional>
namespace delfi
{
    class Field
    {
    private:
        class _SafeProvider
        {
        public:
            std::function<Vector(const Vector)>
                func;
            size_t ArgLen;
            size_t RetLen;

        private:
            inline void CheckArgs(const Variable x) const {};
            inline void CheckRet(const Variable x) const {};
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

        public:
            inline Vector operator()(const Vector x) const
            {
                this->CheckFunction();
                this->CheckArgs(x);
                auto result = this->func(x);
                this->CheckRet(result);
                return this->func(x);
            }
        } _sfunc;

    public:
        Field() = default;
        Field(const std::function<Vector(const Vector)> &func, const size_t d1, const size_t d2);
        Field(const std::vector<MultiFunction> &mfs);
        Field(const Field &other);
        const Field &operator=(const Field &other);
        const Field &operator=(std::vector<MultiFunction> &mfs);
        Vector operator()(const Vector &x) const;
        size_t getDim1() const;
        size_t getDim2() const;
        Variable Derivative(const Vector x, const size_t i, const size_t j); // 偏导数 partial derivative
        Variable Divergence(const Vector x);                                 // 散度 divergence
    };
} // namespace delfi {

#endif // DELFI_FIELD_H