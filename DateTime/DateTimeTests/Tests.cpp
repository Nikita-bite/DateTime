#include <gtest/gtest.h>
#include "DateTime.h"


TEST(DateTime, Constructor) {
    DateTime dt(0, 1, 1, 2000);
    
    EXPECT_EQ(dt.getYear(), 2000);
    EXPECT_EQ(dt.getMonth(), 1);
    EXPECT_EQ(dt.getDayOfMonth(), 1);
    EXPECT_EQ(dt.getSecondsInDay(), 0);
}


TEST(DateTime, ConstructorValidation) {
    EXPECT_NO_THROW(DateTime(0, 29, 2, 2020));
    EXPECT_THROW(DateTime(0, 29, 2, 2021), std::runtime_error);
    
    
    EXPECT_NO_THROW(DateTime(86399, 1, 1, 2023));
    EXPECT_THROW(DateTime(86400, 1, 1, 2023), std::runtime_error);


    EXPECT_THROW(DateTime(0, 1, 13, 2023), std::runtime_error);
    EXPECT_THROW(DateTime(0, 1, 0, 2023), std::runtime_error);


    EXPECT_THROW(DateTime(0, 31, 4, 2023), std::runtime_error);
    EXPECT_NO_THROW(DateTime(0, 31, 3, 2023));
}


TEST(DateTime, ToStringFormat) {
    DateTime dt(0, 1, 1, 2000);
    

    std::string result = dt.ToString();
    EXPECT_EQ(result, "2000-01-01-00000");

    dt.setYear(2023);
    dt.setMonth(12);
    dt.setDayOfMonth(31);
    EXPECT_EQ(dt.ToString(), "2023-12-31-00000");
}


TEST(DateTime, EdgeCases) {
    DateTime dt;
    
    dt.setYear(0);
    dt.setMonth(1);
    dt.setDayOfMonth(1);
    dt.setSecondsInDay(0);
    EXPECT_EQ(dt.ToString(), "0000-01-01-00000");
    
    dt.setYear(9999);
    dt.setMonth(12);
    dt.setDayOfMonth(31);
    dt.setSecondsInDay(10000);
    EXPECT_EQ(dt.ToString(), "9999-12-31-10000");
}


TEST(DateTime, AddDaysEdgeCases) {
    DateTime dt1(0, 28, 2, 2020);
    dt1.AddDays(1);
    EXPECT_EQ(dt1.getDayOfMonth(), 29);
    EXPECT_EQ(dt1.getMonth(), 2);
    
    dt1.AddDays(1);
    EXPECT_EQ(dt1.getDayOfMonth(), 1);
    EXPECT_EQ(dt1.getMonth(), 3);

    // Переход через год
    DateTime dt2(0, 31, 12, 2023);
    dt2.AddDays(1);
    EXPECT_EQ(dt2.getYear(), 2024);
    EXPECT_EQ(dt2.getMonth(), 1);
    EXPECT_EQ(dt2.getDayOfMonth(), 1);

    // Вычитание дней
    DateTime dt3(0, 1, 1, 2023);
    dt3.AddDays(-1);
    EXPECT_EQ(dt3.getYear(), 2022);
    EXPECT_EQ(dt3.getMonth(), 12);
    EXPECT_EQ(dt3.getDayOfMonth(), 31);

    // Добавление нескольких лет через дни
    DateTime dt4(0, 1, 1, 2000);
    dt4.AddDays(365*25 + 7);
    EXPECT_EQ(dt4.getYear(), 2025);
}


// Тестирование Unix-time преобразований
TEST(DateTime, UnixTimeConversion) {
    // Начальная точка (1 января 1970)
    DateTime dt1(0);
    EXPECT_EQ(dt1.getYear(), 1970);
    EXPECT_EQ(dt1.getMonth(), 1);
    EXPECT_EQ(dt1.getDayOfMonth(), 1);
    EXPECT_EQ(dt1.getSecondsInDay(), 0);

    // Високосный год
    DateTime dt2(31622400);  // 366 дней
//    std::cout << "TEST: " << dt2.getSecondsInDay() << ", " << dt2.getDayOfMonth() << ", " << dt2.getMonth() << ", " << dt2.getYear() << "\n";
    EXPECT_EQ(dt2.getYear(), 1971);
    EXPECT_EQ(dt2.getMonth(), 1);
    EXPECT_EQ(dt2.getDayOfMonth(), 2);
//    std::cout << "TEST: " << dt2.getSecondsInDay() << ", " << dt2.getDayOfMonth() << ", " << dt2.getMonth() << ", " << dt2.getYear() << "\n";

    // Точное время
    DateTime dt3(123456);
    EXPECT_EQ(dt3.getSecondsInDay(), 123456 % 86400);
}


// Тестирование дня недели
TEST(DateTime, DayOfWeekCalculation) {
    // Известные даты
    DateTime dt1(0, 1, 1, 2023);  // Воскресенье
    EXPECT_EQ(dt1.DayofWeek(), 1);
    EXPECT_EQ(dt1.DayofWeekName(), "Воскресенье");

    DateTime dt2(0, 2, 1, 2023);  // Понедельник
    EXPECT_EQ(dt2.DayofWeek(), 2);
    
    DateTime dt3(0, 23, 2, 1986);
    EXPECT_EQ(dt3.DayofWeek(), 1);  // Воскресенье
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
