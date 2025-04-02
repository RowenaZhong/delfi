#include "delfi/Function.h"
#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    auto f = delfi::Function([](const delfi::Variable x) -> delfi::Variable
                             { return pow(x, 5) + pow(x, 4) + pow(x, 3) + pow(x, 2) + x + 1; });
    cout << "{";
    for (auto x = 0.0; x <= 10; x += 1e-1)
        cout << "(" << x << "," << f.Integral(0, x) << "),";
    cout << "\b}\n";
    return 0;
}