// 示例测试代码结构
#include <gtest/gtest.h>
#include "delfi/MultiFunction.h"

TEST(MultiFunctionTest, Addition)
{
    delfi::MultiFunction mf([](delfi::Vector x) -> delfi::Variable
                            { return x[0] + x[1]; }, 2);
    delfi::Vector x = (std::vector<double>){1.0, 2.0};
    delfi::Variable y = mf(x);
    EXPECT_EQ(y, 3.0);
}

TEST(MultiFunctionTest, Derivative)
{
    delfi::MultiFunction mf([](delfi::Vector x) -> delfi::Variable
                            { return x[0] * x[1]; }, 2);
    delfi::Vector x = (std::vector<double>){2.0, 3.0};
    auto frac_df_dx = mf.Derivative(x, 0);
    EXPECT_NEAR(frac_df_dx, 3.0, 1e-6);
}
TEST(MultiFunctionTest, Integral)
{
    delfi::MultiFunction mf([](delfi::Vector x) -> delfi::Variable
                            { return x[0] * x[1]; }, 2);
    delfi::Vector x = (std::vector<double>){2.0, 3.0};
    auto integral = mf.Integral(x, 0, 3.0);
    EXPECT_NEAR(integral, 7.5, 1e-6);
}
// TEST(MultiFunctionTest, Compount)
// {
//     delfi::MultiFunction mf([](delfi::Vector x) -> delfi::Variable
//                             { return x[0] * x[1]; }, 2);
//     delfi::Function f([](delfi::Variable x) -> delfi::Variable
//                       { return x + 5; });
//     delfi::Vector x = (std::vector<double>){2.0, 3.0};
//     auto g = mf * f;
//     auto y = g(x);
//     EXPECT_NEAR(y, 11.0, 1e-6);
// }
TEST(MultiFunctionTest, Gradient)
{
    delfi::MultiFunction mf([](delfi::Vector x) -> delfi::Variable
                            { return x[0] * x[0] * x[1]; }, 2);
    delfi::Vector x = (std::vector<double>){2.0, 3.0};
    auto grad = mf.Gradient(x);
    EXPECT_NEAR(grad[0], 12.0, 1e-6);
    EXPECT_NEAR(grad[1], 4.0, 1e-6);
}
int main(int argc, char **argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}