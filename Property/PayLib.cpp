#include "PayLib.h"
#include <vector>
#include <tuple>
#include <cmath>
#include <stdexcept>

using namespace std;

static void ValidatePositive(double value, const char* name)
{
    if (value <= 0)
        throw std::invalid_argument(std::string(name) + " must be positive.");
}

//Equal Installment or Equal Amortization
extern "C" __declspec(dllexport) double __stdcall EqualAmortization(double amt, double ir, int p)
{
    ValidatePositive(amt, "LoanAmount");
    ValidatePositive(ir, "Interest");
    ValidatePositive(static_cast<double>(p), "Period");

    double n = ir / 1200.0;
    double i = std::pow(1.0 + n, p);
    double l = amt * (n + n / (i - 1.0));

    return std::round(l * 100.0) / 100.0;
}

extern "C" __declspec(dllexport) double __stdcall Add(double a, double b)
{
    return a + b;
}

extern "C" __declspec(dllexport) double __stdcall Multiply(double a, double b)
{
    return a * b;
}

static double DailyInterest(double amt, double ir, int daysInYear)
{
    if (amt > 0.0)
        return amt * ir / 100 / daysInYear;
    return 0.0;
}

static bool IsLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static int DaysInYear(int year) {
    return IsLeapYear(year) ? 366 : 365;
}

static int DaysInMonth(int year, int month) {
    if (month < 1 || month > 12) return 0; // invalid month

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

static vector<DailyCompound> MonthlyInterest(
    double amt,
    const std::vector<std::tuple<int, double>>& payments,
    const std::vector<std::tuple<int, double>>& rates,
    int month,
    int year) {

    std::vector<DailyCompound> result;
    int daysInMonth = DaysInMonth(year, month);
    int daysInYear = DaysInYear(year);
    double currentRate = 0.0;

    for (int day = 1; day <= daysInMonth; ++day) {
        DailyCompound d;
        d.IDate.year = year; 
        d.IDate.month = month; 
        d.IDate.day = day;
        d.IBalance = amt;

        for (auto& r : rates) {
            if (std::get<0>(r) == day) {
                currentRate = std::get<1>(r);
                break;
            }
        }
        d.IRate = currentRate;

        d.IPay = 0.0;
        for (auto& p : payments) {
            if (std::get<0>(p) == day) d.IPay = std::get<1>(p);
        }

        double i = 0;
        if (amt - d.IPay > 0) {
            amt -= d.IPay;
            i = DailyInterest(amt, d.IRate, daysInYear);
        }
        
        d.IRate_Amount_1 = round(i * 100000) / 100000.0;
        d.IRate_Amount_2 = round(i * 100) / 100.0;
    }
}

