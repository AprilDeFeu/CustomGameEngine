#pragma once
#include <cmath>
#include <iostream>
#include <string>
#include "Math\Vectors.h"
#include "Math\Geometry.h"
#include "Math\Matrices.h"

using namespace std;

#define IS_TRUE(testVal) if (!(testVal)) {cout << __FUNCTION__ << " test failed on line " << __LINE__ << endl}
#define IS_LESS(testVal, expectedVal) if ((testVal)>=(expectedVal)) cout << __FUNCTION__ << " test failed on line " << __LINE__ << endl
#define IS_GREATER(testVal, expectedVal) if ((testVal)<=(expectedVal)) cout << __FUNCTION__ << " test failed on line " << __LINE__ << endl
#define IS_LESS_EQUAL(testVal, expectedVal) if ((testVal)>(expectedVal)) cout << __FUNCTION__ << " test failed on line " << __LINE__ << endl
#define IS_GREATER_EQUAL(testVal, expectedVal) if ((testVal)<(expectedVal)) cout << __FUNCTION__ << " test failed on line " << __LINE__ << endl
#define IS_CLOSE(testVal, expectedVal) if (fabs((testVal)-(expectedVal))>=1e-6) cout << __FUNCTION__ << " test failed on line " << __LINE__ << endl
#define IS_NOT_CLOSE(testVal, expectedVal) if (fabs((testVal)-(expectedVal))<1e-6) cout << __FUNCTION__ << " test failed on line " << __LINE__ << endl
#define IS_FALSE(testVal) if (testVal) cout << __FUNCTION__ << " test failed on line " << __LINE__ << endl
#define IS_EQUAL(testVal, expectedVal) if ((testVal)!=(expectedVal)) cout << __FUNCTION__ << " test failed on line " << __LINE__ << endl
#define IS_NOTEQUAL(testVal, expectedVal) if ((testVal)==(expectedVal)) cout << __FUNCTION__ << " test failed on line " << __LINE__ << endl


struct Counter
{
private:
    int countPass = 0;
    int countFail = 0;
    int total = 0;
    int accumulator_p = 0;
    int accumulator_f = 0;
    int accumulator_t = 0;
public:
    void SetCount(bool check)
    {
        if (check) {countPass++; total++;}
        else {countFail++; total++;}
    }
    void SetCountClose(float a, float b)
    {
        if (fabs(a - b) <= 1e-6) {countPass++; total++;}
        else {countFail++; total++;}
    }
    int GetCountPass(void) { return countPass; }
    int GetCountFail(void) { return countFail; }
    int GetTotal(void) { return total; }
    void Reset(void)
    {
        accumulator_p += countPass; countPass = 0;
        accumulator_f += countFail; countFail = 0;
        accumulator_t += total; total = 0;
    }
    void ResetAccumulator(void)
    {
        accumulator_p = 0;
        accumulator_f = 0;
        accumulator_t = 0;
    }
    int GetAccumulatorPass(void) { return accumulator_p; }
    int GetAccumulatorFail(void) { return accumulator_f; }
    int GetAccumulatorTotal(void) { return accumulator_t; }

};
struct TestVector2
{
public:
    Counter counter;
    void Initialize(void)
    {
        int pass, fail;
        Vector2 t(0.0f, 0.0f);
        cout << "Testing Vector2 initialization...\n";
        IS_EQUAL(t.ToString(), ("("+to_string(0.0f)+", "+to_string(0.0f)+")"));
        counter.SetCount(t.ToString() == ("("+to_string(0.0f)+", "+to_string(0.0f)+")"));
        t += Vector2(-69.0f, 420.0f);
        IS_EQUAL(t.ToString(), ("("+to_string(-69.0f)+", "+to_string(420.0f)+")"));
        counter.SetCount(t.ToString() == ("("+to_string(-69.0f)+", "+to_string(420.0f)+")"));
        t = Vector2(3,4);
        IS_EQUAL(t.ToString(), ("("+to_string(3.0f)+", "+to_string(4.0f)+")"));
        counter.SetCount(t.ToString() == ("("+to_string(3.0f)+", "+to_string(4.0f)+")"));
        cout << "Testing of Vector2 initalization complete!\n";
        pass = counter.GetCountPass();
        fail = counter.GetCountFail();
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(pass) << endl;
        cout << "-Tests Failed: " << to_string(fail) << endl << endl;
        counter.Reset();
    }
    void ValueChange(void)
    {
        int pass, fail;
        cout << "Testing Vector2 value change...\n";
        Vector2 t(1.0f, 2.0f);
        IS_EQUAL(t, Vector2(1.0f, 2.0f));
        counter.SetCount(t == Vector2(1.0f, 2.0f));
        t.x = 3.0f;
        t.y = 4.0f;
        IS_NOTEQUAL(t, Vector2(1.0f, 2.0f));
        counter.SetCount(t != Vector2(1.0f, 2.0f));
        t = Vector2(5.0f, 6.0f);
        IS_NOTEQUAL(t, Vector2(1.0f, 2.0f));
        counter.SetCount(t != Vector2(1.0f, 2.0f));
        Vector2 x(1.0f, 2.0f);
        t=x;
        IS_EQUAL(t, Vector2(1.0f, 2.0f));
        counter.SetCount(t == Vector2(1.0f, 2.0f));
        cout << "Testing of Vector2 value change complete!\n";
        pass = counter.GetCountPass();
        fail = counter.GetCountFail();
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(pass) << endl;
        cout << "-Tests Failed: " << to_string(fail) << endl << endl;
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        int pass, fail;
        cout << "Testing Vector2 memory placement...\n";
        Vector2 s(1.0f, 2.0f), t(3.0f, 4.0f);
        Vector2 *a, *b;
        a = &s;
        b = &t;
        IS_NOTEQUAL(a, b);
        counter.SetCount(a != b);
        b = &s;
        IS_EQUAL(a, b);
        counter.SetCount(a == b);
        cout << "Testing of Vector2 memory placement complete!\n";
        pass = counter.GetCountPass();
        fail = counter.GetCountFail();
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(pass) << endl;
        cout << "-Tests Failed: " << to_string(fail) << endl << endl;
        counter.Reset();
    }
    void ClassOperators(void)
    {
        int pass, fail;
        cout << "Testing Vector2 class operators...\n";
        Vector2 t(1.0f, 2.0f);
        t += Vector2(-2.0f, 1.0f);
        IS_EQUAL(t, Vector2(-1.0f, 3.0f));
        counter.SetCount(t == Vector2(-1.0f, 3.0f));
        t -= Vector2(-4.0f, -2.0f);
        IS_EQUAL(t, Vector2(3.0f, 5.0f));
        counter.SetCount(t == Vector2(3.0f, 5.0f));
        float f = (t *= Vector2(2.0f, 3.0f));
        IS_EQUAL(f, 21.0f);
        t = Vector2(3.0f, 5.0f);
        t *= 2.0f;
        IS_EQUAL(t, Vector2(6.0f, 10.0f));
        counter.SetCount(t == Vector2(6.0f, 10.0f));
        t /= 2.0f;
        IS_EQUAL(t, Vector2(3.0f, 5.0f));
        counter.SetCount(t == Vector2(3.0f, 5.0f));
        IS_EQUAL(t.x, 3.0f);
        counter.SetCount(t.x == 3.0f);
        IS_EQUAL(t.y, 5.0f);
        counter.SetCount(t.y == 5.0f);
        IS_EQUAL(t.Zero(), Vector2(0.0f, 0.0f));
        counter.SetCount(t.Zero() == Vector2(0.0f, 0.0f));
        cout << "Testing of Vector2 class operators complete!\n";
        pass = counter.GetCountPass();
        fail = counter.GetCountFail();
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(pass) << endl;
        cout << "-Tests Failed: " << to_string(fail) << endl << endl;
        counter.Reset();
    }
    void Methods(void)
    {
        int pass, fail;
        cout << "Testing Vector2 methods...\n";
        Vector2 t(1.0f, 2.0f);
        IS_EQUAL((t*t), 5.0f);
        counter.SetCount((t*t) == 5.0f);
        IS_NOTEQUAL((t*t), 3.0f);
        counter.SetCount((t*t) != 3.0f);
        IS_EQUAL((t.Zero()*t.Zero()), 0.0f);
        counter.SetCount((t.Zero()*t.Zero()) == 0.0f);

        Vector2 x(3.0f, 4.0f);
        IS_EQUAL((t+x), Vector2(4.0f, 6.0f));
        counter.SetCount((t+x) == Vector2(4.0f, 6.0f));
        IS_EQUAL((t-x), Vector2(-2.0f, -2.0f));
        counter.SetCount((t-x) == Vector2(-2.0f, -2.0f));
        IS_EQUAL((t*2.0f), Vector2(2.0f, 4.0f));
        counter.SetCount((t*2.0f) == Vector2(2.0f, 4.0f));
        IS_EQUAL((2.0f*t), Vector2(2.0f, 4.0f));
        counter.SetCount((2.0f*t) == Vector2(2.0f, 4.0f));
        IS_EQUAL((t/2.0f), Vector2(0.5f, 1.0f));
        counter.SetCount((t/2.0f) == Vector2(0.5f, 1.0f));
        IS_EQUAL((-t), Vector2(-1.0f, -2.0f));
        counter.SetCount((-t) == Vector2(-1.0f, -2.0f));
        IS_EQUAL((t*x), 11.0f);
        counter.SetCount((t*x) == 11.0f);
        IS_CLOSE(Magnitude(t), sqrt(5.0f));
        counter.SetCountClose(Magnitude(t),sqrt(5.0f));
        IS_EQUAL(Normalize(t), Vector2((1.0f/sqrt(5.0f)), 2.0f/sqrt(5.0f)));
        counter.SetCount(Normalize(t) == Vector2((1.0f/sqrt(5.0f)), 2.0f/sqrt(5.0f)));
        Swap(&t,&x);
        IS_NOTEQUAL(t, Vector2(1.0f, 2.0f));
        counter.SetCount(t != Vector2(1.0f, 2.0f));
        IS_NOTEQUAL(x, Vector2(3.0f, 4.0f));
        counter.SetCount(x != Vector2(3.0f, 4.0f));
        Swap(&t,&x);
        IS_EQUAL(t, Vector2(1.0f, 2.0f));
        counter.SetCount(t == Vector2(1.0f, 2.0f));
        IS_EQUAL(x, Vector2(3.0f, 4.0f));
        counter.SetCount(x == Vector2(3.0f, 4.0f));
        IS_CLOSE(Angle(t,x), acosf(11.0f/(sqrtf(5.0f)*5.0f)));
        counter.SetCountClose(Angle(t,x), acosf(11.0f/(sqrtf(5.0f)*5.0f)));
        Vector2 p = Projection(t,x);
        IS_CLOSE(p.x, 33.0f/25.0f);
        counter.SetCountClose(p.x, 33.0f/25.0f);
        IS_CLOSE(p.y, 44.0f/25.0f);
        counter.SetCountClose(p.y, 44.0f/25.0f);
        p = Rejection(t,x);
        IS_CLOSE(p.x, -8.0f/25.0f);
        counter.SetCountClose(p.x, -8.0f/25.0f);
        IS_CLOSE(p.y, 6.0f/25.0f);
        counter.SetCountClose(p.y, 6.0f/25.0f);
        cout << "Testing of Vector2 methods complete!\n";
        pass = counter.GetCountPass();
        fail = counter.GetCountFail();
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(pass) << endl;
        cout << "-Tests Failed: " << to_string(fail) << endl << endl;
        counter.Reset();
    }

    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            VECTOR2 UNIT TESTING           " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      ALL VECTOR2 TESTS HAVE FINISHED      " << endl;
        cout << "                                           " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl;
                counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestVector3
{
    Counter counter;
    void Initialize(void)
    {
        int pass, fail;
        Vector3 t(0.0f, 0.0f, 0.0f);
        cout << "Testing Vector3 initialization...\n";
        IS_EQUAL(t.ToString(), ("("+to_string(0.0f)+", "+to_string(0.0f)+", "+to_string(0.0f)+")"));
        counter.SetCount(t.ToString() == ("("+to_string(0.0f)+", "+to_string(0.0f)+", "+to_string(0.0f)+")"));
        t += Vector3(-69.0f, 420.0f, 13.0f);
        IS_EQUAL(t.ToString(), ("("+to_string(-69.0f)+", "+to_string(420.0f)+", "+to_string(13.0f)+")"));
        counter.SetCount(t.ToString() == ("("+to_string(-69.0f)+", "+to_string(420.0f)+", "+to_string(13.0f)+")"));
        t = Vector3(3,4,5);
        IS_EQUAL(t.ToString(), ("("+to_string(3.0f)+", "+to_string(4.0f)+", "+to_string(5.0f)+")"));
        counter.SetCount(t.ToString() == ("("+to_string(3.0f)+", "+to_string(4.0f)+", "+to_string(5.0f)+")"));
        cout << "Testing of Vector3 initalization complete!\n";
        pass = counter.GetCountPass();
        fail = counter.GetCountFail();
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(pass) << endl;
        cout << "-Tests Failed: " << to_string(fail) << endl << endl;
        counter.Reset();
    }
    void ValueChange(void)
    {
        int pass, fail;
        cout << "Testing Vector3 value change...\n";
        Vector3 t(1.0f, 2.0f, 3.0f);
        IS_EQUAL(t, Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(t == Vector3(1.0f, 2.0f, 3.0f));
        t.x = 3.0f;
        t.y = 4.0f;
        t.z = 5.0f;
        IS_NOTEQUAL(t, Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(t != Vector3(1.0f, 2.0f, 3.0f));
        t = Vector3(5.0f, 6.0f, 7.0f);
        IS_NOTEQUAL(t, Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(t != Vector3(1.0f, 2.0f, 3.0f));
        Vector3 x(1.0f, 2.0f, 3.0f);
        t=x;
        IS_EQUAL(t, Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(t == Vector3(1.0f, 2.0f, 3.0f));
        cout << "Testing of Vector3 value change complete!\n";
        pass = counter.GetCountPass();
        fail = counter.GetCountFail();
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(pass) << endl;
        cout << "-Tests Failed: " << to_string(fail) << endl << endl;
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        int pass, fail;
        cout << "Testing Vector3 memory placement...\n";
        Vector3 s(1.0f, 2.0f, 3.0f), t(3.0f, 4.0f, 5.0f);
        Vector3 *a, *b;
        a = &s;
        b = &t;
        IS_NOTEQUAL(a, b);
        counter.SetCount(a != b);
        b = &s;
        IS_EQUAL(a, b);
        counter.SetCount(a == b);
        cout << "Testing of Vector3 memory placement complete!\n";
        pass = counter.GetCountPass();
        fail = counter.GetCountFail();
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(pass) << endl;
        cout << "-Tests Failed: " << to_string(fail) << endl << endl;
        counter.Reset();
    }
    void ClassOperators(void)
    {
        int pass, fail;
        cout << "Testing Vector3 class operators...\n";
        Vector3 t(1.0f, 2.0f, 3.0f);
        t += Vector3(-2.0f, 1.0f, 3.0f);
        IS_EQUAL(t, Vector3(-1.0f, 3.0f, 6.0f));
        counter.SetCount(t == Vector3(-1.0f, 3.0f, 6.0f));
        t -= Vector3(-4.0f, -2.0f, 2.0f);
        IS_EQUAL(t, Vector3(3.0f, 5.0f, 4.0f));
        counter.SetCount(t == Vector3(3.0f, 5.0f, 4.0f));
        float f = (t *= Vector3(1.0f, 1.0f, 1.0f));
        IS_EQUAL(f, 12.0f);
        counter.SetCount(f == 12.0f);
        t = Vector3(3.0f, 5.0f, 4.0f);
        t *= 2.0f;
        IS_EQUAL(t, Vector3(6.0f, 10.0f, 8.0f));
        counter.SetCount(t == Vector3(6.0f, 10.0f, 8.0f));
        t /= 2.0f;
        IS_EQUAL(t, Vector3(3.0f, 5.0f, 4.0f));
        counter.SetCount(t == Vector3(3.0f, 5.0f, 4.0f));
        IS_EQUAL(t.x, 3.0f);
        counter.SetCount(t.x == 3.0f);
        IS_EQUAL(t.Zero(), Vector3(0.0f, 0.0f, 0.0f));
        counter.SetCount(t.Zero() == Vector3(0.0f, 0.0f, 0.0f));
        cout << "Testing of Vector3 class operators complete!\n";
        pass = counter.GetCountPass();
        fail = counter.GetCountFail();
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(pass) << endl;
        cout << "-Tests Failed: " << to_string(fail) << endl << endl;
        counter.Reset();
    }
    void Methods(void)
    {
        int pass, fail;
        cout << "Testing Vector3 methods...\n";
        Vector3 t(1.0f, 2.0f, 1.0f);
        IS_EQUAL((t*t), 6.0f);
        counter.SetCount((t*t) == 6.0f);
        IS_NOTEQUAL((t*t), 3.0f);
        counter.SetCount((t*t) != 3.0f);
        IS_EQUAL((t.Zero()*t.Zero()), 0.0f);
        counter.SetCount((t.Zero()*t.Zero()) == 0.0f);

        Vector3 x(3.0f, 4.0f, 5.0f);
        IS_EQUAL((t+x), Vector3(4.0f, 6.0f, 6.0f));
        counter.SetCount((t+x) == Vector3(4.0f, 6.0f, 6.0f));
        IS_EQUAL((t-x), Vector3(-2.0f, -2.0f, -4.0f));
        counter.SetCount((t-x) == Vector3(-2.0f, -2.0f, -4.0f));
        IS_EQUAL((t*2.0f), Vector3(2.0f, 4.0f, 2.0f));
        counter.SetCount((t*2.0f) == Vector3(2.0f, 4.0f, 2.0f));
        IS_EQUAL((2.0f*t), Vector3(2.0f, 4.0f, 2.0f));
        counter.SetCount((2.0f*t) == Vector3(2.0f, 4.0f, 2.0f));
        IS_EQUAL((t/2.0f), Vector3(0.5f, 1.0f, 0.5f));
        counter.SetCount((t/2.0f) == Vector3(0.5f, 1.0f, 0.5f));
        IS_EQUAL((-t), Vector3(-1.0f, -2.0f, -1.0f));
        counter.SetCount((-t) == Vector3(-1.0f, -2.0f, -1.0f));
        IS_EQUAL((t*x), 16.0f);
        counter.SetCount((t*x) == 16.0f);
        IS_CLOSE(Magnitude(t), sqrtf(6.0f));
        counter.SetCountClose(Magnitude(t), sqrtf(6.0f));
        Vector3 n = Normalize(t);
        IS_CLOSE(n.x, 1.0f/sqrtf(6.0f));
        counter.SetCountClose(n.x, 1.0f/sqrtf(6.0f));
        IS_CLOSE(n.y, sqrtf(2.0f/3.0f));
        counter.SetCountClose(n.y, sqrtf(2.0f/3.0f));
        IS_CLOSE(n.z, 1.0f/sqrtf(6.0f));
        counter.SetCountClose(n.z, 1.0f/sqrtf(6.0f));
        Swap(&t,&x);
        IS_NOTEQUAL(t, Vector3(1.0f, 2.0f, 1.0f));
        counter.SetCount(t != Vector3(1.0f, 2.0f, 1.0f));
        IS_NOTEQUAL(x, Vector3(3.0f, 4.0f, 5.0f));
        counter.SetCount(x != Vector3(3.0f, 4.0f, 5.0f));
        Swap(&t,&x);
        IS_EQUAL(t, Vector3(1.0f, 2.0f, 1.0f));
        counter.SetCount(t == Vector3(1.0f, 2.0f, 1.0f));
        IS_EQUAL(x, Vector3(3.0f, 4.0f, 5.0f));
        counter.SetCount(x == Vector3(3.0f, 4.0f, 5.0f));
        IS_EQUAL(CrossProduct(t,x), Vector3(6.0f, -2.0f, -2.0f));
        counter.SetCount(CrossProduct(t,x) == Vector3(6.0f, -2.0f, -2.0f));
        IS_EQUAL(CrossProduct(x,t), Vector3(-6.0f, 2.0f, 2.0f));
        counter.SetCount(CrossProduct(x,t) == Vector3(-6.0f, 2.0f, 2.0f));
        Vector3 y(3.0f, 7.0f, 9.0f);
        IS_CLOSE(ScalarTripleProduct(t,x,y), -14.0f);
        counter.SetCountClose(ScalarTripleProduct(t,x,y), -14.0f);
        IS_CLOSE(Angle(t,x), acosf(16.0f/(sqrtf(50.0f)*sqrtf(6.0f))));
        counter.SetCountClose(Angle(t,x), acosf(16.0f/(sqrtf(50.0f)*sqrtf(6.0f))));
        Vector3 p = Projection(t,x);
        IS_CLOSE(p.x, 24.0f/25.0f);
        counter.SetCountClose(p.x, 24.0f/25.0f);
        IS_CLOSE(p.y, 32.0f/25.0f);
        counter.SetCountClose(p.y, 32.0f/25.0f);
        IS_CLOSE(p.z, 8.0f/5.0f);
        counter.SetCountClose(p.z, 8.0f/5.0f);
        p = Rejection(t,x);
        IS_CLOSE(p.x, 1.0f/25.0f);
        counter.SetCountClose(p.x, 1.0f/25.0f);
        IS_CLOSE(p.y, 18.0f/25.0f);
        counter.SetCountClose(p.y, 18.0f/25.0f);
        IS_CLOSE(p.z, -3.0f/5.0f);
        counter.SetCountClose(p.z, -3.0f/5.0f);
        cout << "Testing of Vector3 methods complete!\n";
        pass = counter.GetCountPass();
        fail = counter.GetCountFail();
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(pass) << endl;
        cout << "-Tests Failed: " << to_string(fail) << endl << endl;
        counter.Reset();
    }
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            VECTOR3 UNIT TESTING          " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      ALL VECTOR3 TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestVector4
{
    Counter counter;
    void Initialize(void)
    {
        cout << "Testing Vector4 initialization...\n";
        Vector4 t(0.0f, 0.0f, 0.0f, 0.0f);
        IS_EQUAL(t.ToString(), "("+to_string(0.0f)+", "+to_string(0.0f)+", "+to_string(0.0f)+", "+to_string(0.0f)+")");
        counter.SetCount(t.ToString() == "("+to_string(0.0f)+", "+to_string(0.0f)+", "+to_string(0.0f)+", "+to_string(0.0f)+")");
        t += Vector4(1.0f, 2.0f, 3.0f, 4.0f);
        IS_EQUAL(t.ToString(), "("+to_string(1.0f)+", "+to_string(2.0f)+", "+to_string(3.0f)+", "+to_string(4.0f)+")");
        counter.SetCount(t.ToString() == "("+to_string(1.0f)+", "+to_string(2.0f)+", "+to_string(3.0f)+", "+to_string(4.0f)+")");
        t = Vector4(5.0f, 6.0f, 7.0f, 8.0f);
        IS_EQUAL(t.ToString(), "("+to_string(5.0f)+", "+to_string(6.0f)+", "+to_string(7.0f)+", "+to_string(8.0f)+")");
        counter.SetCount(t.ToString() == "("+to_string(5.0f)+", "+to_string(6.0f)+", "+to_string(7.0f)+", "+to_string(8.0f)+")");
        cout << "Testing of Vector4 initalization complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void ValueChange(void)
    {
        cout << "Testing Vector4 value change...\n";
        Vector4 t(1.0f, 2.0f, 3.0f, 4.0f);
        IS_EQUAL(t, Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        counter.SetCount(t == Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        t.x = 5.0f;
        t.y = 6.0f;
        t.z = 7.0f;
        t.w = 8.0f;
        IS_NOTEQUAL(t, Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        counter.SetCount(t != Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        t = Vector4(3.0f, 5.0f, 7.0f, 9.0f);
        IS_NOTEQUAL(t, Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        counter.SetCount(t != Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        Vector4 x(1.0f, 2.0f, 3.0f, 4.0f);
        t=x;
        IS_EQUAL(t, Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        counter.SetCount(t == Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        cout << "Testing of Vector4 value change complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        cout << "Testing Vector3 memory placement...\n";
        Vector4 s  (1.0f, 2.0f, 3.0f, 4.0f), t(5.0f, 6.0f, 7.0f, 8.0f);
        Vector4 *a, *b;
        a = &s;
        b = &t;
        IS_NOTEQUAL(a, b);
        counter.SetCount(a != b);
        b = &s;
        IS_EQUAL(a, b);
        counter.SetCount(a == b);
        cout << "Testing of Vector4 memory placement complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void ClassOperators(void)
    {
        cout << "Testing Vector4 class operators...\n";
        Vector4 t(1.0f, 2.0f, 3.0f, 4.0f);
        t += Vector4(-2.0f, 1.0f, 3.0f, -5.0f);
        IS_EQUAL(t, Vector4(-1.0f, 3.0f, 6.0f, -1.0f));
        counter.SetCount(t == Vector4(-1.0f, 3.0f, 6.0f, -1.0f));
        t -= Vector4(1.0f, -2.0f, 3.0f, -4.0f);
        IS_EQUAL(t, Vector4(-2.0f, 5.0f, 3.0f, 3.0f));
        counter.SetCount(t == Vector4(-2.0f, 5.0f, 3.0f, 3.0f));
        float f = (t *= Vector4(3.0f, 2.0f, 1.0f, 4.0f));
        IS_EQUAL(f, 19.0f);
        counter.SetCount(f == 19.0f);
        t = Vector4(-2.0f, 5.0f, 3.0f, 3.0f);
        t *= 2.0f;
        IS_EQUAL(t, Vector4(-4.0f, 10.0f, 6.0f, 6.0f));
        counter.SetCount(t == Vector4(-4.0f, 10.0f, 6.0f, 6.0f));
        t /= 2.0f;
        IS_EQUAL(t, Vector4(-2.0f, 5.0f, 3.0f, 3.0f));
        counter.SetCount(t == Vector4(-2.0f, 5.0f, 3.0f, 3.0f));
        IS_EQUAL(t.Zero(), Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        counter.SetCount(t.Zero() == Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        cout << "Testing of Vector4 class operators complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void Methods(void)
    {
        cout << "Testing Vector4 methods...\n";
        Vector4 t(1.0f, 2.0f, 1.0f, 2.0f);
        IS_EQUAL((t*t), 10.0f);
        counter.SetCount((t*t) == 10.0f);
        IS_NOTEQUAL((t*t), 5.0f);
        counter.SetCount((t*t) != 5.0f);
        IS_EQUAL((t.Zero()*t.Zero()), 0.0f);

        Vector4 x(3.0f, 4.0f, 5.0f, 6.0f);
        IS_EQUAL((t+x), Vector4(4.0f, 6.0f, 6.0f, 8.0f));
        counter.SetCount((t+x) == Vector4(4.0f, 6.0f, 6.0f, 8.0f));
        IS_EQUAL((t-x), Vector4(-2.0f, -2.0f, -4.0f, -4.0f));
        counter.SetCount((t-x) == Vector4(-2.0f, -2.0f, -4.0f, -4.0f));
        IS_EQUAL((t*2.0f), Vector4(2.0f, 4.0f, 2.0f, 4.0f));
        counter.SetCount((t*2.0f) == Vector4(2.0f, 4.0f, 2.0f, 4.0f));
        IS_EQUAL((2.0f*t), Vector4(2.0f, 4.0f, 2.0f, 4.0f));
        counter.SetCount((2.0f*t) == Vector4(2.0f, 4.0f, 2.0f, 4.0f));
        IS_EQUAL((t/2.0f), Vector4(0.5f, 1.0f, 0.5f, 1.0f));
        counter.SetCount((t/2.0f) == Vector4(0.5f, 1.0f, 0.5f, 1.0f));
        IS_EQUAL((-t), Vector4(-1.0f, -2.0f, -1.0f, -2.0f));
        counter.SetCount(((-t) == Vector4(-1.0f, -2.0f, -1.0f, -2.0f)));
        IS_EQUAL((t*x), (28.0f));
        counter.SetCount((t*x) == (28.0f));
        IS_CLOSE(Magnitude(t), sqrtf(10.0f));
        counter.SetCountClose(Magnitude(t), sqrtf(10.0f));

        Vector4 n = Normalize(t);
        IS_CLOSE(n.x, 1.0f/sqrtf(10.0f));
        counter.SetCountClose(n.x, 1.0f/sqrtf(10.0f));
        IS_CLOSE(n.y, 2.0f/sqrtf(10.0f));
        counter.SetCountClose(n.y, 2.0f/sqrtf(10.0f));
        IS_CLOSE(n.z, 1.0f/sqrtf(10.0f));
        counter.SetCountClose(n.z, 1.0f/sqrtf(10.0f));
        IS_CLOSE(n.w, 2.0f/sqrtf(10.0f));
        counter.SetCountClose(n.w, 2.0f/sqrtf(10.0f));

        Swap(&t, &x);
        IS_NOTEQUAL(t, Vector4(1.0f, 2.0f, 1.0f, 2.0f));
        counter.SetCount(t != Vector4(1.0f, 2.0f, 1.0f, 2.0f));
        IS_NOTEQUAL(x, Vector4(3.0f, 4.0f, 5.0f, 6.0f));
        counter.SetCount(x != Vector4(3.0f, 4.0f, 5.0f, 6.0f));
        Swap(&t, &x);
        IS_EQUAL(t, Vector4(1.0f, 2.0f, 1.0f, 2.0f));
        counter.SetCount(t == Vector4(1.0f, 2.0f, 1.0f, 2.0f));
        IS_EQUAL(x, Vector4(3.0f, 4.0f, 5.0f, 6.0f));
        counter.SetCount(x == Vector4(3.0f, 4.0f, 5.0f, 6.0f));
        IS_CLOSE(Angle(t,x), 0.30183677f);
        counter.SetCountClose(Angle(t,x), 0.30183677f);

        Vector4 p = Projection(t, x);
        IS_CLOSE(p.x, 42.0f/43.0f);
        counter.SetCountClose(p.x, 42.0f/43.0f);
        IS_CLOSE(p.y, 56.0f/43.0f);
        counter.SetCountClose(p.y, 56.0f/43.0f);
        IS_CLOSE(p.z, 70.0f/43.0f);
        counter.SetCountClose(p.z, 70.0f/43.0f);
        IS_CLOSE(p.w, 84.0f/43.0f);
        counter.SetCountClose(p.w, 84.0f/43.0f);

        p = Rejection(t, x);
        IS_CLOSE(p.x, 1.0f/43.0f);
        counter.SetCountClose(p.x, 1.0f/43.0f);
        IS_CLOSE(p.y, 30.0f/43.0f);
        counter.SetCountClose(p.y, 30.0f/43.0f);
        IS_CLOSE(p.z, -27.0f/43.0f);
        counter.SetCountClose(p.z, -27.0f/43.0f);
        IS_CLOSE(p.w, 2.0f/43.0f);
        counter.SetCountClose(p.w, 2.0f/43.0f);

        cout << "Testing of Vector4 class methods complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            VECTOR4 UNIT TESTING          " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      ALL VECTOR4 TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestPoint2
{
    Counter counter;
    void Initialize(void)
    {
        Point2 t(3.0f, 4.0f);
        cout << "Testing Point2 initialization...\n";
        IS_EQUAL(t.ToString(), "("+to_string(3.0f)+", "+to_string(4.0f)+")");
        counter.SetCount(t.ToString() == "("+to_string(3.0f)+", "+to_string(4.0f)+")");
        t += Point2(1.0f, 2.0f);
        IS_EQUAL(t.ToString(), "("+to_string(4.0f)+", "+to_string(6.0f)+")");
        counter.SetCount(t.ToString() == "("+to_string(4.0f)+", "+to_string(6.0f)+")");
        t = Point2(-2.5f, -3.5f);
        IS_EQUAL(t.ToString(), "("+to_string(-2.5f)+", "+to_string(-3.5f)+")");
        counter.SetCount(t.ToString() == "("+to_string(-2.5f)+", "+to_string(-3.5f)+")");

        cout << "Testing Point2 initialization complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();

    }
    void ValueChange(void)
    {
        cout << "Testing Point2 value change...\n";
        Point2 t(3.0f, 4.0f);
        IS_EQUAL(t, Point2(3.0f, 4.0f));
        counter.SetCount(t == Point2(3.0f, 4.0f));
        t.x = 4.0f; t.y = 3.0f;
        IS_NOTEQUAL(t, Point2(3.0f, 4.0f));
        counter.SetCount(t != Point2(3.0f, 4.0f));
        t = Point2(5.0f, 6.0f);
        IS_NOTEQUAL(t, Point2(3.0f, 4.0f));
        counter.SetCount(t != Point2(3.0f, 4.0f));
        Point2 x(3.0f, 4.0f);
        t = x;
        IS_EQUAL(t, Point2(3.0f, 4.0f));
        counter.SetCount(t == Point2(3.0f, 4.0f));

        cout << "Testing Point2 value change complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        cout << "Testing Point2 memory placement...\n";
        Point2 s(1.0f, 2.0f), t(3.0f, 4.0f);
        Point2 *a, *b;
        a = &s; b = &t;
        IS_NOTEQUAL(a,b);
        counter.SetCount(a != b);
        b = &s;
        IS_EQUAL(a,b);
        counter.SetCount(a == b);

        cout << "Testing Point2 memory placement complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void ClassOperators(void)
    {
        cout << "Testing Point2 class operators...\n";
        Point2 t(1.0f, 2.0f);
        t += Point2(-2.0f, 1.0f);
        IS_EQUAL(t, Point2(-1.0f, 3.0f));
        counter.SetCount(t == Point2(-1.0f, 3.0f));
        Vector2 v = (t -= Point2(2.0f, 1.0f));
        IS_EQUAL(v, Vector2(-3.0f, 2.0f));
        counter.SetCount(v == Vector2(-3.0f, 2.0f));
        t = Point2(-3.0f, 2.0f); t *= 2.0f;
        IS_EQUAL(t, Point2(-6.0f, 4.0f));
        counter.SetCount(t == Point2(-6.0f, 4.0f));
        t /= 2.0f;
        IS_EQUAL(t, Point2(-3.0f, 2.0f));
        counter.SetCount(t == Point2(-3.0f, 2.0f));
        IS_EQUAL(t.x, -3.0f);
        counter.SetCount(t.x == -3.0f);
        IS_EQUAL(t.y, 2.0f);
        counter.SetCount(t.y == 2.0f);
        IS_EQUAL(t.Zero(), Point2(0.0f, 0.0f));
        counter.SetCount(t.Zero() == Point2(0.0f, 0.0f));

        cout << "Testing Point2 class operators complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();

    }
    void Methods(void)
    {
        //! @brief Comment test \e \e \e \e \e \e \e \e
        cout << "Testing Point2 class methods...\n";
        Point2 t(1.0f, 2.0f);
        IS_EQUAL((t*t), 5.0f);
        counter.SetCount((t*t) == 5.0f);
        IS_NOTEQUAL((t*t), 3.0f);
        counter.SetCount((t*t) != 3.0f);
        IS_EQUAL((t.Zero()*t.Zero()), 0.0f);
        counter.SetCount((t.Zero()*t.Zero()) == 0.0f);

        Point2 x(3.0f, 4.0f);
        IS_EQUAL((t+x), Point2(4.0f, 6.0f));
        counter.SetCount((t+x) == Point2(4.0f, 6.0f));
        IS_NOTEQUAL((t+x), Point2(5.0f, 6.0f));
        counter.SetCount((t+x) != Point2(5.0f, 6.0f));
        IS_EQUAL((t-x), Vector2(-2.0f, -2.0f));
        counter.SetCount((t-x) == Vector2(-2.0f, -2.0f));
        IS_EQUAL((t*2.0f), Point2(2.0f, 4.0f));
        counter.SetCount((t*2.0f) == Point2(2.0f, 4.0f));
        IS_EQUAL((t/2.0f), Point2(0.5f, 1.0f));
        counter.SetCount((t/2.0f) == Point2(0.5f, 1.0f));
        IS_EQUAL((-t), Point2(-1.0f, -2.0f));
        counter.SetCount((-t) == Point2(-1.0f, -2.0f));
        IS_EQUAL((t*x), 11.0f);
        counter.SetCount((t*x) == 11.0f);

        cout << "Testing Point2 class methods complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            POINT2 UNIT TESTING          " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      ALL POINT2 TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestPoint3
{
    Counter counter;
    void Initialize(void)
    {
        Point3 t(2.0f, 3.0f, 4.0f);
        cout << "Testing Point3 initialization...\n";
        IS_EQUAL(t.ToString(), "("+to_string(2.0f)+", "+to_string(3.0f)+", "+to_string(4.0f)+")");
        counter.SetCount(t.ToString() == "("+to_string(2.0f)+", "+to_string(3.0f)+", "+to_string(4.0f)+")");
        t += Point3(1.0f, 2.0f, 3.0f);
        IS_EQUAL(t.ToString(), "("+to_string(3.0f)+", "+to_string(5.0f)+", "+to_string(7.0f)+")");
        counter.SetCount(t.ToString() == "("+to_string(3.0f)+", "+to_string(5.0f)+", "+to_string(7.0f)+")");
        t = Point3(-2.5f, -3.5f, -4.5f);
        IS_EQUAL(t.ToString(), "("+to_string(-2.5f)+", "+to_string(-3.5f)+", "+to_string(-4.5f)+")");
        counter.SetCount(t.ToString() == "("+to_string(-2.5f)+", "+to_string(-3.5f)+", "+to_string(-4.5f)+")");

        cout << "Testing Point3 initialization complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();

    }
    void ValueChange(void)
    {
        cout << "Testing Point3 value change...\n";
        Point3 t(2.0f, 3.0f, 4.0f);
        IS_EQUAL(t, Point3(2.0f, 3.0f, 4.0f));
        counter.SetCount(t == Point3(2.0f, 3.0f, 4.0f));
        t.x = 4.0f; t.y = 3.0f; t.z = 2.0f;
        IS_NOTEQUAL(t, Point3(2.0f, 3.0f, 4.0f));
        counter.SetCount(t != Point3(2.0f, 3.0f, 4.0f));
        t = Point3(4.0f, 5.0f, 6.0f);
        IS_NOTEQUAL(t, Point3(2.0f, 3.0f, 4.0f));
        counter.SetCount(t != Point3(2.0f, 3.0f, 4.0f));
        Point3 x(2.0f, 3.0f, 4.0f);
        t = x;
        IS_EQUAL(t, Point3(2.0f, 3.0f, 4.0f));
        counter.SetCount(t == Point3(2.0f, 3.0f, 4.0f));

        cout << "Testing Point3 value change complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        cout << "Testing Point3 memory placement...\n";
        Point3 s(1.0f, 2.0f, 3.0f), t(4.0f, 5.0f, 6.0f);
        Point3 *a, *b;
        a = &s; b = &t;
        IS_NOTEQUAL(a,b);
        counter.SetCount(a != b);
        b = &s;
        IS_EQUAL(a,b);
        counter.SetCount(a == b);

        cout << "Testing Point3 memory placement complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void ClassOperators(void)
    {
        cout << "Testing Point3 class operators...\n";
        Point3 t(1.0f, 2.0f, 3.0f);
        t += Point3(-2.0f, 1.0f, -2.5f);
        IS_EQUAL(t, Point3(-1.0f, 3.0f, 0.5f));
        counter.SetCount(t == Point3(-1.0f, 3.0, 0.5f));
        Vector3 v = (t -= Point3(2.0f, 1.0f, 4.0f));
        IS_EQUAL(v, Vector3(-3.0f, 2.0f, -3.5f));
        counter.SetCount(v == Vector3(-3.0f, 2.0f, -3.5f));
        t = Point3(-3.0f, 2.0f, -3.5f); t *= 2.0f;
        IS_EQUAL(t, Point3(-6.0f, 4.0f, -7.0f));
        counter.SetCount(t == Point3(-6.0f, 4.0f, -7.0f));
        t /= 2.0f;
        IS_EQUAL(t, Point3(-3.0f, 2.0f, -3.5f));
        counter.SetCount(t == Point3(-3.0f, 2.0f, -3.5f));
        IS_EQUAL(t.x, -3.0f);
        counter.SetCount(t.x == -3.0f);
        IS_EQUAL(t.y, 2.0f);
        counter.SetCount(t.y == 2.0f);
        IS_EQUAL(t.z, -3.5f);
        counter.SetCount(t.z == -3.5f);
        IS_EQUAL(t.Zero(), Point3(0.0f, 0.0f, 0.0f));
        counter.SetCount(t.Zero() == Point3(0.0f, 0.0f, 0.0f));

        cout << "Testing Point3 class operators complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();

    }
    void Methods(void)
    {
        cout << "Testing Point3 class methods...\n";
        Point3 t(1.0f, 2.0f, 3.0f);
        IS_EQUAL((t*t), 14.0f);
        counter.SetCount((t*t) == 14.0f);
        IS_NOTEQUAL((t*t), 10.0f);
        counter.SetCount((t*t) != 10.0f);
        IS_EQUAL((t.Zero()*t.Zero()), 0.0f);
        counter.SetCount((t.Zero()*t.Zero()) == 0.0f);

        Point3 x(3.0f, 4.0f, 5.0f);
        IS_EQUAL((t+x), Point3(4.0f, 6.0f, 8.0f));
        counter.SetCount((t+x) == Point3(4.0f, 6.0f, 8.0f));
        IS_NOTEQUAL((t+x), Point3(5.0f, 6.0f, 7.0f));
        counter.SetCount((t+x) != Point3(5.0f, 6.0f, 7.0f));
        IS_EQUAL((t-x), Vector3(-2.0f, -2.0f, -2.0f));
        counter.SetCount((t-x) == Vector3(-2.0f, -2.0f, -2.0f));
        IS_EQUAL((t*2.0f), Point3(2.0f, 4.0f, 6.0f));
        counter.SetCount((t*2.0f) == Point3(2.0f, 4.0f, 6.0f));
        IS_EQUAL((t/2.0f), Point3(0.5f, 1.0f, 1.5f));
        counter.SetCount((t/2.0f) == Point3(0.5f, 1.0f, 1.5f));
        IS_EQUAL((-t), Point3(-1.0f, -2.0f, -3.0f));
        counter.SetCount((-t) == Point3(-1.0f, -2.0f, -3.0f));
        IS_EQUAL((t*x), 26.0f);
        counter.SetCount((t*x) == 26.0f);

        cout << "Testing Point3 class methods complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            POINT3 UNIT TESTING          " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      ALL POINT3 TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestPoint4
{
    Counter counter;
    void Initialize(void){}
    void ValueChange(void){}
    void MemoryPlacement(void){}
    void ClassOperators(void){}
    void Methods(void){}
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            POINT4 UNIT TESTING          " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      ALL POINT4 TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestLine
{
    Counter counter;
    void Initialize(void){}
    void ValueChange(void){}
    void MemoryPlacement(void){}
    void ClassOperators(void){}
    void Methods(void){}
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            LINE UNIT TESTING          " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      ALL LINE TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestPlane
{
    Counter counter;
    void Initialize(void){}
    void ValueChange(void){}
    void MemoryPlacement(void){}
    void ClassOperators(void){}
    void Methods(void){}
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            PLANE UNIT TESTING          " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      ALL PLANE TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestHomogeneous3
{
    Counter counter;
    void Initialize(void){}
    void ValueChange(void){}
    void MemoryPlacement(void){}
    void ClassOperators(void){}
    void Methods(void){}
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      HOMOGENEOUSPOINT3 UNIT TESTING       " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      ALL HOMOGENEOUSPOINT3 TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestTriangle2
{
    Counter counter;
    void Initialize(void){}
    void ValueChange(void){}
    void MemoryPlacement(void){}
    void ClassOperators(void){}
    void Methods(void){}
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "           TRIANGLE2 UNIT TESTING          " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "     ALL TRIANGLE2 TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestTriangle3
{
    Counter counter;
    void Initialize(void){}
    void ValueChange(void){}
    void MemoryPlacement(void){}
    void ClassOperators(void){}
    void Methods(void){}
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "           TRIANGLE3 UNIT TESTING          " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "     ALL TRIANGLE3 TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestMatrix2
{
    Counter counter;
    void Initialize(void){}
    void ValueChange(void){}
    void MemoryPlacement(void){}
    void ClassOperators(void){}
    void Methods(void){}
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "           MATRIX2 UNIT TESTING          " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "     ALL MATRIX2 TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestMatrix3
{
    Counter counter;
    void Initialize(void){}
    void ValueChange(void){}
    void MemoryPlacement(void){}
    void ClassOperators(void){}
    void Methods(void){}
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            MATRIX3 UNIT TESTING           " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      ALL MATRIX3 TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestMatrix4
{
    Counter counter;
    void Initialize(void){}
    void ValueChange(void){}
    void MemoryPlacement(void){}
    void ClassOperators(void){}
    void Methods(void){}
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            MATRIX4 UNIT TESTING           " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      ALL MATRIX4 TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestTransform3
{
    Counter counter;
    void Initialize(void){}
    void ValueChange(void){}
    void MemoryPlacement(void){}
    void ClassOperators(void){}
    void Methods(void){}
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            TRANSFORM3 UNIT TESTING           " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      ALL TRANSFORM3 TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestTransform4
{
    Counter counter;
    void Initialize(void){}
    void ValueChange(void){}
    void MemoryPlacement(void){}
    void ClassOperators(void){}
    void Methods(void){}
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            TRANSFORM4 UNIT TESTING           " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      ALL TRANSFORM4 TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};
struct TestQuaternion
{
    Counter counter;
    void Initialize(void){}
    void ValueChange(void){}
    void MemoryPlacement(void){}
    void ClassOperators(void){}
    void Methods(void){}
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            QUATERNION UNIT TESTING           " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
        ClassOperators();
        Methods();

        cout << endl << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "      ALL QUATERNION TESTS HAVE FINISHED      " << endl;
        cout << " - Total Tests: " << to_string(counter.GetAccumulatorTotal()) << endl;
        cout << " - Tests Passed: " << to_string(counter.GetAccumulatorPass()) << endl;
        cout << " - Tests Failed: " << to_string(counter.GetAccumulatorFail()) << endl << endl;
        counter.ResetAccumulator();
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    }
};