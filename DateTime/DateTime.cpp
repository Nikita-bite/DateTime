#include "DateTime.h"

bool DateTime::Validate() const { return true; }

DateTime::DateTime() : secondsInDay(0), dayOfMonth(1), month(1), year(2000) {}

int DateTime::getSecondsInDay() const { return secondsInDay; }
int DateTime::getDayOfMonth() const { return dayOfMonth; }
int DateTime::getMonth() const { return month; }
int DateTime::getYear() const { return year; }
void DateTime::setSecondsInDay(int Sec) { secondsInDay = Sec; }
void DateTime::setDayOfMonth(int Day) { dayOfMonth = Day; }
void DateTime::setMonth(int Month) { month = Month; }
void DateTime::setYear(int Year) { year = Year; }

bool DateTime::isEqual(const DateTime& a, const DateTime& b) { return true; }

void DateTime::AddDays(int N) {}
void DateTime::AddMonth(int M) {}
void DateTime::AddYears(int Y) {}

int DateTime::DayofWeek() { return 0; }

DateTime DateTime::get_Now() { return DateTime(); }

std::string DateTime::ToString() const { return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(dayOfMonth) + "-" + std::to_string(secondsInDay); }
