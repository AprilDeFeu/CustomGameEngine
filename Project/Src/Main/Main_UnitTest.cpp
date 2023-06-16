#include <iostream>
#include <cmath>
#include "Math\Vectors.h"
#include "Math\Geometry.h"
#include "Math\Matrices.h"
#include "UnitTest\MathUnitTests.h"

using namespace std;

int main()
{
    TestVector testV;
    TestPoint testP;
    TestGeometry testG;
    TestMatrix testM;
    TestTransforms testT;

    testV.AllVectorTests();
    testP.AllPointTests();
    testG.AllGeometryTests();
    testM.AllMatrixTests();
    testT.AllTransformTests();

    return 0;
}