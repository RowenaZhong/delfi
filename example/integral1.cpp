#include "delfi/Function.h"
#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    auto f = delfi::Function([](const delfi::Variable x) -> delfi::Variable
                             { return x / (cos(x * x + 1) * cos(x * x + 1) + 1); });
    cout << "{";
    for (auto x = 0.0; x <= 10; x += 1e-1)
        cout << "(" << x << "," << f.Integral(0, x) << "),";
    cout << "\b}\n";
}