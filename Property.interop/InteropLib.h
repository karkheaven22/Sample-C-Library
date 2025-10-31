#pragma once
#include "../Property/model.h"
#include "../Property/Property.h"
#include "../Property/PayLib.h"
#using <mscorlib.dll>
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace InteropLib
{
    [StructLayout(LayoutKind::Sequential)]
    public value struct Date {
        int Year;
        int Month;
        int Day;

        DateTime ToDateTime() {
            return DateTime(Year, Month, Day);
        }

        static Date FromDateTime(DateTime dt) {
            Date d;
            d.Year = dt.Year;
            d.Month = dt.Month;
            d.Day = dt.Day;
            return d;
        }
    };

    public value struct ManagedPayment {
        System::Decimal Pay;
        Date DateInfo;

        ManagedPayment(System::DateTime dt, System::Decimal p) {
            DateInfo.Year = dt.Year;
            DateInfo.Month = dt.Month;
            DateInfo.Day = dt.Day;
            Pay = p;
        }

        virtual Payment ToNative() {
            Payment p;
            p.date.year = DateInfo.Year;
            p.date.month = DateInfo.Month;
            p.date.day = DateInfo.Day;
            System::Decimal scaled = System::Decimal::Multiply(Pay, System::Decimal(100));
            p.pay = System::Decimal::ToInt64(scaled);
            return p;
        }
    };

    public value struct ManagedInterest {
        System::Decimal interest;
        Date DateInfo;

        ManagedInterest(System::DateTime dt, System::Decimal p) {
            DateInfo.Year = dt.Year;
            DateInfo.Month = dt.Month;
            DateInfo.Day = dt.Day;
            interest = p;
        }

        virtual Interest ToNative() {
            Interest p;
            p.date.year = DateInfo.Year;
            p.date.month = DateInfo.Month;
            p.date.day = DateInfo.Day;
            System::Decimal scaled = System::Decimal::Multiply(interest, System::Decimal(100));
            p.interest = static_cast<unsigned int>(System::Decimal::ToInt64(scaled));
            return p;
        }
    };

    public value struct ManagedDailyCompound {
        Date IDate;
        long long IBalance;
        long long IPay;
        unsigned int IRate;
        long long IRate_Amount;

        property System::Decimal Rate {
            System::Decimal get() {
                return System::Decimal(IRate) / 100;
            }
        }

        property System::Decimal Balance{
            System::Decimal get() {
                return System::Decimal(IBalance) / 100;
            }
        }

        property System::Decimal Pay{
            System::Decimal get() {
                return System::Decimal(IPay) / 100;
            }
            void set(System::Decimal value) {
                IPay = static_cast<long long>(value * 100);
            }
        }

        property System::Decimal InterestAmount{
            System::Decimal get() {
                return System::Decimal(IRate_Amount) / 100;
            }
            void set(System::Decimal value) {
                IRate_Amount = static_cast<long long>(value * 100);
            }
        }
    };

    public ref class PropertyWrapper
    {
    private:
        Property* native; 

    public:
        PropertyWrapper();
        PropertyWrapper(System::Decimal amt);
        ~PropertyWrapper();
        !PropertyWrapper();

        property System::Decimal Amount{
            System::Decimal get() {
                return System::Decimal(native->amt) / 100;
            }
            void set(System::Decimal value) {
                System::Decimal scaled = System::Decimal::Multiply(value, System::Decimal(100));
                native->amt = static_cast<long long>(System::Decimal::ToInt64(scaled));
            }
        };

        void AddPayment(ManagedPayment payment);

        void AddPayment(long long pay, int year, int month, int day);

        void AddInterest(ManagedInterest interest);

        void AddInterest(unsigned int rate, int year, int month, int day);

        void BulkAddPayment(array<ManagedPayment>^ list);

        void BulkAddIntrest(array<ManagedInterest>^ list);

        ManagedDailyCompound GetMonthlyInterest(int month, int year);

        double EqualAmortization(double amt, double interest, int period);
    };
}