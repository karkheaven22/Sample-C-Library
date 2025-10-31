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
double __stdcall EqualAmortization(double amt, double ir, int p)
{
    ValidatePositive(amt, "LoanAmount");
    ValidatePositive(ir, "Interest");
    ValidatePositive(static_cast<double>(p), "Period");

    double n = ir / 1200.0;
    double i = std::pow(1.0 + n, p);
    double l = amt * (n + n / (i - 1.0));

    return RoundToCents(l, 2) / 100.0;
}
