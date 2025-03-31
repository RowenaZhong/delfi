#include "delfi/Field.h"
#include <stdexcept>
namespace delfi
{
    Field::Field(const std::function<Vector(const Vector)> &func, const size_t d1, const size_t d2)
    {
        this->_sfunc.func = func;
        this->_sfunc.ArgLen = d1;
        this->_sfunc.RetLen = d2;
    }

    Field::Field(const std::vector<MultiFunction> &mfs)
    {
        for (const auto &mf : mfs)
            if (mf.GetDim() != mfs[0].GetDim())
                throw std::invalid_argument("All functions must have the same dimension"); // TODO rewrite
        this->_sfunc.func = [mfs](const Vector x) -> Vector
        {
            Vector result;
            for (auto &mf : mfs)
                result.push_back(mf(x));
            return result;
        };
        this->_sfunc.ArgLen = mfs[0].GetDim();
        this->_sfunc.RetLen = mfs.size();
    }
    Field::Field(const Field &other)
    {
        this->_sfunc = other._sfunc;
    }
    const Field &Field::operator=(const Field &other)
    {
        this->_sfunc = other._sfunc;
        return *this;
    }
    const Field &Field::operator=(std::vector<MultiFunction> &mfs)
    {
        for (const auto &mf : mfs)
            if (mf.GetDim() != mfs[0].GetDim())
                throw std::invalid_argument("All functions must have the same dimension"); // TODO rewrite
        this->_sfunc.func = [mfs](const Vector x) -> Vector
        {
            Vector result;
            for (auto &mf : mfs)
                result.push_back(mf(x));
            return result;
        };
        this->_sfunc.ArgLen = mfs[0].GetDim();
        this->_sfunc.RetLen = mfs.size();
        return *this;
    }
    Vector Field::operator()(const Vector &x) const
    {
        return this->_sfunc(x);
    }
    size_t Field::getDim1() const
    {
        return this->_sfunc.ArgLen;
    }
    size_t Field::getDim2() const
    {
        return size_t(this->_sfunc.RetLen);
    }
    Variable Field::Derivative(const Vector P, const size_t i, const size_t j)
    {
        auto temp = Function([this, P, i, j](const Variable x) -> Variable
                             {
            Vector t = P;
            t[i] = x;
            return this->_sfunc(t)[j]; });
        return temp.Derivative(P[i]);
    }
    Variable Field::Divergence(const Vector x)
    {
        if (this->_sfunc.ArgLen != this->_sfunc.RetLen)
            throw std::invalid_argument("Divergence is only defined for vector fields"); // TODO rewrite
        Variable result = 0;
        for (size_t i = 0; i < this->_sfunc.ArgLen; i++)
            result += Derivative(x, i, i);
        return result;
    }

} // namespace delfi
