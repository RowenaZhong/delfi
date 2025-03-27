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
        std::function<Vector(const Vector)> _func;
        size_t _dim1, _dim2;

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
    };
} // namespace delfi {

#endif // DELFI_FIELD_H