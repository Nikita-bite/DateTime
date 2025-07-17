#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <climits>
class DateTime
{
  static const int daysInMonth[13];

  int secondsInDay : 18;
  int dayOfMonth : 7;
  int month : 6;
  int year : 20;

  //Алгоритм Хиннанта (дней от 1.01.0001 до заданной даты);
  //Смысл: поделить год на блоки по 400 лет (один цикл григорианского календаря),
  //год начинается с марта, далее находим номер дня в пределах года и считаем общее количество дней от эпохи.
  //static long long daysSinceCivil(int y, int m, int d);
  static long long daysSinceCivil(int y, int m, int d);
  void civilFromDays(long long Days);
    
  int getDaysInCurrentMonth() const;
    
  // Конвертирует Unix дату
  void convertFromUnix(time_t seconds);
    
  // Проверка является ли текущий год високосным
  bool isLeapYear(const int& _year) const;
  bool Validate() const;

  void AddSeconds(long long S);

public:
  DateTime(time_t unixTime = 0);
  DateTime(DateTime&& other);
  DateTime(const DateTime& other) = default;
  DateTime(int Sec, int Day, int Month, int Year);
  DateTime(int Day, int Month, int Year, int Hour, int Min, int Sec);
  DateTime(std::string DATE);
  DateTime& operator=(const DateTime& other) = default;
  DateTime get_Now();  
  DateTime operator+(const DateTime& other) const;
  DateTime operator+(long long seconds) const;
  DateTime operator-(long long seconds) const;



  int getSecondsInDay() const;
  int getDayOfMonth() const;
  int getMonth() const;
  int getYear() const;
  int DayofWeek() const;      // алгоритм Зеллера
  long long operator-(const DateTime& other) const;



  void setSecondsInDay(int Sec);
  void setDayOfMonth(int Day);
  void setMonth(int Month);
  void setYear(int Year);
  void AddDays(int N);
  void AddMonth(int M);
  void AddYears(int Y);
  

  
  static bool isEqual(const DateTime& a, const DateTime& b);
  bool operator==(const DateTime& other) const;
  bool operator!=(const DateTime& other) const;
  bool operator>=(const DateTime& other) const;
  bool operator<=(const DateTime& other) const;
  bool operator>(const DateTime& other) const;
  bool operator<(const DateTime& other) const;

  
  
  std::string DayofWeekName() const;
  std::string ToString() const;
};