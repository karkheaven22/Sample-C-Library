#include <iostream>
#include <oaidl.h>
#include <windows.h>
#include "CppUnitTest.h"
#include "PayLib.h"
#include "Property.h"
#include "MathUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(PayLibTests)
	{
	public:
		
		TEST_METHOD(EqualAmortization_shouldSame)
		{
			double result = EqualAmortization(100000, 3.4, 360);
			Assert::AreEqual(443.48, result);
		}

		TEST_METHOD(EqualAmortization_shouldSame2)
		{
			double amt = 1000000;
			int payDays[] = { 1, 15, 30 };
			double payAmounts[] = { 1000, 2000, 1500 };
			int payCount = 3;

			int rateDays[] = { 1, 10, 20 };
			double rateValues[] = { 3.5, 3.7, 3.9 };
			int rateCount = 3;

			int month = 10;
			int year = 2025;

			std::vector<Payment> payments = {
				{ {2025, 10, 1}, 1000LL },
				{ {2025, 10, 15}, 2000LL },
				{ {2025, 10, 30}, 1500LL }
			};

			std::vector<Interest> interests = {
				{ {2025, 10, 1}, 350 },
				{ {2025, 10, 10}, 370 },
				{ {2025, 10, 20}, 390 }
			};

			Property p = Property();
			p.amt = 1000000;
			p.BulkAddInterest(interests);
			p.BulkAddPayment(payments);
			DailyCompound result = p.GetMonthlyInterest(10, 2025);

			std::wstringstream ss;
			ss  << L"Date=" << result.IDate.year << L"-" << result.IDate.month << L"-" << result.IDate.day
				<< L", Balance=" << result.IBalance
				<< L", Pay=" << result.IPay
				<< L", Rate=" << result.IRate
				<< L", RateAmt1=" << result.IRate_Amount
				<< std::endl;
			Logger::WriteMessage(ss.str().c_str());
		}
	};
}
