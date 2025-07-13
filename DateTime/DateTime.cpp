#include "DateTime.h"
#include <iomanip>
#include <sstream>


const int DateTime::daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


long long DateTime::daysSinceCivil(int y, int m, int d) 
{
    y -= m <= 2; // Год начинается с марта
    const int era = (y >= 0 ? y : y - 399) / 400; // Эра (400-летний цикл)
    const unsigned yoe = static_cast<unsigned>(y - era * 400); // Год в эре
    const unsigned doy = (153*(m + (m > 2 ? -3 : 9)) + 2)/5 + d - 1; // День в году (от марта)
    const unsigned doe = yoe*365 + yoe/4 - yoe/100 + doy; // День в эре (от 0000-03-01)
    return era*146097LL + static_cast<long long>(doe) - 306; // Коррекция для 01.01.0001
}
long long DateTime::operator-(const DateTime& other) const
{
    long long days = daysSinceCivil(this->year, this->month, this->dayOfMonth) - daysSinceCivil(other.year, other.month, other.dayOfMonth);

    return days*86400LL + static_cast<long long>(this->secondsInDay) - other.secondsInDay;
}



bool DateTime::isLeapYear(const int& _year) const {
    if (year < 0)
        throw std::runtime_error("Invalid year");
    return ((_year % 400 == 0) || (_year % 100 != 0 && _year % 4 == 0));
}
bool DateTime::Validate() const {
    if (daysSinceCivil(year, month, dayOfMonth) < daysSinceCivil(1, 1, 1))
        return false;
    
    if (month < 1 || month > 12) 
        return false;
    if (dayOfMonth < 1) 
        return false;

    if (month == 2) {
        if (isLeapYear(year)) 
        {
            if (dayOfMonth > 29)
                return false;
        } 
        else 
        {
            if (dayOfMonth > 28) 
                return false;
        }
    } 
    else 
    {
        if (dayOfMonth > daysInMonth[month]) 
            return false;
    }

    return true;
}
bool DateTime::isEqual(const DateTime& a, const DateTime& b) {
    return a.secondsInDay == b.secondsInDay && a.dayOfMonth == b.dayOfMonth && a.month == b.month && a.year == b.year;
}
bool DateTime::operator==(const DateTime& other) const
{
    return (isEqual(*this, other));
}
bool DateTime::operator!=(const DateTime& other) const
{
    return !(*this == other);
}
bool DateTime::operator<(const DateTime& other) const
{
    if (this->year != other.year)
        return this->year < other.year;
    if (this->month != other.month)
        return this->month < other.month;
    if (this->dayOfMonth != other.dayOfMonth)
        return this->dayOfMonth < other.dayOfMonth;
    
    return this->secondsInDay < other.secondsInDay;
}
bool DateTime::operator>(const DateTime& other) const
{
    return other < *this;
}
bool DateTime::operator>=(const DateTime& other) const
{
    return !(*this < other);
}
bool DateTime::operator<=(const DateTime& other) const
{
    return !(*this > other);
}



DateTime::DateTime(time_t unixTime) : secondsInDay(0), dayOfMonth(1), month(1), year(1970) {
    convertFromUnix(unixTime);
}
DateTime::DateTime(DateTime&& other) : secondsInDay(other.secondsInDay), dayOfMonth(other.dayOfMonth), month(other.month), year(other.year) 
{

}
DateTime::DateTime(int Sec, int Day, int Month, int Year) {
    if (daysSinceCivil(Year, Month, Day) < daysSinceCivil(1, 1, 1))
        throw std::runtime_error("Date cannot be before 01.01.0001");

    if (Sec < 0 || Sec > 86399)
        throw std::runtime_error("Invalid second");

    secondsInDay = Sec;
    int maxDay = daysInMonth[Month];
    if (Month == 2 && isLeapYear(Year)) {
        maxDay = 29;
    }

    if (Day < 1 || Day > maxDay)
        throw std::runtime_error("Invalid day");

    dayOfMonth = Day;
    if (Month < 1 || Month > 12)
        throw std::runtime_error("Invalid month");

    month = Month;
    year = Year;
}
DateTime::DateTime(int Day, int Month, int Year, int Hour, int Min, int Sec)
{
    if (daysSinceCivil(Year, Month, Day) < daysSinceCivil(1, 1, 1))
        throw std::runtime_error("Date cannot be before 01.01.0001");
    
    Sec = Sec + Min * 60 + Hour * 3600;
    if (Sec < 0 || Sec > 86399)
        throw std::runtime_error("Invalid second");

    secondsInDay = Sec;
    int maxDay = daysInMonth[Month];
    if (Month == 2 && isLeapYear(Year)) {
        maxDay = 29;
    }

    if (Day < 1 || Day > maxDay)
        throw std::runtime_error("Invalid day");

    dayOfMonth = Day;
    if (Month < 1 || Month > 12)
        throw std::runtime_error("Invalid month");

    month = Month;
    year = Year;
}



int DateTime::getSecondsInDay() const
{
    return secondsInDay;
}
int DateTime::getDayOfMonth() const
{
    return dayOfMonth;
}
int DateTime::getMonth() const
{
    return month;
}
int DateTime::getYear() const
{
    return year;
}
int DateTime::DayofWeek() const // алгоритм Зеллера
{
    int h, m = month, y = year;
    if (m < 3)
    {
        m += 12;
        --y;
    }

    // Формула Зеллера (0 - суббота, 1 - воскресенье, ..., 6 - пятница)
    h = (dayOfMonth + (13 * (m + 1)) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    return h;
}
int DateTime::getDaysInCurrentMonth() const
{
    if (month == 2 && isLeapYear(year))
        return 29;
    return daysInMonth[month];
}



void DateTime::setSecondsInDay(int Sec)
{
    if (Sec < 0 || Sec > 86399)
        throw std::runtime_error("Invalid second");
    secondsInDay = Sec;
}
void DateTime::setDayOfMonth(int Day)
{
    if (Day < 1 || Day > 31)
        throw std::runtime_error("Invalid day");
    int tmpdayOfMonth = dayOfMonth;
    dayOfMonth = Day;
    if (!Validate()) {
        dayOfMonth = tmpdayOfMonth;
        throw std::runtime_error("Invalid date");
    }
}
void DateTime::setMonth(int Month)
{
    if (Month < 1 || Month > 12)
        throw std::runtime_error("Invalid month");
    int tmpMonth = month;
    month = Month;
    if (!Validate()) {
        month = tmpMonth;
        throw std::runtime_error("Invalid date");
    }
}
void DateTime::setYear(int Year) 
{
    if (Year < 0)
        throw std::runtime_error("Invalid year");
    int tmpYear = year;
    year = Year;
    if (!Validate()) {
        year = tmpYear;
        throw std::runtime_error("Invalid date");
    }
}
void DateTime::convertFromUnix(time_t seconds) 
{
    int days = seconds / 86400;
    AddDays(days);

    secondsInDay = seconds % 86400;

    if (!Validate())
        throw std::runtime_error("Invalid date after UNIX time convertation");
}
void DateTime::AddSeconds(long long S)
{
    long long total =static_cast<long long>(secondsInDay) + S;
    
    long long days = total / 86400;
    long long sec = total % 86400;
    if(sec < 0){
        sec+=86400;
        --days;
    }

    secondsInDay = static_cast<int>(sec);
    if(days != 0) AddDays(static_cast<int>(days));
}
void DateTime::AddDays(int N)
{
    if (N == 0)
        return;
    long long currentDays = daysSinceCivil(year, month, dayOfMonth);
    long long newDays = currentDays + N;

    if (newDays < 1)
        throw std::runtime_error("Cannot go below 01.01.0001");
    
    if (N > 0) 
    {
        while (N > 0) 
        {
            int daysInMonth = getDaysInCurrentMonth();
            int daysRemaining = daysInMonth - dayOfMonth + 1;
            int daysToAdd = N < daysRemaining ? N : daysRemaining;

            dayOfMonth += daysToAdd;
            N -= daysToAdd;

            if (dayOfMonth > daysInMonth) 
            {
                dayOfMonth = 1;
                AddMonth(1);
            }
        }
    }
    else 
    {
        while (N < 0) 
        {
            if (dayOfMonth + N > 0) 
            {
                dayOfMonth += N;
                N = 0;
            }
            else 
            {
                N += dayOfMonth;
                AddMonth(-1);
                dayOfMonth = getDaysInCurrentMonth();
            }
        }
    }

    if (!Validate())
        throw std::runtime_error("Invalid date after AddDays operation");
}
void DateTime::AddMonth(int M)
{
    if (M == 0)
        return;

    int totalMonth = month + M;
    int yearsToAdd = (totalMonth - 1) / 12;
    int newMonth = (totalMonth - 1) % 12 + 1;
    
    if (year + yearsToAdd < 1)
        throw std::runtime_error("Cannot go below year 1 (01.01.0001)");

    if (newMonth < 1) 
    {
        newMonth += 12;
        AddYears(-1);
    }
    month = newMonth;
    AddYears(yearsToAdd);    

    // Проверяем не переполнен ли наш месяц.
    int maxDays =  getDaysInCurrentMonth();

    if (dayOfMonth > maxDays)
        dayOfMonth = maxDays;

    if (!Validate())
        throw std::runtime_error("Invalid date after AddMonth operation");
}
void DateTime::AddYears(int Y) 
{
    if (Y == 0)
        return;

    int newYear = year + Y;
    
    if (newYear < 1)
        throw std::runtime_error("Cannot go below year 1 (01.01.0001)");
    
    year = newYear;
    if (month == 2 && dayOfMonth == 29 && !isLeapYear(year)) 
        dayOfMonth = 28;
    
    int maxDays =  getDaysInCurrentMonth();
    if (dayOfMonth > maxDays)
        dayOfMonth = maxDays;

    if (!Validate())
        throw std::runtime_error("Invalid date after AddYear operation");
}



std::string DateTime::DayofWeekName() const
{
    const char* names[] = { "Суббота", "Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница" };
    return names[DayofWeek()];
}


std::string DateTime::ToString() const {
    int totalSeconds = secondsInDay;
        int hours = totalSeconds / 3600;
        int minutes = (totalSeconds % 3600) / 60;
        int seconds = totalSeconds % 60;

        std::ostringstream oss;

        oss << std::setfill('0') << std::setw(2) << dayOfMonth << '-' << std::setw(2) << month << '-';

        if (year < 10000) {
            oss << std::setw(4) << year;
        } else {
            oss << year;
        }

        oss << ' ' << std::setw(2) << hours << ':' << std::setw(2) << minutes << ':' << std::setw(2) << seconds;

        return oss.str();
}



DateTime DateTime::get_Now() {
    time_t now = time(0);
    return DateTime(now);
}


DateTime DateTime::operator+(const DateTime& other) const
{
    long long days = daysSinceCivil(other.year, other.month, other.dayOfMonth) - daysSinceCivil(1, 1, 1);
    DateTime res(*this);
    res.AddDays(static_cast<int>(days));
    res.AddSeconds(other.secondsInDay);
    return res;
}
DateTime DateTime::operator+(long long seconds) const
{
    DateTime res(*this);
    res.AddSeconds(seconds);
    return res;
}
DateTime DateTime::operator-(long long seconds) const
{
    return *this + (-seconds);
}
