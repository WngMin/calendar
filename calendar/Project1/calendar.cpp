#include "calendar.h"

std::vector<MonthAndWeek> Calendar::GetMonthOfYear(unsigned int year)
{
    if (year == m_curyear)
        ;
    else
        SetYear(year);
    return m_monthOfYear;
}

void Calendar::SetYear(unsigned int year)
{
    m_curyear = year;
    m_monthOfYear.clear();
    unsigned int normalYear[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    unsigned int LeapYear[12]{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    unsigned totalDays = 1;
    for (int i = 0; i < 12; i++)
    {
        unsigned week = 0;
        if (IsLeapYear(m_curyear))
        {
            totalDays += LeapYear[i];
            week = FirstDayWeek(1, (i + 1), m_curyear);
            m_monthOfYear.push_back(MonthAndWeek(LeapYear[i], week));
        }
        else
        {
            totalDays += normalYear[i];
            week = FirstDayWeek(1, (i + 1), m_curyear);
            m_monthOfYear.push_back(MonthAndWeek(normalYear[i], week));
        }
    }
}

bool Calendar::IsLeapYear(unsigned int year)
{
    bool res = false;
    if (year % 4 == 0 && year % 100 != 0)
        res = true;
    else if (year % 4 == 0 && year % 400 == 0)
        res = true;
    return res;
}

unsigned Calendar::FirstDayWeek(int d, int m, int y)
{
    if (m == 1 || m == 2)
    {
        m += 12;
        y--;
    }
    return (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400 + 1) % 7;
}
