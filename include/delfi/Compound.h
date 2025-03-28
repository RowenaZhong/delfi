#pragma once
#ifndef DELFI_COMPOUND
#define DELFI_COMPOUND

#include "Function.h"
#include "MultiFunction.h"
#include "VecValFunction.h"
#include "Field.h"
#include <string>
namespace delfi
{
    Function operator*(const Function &f1, const Function &f2);
    Function operator*(const VecValFunction &f1, const MultiFunction &f2);
    MultiFunction operator*(const MultiFunction &f1, const Function &f2);
    MultiFunction operator*(const Field &f1, const MultiFunction &f2);
    VecValFunction operator*(const VecValFunction &f1, const Field &f2);
    VecValFunction operator*(const Function &f1, const VecValFunction &f2);
    Field operator*(const Field &f1, const Field &f2);
    Field operator*(const MultiFunction &f1, const VecValFunction &f2);
}
#endif // DELFI_COMPOUND