#include "DateTime.h"


const int DateTime::daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


void DateTime::convertFromUnix(time_t seconds) {
    int days = seconds / 86400;
    std::cout << "FUCK: " << days << "\n";
    AddDays(days);

    secondsInDay = seconds % 86400;

    if (!Validate())
        throw std::runtime_error("Invalid date after UNIX time convertation");
}


bool DateTime::isLeapYear() const {
    return ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0));
}


bool DateTime::Validate() const { return true; }


DateTime::DateTime(time_t unixTime) : year(1970), month(1), dayOfMonth(1), secondsInDay(0) {
    convertFromUnix(unixTime);
}


DateTime::DateTime(DateTime&& other) : secondsInDay(other.secondsInDay), dayOfMonth(other.dayOfMonth), month(other.month), year(other.year) {}


DateTime::DateTime(int Sec, int Day, int Month, int Year) {
    if (Sec < 0 || Sec > 86399) {
        throw std::runtime_error("Invalid second");
    }
    secondsInDay = Sec;
    
    bool isLeapYear = (Year % 400 == 0) || (Year % 100 != 0 && Year % 4 == 0);
    int maxDay = daysInMonth[Month];

    if (Month == 2 && isLeapYear) {
        maxDay = 29;
    }
    //std::cout << "FUCK: " << maxDay << ", " << Month << ", " << isLeapYear << "\n";
    if (Day < 1 || Day > maxDay) {
        throw std::runtime_error("Invalid day");
    }
    dayOfMonth = Day;
    if (Month < 1 || Month > 12) {
        throw std::runtime_error("Invalid month");
    }
    month = Month;
    year = Year;
}


int DateTime::getSecondsInDay() const {
    return secondsInDay; 
}


int DateTime::getDayOfMonth() const {
    return dayOfMonth; 
}


int DateTime::getMonth() const {
    return month; 
}


int DateTime::getYear() const {
    return year; 
}


void DateTime::setSecondsInDay(int Sec) {
    if (Sec < 0 || Sec > 86399)
      throw std::runtime_error("Invalid second");
    secondsInDay = Sec;
}


void DateTime::setDayOfMonth(int Day) {
    if (Day < 1 || Day > 31) 
        throw std::runtime_error("Invalid day");
    dayOfMonth = Day; 
    if (!Validate())
        throw std::runtime_error("Invalid date");
}


void DateTime::setMonth(int Month) {
    if (Month < 1 || Month > 12)
        throw std::runtime_error("Invalid month");
    month = Month;
}


void DateTime::setYear(int Year) {
    year = Year; 
}


bool DateTime::isEqual(const DateTime& a, const DateTime& b) { return true; }


void DateTime::AddDays(int N) {
    if (N == 0)
    return;

    if (N > 0)
        while (N > 0)
        {
            int maxDays = daysInMonth[month], daysToAdd;
            if (month == 2 && isLeapYear())
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
            std::cout << "INNER: " << N << "\n";
        }
    else
        while (N < 0)
            if (dayOfMonth + N > 0)
            {
                dayOfMonth += N;
                N = 0;
            } 
            else
            {
                AddMonth(-1);
                int maxDays = daysInMonth[month];

                if (month == 2 && isLeapYear())
                    maxDays = 29;
                
                N += dayOfMonth;
                dayOfMonth = maxDays;
            }

    
    std::cout << "FINAL: " << secondsInDay << ", " << dayOfMonth << ", " << month << ", " << year << "\n";
    
    if (!Validate())
        throw std::runtime_error("Invalid date after AddDays operation");
    
    std::cout << "FINAL: " << secondsInDay << ", " << dayOfMonth << ", " << month << ", " << year << "\n";
    
}


void DateTime::AddMonth(int M) 
{
    if (M == 0)
        return;

    int sign = M > 0 ? 1 : -1;
    M = sign * M;

    while (M != 0)
        if (M > 12)
        {
            AddYears(sign);
            M -= 12;
        } 
        else
        {
            month += sign * M;
            M = 0;
            if (month <= 0)
            {
                AddYears(-1);
                month += 12;
            } 
            else if (month >= 13)
            {
                AddYears(1);
                month -= 12;
            }
        }

    // Проверяем не переполнен ли наш месяц.
    int maxDays = daysInMonth[month];
    if (month == 2 && isLeapYear())
        maxDays = 29;

    if (dayOfMonth > maxDays)
        dayOfMonth = maxDays;
    
    if (!Validate())
        throw std::runtime_error("Invalid date after AddMonth operation");
}


void DateTime::AddYears(int Y) {}

// алгоритм Зеллера
int DateTime::DayofWeek() const
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


std::string DateTime::DayofWeekName() const
{
    const char* names[] = {"Суббота", "Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница"};
    return names[DayofWeek()];
}


DateTime DateTime::get_Now() { return DateTime(); }


std::string DateTime::ToString() const {
    std::string result(16, ' ');
    result[0] = '0' + (year / 1000) % 10;
    result[1] = '0' + (year / 100) % 10;
    result[2] = '0' + (year / 10) % 10;
    result[3] = '0' + year % 10;
    result[4] = '-';
    result[5] = '0' + (month / 10) % 10;
    result[6] = '0' + month % 10;
    result[7] = '-';
    result[8] = '0' + (dayOfMonth / 10) % 10;
    result[9] = '0' + dayOfMonth % 10;
    result[10] = '-';
    result[11] = '0' + (secondsInDay / 10000) % 10;
    result[12] = '0' + (secondsInDay / 1000) % 10;
    result[13] = '0' + (secondsInDay / 100) % 10;
    result[14] = '0' + (secondsInDay / 10) % 10;
    result[15] = '0' + secondsInDay % 10;
    return result;
}

