#include "delfi/Compound.h"
#include "delfi/reporter.h"
namespace delfi
{
    Function operator*(const Function &f1, const Function &f2)
    {
        return Function([f = f1, g = f2](const Variable x) -> Variable
                        { return g(f(x)); });
    }
    Function operator*(const VecValFunction &f1, const MultiFunction &f2)
    {
        if (f1.GetDim() != f2.GetDim())
            throw delfi::InvalidArgumentReporter(f1.GetDim(), f2.GetDim());
        return Function([f = f1, g = f2](const Variable x) -> Variable
                        { return g(f(x)); });
    }
    MultiFunction operator*(const MultiFunction &f1, const Function &f2)
    {
        return MultiFunction([f = f1, g = f2](const Vector x) -> Variable
                             { return g(f(x)); }, f1.GetDim());
    }
    MultiFunction operator*(const Field &f1, const MultiFunction &f2)
    {
        if (f1.getDim2() != f2.GetDim())
            throw delfi::InvalidArgumentReporter(f1.GetDim(), f2.GetDim());
        return MultiFunction([f = f1, g = f2](const Vector x) -> Variable
                             { return g(f(x)); }, f1.getDim1());
    }
    VecValFunction operator*(const VecValFunction &f1, const Field &f2)
    {
        if (f1.GetDim() != f2.getDim1())
            throw delfi::InvalidArgumentReporter(f1.GetDim(), f2.GetDim());
        return VecValFunction([f = f1, g = f2](const Variable x) -> Vector
                              { return g(f(x)); }, f2.getDim2());
    }
    VecValFunction operator*(const Function &f1, const VecValFunction &f2)
    {
        return VecValFunction([f = f1, g = f2](const Variable x) -> Vector
                              { return g(f(x)); }, f2.GetDim());
    }
    Field operator*(const Field &f1, const Field &f2)
    {
        if (f1.getDim2() != f2.getDim1())
            throw delfi::InvalidArgumentReporter(f1.GetDim(), f2.GetDim());
        return Field([f = f1, g = f2](const Vector x) -> Vector
                     { return g(f(x)); }, f1.getDim1(), f2.getDim2());
    }
    Field operator*(const MultiFunction &f1, const VecValFunction &f2)
    {
        return Field([f = f1, g = f2](const Vector x) -> Vector
                     { return g(f(x)); }, f1.GetDim(), f2.GetDim());
    }
}