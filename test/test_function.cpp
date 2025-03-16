#include "delfi/Function.h"
#include "delfi/constants.h"

#include <iostream>
#include <cmath>
int main()
{
    delfi::Function a([](delfi::Variable x) -> delfi::Variable
                      { return exp(x); });
    std::cout << a.Integral(0, 1) << std::endl;
}