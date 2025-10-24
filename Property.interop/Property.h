#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Property {
	public ref class interop
	{
	public:
		double EqualAmortization(double amt, double interest, int period);
	};
}