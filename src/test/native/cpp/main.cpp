#include <hal/HAL.h>

#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    HAL_Initialize(500, 0);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
