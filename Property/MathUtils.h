#pragma once
#include <vector>
#include <cmath>
#include "model.h"

inline bool IsLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

inline int DaysInYear(int year) {
    return IsLeapYear(year) ? 366 : 365;
}

inline int DaysInMonth(int year, int month) {
    if (month < 1 || month > 12) return 0;

    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return IsLeapYear(year) ? 29 : 28;
    }
    return 0;
}

inline long long RoundToCents(double value, int digits = 2)
{
    const long long scale = static_cast<long long>(std::pow(10, digits));
    return static_cast<long long>(std::llround(value * scale));
}

inline double RoundTo(double value, int digits)
{
    long long scaled = RoundToCents(value, digits);
    return scaled / static_cast<double>(std::pow(10, digits));
}

inline long long DailyInterest(long long amt, int rate, int daysInYear)
{
    if (amt <= 0) return 0;
    return (amt * rate) / (daysInYear * 100);
}

inline DailyCompound SumAll(const std::vector<DailyCompound>& list)
{
    DailyCompound sum{};

    if (!list.empty()) {
        sum.IBalance = list.front().IBalance;
        sum.IRate = list.front().IRate;
        sum.IDate = list.front().IDate;
    }

    for (auto& d : list) {
        sum.IPay += d.IPay;
        sum.IRate_Amount += d.IRate_Amount;
    }
    sum.IRate_Amount /= 100;
    return sum;
}