#include "delfi/Function.h"
#include "delfi/constants.h"

#include <iostream>
int main()
{
    Delfi::Function a([](Delfi::Variable x) -> Delfi::Variable
                      { return x * x; });
    std::cout << a.Derivative(2.5) << std::endl;
}