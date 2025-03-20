// 示例测试代码结构
#include <gtest/gtest.h>
#include "delfi/Function.h"

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

TEST(CompoundTest, Addition)
{
    delfi::Function f([](auto x) -> auto
                      { return x * x; });
    delfi::Function g([](auto x) -> auto
                      { return x + 1; });
    auto h = f * g; // h(x) = g(f(x))
    auto i = g * f; // i(x) = f(g(x))
    auto j = g * g * g;
    EXPECT_NEAR(h(2), 5, 1e-6);
    EXPECT_NEAR(i(2), 9, 1e-6);
    EXPECT_NEAR(j(2), 5, 1e-6); // FIXME : SEGFAULT
}
int main(int argc, char **argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}