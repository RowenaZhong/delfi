#include "delfi/Matrix.h"
#include <cstdio>
int main()
{
    delfi::Matrix A(2, 2);
    delfi::Matrix B(2, 2);
    double a, b, c, d;
    scanf("A = [%lf,%lf;%lf,%lf]\n", &a, &b, &c, &d);
    A(0, 0) = a;
    A(0, 1) = b;
    A(1, 0) = c;
    A(1, 1) = d;
    scanf("B = [%lf,%lf;%lf,%lf]\n", &a, &b, &c, &d);
    B(0, 0) = a;
    B(0, 1) = b;
    B(1, 0) = c;
    B(1, 1) = d;
    printf("A = \n");
    printf("\t[%lf, %lf]\n", (double)A(0, 0), (double)A(0, 1));
    printf("\t[%lf, %lf]\n", (double)A(1, 0), (double)A(1, 1));
    printf("B = \n");
    printf("\t[%lf, %lf]\n", (double)B(0, 0), (double)B(0, 1));
    printf("\t[%lf, %lf]\n", (double)B(1, 0), (double)B(1, 1));
    auto C = A + B;
    printf("C = A + B\n");
    printf("C = \n");
    printf("\t[%lf, %lf]\n", (double)C(0, 0), (double)C(0, 1));
    printf("\t[%lf, %lf]\n", (double)C(1, 0), (double)C(1, 1));
    auto D = A * B;
    printf("D = A * B\n");
    printf("D = \n");
    printf("\t[%lf, %lf]\n", (double)D(0, 0), (double)D(0, 1));
    printf("\t[%lf, %lf]\n", (double)D(1, 0), (double)D(1, 1));
    auto E = A * 2.0;
    printf("E = A * 2.0\n");
    printf("E = \n");
    printf("\t[%lf, %lf]\n", (double)E(0, 0), (double)E(0, 1));
    printf("\t[%lf, %lf]\n", (double)E(1, 0), (double)E(1, 1));
    auto F = A;
    F.transpose();
    printf("F = T(A)\n");
    printf("F = \n");
    printf("\t[%lf, %lf]\n", (double)F(0, 0), (double)F(0, 1));
    printf("\t[%lf, %lf]\n", (double)F(1, 0), (double)F(1, 1));
    auto G = A;
    G.inverse();
    printf("G = inv(A)\n");
    printf("G = \n");
    printf("\t[%lf, %lf]\n", (double)G(0, 0), (double)G(0, 1));
    printf("\t[%lf, %lf]\n", (double)G(1, 0), (double)G(1, 1));
    auto H = A * G;
    printf("H = A * inv(A)\n");
    printf("H = \n");
    printf("\t[%lf, %lf]\n", (double)H(0, 0), (double)H(0, 1));
    printf("\t[%lf, %lf]\n", (double)H(1, 0), (double)H(1, 1));
    auto I = A;
    I.gassJordanElimination();
    printf("I = gassJordanElimination(A)\n");
    printf("I = \n");
    printf("\t[%lf, %lf]\n", (double)I(0, 0), (double)I(0, 1));
    printf("\t[%lf, %lf]\n", (double)I(1, 0), (double)I(1, 1));

    return 0;
}