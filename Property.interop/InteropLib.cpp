#include "InteropLib.h"

namespace InteropLib {

    PropertyWrapper::PropertyWrapper() {
        native = new Property();
    }

    PropertyWrapper::PropertyWrapper(System::Decimal amt) {
        native = new Property();
        System::Decimal scaled = System::Decimal::Multiply(amt, System::Decimal(100));
        native->amt = System::Decimal::ToInt64(scaled);
    }

    PropertyWrapper::~PropertyWrapper() {
        this->!PropertyWrapper();
        GC::SuppressFinalize(this);
    }

    PropertyWrapper::!PropertyWrapper() {
        if (native != nullptr) {
            delete native;
            native = nullptr;
        }
    }

    void PropertyWrapper::AddPayment(ManagedPayment payment) {
        native->AddPayment(payment.ToNative());
    }

    void PropertyWrapper::AddPayment(long long pay, int year, int month, int day) {
        Payment p;
        p.pay = pay;
        p.date = { year, month, day };
        native->AddPayment(p);
    }

    void PropertyWrapper::AddInterest(ManagedInterest interest) {
        native->AddInterest(interest.ToNative());
    }

    void PropertyWrapper::AddInterest(unsigned int rate, int year, int month, int day) {
        Interest i;
        i.interest = rate;
        i.date = { year, month, day };
        native->AddInterest(i);
    }

    void PropertyWrapper::BulkAddPayment(array<ManagedPayment>^ payments) {
        if (payments == nullptr || payments->Length == 0) return;

        std::vector<Payment> nativeList;
        nativeList.reserve(payments->Length);

        for (int i = 0; i < payments->Length; ++i) {
            nativeList.push_back(payments[i].ToNative());
        }

        native->BulkAddPayment(nativeList);
    }

    void PropertyWrapper::BulkAddIntrest(array<ManagedInterest>^ interest) {
        if (interest == nullptr || interest->Length == 0) return;

        std::vector<Interest> nativeList;
        nativeList.reserve(interest->Length);

        for (int i = 0; i < interest->Length; ++i) {
            nativeList.push_back(interest[i].ToNative());
        }

        native->BulkAddInterest(nativeList);
    }

    ManagedDailyCompound PropertyWrapper::GetMonthlyInterest(int month, int year) {
        DailyCompound dc = native->GetMonthlyInterest(month, year);
        ManagedDailyCompound mdc;
        mdc.IDate = { dc.IDate.year, dc.IDate.month, dc.IDate.day };
        mdc.IBalance = dc.IBalance;
        mdc.IPay = dc.IPay;
        mdc.IRate = dc.IRate;
        mdc.IRate_Amount = dc.IRate_Amount;
        return mdc;
    }
}