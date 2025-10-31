#pragma once
#include <vector>
#include "model.h"
#include "MathUtils.h"


inline std::vector<DailyCompound> MonthlyInterest(
    long long amt,
    const std::vector<Payment>& payments,
    const std::vector<Interest>& rates,
    int month,
    int year) {

    std::vector<DailyCompound> result;
    int daysInMonth = DaysInMonth(year, month);
    int daysInYear = DaysInYear(year);
    int currentRate = 0;

    for (int day = 1; day <= daysInMonth; ++day) {
        DailyCompound d;
        d.IDate.year = year; 
        d.IDate.month = month; 
        d.IDate.day = day;
        d.IBalance = amt;

        for (auto& r : rates) {
            if (r.date.year == year &&
                r.date.month == month &&
                r.date.day == day) {
                currentRate = r.interest;
                break;
            }
        }
        d.IRate = currentRate;

        d.IPay = 0;
        for (auto& p : payments) {
            if (p.date.year == year &&
                p.date.month == month &&
                p.date.day == day) {
                d.IPay = p.pay;
                break;
            }
        }

        long long i = 0;
        if (amt - d.IPay > 0) {
            amt -= d.IPay;
            i = DailyInterest(amt, d.IRate, daysInYear);
        }
        
        d.IRate_Amount = i;

        result.push_back(d);
    }
    return result;
}

inline DailyCompound GetMonthlyInterest(
    long long amt,
    const std::vector<Payment>& payments,
    const std::vector<Interest>& rates,
    int month,
    int year) {
    auto result = MonthlyInterest(amt, payments, rates, month, year);
    if (result.empty()) {
        return DailyCompound{};
    }
    
    return SumAll(result);
}

class Property {
	private:
		std::vector<Payment> payments;
		std::vector<Interest> interests;

	public:
		long long amt = 0;

		// Single Add
		void AddPayment(const Payment& p) { payments.push_back(p); }
		void AddInterest(const Interest& i) { interests.push_back(i); }

		// Bulk Add
		void BulkAddPayment(const Payment* list, int count) {
			if (!list || count <= 0) return;
			payments.insert(payments.end(), list, list + count);
		}

        void BulkAddPayment(const std::vector<Payment>& list) {
            if (list.empty()) return;
            payments = list;
        }

		void BulkAddInterest(const Interest* list, int count) {
			if (!list || count <= 0) return;
			interests.insert(interests.end(), list, list + count);
		}

        void BulkAddInterest(const std::vector<Interest>& list) {
            if (list.empty()) return;
            interests = list;
        }

        DailyCompound GetMonthlyInterest(int month, int year) const {
            return ::GetMonthlyInterest(amt, payments, interests, month, year);
        }
};