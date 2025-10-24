#include "Property.h"
#include "../Property/PayLib.h"

using namespace Property;

double interop::EqualAmortization(double amt, double interest, int period)
{
	return ::EqualAmortization(amt, interest, period);
}
