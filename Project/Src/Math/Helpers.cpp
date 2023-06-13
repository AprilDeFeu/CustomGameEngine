#include "Math\Helpers.h"

double Power(double base, int exponent, double accumulator)
{
    while (exponent != 1) {exponent -= 1; accumulator *= base;}
    return accumulator*base;
}