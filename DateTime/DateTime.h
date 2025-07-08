#pragma once
#include <iostream>
#include <string>

class DateTime
{
  int secondsInDay : 18;
  int dayOfMonth : 6;
  int month : 5;
  int year : 17;

  bool Validate() const;
public:
  DateTime();

  int getSecondsInDay() const;
  int getDayOfMonth() const;
  int getMonth() const;
  int getYear() const;
  void setSecondsInDay(int Sec);
  void setDayOfMonth(int Day);
  void setMonth(int Month);
  void setYear(int Year);

  static bool isEqual(const DateTime& a, const DateTime& b);

  void AddDays(int N);

  void AddMonth(int M);

  void AddYears(int Y);

  int DayofWeek();

  DateTime get_Now();

  std::string ToString() const;
};

