#include "DateTime.h"


const int DateTime::daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


long long DateTime::daysSinceCivil(int y, int m, int d)
{
    y-= m <= 2; //считаем год с марта - так проще високосность смотреть
    const int era = (y >= 0 ? y : y-399) / 400; // делим на блоки по 400
    const unsigned yoe = static_cast<unsigned>(y - era * 400); // year of era
    const unsigned doy = (153*(m + (m > 2 ? -3 : 9)) + 2)/5 + d - 1; // day of year
    const unsigned doe = yoe*365 + yoe/4 - yoe/100 + doy; // day of era
    return era*146097LL + static_cast<long long>(doe);
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
DateTime::DateTime(int Sec, int Day, int Month, int Year) : year(Year) {
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
void DateTime::AddSeconds(long long S) {
    if (year == 1 && month == 1 && dayOfMonth == 1) {
        long long total_seconds = static_cast<long long>(secondsInDay) + S;
        if (total_seconds < 0) {
            secondsInDay = 0;
            throw std::runtime_error("Cannot go before 01.01.0001");
        }
    }

    long long total_seconds = static_cast<long long>(secondsInDay) + S;
    long long days = total_seconds / 86400;
    int remaining_sec = static_cast<int>(total_seconds % 86400);

    if (remaining_sec < 0) {
        remaining_sec += 86400;
        days--;
    }

    secondsInDay = remaining_sec;
    
    if (days != 0) {
        const int max_safe_days = INT_MAX / 2;
        while (days > max_safe_days) {
            AddDays(max_safe_days);
            days -= max_safe_days;
            if (year == 1 && month == 1 && dayOfMonth == 1 && days < 0)
                throw std::runtime_error("Cannot go before 01.01.0001");
        }
        while (days < -max_safe_days) 
        {
            AddDays(-max_safe_days);
            days += max_safe_days;

            if (year == 1 && month == 1 && dayOfMonth == 1)
            {
                if (secondsInDay == 0 && days < 0)
                {
                    throw std::runtime_error("Cannot go before 01.01.0001");
                }
                break;
            }
        }
        

        if (days != 0) 
        {
            AddDays(static_cast<int>(days));

            if (year == 1 && month == 1 && dayOfMonth == 1 && secondsInDay == 0)
                throw std::runtime_error("Cannot go before 01.01.0001");
        }
    }
}
void DateTime::AddDays(int N)
{
    if (N == 0)
        return;
    long long currentDays = daysSinceCivil(year, month, dayOfMonth);
    long long newDays = currentDays + N;

    if (newDays < daysSinceCivil(1, 1, 1))
        throw std::runtime_error("Cannot go below 01.01.0001");
    
    if (N > 0) 
    {
        while (N > 0) 
        {
            int daysInMonth = getDaysInCurrentMonth();
            int daysRemaining = daysInMonth - dayOfMonth + 1;
            int daysToAdd = std::min(N, daysRemaining);

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

    month = newMonth;
    AddYears(yearsToAdd);

    // Проверяем не переполнен ли наш месяц.
    int maxDays = getDaysInCurrentMonth();

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
    std::string result(25, ' ');
    result[0] = '0' + (hours / 10) % 10;
    result[1] = '0' + hours % 10;
    result[2] = ':';
    result[3] = '0' + (minutes / 10) % 10;
    result[4] = '0' + minutes % 10;
    result[5] = ':';
    result[6] = '0' + (seconds / 10) % 10;
    result[7] = '0' + seconds % 10;
    result[8] = ' ';
    result[9] = '0' + (dayOfMonth / 10) % 10;
    result[10] = '0' + dayOfMonth % 10;
    result[11] = '-';
    result[12] = '0' + (month / 10) % 10;
    result[13] = '0' + month % 10;
    result[14] = '-';
    result[15] = '0' + (year / 1000) % 10;
    result[16] = '0' + (year / 100) % 10;
    result[17] = '0' + (year / 10) % 10;
    result[18] = '0' + year % 10;
    result[19] = ' ';
    result[20] = '0' + (secondsInDay / 10000) % 10;
    result[21] = '0' + (secondsInDay / 1000) % 10;
    result[22] = '0' + (secondsInDay / 100) % 10;
    result[23] = '0' + (secondsInDay / 10) % 10;
    result[24] = '0' + secondsInDay % 10;
    return result;
}



DateTime DateTime::get_Now() 
{ 
    return DateTime(); 
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
