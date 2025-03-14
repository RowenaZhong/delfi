#include "delfi/Matrix.h"
#include <vector>
namespace Delfi
{

    template <size_t N, size_t M>
    Matrix<N, M>::Matrix()
    {
        this->_data = std::vector<std::vector<Variable>>(N, std::vector<Variable>(M));
    }
    template <size_t N, size_t M>
    Matrix<N, M>::Matrix(const Matrix<N, M> &other)
    {
        this->_data = other._data;
    }

    // operator =
    template <size_t N, size_t M>
    Matrix<N, M> &Matrix<N, M>::operator=(const Matrix<N, M> &other)
    {
        this->_data = other._data;
        return *this;
    }

    template <size_t N, size_t M>
    Matrix<N, M>::~Matrix()
    {
    }

    template <size_t N, size_t M>
    Variable &Matrix<N, M>::operator()(size_t i, size_t j)
    {
        return this->_data[i][j];
    }

    template <size_t N, size_t M>
    const Variable &Matrix<N, M>::operator()(size_t i, size_t j) const
    {
        return this->_data[i][j];
    }

    template <size_t N, size_t M>
    Matrix<N, M> &Matrix<N, M>::operator+=(const Matrix<N, M> &other)
    {
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < M; j++)
                this->_data[i][j] += other._data[i][j];
        return *this;
    }

    template <size_t N, size_t M>
    Matrix<N, M> &Matrix<N, M>::operator-=(const Matrix<N, M> &other)
    {
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < M; j++)
                this->_data[i][j] -= other._data[i][j];
        return *this;
    }
    template <size_t N, size_t M>
    Matrix<N, M> Matrix<N, M>::operator+(const Matrix<N, M> &other) const
    {
        Matrix<N, M> result(*this);
        result += other;
        return result;
    }
    template <size_t N, size_t M>
    Matrix<N, M> Matrix<N, M>::operator-(const Matrix<N, M> &other) const
    {
        Matrix<N, M> result(*this);
        result -= other;
        return result;
    }
}