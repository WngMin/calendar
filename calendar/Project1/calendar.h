#pragma once

#include <vector>
#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include "frameresource.h"

struct MonthAndWeek
{
	MonthAndWeek(unsigned int month, unsigned int week) : m_month(month), m_week(week) {}
	unsigned int m_month;
	unsigned int m_week;
};
class Calendar
{
public:
	std::vector<MonthAndWeek> GetMonthOfYear(unsigned int year);

private:
	void SetYear(unsigned int year);
	bool IsLeapYear(unsigned int year);
	unsigned FirstDayWeek(int d, int m, int y);
private:
	unsigned int m_curyear = 0;
	std::vector<MonthAndWeek> m_monthOfYear;
};