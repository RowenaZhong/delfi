#include "Field.h"

namespace delfi
{
    Field::Field(std::function<Vector(const Vector)> &func, const size_t d1, const size_t d2)
    {
        if (d1 == 0 || d2 == 0)
        {
            throw std::invalid_argument("Field dimensions must be greater than 0");
        }
        this->_func = func;
        this->_dim1 = d1;
        this->_dim2 = d2;
    }

    Field::Field(std::vector<MultiFunction> &mfs)
    {
        if (mfs.size() == 0)
        {
            throw std::invalid_argument("Field must contain at least one function");
        }
        this->_func = [mfs](const Vector x) -> Vector
        {
            Vector result;
            for (auto &mf : mfs)
                result.push_back(mf(x));
            return result;
        };
        this->_dim1 = mfs[0].getDim();
        this->_dim2 = mfs.size();
    }
    Field::Field(const Field &other)
    {
        this->_func = other._func;
        this->_dim1 = other._dim1;
        this->_dim2 = other._dim2;
    }
    const Field &Field::operator=(const Field &other)
    {
        this->_func = other._func;
        this->_dim1 = other._dim1;
        this->_dim2 = other._dim2;
        return *this;
    }
    const Field &Field::operator=(std::vector<MultiFunction> &mfs)
    {
        if (mfs.size() == 0)
        {
            throw std::invalid_argument("Field must contain at least one function");
        }
        this->_func = [mfs](const Vector x) -> Vector
        {
            Vector result;
            for (auto &mf : mfs)
                result.push_back(mf(x));
            return result;
        };
        this->_dim1 = mfs[0].getDim();
        this->_dim2 = mfs.size();
        return *this;
    }
    Vector Field::operator()(const Vector &x) const
    {
        return this->_func(x);
    }
    size_t Field::getDim1() const
    {
        return size_t(this->_dim1);
    }
    size_t Field::getDim2() const
    {
        return size_t(this->_dim2);
    }
} // namespace delfi
