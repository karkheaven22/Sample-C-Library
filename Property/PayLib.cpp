#include "PayLib.h"

static void ValidatePositive(double value, const char* name)
{
    if (value <= 0)
        throw std::invalid_argument(std::string(name) + " must be positive.");
}

static double DailyInterest(double amt, double ir, int daysInYear)
{
    if (amt > 0.0)
        return amt * ir / (100 * daysInYear);
    return 0.0;
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

    return RoundToCents(l, 2) / 100.0;
}


//extern "C" __declspec(dllexport) DailyCompound __stdcall GetMonthlyInterest(
//    double amt,
//    const int* payDays, const double* payAmounts, int payCount,
//    const int* rateDays, const double* rateValues, int rateCount,
//    int month, int year)
//{
//    std::vector<Payment> payments;
//    payments.reserve(payCount);
//    for (int i = 0; i < payCount; ++i) {
//        payments.push_back({ (int)payDays[i], RoundToCents(payAmounts[i]) });
//    }
//
//    std::vector<Rate> rates;
//    rates.reserve(rateCount);
//    for (int i = 0; i < rateCount; ++i) {
//        rates.push_back({ (int)rateDays[i], (int)RoundToCents(rateValues[i]) });
//    }
//
//    auto result = MonthlyInterest(RoundToCents(amt), payments, rates, month, year);
//    if (result.empty()) {
//        return DailyCompound{};
//    }
//
//    return SumAll(result);
//}


//static vector<DailyCompound> MonthlyInterest(
//    long long amt,
//    const std::vector<Payment>& payments,
//    const std::vector<Rate>& rates,
//    int month,
//    int year) {
//
//    std::vector<DailyCompound> result;
//    int daysInMonth = DaysInMonth(year, month);
//    int daysInYear = DaysInYear(year);
//    int currentRate = 0;
//
//    for (int day = 1; day <= daysInMonth; ++day) {
//        DailyCompound d;
//        d.IDate.year = year; 
//        d.IDate.month = month; 
//        d.IDate.day = day;
//        d.IBalance = amt;
//
//        for (auto& r : rates) {
//            if (r.day == day) {
//                currentRate = r.rate;
//                break;
//            }
//        }
//        d.IRate = currentRate;
//
//        d.IPay = 0;
//        for (auto& p : payments) {
//            if (p.day == day) {
//                d.IPay = p.amount;
//                break;
//            }
//        }
//
//        long long i = 0;
//        if (amt - d.IPay > 0) {
//            amt -= d.IPay;
//            i = DailyInterestCents(amt, d.IRate, daysInYear);
//        }
//        
//        d.IRate_Amount = RoundToCents(i / 10000.0);
//
//        result.push_back(d);
//    }
//    return result;
//}

