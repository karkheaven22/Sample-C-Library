#pragma once

struct cDate {
    int year;
    int month;
    int day;
};

struct DailyCompound {
    cDate IDate;
    long long IBalance;
    long long IPay;
    int IRate;
    long long IRate_Amount;
};

struct Payment {
    long long pay;
    cDate date;

    Payment() : pay(0), date{ 1900, 1, 1 } {}
    Payment(cDate d, long long p) : date(d), pay(p) {}
};

struct Interest {
    unsigned int interest;
    cDate date;

    Interest() : interest(0), date{ 1900, 1, 1 } {}
    Interest(cDate d, unsigned int i) : date(d), interest(i) {}
};
