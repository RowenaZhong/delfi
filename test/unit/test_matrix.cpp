// 示例测试代码结构
#include <gtest/gtest.h>
#include "delfi/Matrix.h"

TEST(MatrixTest, Addition)
{
    delfi::Matrix a(3, 3);
    delfi::Matrix b(3, 3);
    /*
    a =
        1 2 3
        4 5 6
        7 8 9
    */
    a(0, 0) = 1;
    a(0, 1) = 2;
    a(0, 2) = 3;
    a(1, 0) = 4;
    a(1, 1) = 5;
    a(1, 2) = 6;
    a(2, 0) = 7;
    a(2, 1) = 8;
    a(2, 2) = 9;

    /*
    b =
        1 0 0
        0 1 0
        0 0 1
    */
    b(0, 0) = 1;
    b(1, 1) = 1;
    b(2, 2) = 1;

    // c = a + b
    delfi::Matrix c = a + b;
    delfi::Matrix c_expected;
    c_expected(0, 0) = 2;
    c_expected(0, 1) = 2;
    c_expected(0, 2) = 3;
    c_expected(1, 0) = 4;
    c_expected(1, 1) = 6;
    c_expected(1, 2) = 6;
    c_expected(2, 0) = 7;
    c_expected(2, 1) = 8;
    c_expected(2, 2) = 10;

    ASSERT_EQ(c, c_expected);

    delfi::Matrix d = a.transpose();
    delfi::Matrix d_expected;
    d_expected(0, 0) = 1;
    d_expected(1, 0) = 4;
    d_expected(2, 0) = 7;
    d_expected(0, 1) = 2;
    d_expected(1, 1) = 5;
    d_expected(2, 1) = 8;
    d_expected(0, 2) = 3;
    d_expected(1, 2) = 6;
    d_expected(2, 2) = 9;

    ASSERT_EQ(d, d_expected);

    delfi::Matrix e = a * b;
    delfi::Matrix e_expected;
    e_expected(0, 0) = 1;
    e_expected(0, 1) = 2;
    e_expected(0, 2) = 3;
    e_expected(1, 0) = 4;
    e_expected(1, 1) = 5;
    e_expected(1, 2) = 6;
    e_expected(2, 0) = 7;
    e_expected(2, 1) = 8;
    e_expected(2, 2) = 9;

    ASSERT_EQ(e, e_expected);
    delfi::Matrix f = a.inverse();
    delfi::Matrix f_expected;
    f_expected(0, 0) = 1;
    f_expected(0, 1) = 2;
    f_expected(0, 2) = 3;
    f_expected(1, 0) = 4;
    f_expected(1, 1) = 5;
    f_expected(1, 2) = 6;
    f_expected(2, 0) = 7;
    f_expected(2, 1) = 8;
    f_expected(2, 2) = 9;

    ASSERT_EQ(f, f_expected);
}
int main(int argc, char **argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}