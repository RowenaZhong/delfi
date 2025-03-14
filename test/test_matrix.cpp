#include "delfi/Matrix.h"
#include <cstdio>
int main()
{
    // Test 1: Create a 2x2 matrix and check its values
    Delfi::Matrix<2, 2> A;
    A(0, 0) = 1;
    A(1, 1) = 1;
    Delfi::Matrix<2, 2> B;
    B(0, 0) = 2;
    B(1, 0) = 2;
    Delfi::Matrix<2, 2> C = A + B;
    printf("A = \n");
    for (int i = 0; i < 2; i++)
    {
        printf("\t[ ");
        for (int j = 0; j < 2; j++)
        {
            printf("%lf ", (double)A(i, j));
        }
        printf("]\n");
    }
    printf("B = \n");
    for (int i = 0; i < 2; i++)
    {
        printf("\t[ ");
        for (int j = 0; j < 2; j++)
        {
            printf("%lf ", (double)B(i, j));
        }
        printf("]\n");
    }
    puts("C = A + B");
    printf("C = \n");
    for (int i = 0; i < 2; i++)
    {
        printf("\t[ ");
        for (int j = 0; j < 2; j++)
        {
            printf("%lf ", (double)C(i, j));
        }
        printf("]\n");
    }
    return 0;
}