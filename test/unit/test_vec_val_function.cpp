// 示例测试代码结构
#include <gtest/gtest.h>
#include "delfi/VecValFunction.h"
#include <cmath>
#include <string>

auto func = delfi::VecValFunction([](const delfi::Variable &x) -> delfi::Vector
                                  { return std::vector<delfi::Variable>{cos(x), sin(x), x}; }, 3);

TEST(VecValFunctionTest, CACULATE)
{
    auto x = delfi::Variable(0.5);
    auto y = func(x);
    EXPECT_EQ(y.size(), 3);
    EXPECT_NEAR(y[0], cos(0.5), 1e-6);
    EXPECT_NEAR(y[1], sin(0.5), 1e-6);
    EXPECT_NEAR(y[2], 0.5, 1e-6);
}
TEST(VecValFunctionTest, DERIVATIVE)
{
    auto x = delfi::Variable(0.5);
    auto y = func(x);
    auto dy = func.Derivative(x);
    EXPECT_EQ(dy.size(), 3);
    EXPECT_NEAR(dy[0], -sin(0.5), 1e-4);
    EXPECT_NEAR(dy[1], cos(0.5), 1e-4);
    EXPECT_NEAR(dy[2], 1, 1e-6);
}
TEST(VecValFunctionTest, INTEGRAL)
{
    auto x = delfi::Variable(0.5);
    auto y = func.Integral(0, x);
    EXPECT_EQ(y.size(), 3);
    EXPECT_NEAR(y[0], sin(0.5), 1e-4);
    EXPECT_NEAR(y[1], -cos(0.5) + cos(0), 1e-4);
    EXPECT_NEAR(y[2], 0.5 * 0.5 * 0.5, 1e-6);
}
int main(int argc, char **argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}