#include <iostream>
#include <cmath>
#include "Math\Vectors.h"
#include "Math\Geometry.h"
#include "Math\Matrices.h"
#include "UnitTest\UnitTests.h"

using namespace std;

int main()
{
    TestVector2 v2;
    TestVector3 v3;

    v2.AllTests();
    v3.AllTests();

    return 0;
}