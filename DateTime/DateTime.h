#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

class DateTime
{
  static const int daysInMonth[13];

  int secondsInDay : 18;
  int dayOfMonth : 7;
  int month : 6;
  int year : 17;
  
  // Конвертирует Unix дату
  void convertFromUnix(time_t seconds);
  // Проверка является ли текущий год високосным
  bool isLeapYear() const;
  // Настя
  bool Validate() const;
public:
  // Егор
  DateTime(time_t unixTime = 0);
  DateTime(DateTime&& other);
  DateTime(int Sec, int Day, int Month, int Year);
  // Илья Х.
  int getSecondsInDay() const;
  int getDayOfMonth() const;
  int getMonth() const;
  int getYear() const;
  void setSecondsInDay(int Sec);
  void setDayOfMonth(int Day);
  void setMonth(int Month);
  void setYear(int Year);
  // Илья Х.
  static bool isEqual(const DateTime& a, const DateTime& b);
  static bool isLeapYear(int year);
  // Илья Б.
  void AddDays(int N);
  // Егор
  void AddMonth(int M);
  // Настя
  void AddYears(int Y);
  // Илья Б.
  int DayofWeek() const;
  std::string DayofWeekName() const;

  // Никита
  DateTime get_Now();

  std::string ToString() const;
};

