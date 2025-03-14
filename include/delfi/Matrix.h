#pragma once
#ifndef DELFI_MATRIX_H
#define DELFI_MATRIX_H

#include "constants.h"
#include <vector>

namespace Delfi
{
    template <size_t N, size_t M>
    class Matrix
    {
    private:
        std::vector<std::vector<Variable>> _data;

    public:
        Matrix();
        Matrix(const Matrix<N, M> &other);
        Matrix<N, M> &operator=(const Matrix<N, M> &other);
        ~Matrix();

        Variable &operator()(size_t i, size_t j);
        const Variable &operator()(size_t i, size_t j) const;

        Matrix<N, M> &operator+=(const Matrix<N, M> &other);
        Matrix<N, M> &operator-=(const Matrix<N, M> &other);
        Matrix<N, M> operator+(const Matrix<N, M> &other) const;
        Matrix<N, M> operator-(const Matrix<N, M> &other) const;
    };
}

#endif // DELFI_MATRIX_H