#include "delfi/Function.h"
#include "delfi/constants.h"

#include <iostream>
#include <cmath>
int main()
{
    Delfi::Function a([](Delfi::Variable x) -> Delfi::Variable
                      { return exp(x); });
    std::cout << a.Integral(0, 1) << std::endl;
}