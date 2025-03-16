#pragma once
#ifndef DELFI_MATRIX_H
#define DELFI_MATRIX_H

#include "constants.h"
#include <vector>

namespace delfi
{
    // FIXME No fixed dimension matrices
    class Matrix
    {
    private:
        std::vector<std::vector<Variable>> _data;
        size_t _rows, _cols;

    public:
        Matrix();
        Matrix(const Matrix &other);
        Matrix(size_t rows, size_t cols);
        Matrix &resize(size_t rows, size_t cols);
        size_t rows() const;
        size_t cols() const;
        Variable operator()(size_t row, size_t col) const;
        Variable &operator()(size_t row, size_t col);
        Matrix &operator=(const Matrix &other);
        Matrix &operator+=(const Matrix &other);
        Matrix &operator-=(const Matrix &other);
        Matrix &operator*=(const Matrix &other);
        Matrix operator+(const Matrix &other) const;
        Matrix operator-(const Matrix &other) const;
        Matrix operator*(const Matrix &other) const;
        Matrix operator*(const Variable scalar) const;
        Matrix operator/(const Variable scalar) const;
        Matrix transpose();
        Matrix inverse();
        Matrix gassJordanElimination();
    };
    Matrix operator*(Variable scalar, const Matrix &matrix);
}

#endif // DELFI_MATRIX_H