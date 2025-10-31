#pragma once
#include <vector>
#include <cmath>
#include <stdexcept>
#include "model.h"
#include "MathUtils.h"
#include "Property.h"

#ifdef _WIN32
    #define EXPORT_API __declspec(dllexport)
#elif __APPLE__
    #define EXPORT_API __attribute__((visibility("default")))
#else
    #define EXPORT_API __declspec(dllimport)
#endif

extern "C" {
    EXPORT_API double __stdcall EqualAmortization(double amt, double interest, int period);

    EXPORT_API Property* CreateProperty() { return new Property(); }
    EXPORT_API void FreeProperty(Property* p) { delete p; }

    EXPORT_API void AddPayment(Property* p, const Payment& pay) { p->AddPayment(pay); }
    EXPORT_API void AddRate(Property* p, const Interest& r) { p->AddInterest(r); }

    EXPORT_API void BulkAddPayment(Property* p, const Payment* list, int count) { p->BulkAddPayment(list, count); }
    EXPORT_API void BulkAddRate(Property* p, const Interest* list, int count) { p->BulkAddInterest(list, count); }

    EXPORT_API DailyCompound __stdcall GetMonthlyInterest(Property* p, int month, int year) { return p->GetMonthlyInterest(month, year); }
}