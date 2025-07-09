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
	bool isLeapYear(const int& _year) const;
	// Настя
	bool Validate() const;
  //Илья Х.
   void AddSeconds(long long S);

public:
	// Егор
	DateTime(time_t unixTime = 0);
	DateTime(DateTime&& other);
  DateTime(const DateTime& other) = default;
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

  //Илья Х.
  // друзья)
  bool operator==(const DateTime& other) const;
  bool operator!=(const DateTime& other) const;
  bool operator>=(const DateTime& other) const;
  bool operator<=(const DateTime& other) const;
  bool operator>(const DateTime& other) const;
  bool operator<(const DateTime& other) const;

  friend DateTime operator+(const DateTime& a, long long seconds);
  friend DateTime operator-(const DateTime& a, long long seconds);
  friend DateTime operator+(const DateTime& a, const DateTime& interval);
  friend long long operator-(const DateTime& a, const DateTime& b);
};
/*

ПЕРЕД ЗАПУСКОМ ПРОГРАММЫ В ТЕРМИНАЛЕ ВЫПОЛНИТЬ:

cd .. 
...\DateTime> после выполнения команды cd .. конечный путь в терминале должен быть таким 
.\setup_keys.bat
Надо перезапустить VS Code
после этого работает команда ctrl+shift+t

*/