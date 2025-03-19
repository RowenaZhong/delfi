// 示例测试代码结构
#include <gtest/gtest.h>
#include "delfi/Function.h"

TEST(FunctionTest, Addition)
{
    delfi::Function f([](auto x) -> auto
                      { return x * x; });
    EXPECT_EQ(f(2), 4);
    EXPECT_EQ(f.Derivative(2), 4);
    EXPECT_EQ(f.Integral(2, 3), 5);
}
int main(int argc, char **argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}