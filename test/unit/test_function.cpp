// 示例测试代码结构
#include <gtest/gtest.h>
#include "delfi/Function.h"
#include <string>
TEST(BasicCalcTest, Addition)
{
    delfi::Function f([](auto x) -> auto
                      { return x * x; });
    EXPECT_NEAR(f(2), 4, 1e-6);
}

TEST(DerivativeTest, Addition)
{
    delfi::Function f([](auto x) -> auto
                      { return x * x; });
    EXPECT_NEAR(f.Derivative(2), 4, 1e-6);
}

TEST(IntegralTest, Addition)
{
    delfi::Function f([](auto x) -> auto
                      { return x * x; });
    EXPECT_NEAR(f.Integral(2, 3), 6.33333333, 1e-6);
}

// TEST(CompoundTest, Addition)
// {
//     delfi::Function f([](auto x) -> auto
//                       { return x * x; });
//     delfi::Function g([](auto x) -> auto
//                       { return x + 1; });
//     delfi::Function h([](auto x) -> auto
//                       { return x / 2; });
//     auto a = f * g * h;
//     auto b = g * f * h;
//     auto c = f * h * g;
//     auto d = h * f * g;
//     auto e = h * g * f;
//     auto i = g * h * f;
//     EXPECT_NEAR(a(2), 2.5, 1e-6);
//     EXPECT_NEAR(b(2), 4.5, 1e-6);
//     EXPECT_NEAR(c(2), 3, 1e-6);
//     EXPECT_NEAR(d(2), 2, 1e-6);
//     EXPECT_NEAR(e(2), 4, 1e-6);
//     EXPECT_NEAR(i(2), 2.25, 1e-6);
// }

int main(int argc, char **argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}