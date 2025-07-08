#include <gtest/gtest.h>
#include "DateTime.h"


TEST(DateTime, DefaultConstructor) {
    DateTime dt;
    
    EXPECT_EQ(dt.getYear(), 2000);
    EXPECT_EQ(dt.getMonth(), 1);
    EXPECT_EQ(dt.getDayOfMonth(), 1);
    EXPECT_EQ(dt.getSecondsInDay(), 0);
}


TEST(DateTime, ToStringFormat) {
    DateTime dt;
    

    std::string result = dt.ToString();
    EXPECT_EQ(result, "2000-1-1-0");

    dt.setYear(2023);
    dt.setMonth(12);
    dt.setDayOfMonth(31);
    EXPECT_EQ(dt.ToString(), "2023-12-31-0");
}


TEST(DateTime, EdgeCases) {
    DateTime dt;
    
    dt.setYear(0);
    dt.setMonth(1);
    dt.setDayOfMonth(1);
    EXPECT_EQ(dt.ToString(), "0-1-1-0");
    
    dt.setYear(9999);
    dt.setMonth(12);
    dt.setDayOfMonth(31);
    EXPECT_EQ(dt.ToString(), "9999-12-31-0");
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
