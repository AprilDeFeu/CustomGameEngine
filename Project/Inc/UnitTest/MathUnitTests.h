#pragma once
#include "UnitTest\MathUnitClasses.h"

using namespace std;
struct TestVector
{
private:
    TestVector2 v2;
    TestVector3 v3;
    TestVector4 v4;
public:
    void Initialize2(void) {v2.Initialize();}
    void ValueChange2(void) {v2.ValueChange();}
    void MemoryPlacement2(void) {v2.MemoryPlacement();}
    void ClassOperators2(void) {v2.ClassOperators();}
    void Methods2(void) {v2.Methods();}
    void AllTests2(void) {v2.AllTests();}

    void Initialize3(void) {v3.Initialize();}
    void ValueChange3(void) {v3.ValueChange();}
    void MemoryPlacement3(void) {v3.MemoryPlacement();}
    void ClassOperators3(void) {v3.ClassOperators();}
    void Methods3(void) {v3.Methods();}
    void AllTests3(void) {v3.AllTests();}

    void Initialize4(void) {v4.Initialize();}
    void ValueChange4(void) {v4.ValueChange();}
    void MemoryPlacement4(void) {v4.MemoryPlacement();}
    void ClassOperators4(void) {v4.ClassOperators();}
    void Methods4(void) {v4.Methods();}
    void AllTests4(void) {v4.AllTests();}

    void InitializeAll(void) {v2.Initialize(); v3.Initialize(); v4.Initialize();}
    void ValueChangeAll(void) {v2.ValueChange(); v3.ValueChange(); v4.ValueChange();}
    void MemoryPlacementAll(void) {v2.MemoryPlacement(); v3.MemoryPlacement(); v4.MemoryPlacement();}
    void ClassOperatorsAll(void) {v2.ClassOperators(); v3.ClassOperators(); v4.ClassOperators();}
    void MethodsAll(void) {v2.Methods(); v3.Methods(); v4.Methods();}
    void AllVectorTests(void) {v2.AllTests(); v3.AllTests(); v4.AllTests();}
};
struct TestPoint
{
private:
    TestPoint2 p2;
    TestPoint3 p3;
    TestPoint4 p4;
    TestHomogeneousPoint3 h3;
public:
    void Initialize2(void) {p2.Initialize();}
    void Initialize3(void) {p3.Initialize();}
    void Initialize4(void) {p4.Initialize();}
    void InitializeH3(void) {h3.Initialize();}
    void InitializeAll(void) {p2.Initialize();p3.Initialize();p4.Initialize();h3.Initialize();}

    void ValueChange2(void) {p2.ValueChange();}
    void ValueChange3(void) {p3.ValueChange();}
    void ValueChange4(void) {p4.ValueChange();}
    void ValueChangeH3(void) {h3.ValueChange();}
    void ValueChangeAll(void) {p2.ValueChange();p3.ValueChange();p4.ValueChange();h3.ValueChange();}

    void MemoryPlacement2(void) {p2.MemoryPlacement();}
    void MemoryPlacement3(void) {p3.MemoryPlacement();}
    void MemoryPlacement4(void) {p4.MemoryPlacement();}
    void MemoryPlacementH3(void) {h3.MemoryPlacement();}
    void MemoryPlacementAll(void) {p2.MemoryPlacement();p3.MemoryPlacement();p4.MemoryPlacement();h3.MemoryPlacement();}

    void ClassOperators2(void) {p2.ClassOperators();}
    void ClassOperators3(void) {p3.ClassOperators();}
    void ClassOperators4(void) {p4.ClassOperators();}
    void ClassOperatorsH3(void) {h3.ClassOperators();}
    void ClassOperatorsAll(void) {p2.ClassOperators();p3.ClassOperators();p4.ClassOperators();h3.ClassOperators();}

    void Methods2(void) {p2.Methods();}
    void Methods3(void) {p3.Methods();}
    void Methods4(void) {p4.Methods();}
    void MethodsH3(void) {h3.Methods();}
    void MethodsAll(void) {p2.Methods();p3.Methods();p4.Methods();h3.Methods();}

    void AllTests2(void) {p2.AllTests();}
    void AllTests3(void) {p3.AllTests();}
    void AllTests4(void) {p4.AllTests();}
    void AllTestsH3(void) {h3.AllTests();}
    void AllPointTests(void) {p2.AllTests();p3.AllTests();p4.AllTests();h3.AllTests();}
};
struct TestGeometry
{
private:
    TestLine L;
    TestPlane F;
    TestTriangle2 T2;
    TestTriangle3 T3;
public:
    void InitializeLine(void) {L.Initialize();}
    void InitializePlane(void) {F.Initialize();}
    void InitializeTriangle2(void) {T2.Initialize();}
    void InitializeTriangle3(void) {T3.Initialize();}
    void InitializeAll(void) {InitializeLine(); InitializePlane(); InitializeTriangle2(); InitializeTriangle3();}

    void ValueChangeLine(void) {L.ValueChange();}
    void ValueChangePlane(void) {F.ValueChange();}
    void ValueChangeTriangle2(void) {T2.ValueChange();}
    void ValueChangeTriangle3(void) {T3.ValueChange();}
    void ValueChangeAll(void) {ValueChangeLine(); ValueChangePlane(); ValueChangeTriangle2(); ValueChangeTriangle3();}

    void MemoryPlacementLine(void) {L.MemoryPlacement();}
    void MemoryPlacementPlane(void) {F.MemoryPlacement();}
    void MemoryPlacementTriangle2(void) {T2.MemoryPlacement();}
    void MemoryPlacementTriangle3(void) {T3.MemoryPlacement();}
    void MemoryPlacementAll(void) {MemoryPlacementLine(); MemoryPlacementPlane(); MemoryPlacementTriangle2(); MemoryPlacementTriangle3();}

    void AllTestsLine(void) {L.AllTests();}
    void AllTestsPlane(void) {F.AllTests();}
    void AllTestsTriangle2(void) {T2.AllTests();}
    void AllTestsTriangle3(void) {T3.AllTests();}
    void AllGeometryTests(void) {AllTestsLine(); AllTestsPlane(); AllTestsTriangle2(); AllTestsTriangle3();}
};
struct TestMatrix
{
private:
    TestMatrix2 M2; TestMatrix3 M3; TestMatrix4 M4;
public:
    void InitializeMatrix2(void) {M2.Initialize();}
    void InitializeMatrix3(void) {M3.Initialize();}
    void InitializeMatrix4(void) {M4.Initialize();}
    void InitializeAll(void) {InitializeMatrix2(); InitializeMatrix3(); InitializeMatrix4();}

    void ValueChangeMatrix2(void) {M2.ValueChange();}
    void ValueChangeMatrix3(void) {M3.ValueChange();}
    void ValueChangeMatrix4(void) {M4.ValueChange();}
    void ValueChangeAll(void) {ValueChangeMatrix2(); ValueChangeMatrix3(); ValueChangeMatrix4();}

    void MemoryPlacementMatrix2(void) {M2.MemoryPlacement();}
    void MemoryPlacementMatrix3(void) {M3.MemoryPlacement();}
    void MemoryPlacementMatrix4(void) {M4.MemoryPlacement();}
    void MemoryPlacementAll(void) {MemoryPlacementMatrix2(); MemoryPlacementMatrix3(); MemoryPlacementMatrix4();}

    void ClassOperatorsMatrix2(void) {M2.ClassOperators();}
    void ClassOperatorsMatrix3(void) {M3.ClassOperators();}
    void ClassOperatorsMatrix4(void) {M4.ClassOperators();}
    void ClassOperatorsAll(void) {ClassOperatorsMatrix2(); ClassOperatorsMatrix3(); ClassOperatorsMatrix4();}

    void AllTestsMatrix2(void) {M2.AllTests();}
    void AllTestsMatrix3(void) {M3.AllTests();}
    void AllTestsMatrix4(void) {M4.AllTests();}
    void AllMatrixTests(void) {AllTestsMatrix2(); AllTestsMatrix3(); AllTestsMatrix4();}
};
struct TestTransforms
{
private:
    TestTransform3 T3; TestTransform4 T4; TestQuaternion Q;
public:
    void InitializeTransform3(void) {T3.Initialize();}
    void InitializeTransform4(void) {T4.Initialize();}
    void InitializeQuaternion(void) {Q.Initialize();}
    void InitializeAll(void) {InitializeTransform3(); InitializeTransform4(); InitializeQuaternion();}

    void ValueChangeTransform3(void) {T3.ValueChange();}
    void ValueChangeTransform4(void) {T4.ValueChange();}
    void ValueChangeQuaternion(void) {Q.ValueChange();}
    void ValueChangeAll(void) {ValueChangeTransform3(); ValueChangeTransform4(); ValueChangeQuaternion();}

    void MemoryPlacementTransform3(void) {T3.MemoryPlacement();}
    void MemoryPlacementTransform4(void) {T4.MemoryPlacement();}
    void MemoryPlacementQuaternion(void) {Q.MemoryPlacement();}
    void MemoryPlacementAll(void) {MemoryPlacementTransform3(); MemoryPlacementTransform4(); MemoryPlacementQuaternion();}

    void ClassOperatorsTransform3(void) {T3.ClassOperators();}
    void ClassOperatorsTransform4(void) {T4.ClassOperators();}
    void ClassOperatorsQuaternion(void) {Q.ClassOperators();}
    void ClassOperatorsAll(void) {ClassOperatorsTransform3(); ClassOperatorsTransform4(); ClassOperatorsQuaternion();}

    void AllTestsTransform3(void) {T3.AllTests();}
    void AllTestsTransform4(void) {T4.AllTests();}
    void AllTestsQuaternion(void) {Q.AllTests();}
    void AllTransformTests(void) {AllTestsTransform3(); AllTestsTransform4(); AllTestsQuaternion();}
};