#include <gtest/gtest.h>

#include "Utilities/EnumUtilities.h"

enum class DummyEnum : uint8_t
{
    Zero,
    One,
    Two,
    Three,
    Four,
    MAX
};

TEST(EnumUtilitiesTest, EnumCountShouldGiveCorrectCount) {
    EXPECT_EQ(Finally::EnumUtilities::EnumCount<DummyEnum>(), 5);
}

TEST(EnumUtilitiesTest, EnumIndexShouldGiveCorrectIndex) {
    EXPECT_EQ(Finally::EnumUtilities::EnumIndex(DummyEnum::Two), 2);
}
