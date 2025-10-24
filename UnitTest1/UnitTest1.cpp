#include "CppUnitTest.h"
#include "PayLib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(PayLibTests)
	{
	public:
		
		TEST_METHOD(EqualAmortization_shouldSame)
		{
			double result = EqualAmortization(100000, 3.4, 360);
			/*Calculator^ calc = Calculator();
			double result = calc->EqualAmortization(100000, 3.4, 30);*/

			Assert::AreEqual(443.48, result);
		}
	};
}
