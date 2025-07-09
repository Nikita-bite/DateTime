#include "DateTime.h"


const int DateTime::daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


void DateTime::convertFromUnix(time_t seconds) {
    int days = seconds / 86400;
    AddDays(days);

    secondsInDay = seconds % 86400;

    if (!Validate())
        throw std::runtime_error("Invalid date after UNIX time convertation");
}


bool DateTime::isLeapYear(const int& _year) const {
    if (year < 0)
        throw std::runtime_error("Invalid year");
    return ((_year % 400 == 0) || (_year % 100 != 0 && _year % 4 == 0));
}


bool DateTime::Validate() const {
    if (year < 1) return false;
    if (month < 1 || month > 12) return false;
    if (dayOfMonth < 1) return false;

    if (month == 2) {
        if (isLeapYear(year)) {
            if (dayOfMonth > 29) return false;
        } else {
            if (dayOfMonth > 28) return false;
        }
    } else {
        if (dayOfMonth > daysInMonth[month]) return false;
    }

    return true;
}


DateTime::DateTime(time_t unixTime) : secondsInDay(0), dayOfMonth(1), month(1), year(1970) {
    convertFromUnix(unixTime);
}


DateTime::DateTime(DateTime&& other) : secondsInDay(other.secondsInDay), dayOfMonth(other.dayOfMonth), month(other.month), year(other.year) {}


DateTime::DateTime(int Sec, int Day, int Month, int Year) : year(Year) {
    if (Sec < 0 || Sec > 86399) {
        throw std::runtime_error("Invalid second");
    }
    secondsInDay = Sec;
    int maxDay = daysInMonth[Month];
    if (Month == 2 && isLeapYear(Year)) {
        maxDay = 29;
    }

    if (Day < 1 || Day > maxDay) {
        throw std::runtime_error("Invalid day");
    }
    dayOfMonth = Day;
    if (Month < 1 || Month > 12) {
        throw std::runtime_error("Invalid month");
    }
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


bool DateTime::isEqual(const DateTime& a, const DateTime& b) {
    return a.secondsInDay == b.secondsInDay && a.dayOfMonth == b.dayOfMonth && a.month == b.month && a.year == b.year;
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
    int tmpMonth = month;
    int tmpDay = dayOfMonth;
    if (N == 0)
        return;

    if (N > 0)
        while (N > 0)
        {
            int maxDays = daysInMonth[month], daysToAdd;
            if (month == 2 && isLeapYear(year))
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
            if (dayOfMonth + N > 0)
            {
                dayOfMonth += N;
                N = 0;
            }
            else
            {
                AddMonth(-1);
                int maxDays = daysInMonth[month];

                if (month == 2 && isLeapYear(year))
                    maxDays = 29;

                N += dayOfMonth;
                dayOfMonth = maxDays;
            }

    if (!Validate()){
        month = tmpMonth;
        dayOfMonth = tmpDay;
        throw std::runtime_error("Invalid date after AddDays operation");
    }

}
void DateTime::AddMonth(int M)
{
    int tmpMonth = month;
    int tmpYear = year;
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
                month += 12;
                AddYears(-1);
            }
            else if (month >= 13)
            {
                month -= 12;
                AddYears(1);
            }
        }

    // Проверяем не переполнен ли наш месяц.
    int maxDays = daysInMonth[month];
    if (month == 2 && isLeapYear(year))
        maxDays = 29;

    if (dayOfMonth > maxDays)
        dayOfMonth = maxDays;

    if (!Validate()){
        year = tmpYear;
        month = tmpMonth;
        throw std::runtime_error("Invalid date after AddMonth operation");
    }
}

void DateTime::AddYears(int Y) 
{
    int tmpYear = year;
    if (Y == 0)
        return;
    else
        year += Y;
        
    if (month == 2 && dayOfMonth == 29) 
    {
        if (!isLeapYear(year)) {dayOfMonth = 28;}
    }
     if (!Validate()){
        year = tmpYear;
        throw std::runtime_error("Invalid date after AddYear operation");
     }
}

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
    const char* names[] = { "Суббота", "Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница" };
    return names[DayofWeek()];
}


DateTime DateTime::get_Now() { return DateTime(); }


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

bool operator==(const DateTime& a, const DateTime& b)
{
    return DateTime::isEqual(a, b);
}

bool operator!=(const DateTime &a, const DateTime &b)
{
    return !(a == b);
}

bool operator<(const DateTime &a, const DateTime &b)
{
    if(a.year != b.year) return a.year < b.year;
    if(a.month != b.month) return a.month < b.month;
    if(a.dayOfMonth != b.dayOfMonth) return a.dayOfMonth < b.dayOfMonth;
    return a.secondsInDay < b.secondsInDay;
}

bool operator>(const DateTime &a, const DateTime &b)
{
    return b < a;
}

bool operator<=(const DateTime &a, const DateTime &b)
{
    return !(b < a);
}

bool operator>=(const DateTime &a, const DateTime &b)
{
    return !(a < b);
}

DateTime operator+(const DateTime &a, long long seconds)
{
    DateTime res(a);
    res.AddSeconds(seconds);
    return res;
}

DateTime operator-(const DateTime &a, long long seconds)
{
    return a + (-seconds);
}

namespace //алгоритм Хиннанта (дней от 1.01.0001 до заданной даты)
//соль в том, чтобы: поделить год на блоки по 400 лет (один цикл григорианского календаря),
//год начинается с марта, далее находим номер дня в пределах года и считаем общее количество дней от эпохи
{
    long long daysSinceCivil(int y, int m, int d){
        y-= m <= 2; //считаем год с марта - так проще високосность смотреть
        const int era = (y >= 0 ? y : y-399) / 400; // делим на блоки по 400
        const unsigned yoe = static_cast<unsigned>(y - era * 400); // year of era
        const unsigned doy = (153*(m + (m > 2 ? -3 : 9)) + 2)/5 + d - 1; // day of year
        const unsigned doe = yoe*365 + yoe/4 - yoe/100 + doy; // day of era
        return era*146097LL + static_cast<long long>(doe);
    }
} 

DateTime operator+(const DateTime &a, const DateTime& interval)
{
    long long days = daysSinceCivil(interval.year, interval.month, interval.dayOfMonth) - daysSinceCivil(1, 1, 1);

    DateTime res(a);
    if (days) res.AddDays(static_cast<int>(days));
    if (interval.secondsInDay) res.AddSeconds(interval.secondsInDay);
    return res;
}

long long operator-(const DateTime &a, const DateTime &b)
{
    long long days = daysSinceCivil(a.year, a.month, a.dayOfMonth) - daysSinceCivil(b.year, b.month, b.dayOfMonth);

    return days*86400LL + static_cast<long long>(a.secondsInDay) - b.secondsInDay;
}