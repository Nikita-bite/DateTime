#pragma once
#include <iostream>
#include <string>

class DateTime
{
  int secondsInDay : 18;
  int dayOfMonth : 6;
  int month : 5;
  int year : 17;
  // Настя
  bool Validate() const;
public:
  // Егор
  DateTime();
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
  // Илья Б.
  void AddDays(int N);
  // Егор
  void AddMonth(int M);
  // Настя
  void AddYears(int Y);
  // Илья Б.
  int DayofWeek();

  // Никита
  DateTime get_Now();

  std::string ToString() const;
};

