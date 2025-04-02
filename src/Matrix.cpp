#include "delfi/Matrix.h"
#include "delfi/reporter.h"
#include <vector>
#include <algorithm>

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
            throw delfi::InvalidArgumentReporter("Index out of range");
        return this->_data[row][col];
    }

    Variable Matrix::operator()(size_t row, size_t col) const
    {
        if (row >= this->_rows && col >= this->_cols)
            throw delfi::InvalidArgumentReporter("Index out of range");
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
            throw delfi::InvalidArgumentReporter("Matrix dimensions do not match");
        for (size_t i = 0; i < this->_rows; i++)
            for (size_t j = 0; j < this->_cols; j++)
                this->_data[i][j] += other._data[i][j];
        return *this;
    }
    Matrix &Matrix::operator-=(const Matrix &other)
    {
        if (this->_rows != other._rows || this->_cols != other._cols)
            throw delfi::InvalidArgumentReporter("Matrix dimensions do not match");
        for (size_t i = 0; i < this->_rows; i++)
            for (size_t j = 0; j < this->_cols; j++)
                this->_data[i][j] -= other._data[i][j];
        return *this;
    }
    Matrix &Matrix::operator*=(const Matrix &other)
    {
        if (this->_cols != other._rows)
            throw delfi::InvalidArgumentReporter("Matrix dimensions do not match");
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

    bool Matrix::operator==(const Matrix &other) const
    {
        if (this->_rows != other._rows || this->_cols != other._cols)
            return false;
        for (size_t i = 0; i < this->_rows; i++)
            for (size_t j = 0; j < this->_cols; j++)
                if (this->_data[i][j] != other._data[i][j])
                    return false;
        return true;
    }
    Matrix Matrix::transpose() const
    {
        Matrix temp(this->_cols, this->_rows);
        for (size_t i = 0; i < this->_rows; i++)
            for (size_t j = 0; j < this->_cols; j++)
                temp(j, i) = this->_data[i][j];
        return temp;
    }
    Matrix Matrix::inverse() const
    {
        if (this->_rows != this->_cols)
            throw delfi::InvalidArgumentReporter("Matrix must be square to have an inverse");
        if (this->determinant() == 0)
            throw delfi::InvalidArgumentReporter("Matrix is not invertible");
        Matrix temp(this->_rows, this->_rows * 2);
        for (size_t i = 0; i < this->_rows; i++)
            for (size_t j = 0; j < this->_rows; j++)
                temp(i, j) = this->_data[i][j];
        for (size_t i = 0; i < this->_rows; i++)
            temp(i, i + this->_rows) = 1;
        temp = temp.gassJordanElimination();
        Matrix ret(this->_rows, this->_cols);

        for (size_t i = 0; i < this->_rows; i++)
            for (size_t j = 0; j < this->_rows; j++)
                ret(i, j) = temp(i, j + this->_rows);
        return Matrix(ret);
    }
    size_t Matrix::rank() const
    {
        auto temp = this->gassJordanElimination();
        size_t r = 0;
        for (auto &row : temp._data)
            if (std::any_of(row.begin(), row.end(), [](const Variable &v)
                            { return std::abs(v) > delfi::eps; }))
                r++;
        return r;
    }
    Variable Matrix::trace() const
    {
        Variable ans = 0;
        for (size_t i = 0; i < this->_rows; i++)
            ans += this->_data[i][i];
        return ans;
    }
    Matrix Matrix::gassJordanElimination() const
    {
        if (this->_rows > this->_cols)
            throw delfi::InvalidArgumentReporter("Gass Jordan elimination is only possible for square matrices or matrices with more rows than columns");
        Matrix temp(*this);
        size_t r = 0, c = 0;
        while (r < temp._rows && c < temp._cols)
        {
            auto t = r;
            for (auto i = r + 1; i < temp._rows; i++)
                if (std::abs(temp(i, c)) > std::abs(temp(t, c)))
                    t = i;
            if (std::abs(temp(t, c)) < delfi::eps)
            {
                c++;
                continue;
            }
            if (t != r)
                temp.SwapRow(r, t);
            temp.MultiplyRow(r, 1 / temp(r, c));
            for (auto i = 0; i < temp._rows; i++)
                if (i != r && std::abs(temp(i, c)) > delfi::eps)
                    temp.AddRow(i, r, -temp(i, c));
            r++, c++;
        }
        return temp;
    }
    Variable Matrix::determinant() const
    {
        if (this->_rows != this->_cols)
            throw delfi::InvalidArgumentReporter("Matrix must be square to have an determinant");
        Matrix temp(*this);
        size_t r = 0, c = 0;
        Variable ans = 1;
        while (r < temp._rows && c < temp._cols)
        {
            auto t = r;
            for (auto i = r + 1; i < temp._rows; i++)
                if (std::abs(temp(i, c)) > std::abs(temp(t, c)))
                    t = i;
            if (std::abs(temp(t, c)) < delfi::eps)
                return 0;
            if (t != r)
                temp.SwapRow(r, t), ans *= -1;
            ans *= temp(r, c);
            temp.MultiplyRow(r, 1 / temp(r, c));
            for (auto i = 0; i < temp._rows; i++)
                if (i != r && std::abs(temp(i, c)) > delfi::eps)
                    temp.AddRow(i, r, -temp(i, c));
            r++, c++;
        }
        return ans;
    }
    Variable Matrix::det() const
    {
        return this->determinant();
    }
    void Matrix::SwapRow(size_t i, size_t j)
    {
        if (i >= this->_rows || j >= this->_rows)
            throw delfi::InvalidArgumentReporter("Invalid row index");
        std::swap(this->_data[i], this->_data[j]);
    }
    void Matrix::SwapColumn(size_t i, size_t j)
    {
        if (i >= this->_cols || j >= this->_cols)
            throw delfi::InvalidArgumentReporter("Invalid column index");
        for (auto &row : this->_data)
            std::swap(row[i], row[j]);
    }

    void Matrix::AddRow(size_t to, size_t from, Variable k)
    {
        if (from >= this->_rows || to >= this->_rows)
            throw delfi::InvalidArgumentReporter("Invalid row index");
        for (size_t i = 0; i < this->_cols; i++)
            this->_data[to][i] += k * this->_data[from][i];
    }

    void Matrix::AddColumn(size_t from, size_t to, Variable k)
    {
        if (from >= this->_cols || to >= this->_cols)
            throw delfi::InvalidArgumentReporter("Invalid column index");
        for (auto &row : this->_data)
            row[to] += k * row[from];
    }
    void Matrix::MultiplyRow(size_t i, Variable k)
    {
        if (i >= this->_rows)
            throw delfi::InvalidArgumentReporter("Invalid row index");
        for (auto &col : this->_data[i])
            col *= k;
    }
    void Matrix::MultiplyColumn(size_t i, Variable k)
    {
        if (i >= this->_cols)
            throw delfi::InvalidArgumentReporter("Invalid column index");
        for (auto &row : this->_data)
            row[i] *= k;
    }
    Matrix operator*(Variable scalar, const Matrix &matrix)
    {
        return matrix * scalar;
    }
}
