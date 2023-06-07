#include <iostream>
#include <cmath>
#include "Math\Vectors.h"
#include "Math\Geometry.h"
#include "Math\Matrices.h"
#include "UnitTest\MathUnitTests.h"

using namespace std;

int main()
{
    TestVector2 v2;
    TestVector3 v3;
    TestVector4 v4;
    TestPoint2 p2;
    TestPoint3 p3;


    v2.AllTests();
    v3.AllTests();
    v4.AllTests();
    p2.AllTests();
    p3.AllTests();

    return 0;
}