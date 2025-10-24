#pragma once

#ifdef _WIN32
    #define EXPORT_API __declspec(dllexport)
#elif __APPLE__
    #define EXPORT_API __attribute__((visibility("default")))
#else
    #define EXPORT_API __declspec(dllimport)
#endif

using namespace std;

struct cDate {
    int year;
    int month;
    int day;
};

struct DailyCompound {
    cDate IDate;
    double IBalance = 0;
    double IPay = 0;
    double IAdvance = 0;
    double IRate = 0;
    double IRate_Amount_1 = 0;
    double IRate_Amount_2 = 0;
};

extern "C" {
    EXPORT_API double __stdcall EqualAmortization(double amt, double interest, int period);
    EXPORT_API double __stdcall Add(double a, double b);
    EXPORT_API double __stdcall Multiply(double a, double b);
}

