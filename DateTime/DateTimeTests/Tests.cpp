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
    EXPECT_EQ(result, "01-01-2000 00:00:00");

    dt.setYear(2023);
    dt.setMonth(12);
    dt.setDayOfMonth(31);
    EXPECT_EQ(dt.ToString(), "31-12-2023 00:00:00");
}


TEST(DateTime, EdgeCases) {
    DateTime dt;

    dt.setYear(1);
    dt.setMonth(1);
    dt.setDayOfMonth(1);
    dt.setSecondsInDay(0);
    EXPECT_EQ(dt.ToString(), "01-01-0001 00:00:00");

    dt.setYear(9999);
    dt.setMonth(12);
    dt.setDayOfMonth(31);
    dt.setSecondsInDay(10000);
    EXPECT_EQ(dt.ToString(), "31-12-9999 02:46:40");

    dt.setYear(99999);
    dt.setMonth(12);
    dt.setDayOfMonth(31);
    dt.setSecondsInDay(10000);
    EXPECT_EQ(dt.ToString(), "31-12-99999 02:46:40");

    dt.setYear(123456);
    dt.setMonth(3);
    dt.setDayOfMonth(16);
    dt.setSecondsInDay(10001);
    EXPECT_EQ(dt.ToString(), "16-03-123456 02:46:41");
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
    dt2.AddMonth(2);
    EXPECT_EQ(dt2.getYear(), 2024);
    EXPECT_EQ(dt2.getMonth(), 2);
    EXPECT_EQ(dt2.getDayOfMonth(), 29);

    // вычитание дней
    DateTime dt3(0, 1, 1, 2025);
    dt3.AddDays(-368);
    EXPECT_EQ(dt3.getYear(), 2023);
    EXPECT_EQ(dt3.getMonth(), 12);
    EXPECT_EQ(dt3.getDayOfMonth(), 30);

    // добавление нескольких лет через дни
    DateTime dt4(0, 1, 1, 2000);
    dt4.AddDays(365*25 + 7);
    EXPECT_EQ(dt4.getYear(), 2025);

    DateTime dt5(0, 1, 1, 1000);
    EXPECT_THROW(dt5.AddDays(-366*1000), std::runtime_error);
    EXPECT_EQ(dt5.getYear(), 1000);

    DateTime dt6(0, 1, 1, 1000);
    EXPECT_NO_THROW(dt6.AddDays(-365*1000 + 365));
    EXPECT_EQ(dt6.getYear(), 1);
    EXPECT_EQ(dt6.getMonth(), 8);
    EXPECT_EQ(dt6.getDayOfMonth(), 31);

    DateTime dt7(0, 15, 3, 2023);
    dt7.AddDays(0);
    EXPECT_EQ(dt7.getDayOfMonth(), 15);
    EXPECT_EQ(dt7.getMonth(), 3);
    EXPECT_EQ(dt7.getYear(), 2023);

    DateTime dt8(0, 15, 3, 2023);
    dt8.AddDays(365);
    EXPECT_EQ(dt8.getDayOfMonth(), 14);
    EXPECT_EQ(dt8.getMonth(), 3);
    EXPECT_EQ(dt8.getYear(), 2024);

    DateTime dt9(0, 15, 3, 2020);
    dt9.AddDays(366);
    EXPECT_EQ(dt9.getDayOfMonth(), 16);
    EXPECT_EQ(dt9.getMonth(), 3);
    EXPECT_EQ(dt9.getYear(), 2021);

    DateTime dt10(0, 31, 12, 2023);
    dt10.AddDays(1);
    EXPECT_EQ(dt10.getDayOfMonth(), 1);
    EXPECT_EQ(dt10.getMonth(), 1);
    EXPECT_EQ(dt10.getYear(), 2024);

    DateTime dt11(0, 1, 1, 2023);
    dt11.AddDays(-1);
    EXPECT_EQ(dt11.getDayOfMonth(), 31);
    EXPECT_EQ(dt11.getMonth(), 12);
    EXPECT_EQ(dt11.getYear(), 2022);

    DateTime dt12(0, 1, 1, 1000);
    dt12.AddDays(365242); // 1000 лет (с високосными)
    EXPECT_EQ(dt12.getYear(), 2000);
    EXPECT_EQ(dt12.getMonth(), 1);
    EXPECT_EQ(dt12.getDayOfMonth(), 1);

    DateTime dt13(0, 1, 1, 1);
    EXPECT_THROW(dt13.AddDays(-1), std::runtime_error);
    EXPECT_EQ(dt13.getDayOfMonth(), 1);
    EXPECT_EQ(dt13.getMonth(), 1);
    EXPECT_EQ(dt13.getYear(), 1);

}


TEST(DateTime, AddDaysBasic) {
    DateTime dt1(0, 15, 3, 2023);
    dt1.AddDays(10);
    EXPECT_EQ(dt1.getDayOfMonth(), 25);
    EXPECT_EQ(dt1.getMonth(), 3);
    EXPECT_EQ(dt1.getYear(), 2023);

    DateTime dt2(0, 25, 3, 2023);
    dt2.AddDays(10);
    EXPECT_EQ(dt2.getDayOfMonth(), 4);
    EXPECT_EQ(dt2.getMonth(), 4);
    EXPECT_EQ(dt2.getYear(), 2023);

    DateTime dt3(0, 15, 6, 2023);
    dt3.AddDays(100);
    EXPECT_EQ(dt3.getDayOfMonth(), 23);
    EXPECT_EQ(dt3.getMonth(), 9);
    EXPECT_EQ(dt3.getYear(), 2023);

    DateTime dt4(0, 15, 12, 2023);
    dt4.AddDays(20);
    EXPECT_EQ(dt4.getDayOfMonth(), 4);
    EXPECT_EQ(dt4.getMonth(), 1);
    EXPECT_EQ(dt4.getYear(), 2024);

    DateTime dt5(0, 15, 3, 2023);
    dt5.AddDays(-10);
    EXPECT_EQ(dt5.getDayOfMonth(), 5);
    EXPECT_EQ(dt5.getMonth(), 3);
    EXPECT_EQ(dt5.getYear(), 2023);

    DateTime dt6(0, 3, 3, 2023);
    dt6.AddDays(-10);
    EXPECT_EQ(dt6.getDayOfMonth(), 21);
    EXPECT_EQ(dt6.getMonth(), 2);
    EXPECT_EQ(dt6.getYear(), 2023);

    DateTime dt7(0, 15, 6, 2023);
    dt7.AddDays(-100);
    EXPECT_EQ(dt7.getDayOfMonth(), 7);
    EXPECT_EQ(dt7.getMonth(), 3);
    EXPECT_EQ(dt7.getYear(), 2023);

    DateTime dt8(0, 5, 1, 2023);
    dt8.AddDays(-10);
    EXPECT_EQ(dt8.getDayOfMonth(), 26);
    EXPECT_EQ(dt8.getMonth(), 12);
    EXPECT_EQ(dt8.getYear(), 2022);

    DateTime dt9(0, 28, 2, 2020);
    dt9.AddDays(1);
    EXPECT_EQ(dt9.getDayOfMonth(), 29);
    EXPECT_EQ(dt9.getMonth(), 2);
    EXPECT_EQ(dt9.getYear(), 2020);

    dt9.AddDays(1);
    EXPECT_EQ(dt9.getDayOfMonth(), 1);
    EXPECT_EQ(dt9.getMonth(), 3);
    EXPECT_EQ(dt9.getYear(), 2020);

    DateTime dt10(0, 1, 3, 2020);
    dt10.AddDays(-1);
    EXPECT_EQ(dt10.getDayOfMonth(), 29);
    EXPECT_EQ(dt10.getMonth(), 2);
    EXPECT_EQ(dt10.getYear(), 2020);

    DateTime dt11(0, 28, 2, 2021);
    dt11.AddDays(1);
    EXPECT_EQ(dt11.getDayOfMonth(), 1);
    EXPECT_EQ(dt11.getMonth(), 3);
    EXPECT_EQ(dt11.getYear(), 2021);
}


// тесты добавления месяцев
TEST(DateTime, AddMonthEdgeCases) {
    DateTime dt1(0, 31, 12, 2023);
    dt1.AddMonth(1);
    EXPECT_EQ(dt1.getYear(), 2024);
    EXPECT_EQ(dt1.getMonth(), 1);
    EXPECT_EQ(dt1.getDayOfMonth(), 31);

    DateTime dt2(0, 1, 1, 2023);
    dt2.AddMonth(-1);
    EXPECT_EQ(dt2.getYear(), 2022);
    EXPECT_EQ(dt2.getMonth(), 12);
    EXPECT_EQ(dt2.getDayOfMonth(), 1);

    DateTime dt3(0, 31, 1, 2023);
    dt3.AddMonth(1);
    EXPECT_EQ(dt3.getMonth(), 2);
    EXPECT_EQ(dt3.getDayOfMonth(), 28);

    DateTime dt4(0, 31, 1, 2020);
    dt4.AddMonth(1);
    EXPECT_EQ(dt4.getMonth(), 2);
    EXPECT_EQ(dt4.getDayOfMonth(), 29);

    DateTime dt5(0, 15, 6, 2022);
    dt5.AddMonth(12);
    EXPECT_EQ(dt5.getYear(), 2023);
    EXPECT_EQ(dt5.getMonth(), 6);
    EXPECT_EQ(dt5.getDayOfMonth(), 15);

    DateTime dt6(0, 10, 3, 2021);
    dt6.AddMonth(18);
    EXPECT_EQ(dt6.getYear(), 2022);
    EXPECT_EQ(dt6.getMonth(), 9);
    EXPECT_EQ(dt6.getDayOfMonth(), 10);

    DateTime dt7(0, 15, 3, 2023);
    dt7.AddMonth(-15);
    EXPECT_EQ(dt7.getYear(), 2021);
    EXPECT_EQ(dt7.getMonth(), 12);
    EXPECT_EQ(dt7.getDayOfMonth(), 15);

    DateTime dt8(0, 29, 2, 2020);
    dt8.AddMonth(12);
    EXPECT_EQ(dt8.getYear(), 2021);
    EXPECT_EQ(dt8.getMonth(), 2);
    EXPECT_EQ(dt8.getDayOfMonth(), 28);

    DateTime dt9(0, 1, 1, 2000);
    dt9.AddMonth(300);
    EXPECT_EQ(dt9.getYear(), 2025);
    EXPECT_EQ(dt9.getMonth(), 1);
    EXPECT_EQ(dt9.getDayOfMonth(), 1);
}


// тесты добавления годов
TEST(DateTime, AddYearsEdgeCases) {
    DateTime dt1(0, 15, 6, 2010);
    dt1.AddYears(5);
    EXPECT_EQ(dt1.getYear(), 2015);
    EXPECT_EQ(dt1.getMonth(), 6);
    EXPECT_EQ(dt1.getDayOfMonth(), 15);

    DateTime dt2(0, 15, 6, 2010);
    dt2.AddYears(-5);
    EXPECT_EQ(dt2.getYear(), 2005);
    EXPECT_EQ(dt2.getMonth(), 6);
    EXPECT_EQ(dt2.getDayOfMonth(), 15);

    DateTime dt3(0, 29, 2, 2020);
    dt3.AddYears(1);
    EXPECT_EQ(dt3.getYear(), 2021);
    EXPECT_EQ(dt3.getMonth(), 2);
    EXPECT_EQ(dt3.getDayOfMonth(), 28);

    DateTime dt4(0, 28, 2, 2020);
    dt4.AddYears(1);
    EXPECT_EQ(dt4.getYear(), 2021);
    EXPECT_EQ(dt4.getMonth(), 2);
    EXPECT_EQ(dt4.getDayOfMonth(), 28);

    DateTime dt5(0, 29, 2, 2020);
    dt5.AddYears(4);
    EXPECT_EQ(dt5.getYear(), 2024);
    EXPECT_EQ(dt5.getMonth(), 2);
    EXPECT_EQ(dt5.getDayOfMonth(), 29);

    DateTime dt6(0, 1, 1, 10);
    EXPECT_THROW(dt6.AddYears(-20), std::runtime_error);
    EXPECT_EQ(dt6.getYear(), 10);

    DateTime dt7(0, 1, 1, 2023);
    dt7.AddYears(1000);
    EXPECT_EQ(dt7.getYear(), 3023);
    EXPECT_EQ(dt7.getMonth(), 1);
    EXPECT_EQ(dt7.getDayOfMonth(), 1);

    DateTime dt8(0, 1, 1, 2023);
    EXPECT_THROW(dt8.AddYears(-2023), std::runtime_error);
    EXPECT_EQ(dt8.getYear(), 2023);
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

    EXPECT_NO_THROW(dt.setDayOfMonth(28));
    // февраль в високосный год
    dt.setYear(2020);
    dt.setMonth(2);
    EXPECT_NO_THROW(dt.setDayOfMonth(29));
    // февраль в невисокосный год
    EXPECT_NO_THROW(dt.setDayOfMonth(28));
    dt.setYear(2021);
    EXPECT_THROW(dt.setDayOfMonth(29), std::runtime_error);
    // месяцы с 30 днями
    dt.setMonth(4);
    EXPECT_NO_THROW(dt.setDayOfMonth(30));
    EXPECT_THROW(dt.setDayOfMonth(31), std::runtime_error);
    EXPECT_NO_THROW(dt.setDayOfMonth(30));

    dt.setMonth(6);
    EXPECT_NO_THROW(dt.setDayOfMonth(30));
    EXPECT_THROW(dt.setDayOfMonth(31), std::runtime_error);
    EXPECT_NO_THROW(dt.setDayOfMonth(30));

    dt.setMonth(9);
    EXPECT_NO_THROW(dt.setDayOfMonth(30));
    EXPECT_THROW(dt.setDayOfMonth(31), std::runtime_error);
    EXPECT_NO_THROW(dt.setDayOfMonth(30));

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
    EXPECT_NO_THROW(dt.setYear(1));
    EXPECT_THROW(dt.setYear(0), std::runtime_error);     // Год 0
    EXPECT_THROW(dt.setYear(-100), std::runtime_error);  // отрицательные годы

    dt.setYear(2020);
    dt.setMonth(2);
    dt.setDayOfMonth(29);

    // високосный -> високосный
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
    EXPECT_NO_THROW(dt.setMonth(5));
    // невалидная последовательность
    EXPECT_NO_THROW(dt.setDayOfMonth(31));
    EXPECT_THROW(dt.setMonth(4), std::runtime_error);  // в апреле меньше дней

    // корректировка после ошибки
    EXPECT_EQ(dt.getMonth(), 5);
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

// тесты операторов сравнения
TEST(DateTimeOperators, Comparison)
{
    DateTime a(0, 15, 7, 2025);      // 15.07.2025 00:00:00
    DateTime b(0, 15, 7, 2025);      // то же самое
    DateTime c(3600, 16, 7, 2025);   // на 1 день + 1 час позже

    EXPECT_TRUE (a == b);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE (c >  b);
    EXPECT_FALSE (a >  b);
    EXPECT_TRUE (b <  c);
    EXPECT_TRUE (b <= a);
    EXPECT_TRUE (c >= a);
}

// тесты сложения секунд
TEST(DateTimeOperators, ArithmeticSeconds)
{
    DateTime base(0, 31, 12, 2023);
    DateTime next = base + 86'400;
    EXPECT_EQ(next.getYear(),  2024);
    EXPECT_EQ(next.getMonth(), 1);
    EXPECT_EQ(next.getDayOfMonth(), 1);
    EXPECT_EQ(next.getSecondsInDay(), 0);

    DateTime prev = next - 90;
    EXPECT_EQ(prev.getYear(),  2023);
    EXPECT_EQ(prev.getMonth(), 12);
    EXPECT_EQ(prev.getDayOfMonth(), 31);
    EXPECT_EQ(prev.getSecondsInDay(), 86'310);

    DateTime base2(0, 31, 12, 2023);
    DateTime next2 = base2 - 86'400 * 2;
    EXPECT_EQ(next2.getYear(),  2023);
    EXPECT_EQ(next2.getMonth(), 12);
    EXPECT_EQ(next2.getDayOfMonth(), 29);
    EXPECT_EQ(next2.getSecondsInDay(), 0);
}

// тесты сложения дат
TEST(DateTimeOperators, ArithmeticInterval)
{
    DateTime base(0,  1,  1, 2020);
    DateTime interval(3'600, 2, 1, 1);

    DateTime shifted = base + interval;
    EXPECT_EQ(shifted.getYear(),  2020);
    EXPECT_EQ(shifted.getMonth(), 1);
    EXPECT_EQ(shifted.getDayOfMonth(), 2);
    EXPECT_EQ(shifted.getSecondsInDay(), 3'600);
}

// тесты разности дат
TEST(DateTimeOperators, DifferenceInSeconds)
{
    DateTime earlier(0,  1, 1, 2020);
    DateTime later  (0,  2, 1, 2020);

    long long diff = later - earlier;
    EXPECT_EQ(diff, 86'400);

    // проверяем знак
    EXPECT_EQ(earlier - later, -86'400);

    DateTime earlier2(0, 28, 2, 2020);
    DateTime later2(1000, 1, 3, 2020);

    long long diff2 = later2 - earlier2;
    EXPECT_EQ(diff2, 86'400 * 2 + 1000);

    // проверяем знак
    EXPECT_EQ(earlier2 - later2, -86'400 * 2 - 1000);


    DateTime earlier3(0, 28, 2, 2020);
    DateTime later3(1000, 1, 3, 2021);

    long long diff3 = later3 - earlier3;
    EXPECT_EQ(diff3, 86'400 * 367 + 1000);

    // проверяем знак
    EXPECT_EQ(earlier3 - later3, -86'400 * 367 - 1000);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
