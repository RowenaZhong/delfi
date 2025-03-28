#include "delfi/Compound.h"
#include <stdexcept>
namespace delfi
{
    Function operator*(const Function &f1, const Function &f2)
    {
        return Function([=, f1, f2](const Variable x) -> Variable
                        { return f2(f1(x)); });
    }
    Function operator*(const VecValFunction &f1, const MultiFunction &f2)
    {
        if (f1.GetDim() != f2.GetDim())
            throw std::invalid_argument("Dimension mismatch");
        return Function([=, f1, f2](const Variable x) -> Variable
                        { return f2(f1(x)); });
    }
    MultiFunction operator*(const MultiFunction &f1, const Function &f2)
    {
        return MultiFunction([=, f1, f2](const Vector x) -> Variable
                             { return f2(f1(x)); }, f1.GetDim());
    }
    MultiFunction operator*(const Field &f1, const MultiFunction &f2)
    {
        if (f1.getDim2() != f2.GetDim())
            throw std::invalid_argument("Dimension mismatch");
        return MultiFunction([=, f1, f2](const Vector x) -> Variable
                             { return f2(f1(x)); }, f1.getDim1());
    }
    VecValFunction operator*(const VecValFunction &f1, const Field &f2)
    {
        if (f1.GetDim() != f2.getDim1())
            throw std::invalid_argument("Dimension mismatch");
        return VecValFunction([=, f1, f2](const Variable x) -> Vector
                              { return f2(f1(x)); }, f2.getDim2());
    }
    VecValFunction operator*(const Function &f1, const VecValFunction &f2)
    {
        return VecValFunction([=, f1, f2](const Variable x) -> Vector
                              { return f2(f1(x)); }, f2.GetDim());
    }
    Field operator*(const Field &f1, const Field &f2)
    {
        if (f1.getDim2() != f2.getDim1())
            throw std::invalid_argument("Dimension mismatch");
        return Field([=, f1, f2](const Vector x) -> Vector
                     { return f2(f1(x)); }, f1.getDim1(), f2.getDim2());
    }
    Field operator*(const MultiFunction &f1, const VecValFunction &f2)
    {
        return Field([=, f1, f2](const Vector x) -> Vector
                     { return f2(f1(x)); }, f1.GetDim(), f2.GetDim());
    }
}