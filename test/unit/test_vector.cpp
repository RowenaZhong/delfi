// 示例测试代码结构
#include <gtest/gtest.h>
#include "delfi/Vector.h"

TEST(VectorTest, TestVectorAddition)
{
    delfi::Vector v1(std::vector<delfi::Variable>({1.0, 2.0, 3.0}));
    delfi::Vector v2(std::vector<delfi::Variable>({4.0, 5.0, 6.0}));
    delfi::Vector v3 = v1 + v2;
    auto v4 = delfi::Vector::cross(v1, v2);
    EXPECT_EQ(v3, delfi::Vector(std::vector<delfi::Variable>({5.0, 7.0, 9.0})));
    EXPECT_EQ(v4, delfi::Vector(std::vector<delfi::Variable>({-3.0, 6.0, -3.0})));
}
int main(int argc, char **argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}