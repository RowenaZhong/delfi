// 示例测试代码结构
#include <gtest/gtest.h>
#include "delfi/Field.h"
#include <cmath>
auto gravityX = delfi::MultiFunction([](const delfi::Vector P) -> delfi::Variable
                                     { return -P[0] / pow(P[0] * P[0] + P[1] * P[1] + P[2] * P[2], 3 / 2); }, 3);
auto gravityY = delfi::MultiFunction([](const delfi::Vector P) -> delfi::Variable
                                     { return -P[1] / pow(P[0] * P[0] + P[1] * P[1] + P[2] * P[2], 3 / 2); }, 3);
auto gravityZ = delfi::MultiFunction([](const delfi::Vector P) -> delfi::Variable
                                     { return -P[2] / pow(P[0] * P[0] + P[1] * P[1] + P[2] * P[2], 3 / 2); }, 3);
auto gravityXYZ = delfi::Field({gravityX, gravityY, gravityZ});
TEST(TestField, Basic)
{
    delfi::Vector P = (std::vector<delfi::Variable>){1, 2, 3};
    delfi::Vector G = gravityXYZ(P);
    EXPECT_NEAR(G[0], -1 / pow(14, 3 / 2), 1e-6);
    EXPECT_NEAR(G[1], -2 / pow(14, 3 / 2), 1e-6);
    EXPECT_NEAR(G[2], -3 / pow(14, 3 / 2), 1e-6);
}
int main(int argc, char **argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}