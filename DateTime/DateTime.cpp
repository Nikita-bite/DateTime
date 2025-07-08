#include "DateTime.h"

const int DateTime::daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

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

void DateTime::AddDays(int N) 
{
    if (N == 0)
    return;

    if (N > 0)
        while (N > 0)
        {
            int maxDays = daysInMonth[month], daysToAdd;
            if (month == 2 && ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0)))
                maxDays = 29;

            if (N > maxDays - dayOfMonth + 1)
                daysToAdd = maxDays - dayOfMonth + 1;
            else
                daysToAdd = N;
            
            dayOfMonth += daysToAdd;
            N -= daysToAdd;

            if (dayOfMonth > maxDays)
            {
                dayOfMonth = 1;
                AddMonth(1);
            }
        }
    else
        while (N < 0)
        {
            if (dayOfMonth + N > 0)
            {
                dayOfMonth += N;
                N = 0;
            } 
            else
            {
                AddMonth(-1);
                int maxDays = daysInMonth[month];

                if (month == 2 && ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0)))
                    maxDays = 29;
                
                N += dayOfMonth;
                dayOfMonth = maxDays;
            }
        }

    if (!Validate())
        throw std::runtime_error("Invalid date after AddDays operation");
    
}
void DateTime::AddMonth(int M) {}
void DateTime::AddYears(int Y) {}

int DateTime::DayofWeek() { return 0; }

DateTime DateTime::get_Now() { return DateTime(); }

std::string DateTime::ToString() const { return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(dayOfMonth) + "-" + std::to_string(secondsInDay); }
