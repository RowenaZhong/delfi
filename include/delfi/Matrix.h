#pragma once
#ifndef DELFI_MATRIX_H
#define DELFI_MATRIX_H

#include "constants.h"
#include <vector>

namespace delfi
{
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
        Matrix transpose() const;
        Matrix inverse() const;
        Matrix gassJordanElimination() const;
        void SwapRow(size_t i, size_t j);
        void SwapColumn(size_t i, size_t j);
        void AddRow(size_t from, size_t to, Variable k);
        void AddColumn(size_t to, size_t from, Variable k);
        void MultiplyRow(size_t i, Variable k);
        void MultiplyColumn(size_t i, Variable k);
        Variable determinant() const;
        Variable det() const;
    };
    Matrix operator*(Variable scalar, const Matrix &matrix);
}

#endif // DELFI_MATRIX_H