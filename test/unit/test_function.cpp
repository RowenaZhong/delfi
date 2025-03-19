// 示例测试代码结构
#include <gtest/gtest.h>
#include "delfi/Function.h"

TEST(FunctionTest, Addition)
{
    delfi::Function f([](auto x) -> auto
                      { return x * x; });
    EXPECT_NEAR(f(2), 4, 1e-6);
    EXPECT_NEAR(f.Derivative(2), 4, 1e-6);
    EXPECT_NEAR(f.Integral(2, 3), (double)19 / 3, 1e-6);
}
int main(int argc, char **argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}