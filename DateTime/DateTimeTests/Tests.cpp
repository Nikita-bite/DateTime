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
    EXPECT_EQ(result, "00:00:00 01-01-2000 00000");

    dt.setYear(2023);
    dt.setMonth(12);
    dt.setDayOfMonth(31);
    EXPECT_EQ(dt.ToString(), "00:00:00 31-12-2023 00000");
}


TEST(DateTime, EdgeCases) {
    DateTime dt;
    
    dt.setYear(0);
    dt.setMonth(1);
    dt.setDayOfMonth(1);
    dt.setSecondsInDay(0);
    EXPECT_EQ(dt.ToString(), "00:00:00 01-01-0000 00000");
    
    dt.setYear(9999);
    dt.setMonth(12);
    dt.setDayOfMonth(31);
    dt.setSecondsInDay(10000);
    EXPECT_EQ(dt.ToString(), "02:46:40 31-12-9999 10000");
}


TEST(DateTime, AddDaysEdgeCases) {
    DateTime dt1(0, 28, 2, 2020);
    dt1.AddDays(1);
    EXPECT_EQ(dt1.getDayOfMonth(), 29);
    EXPECT_EQ(dt1.getMonth(), 2);
    
    dt1.AddDays(1);
    EXPECT_EQ(dt1.getDayOfMonth(), 1);
    EXPECT_EQ(dt1.getMonth(), 3);

    // переход через год
    DateTime dt2(0, 31, 12, 2023);
    dt2.AddDays(1);
    EXPECT_EQ(dt2.getYear(), 2024);
    EXPECT_EQ(dt2.getMonth(), 1);
    EXPECT_EQ(dt2.getDayOfMonth(), 1);

    // вычитание дней
    DateTime dt3(0, 1, 1, 2023);
    dt3.AddDays(-1);
    EXPECT_EQ(dt3.getYear(), 2022);
    EXPECT_EQ(dt3.getMonth(), 12);
    EXPECT_EQ(dt3.getDayOfMonth(), 31);

    // добавление нескольких лет через дни
    DateTime dt4(0, 1, 1, 2000);
    dt4.AddDays(365*25 + 7);
    EXPECT_EQ(dt4.getYear(), 2025);
}


// тестирование Unix-time Conversion
TEST(DateTime, UnixTimeConversion) {
    // 1 января 1970
    DateTime dt1(0);
    EXPECT_EQ(dt1.getYear(), 1970);
    EXPECT_EQ(dt1.getMonth(), 1);
    EXPECT_EQ(dt1.getDayOfMonth(), 1);
    EXPECT_EQ(dt1.getSecondsInDay(), 0);

    // високосный год
    DateTime dt2(31622400);  // 366 дней

    EXPECT_EQ(dt2.getYear(), 1971);
    EXPECT_EQ(dt2.getMonth(), 1);
    EXPECT_EQ(dt2.getDayOfMonth(), 2);

    DateTime dt3(123456);
    EXPECT_EQ(dt3.getSecondsInDay(), 123456 % 86400);
}


// тестирование дня недели
TEST(DateTime, DayOfWeekCalculation) {
    DateTime dt1(0, 1, 1, 2023);  // Воскресенье
    EXPECT_EQ(dt1.DayofWeek(), 1);
    EXPECT_EQ(dt1.DayofWeekName(), "Воскресенье");

    DateTime dt2(0, 2, 1, 2023);  // Понедельник
    EXPECT_EQ(dt2.DayofWeek(), 2);
    
    DateTime dt3(0, 23, 2, 1986);
    EXPECT_EQ(dt3.DayofWeek(), 1);  // Воскресенье
}


// тесты для setDayOfMonth
TEST(DateTime, DayOfMonthValidation) {
    DateTime dt;
    
    EXPECT_NO_THROW(dt.setDayOfMonth(1));
    EXPECT_NO_THROW(dt.setDayOfMonth(31));
    EXPECT_THROW(dt.setDayOfMonth(0), std::runtime_error);
    EXPECT_THROW(dt.setDayOfMonth(-1), std::runtime_error);
    EXPECT_THROW(dt.setDayOfMonth(32), std::runtime_error);
    
    // февраль в високосный год
    dt.setYear(2020);
    dt.setMonth(2);
    EXPECT_NO_THROW(dt.setDayOfMonth(29));
    
    // февраль в невисокосный год
    dt.setYear(2021);
    EXPECT_THROW(dt.setDayOfMonth(29), std::runtime_error);
    
    // месяцы с 30 днями
    dt.setMonth(4);
    EXPECT_NO_THROW(dt.setDayOfMonth(30));
    EXPECT_THROW(dt.setDayOfMonth(31), std::runtime_error);
    
    dt.setMonth(6);
    EXPECT_NO_THROW(dt.setDayOfMonth(30));
    EXPECT_THROW(dt.setDayOfMonth(31), std::runtime_error);
    
    dt.setMonth(9);
    EXPECT_NO_THROW(dt.setDayOfMonth(30));
    EXPECT_THROW(dt.setDayOfMonth(31), std::runtime_error);
    
    dt.setMonth(11);
    EXPECT_NO_THROW(dt.setDayOfMonth(30));
    EXPECT_THROW(dt.setDayOfMonth(31), std::runtime_error);
    
    // 31 день
    dt.setMonth(12);
    EXPECT_NO_THROW(dt.setDayOfMonth(30));
    EXPECT_NO_THROW(dt.setDayOfMonth(31));
}

// тесты для setMonth
TEST(DateTime, MonthValidation) {
    DateTime dt;
    
    EXPECT_NO_THROW(dt.setMonth(1));
    EXPECT_NO_THROW(dt.setMonth(12));
    EXPECT_THROW(dt.setMonth(0), std::runtime_error);
    EXPECT_THROW(dt.setMonth(13), std::runtime_error);
    
    // проверка корректировки дня при смене месяца
    dt.setDayOfMonth(31);
    dt.setMonth(1);
    EXPECT_NO_THROW(dt.setMonth(1));  // январь - 31 день
    
    EXPECT_THROW(dt.setMonth(2), std::runtime_error); // Февраль...
    
    dt.setDayOfMonth(28);
    dt.setYear(2021);  // невисокосный
    EXPECT_NO_THROW(dt.setMonth(2));
    
    // 29 февраля в невисокосном году
    dt.setMonth(1);
    dt.setDayOfMonth(29);
    dt.setYear(2021);
    EXPECT_THROW(dt.setMonth(2), std::runtime_error);
}

// тесты для setSecondsInDay
TEST(DateTime, SecondsValidation) {
    DateTime dt;
    
    EXPECT_NO_THROW(dt.setSecondsInDay(0));
    EXPECT_NO_THROW(dt.setSecondsInDay(86399));
    EXPECT_THROW(dt.setSecondsInDay(-1), std::runtime_error);
    EXPECT_THROW(dt.setSecondsInDay(86400), std::runtime_error);
    
    // граничные значения
    EXPECT_NO_THROW(dt.setSecondsInDay(59));
    EXPECT_NO_THROW(dt.setSecondsInDay(60));
    EXPECT_NO_THROW(dt.setSecondsInDay(3599));
    EXPECT_NO_THROW(dt.setSecondsInDay(3600));
    EXPECT_NO_THROW(dt.setSecondsInDay(86340));
}

// тесты для setYear с учетом високосных годов
TEST(DateTime, YearValidation) {
    DateTime dt;
    
    // стандартные значения
    EXPECT_NO_THROW(dt.setYear(1970));
    EXPECT_NO_THROW(dt.setYear(2023));
    EXPECT_NO_THROW(dt.setYear(0));     // Год 0
    EXPECT_THROW(dt.setYear(-100), std::runtime_error);  // отрицательные годы
    
    // проверка 29 февраля при смене года
    dt.setMonth(2);
    dt.setDayOfMonth(29);
    
    // високосный -> високосный
    dt.setYear(2020);
    EXPECT_NO_THROW(dt.setYear(2024));  // Оба високосные
    
    // високосный -> невисокосный
    dt.setYear(2020);
    EXPECT_THROW(dt.setYear(2021), std::runtime_error);  // Должно упасть
    
    // невисокосный -> високосный (день 28 - должно пройти)
    dt.setDayOfMonth(28);
    dt.setYear(2021);
    EXPECT_NO_THROW(dt.setYear(2020));
    

    dt.setDayOfMonth(29);
    dt.setYear(2000);  // високосный
    EXPECT_NO_THROW(dt.setYear(2400));  // високосный
    
    dt.setYear(2000);
    EXPECT_THROW(dt.setYear(1900), std::runtime_error);  // 1900 не високосный
}

// комплексные тесты с последовательными изменениями
TEST(DateTime, ComplexValidation) {
    DateTime dt;
    
    // валидная последовательность
    EXPECT_NO_THROW({
        dt.setYear(2020);
        dt.setMonth(2);
        dt.setDayOfMonth(29);
    });
    
    // невалидная последовательность
    EXPECT_THROW({
        dt.setDayOfMonth(31);
        dt.setMonth(4);  // в апреле меньше дней
    }, std::runtime_error);
    
    // корректировка после ошибки
    EXPECT_EQ(dt.getMonth(), 2);  // месяц должен остаться февралем
    EXPECT_EQ(dt.getDayOfMonth(), 31);  // день остался 31
    

    EXPECT_THROW(dt.setMonth(4), std::runtime_error);
    EXPECT_NO_THROW(dt.setDayOfMonth(30));
    EXPECT_NO_THROW(dt.setMonth(4));
}

// тесты для крайних случаев с 29 февраля
TEST(DateTime, February29EdgeCases) {
    DateTime dt;
    
    dt.setYear(2020);
    dt.setMonth(2);
    EXPECT_NO_THROW(dt.setDayOfMonth(29));
    
    // смена года на невисокосный
    EXPECT_THROW(dt.setYear(2021), std::runtime_error);
    
    // смена месяца при 29 февраля в високосном году
    EXPECT_NO_THROW(dt.setMonth(3));
    
    // возврат в февраль в невисокосном году
    dt.setYear(2021);
    dt.setDayOfMonth(28);
    dt.setMonth(2);
    EXPECT_THROW(dt.setDayOfMonth(29), std::runtime_error);
    
    DateTime dt2;
    EXPECT_THROW({
        dt2.setYear(2021);
        dt2.setMonth(2);
        dt2.setDayOfMonth(29);
    }, std::runtime_error);
    

    DateTime dt3;
    EXPECT_NO_THROW({
        dt3.setYear(2000);
        dt3.setMonth(2);
        dt3.setDayOfMonth(29);
    });
    
    // вековой невисокосный год
    DateTime dt4;
    EXPECT_THROW({
        dt4.setYear(1900);
        dt4.setMonth(2);
        dt4.setDayOfMonth(29);
    }, std::runtime_error);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
