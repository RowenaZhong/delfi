#include "delfi/Vector.h"
#include <stdexcept>
namespace delfi
{
    Vector::Vector()
    {
        _data = std::vector<Variable>();
        _orientation = Orientation::ROW;
    }

    Vector::Vector(size_t size, Vector::Orientation orientation)
    {
        _data = std::vector<Variable>(size);
        _orientation = orientation;
    }

    Vector::Vector(const Vector &other)
    {
        _data = other._data;
        _orientation = other._orientation;
    }
    Vector::Vector(const Matrix &other)
    {
        if (other.rows() == 1)
        {
            this->_data = std::vector<Variable>(other.cols());
            this->_orientation = Orientation::COL;
            for (size_t i = 0; i < other.cols(); i++)
                this->_data[i] = other(0, i);
        }
        else if (other.cols() == 1)
        {
            this->_data = std::vector<Variable>(other.rows());
            this->_orientation = Orientation::ROW;
            for (size_t i = 0; i < other.rows(); i++)
                this->_data[i] = other(i, 0);
        }
        else
        {
            throw std::invalid_argument("Matrix must be a row or column vector");
        }
    }

    Vector::Vector(const std::vector<double> &other, Orientation orientation)
    {
        this->_data = std::vector<Variable>(other.begin(), other.end());
        this->_orientation = orientation;
    }

    Vector::Vector(const std::vector<Variable> &other, Orientation orientation)
    {
        this->_data = other;
        this->_orientation = orientation;
    }

    Vector::~Vector()
    {
    }

    Vector &Vector::operator=(const Vector &other)
    {
        this->_data = other._data;
        this->_orientation = other._orientation;
        return *this;
    }

    Vector &Vector::operator=(const Matrix &other)
    {
        if (other.rows() == 1)
        {
            this->_data = std::vector<Variable>(other.cols());
            this->_orientation = Orientation::COL;
            for (size_t i = 0; i < other.cols(); i++)
                this->_data[i] = other(0, i);
        }
        else if (other.cols() == 1)
        {
            this->_data = std::vector<Variable>(other.rows());
            this->_orientation = Orientation::ROW;
            for (size_t i = 0; i < other.rows(); i++)
                this->_data[i] = other(i, 0);
        }
        else
        {
            throw std::invalid_argument("Matrix must be a row or column vector");
        }
        return *this;
    }

    Vector &Vector::operator=(const std::vector<double> &other)
    {
        this->_data = std::vector<Variable>(other.begin(), other.end());
        return *this;
    }

    Vector &Vector::operator=(const std::vector<Variable> &other)
    {
        this->_data = other;
        return *this;
    }

    Vector &Vector::operator+=(const Vector &other)
    {
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must be of the same size");
        }
        for (size_t i = 0; i < this->size(); i++)
        {
            this->_data[i] += other[i];
        }
        return *this;
    }
    Vector &Vector::operator-=(const Vector &other)
    {
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must be of the same size");
        }
        for (size_t i = 0; i < this->size(); i++)
        {
            this->_data[i] -= other[i];
        }
        return *this;
    }

    Vector Vector::operator-(const Vector &other) const
    {
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must be of the same size");
        }
        Vector result(this->size(), this->_orientation);
        for (size_t i = 0; i < this->size(); i++)
        {
            result[i] = this->_data[i] - other[i];
        }
        return result;
    }
    Vector Vector::operator+(const Vector &other) const
    {
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must be of the same size");
        }
        Vector result(this->size(), this->_orientation);
        for (size_t i = 0; i < this->size(); i++)
        {
            result[i] = this->_data[i] + other[i];
        }
        return result;
    }
    Variable Vector::operator*(const Vector &other) const
    {
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must be of the same size");
        }
        Variable result = 0;
        for (size_t i = 0; i < this->size(); i++)
        {
            result += this->_data[i] * other[i];
        }
        return result;
    }

    Variable Vector::dot(const Vector &other) const
    {
        return *this * other;
    }
    Vector Vector::cross(const Vector &other) const
    {
        if (this->size() != 3 || other.size() != 3)
        {
            throw std::invalid_argument("Vectors must be of size 3");
        }
        Vector result(3, this->_orientation);
        result[0] = this->_data[1] * other[2] - this->_data[2] * other[1];
        result[1] = this->_data[2] * other[0] - this->_data[0] * other[2];
        result[2] = this->_data[0] * other[1] - this->_data[1] * other[0];
        return result;
    }

    Variable Vector::dot(const Vector &a, const Vector &b)
    {
        return a * b;
    }

    Vector Vector::cross(const Vector &a, const Vector &b)
    {
        return a.cross(b);
    }

    Variable Vector::operator[](size_t index) const
    {
        return this->_data[index];
    }
    Variable &Vector::operator[](size_t index)
    {
        return this->_data[index];
    }
    size_t Vector::size() const
    {
        return this->_data.size();
    }
    Vector::Orientation Vector::orientation() const
    {
        return this->_orientation;
    }

    void Vector::resize(size_t size, Orientation orientation)
    {
        this->_data.resize(size);
        this->_orientation = orientation;
    }
    void Vector::clear()
    {
        this->_data.clear();
    }
    void Vector::setOrientation(Orientation orientation)
    {
        this->_orientation = orientation;
    }

    Vector Vector::toCol() const
    {
        return Vector(this->_data, Orientation::COL);
    }
    Vector Vector::toRow() const
    {
        return Vector(this->_data, Orientation::ROW);
    }
    Vector Vector::transpose() const
    {
        return Vector(this->_data, this->_orientation == Orientation::ROW ? Orientation::COL : Orientation::ROW);
    }

    Matrix Vector::toMatrix() const
    {
        Matrix ret;
        switch (this->orientation())
        {
        case Orientation::COL:
            ret.resize(1, this->size());
            for (size_t i = 0; i < this->size(); i++)
                ret(0, i) = this->_data[i];
            break;
        case Orientation::ROW:
            ret.resize(this->size(), 1);
            for (size_t i = 0; i < this->size(); i++)
                ret(i, 0) = this->_data[i];
            break;
        default:
            throw std::invalid_argument("Invalid orientation");
            break;
        }
        return ret;
    }
}