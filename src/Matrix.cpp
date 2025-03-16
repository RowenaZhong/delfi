#include "delfi/Matrix.h"
#include <vector>
#include <stdexcept>
namespace delfi
{
    Matrix::Matrix()
    {
        this->_rows = 0;
        this->_cols = 0;
    }
    Matrix::Matrix(const Matrix &other)
    {
        this->_rows = other._rows;
        this->_cols = other._cols;
        this->_data = other._data;
    }
    Matrix::Matrix(size_t rows, size_t cols)
    {
        this->_rows = rows;
        this->_cols = cols;
        this->_data = std::vector<std::vector<Variable>>(rows, std::vector<Variable>(cols, 0.0));
    }
    Matrix &Matrix::resize(size_t rows, size_t cols)
    {
        this->_rows = rows;
        this->_cols = cols;
        this->_data = std::vector<std::vector<Variable>>(rows, std::vector<Variable>(cols, 0.0));
        this->_data.resize(rows);
        for (auto &row : this->_data)
            row.resize(cols);
        return *this;
    }
    size_t Matrix::rows() const
    {
        return size_t(this->_rows);
    }
    size_t Matrix::cols() const
    {
        return size_t(this->_cols);
    }
    Variable &Matrix::operator()(size_t row, size_t col)
    {
        if (row >= this->_rows && col >= this->_cols)
            throw std::out_of_range("Index out of range");
        return this->_data[row][col];
    }
    Variable Matrix::operator()(size_t row, size_t col) const
    {
        if (row >= this->_rows && col >= this->_cols)
            throw std::out_of_range("Index out of range");
        return this->_data[row][col];
    }
    Matrix &Matrix::operator=(const Matrix &other)
    {
        this->_rows = other._rows;
        this->_cols = other._cols;
        this->_data = other._data;
        return *this;
    }
    Matrix &Matrix::operator+=(const Matrix &other)
    {
        if (this->_rows != other._rows || this->_cols != other._cols)
            throw std::invalid_argument("Matrix dimensions do not match");
        for (size_t i = 0; i < this->_rows; i++)
            for (size_t j = 0; j < this->_cols; j++)
                this->_data[i][j] += other._data[i][j];
        return *this;
    }
    Matrix &Matrix::operator-=(const Matrix &other)
    {
        if (this->_rows != other._rows || this->_cols != other._cols)
            throw std::invalid_argument("Matrix dimensions do not match");
        for (size_t i = 0; i < this->_rows; i++)
            for (size_t j = 0; j < this->_cols; j++)
                this->_data[i][j] -= other._data[i][j];
        return *this;
    }
    Matrix &Matrix::operator*=(const Matrix &other)
    {
        if (this->_cols != other._rows)
            throw std::invalid_argument("Matrix dimensions do not match");
        Matrix temp(*this);
        this->resize(this->_rows, other._cols);
        for (auto &row : this->_data)
            row.resize(other._cols, 0.0);
        for (size_t i = 0; i < this->_rows; i++)
            for (size_t j = 0; j < other._cols; j++)
                for (size_t k = 0; k < this->_cols; k++)
                    this->_data[i][j] += temp._data[i][k] * other._data[k][j];
        return *this;
    }

    Matrix Matrix::operator+(const Matrix &other) const
    {
        Matrix temp(*this);
        temp += other;
        return temp;
    }
    Matrix Matrix::operator-(const Matrix &other) const
    {
        Matrix temp(*this);
        temp -= other;
        return temp;
    }
    Matrix Matrix::operator*(const Matrix &other) const
    {
        Matrix temp(*this);
        temp *= other;
        return temp;
    }
    Matrix Matrix::operator*(const Variable scalar) const
    {
        Matrix temp(*this);
        for (auto &row : temp._data)
            for (auto &col : row)
                col *= scalar;
        return temp;
    }
    Matrix Matrix::operator/(const Variable scalar) const
    {
        Matrix temp(*this);
        for (auto &row : temp._data)
            for (auto &col : row)
                col /= scalar;
        return temp;
    }

    Matrix Matrix::transpose()
    {
        Matrix temp(*this);
        this->resize(this->_cols, this->_rows);
        for (size_t i = 0; i < this->_rows; i++)
            for (size_t j = 0; j < this->_cols; j++)
                this->_data[i][j] = temp(j, i);

        return *this;
    }
    Matrix Matrix::inverse()
    {
        if (this->_rows != this->_cols)
            throw std::invalid_argument("Matrix is not square");
        // Check Determinant
        Matrix temp(this->_rows, this->_rows * 2);
        for (size_t i = 0; i < this->_rows; i++)
            for (size_t j = 0; j < this->_rows; j++)
                temp(i, j) = this->_data[i][j];
        for (size_t i = 0; i < this->_rows; i++)
            temp(i, i + this->_rows) = 1;
        temp.gassJordanElimination();
        for (size_t i = 0; i < this->_rows; i++)
            for (size_t j = 0; j < this->_rows; j++)
                this->_data[i][j] = temp(i, j + this->_rows);
        return Matrix(*this);
    }
    Matrix Matrix::gassJordanElimination()
    {
        if (this->_rows > this->_cols)
            throw std::invalid_argument("Gass Jordan elimination is only possible for square matrices or matrices with more rows than columns");
        size_t r = 0, c = 0;
        while (r < this->_rows && c < this->_cols)
        {
            int t = r;
            for (int i = r; i < this->_rows; i++)
                if (abs(this->_data[i][c]) > abs(this->_data[t][c]))
                    t = i;
            if (this->_data[t][c] == 0)
            {
                c++;
                continue;
            }
            if (t != r)
                std::swap(this->_data[r], this->_data[t]);
            for (int i = 0; i < this->_cols; i++)
                if (i != c)
                    this->_data[r][i] /= this->_data[r][c];
            this->_data[r][c] = 1;
            for (int i = 0; i < this->_rows; i++)
                if (i != r)
                {
                    for (int j = 0; j < this->_cols; j++)
                        if (j != c)
                            this->_data[i][j] -= this->_data[i][c] * this->_data[r][j];
                    this->_data[i][c] = 0;
                }
            r++, c++;
        }
        return *this;
    }
    Matrix operator*(Variable scalar, const Matrix &matrix)
    {
        return matrix * scalar;
    }
}
