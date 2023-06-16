#pragma once
#include <cmath>
#include <iostream>
#include <string>
#include "Math\Vectors.h"
#include "Math\Geometry.h"
#include "Math\Matrices.h"

using namespace std;

#define IS_TRUE(testVal) if (!(testVal)) cout << __FUNCTION__ << " test failed on line " << __LINE__ << endl
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
private:
    Counter counter;
public:
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
        Print("Testing Vector2 memory placement...");
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
        IS_CLOSE(AngleDegrees(t,x), 10.304846f);
        counter.SetCountClose(AngleDegrees(t,x), 10.304846f);
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
private:
    Counter counter;
public:
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
        IS_CLOSE(AngleDegrees(t,x), 22.517836f);
        counter.SetCountClose(AngleDegrees(t,x), 22.517836f);
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
private:
    Counter counter;
public:
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
        IS_CLOSE(AngleDegrees(t,x), 17.29398302f);
        counter.SetCountClose(AngleDegrees(t,x), 17.29398302f);

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
private:
    Counter counter;
public:
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

        Vector2 v(2.0f, 3.0f);
        IS_EQUAL(toPoint(v), Point2(2.0f, 3.0f));
        counter.SetCount(toPoint(v) == Point2(2.0f, 3.0f));

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
private:
    Counter counter;
public:
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

        Vector3 v(4.0f, 7.0f, 3.0f);
        IS_EQUAL(toPoint(v), Point3(4.0f, 7.0f, 3.0f));
        counter.SetCount(toPoint(v) == Point3(4.0f, 7.0f, 3.0f));

        Point3 y(4.0f, 1.0f, 3.0f);
        IS_EQUAL(Normal(t,x,y), Vector3(2.0f, 6.0f, -8.0f));
        counter.SetCount(Normal(t,x,y) == Vector3(2.0f, 6.0f, -8.0f));
        IS_CLOSE(DistanceToLine(t, x, v), sqrtf(52.0f/37.0f));
        counter.SetCountClose(DistanceToLine(t, x, v), sqrtf(52.0f/37.0f));
        IS_CLOSE(ClosestDistanceToPoint(v, x, y), (13.0f/74.0f)*sqrtf(222.0f));
        counter.SetCountClose(ClosestDistanceToPoint(v, x, y), (13.0f/74.0f)*sqrtf(222.0f));
        IS_CLOSE(DistanceBetweenLines(t, v, x, (y-t)), 2.0f*sqrt(13.0f/55.0f));
        counter.SetCountClose(DistanceBetweenLines(t, v, x, (y-t)), 2.0f*sqrt(13.0f/55.0f));


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
private:
    Counter counter;
public:
    void Initialize(void)
    {
        Point4 t(1.0f, 2.0f, 3.0f, 4.0f);
        cout << "Testing Point4 initialization...\n";
        IS_EQUAL(t.ToString(), "("+to_string(1.0f)+", "+to_string(2.0f)+", "+to_string(3.0f)+", "+to_string(4.0f)+")");
        counter.SetCount(t.ToString() == "("+to_string(1.0f)+", "+to_string(2.0f)+", "+to_string(3.0f)+", "+to_string(4.0f)+")");
        t += Point4(0.0f, 1.0f, 2.0f, 3.0f);
        IS_EQUAL(t.ToString(), "("+to_string(1.0f)+", "+to_string(3.0f)+", "+to_string(5.0f)+", "+to_string(7.0f)+")");
        counter.SetCount(t.ToString() == "("+to_string(1.0f)+", "+to_string(3.0f)+", "+to_string(5.0f)+", "+to_string(7.0f)+")");
        t = Point4(-1.5f, -2.5f, -3.5f, -4.5f);
        IS_EQUAL(t.ToString(), "("+to_string(-1.5f)+", "+to_string(-2.5f)+", "+to_string(-3.5f)+", "+to_string(-4.5f)+")");
        counter.SetCount(t.ToString() == "("+to_string(-1.5f)+", "+to_string(-2.5f)+", "+to_string(-3.5f)+", "+to_string(-4.5f)+")");

        cout << "Testing Point4 initialization complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();

    }
    void ValueChange(void)
    {
        cout << "Testing Point4 value change...\n";
        Point4 t(1.0f, 2.0f, 3.0f, 4.0f);
        IS_EQUAL(t, Point4(1.0f, 2.0f, 3.0f, 4.0f));
        counter.SetCount(t == Point4(1.0f, 2.0f, 3.0f, 4.0f));
        t.x = 4.0f; t.y = 3.0f; t.z = 2.0f; t.w = 1.0f;
        IS_NOTEQUAL(t, Point4(2.0f, 3.0f, 4.0f, 1.0f));
        counter.SetCount(t != Point4(2.0f, 3.0f, 4.0f, 1.0f));
        t = Point4(4.0f, 5.0f, 6.0f, 7.0f);
        IS_NOTEQUAL(t, Point4(1.0f, 2.0f, 3.0f, 4.0f));
        counter.SetCount(t != Point4(1.0f, 2.0f, 3.0f, 4.0f));
        Point4 x(1.0f, 2.0f, 3.0f, 4.0f);
        t = x;
        IS_EQUAL(t, Point4(1.0f, 2.0f, 3.0f, 4.0f));
        counter.SetCount(t == Point4(1.0f, 2.0f, 3.0f, 4.0f));

        cout << "Testing Point4 value change complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        cout << "Testing Point4 memory placement...\n";
        Point4 s(0.0f, 1.0f, 2.0f, 3.0f), t(4.0f, 5.0f, 6.0f, 7.0f);
        Point4 *a, *b;
        a = &s; b = &t;
        IS_NOTEQUAL(a,b);
        counter.SetCount(a != b);
        b = &s;
        IS_EQUAL(a,b);
        counter.SetCount(a == b);

        cout << "Testing Point4 memory placement complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void ClassOperators(void)
    {
        cout << "Testing Point4 class operators...\n";
        Point4 t(1.0f, 2.0f, 3.0f, 4.0f);
        t += Point4(-2.0f, 1.0f, -2.5f, -1.0f);
        IS_EQUAL(t, Point4(-1.0f, 3.0f, 0.5f, 3.0f));
        counter.SetCount(t == Point4(-1.0f, 3.0, 0.5f, 3.0f));
        Vector4 v = (t -= Point4(2.0f, 1.0f, 4.0f, 2.0f));
        IS_EQUAL(v, Vector4(-3.0f, 2.0f, -3.5f, 1.0f));
        counter.SetCount(v == Vector4(-3.0f, 2.0f, -3.5f, 1.0f));
        t = Point4(-3.0f, 2.0f, -3.5f, 2.5f); t *= 2.0f;
        IS_EQUAL(t, Point4(-6.0f, 4.0f, -7.0f, 5.0f));
        counter.SetCount(t == Point4(-6.0f, 4.0f, -7.0f, 5.0f));
        t /= 2.0f;
        IS_EQUAL(t, Point4(-3.0f, 2.0f, -3.5f, 2.5f));
        counter.SetCount(t == Point4(-3.0f, 2.0f, -3.5f, 2.5f));
        IS_EQUAL(t.x, -3.0f);
        counter.SetCount(t.x == -3.0f);
        IS_EQUAL(t.y, 2.0f);
        counter.SetCount(t.y == 2.0f);
        IS_EQUAL(t.z, -3.5f);
        counter.SetCount(t.z == -3.5f);
        IS_EQUAL(t.w, 2.5f);
        counter.SetCount(t.w == 2.5f);
        IS_EQUAL(t.Zero(), Point4(0.0f, 0.0f, 0.0f, 0.0f));
        counter.SetCount(t.Zero() == Point4(0.0f, 0.0f, 0.0f, 0.0f));

        cout << "Testing Point4 class operators complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();

    }
    void Methods(void)
    {
        cout << "Testing Point4 class methods...\n";
        Point4 t(1.0f, 2.0f, 3.0f, 4.0f);
        IS_EQUAL((t*t), 30.0f);
        counter.SetCount((t*t) == 30.0f);
        IS_NOTEQUAL((t*t), 10.0f);
        counter.SetCount((t*t) != 10.0f);
        IS_EQUAL((t.Zero()*t.Zero()), 0.0f);
        counter.SetCount((t.Zero()*t.Zero()) == 0.0f);

        Point4 x(3.0f, 4.0f, 5.0f, 6.0f);
        IS_EQUAL((t+x), Point4(4.0f, 6.0f, 8.0f, 10.0f));
        counter.SetCount((t+x) == Point4(4.0f, 6.0f, 8.0f, 10.0f));
        IS_NOTEQUAL((t+x), Point4(5.0f, 6.0f, 7.0f, 8.0f));
        counter.SetCount((t+x) != Point4(5.0f, 6.0f, 7.0f, 8.0f));
        IS_EQUAL((t-x), Vector4(-2.0f, -2.0f, -2.0f, -2.0f));
        counter.SetCount((t-x) == Vector4(-2.0f, -2.0f, -2.0f, -2.0f));
        IS_EQUAL((t*2.0f), Point4(2.0f, 4.0f, 6.0f, 8.0f));
        counter.SetCount((t*2.0f) == Point4(2.0f, 4.0f, 6.0f, 8.0f));
        IS_EQUAL((t/2.0f), Point4(0.5f, 1.0f, 1.5f, 2.0f));
        counter.SetCount((t/2.0f) == Point4(0.5f, 1.0f, 1.5f, 2.0f));
        IS_EQUAL((-t), Point4(-1.0f, -2.0f, -3.0f, -4.0f));
        counter.SetCount((-t) == Point4(-1.0f, -2.0f, -3.0f, -4.0f));
        IS_EQUAL((t*x), 50.0f);
        counter.SetCount((t*x) == 50.0f);

        Vector4 v(4.0f, 2.0f, 3.0f, 5.0f);
        IS_EQUAL(toPoint(v), Point4(4.0f, 2.0f, 3.0f, 5.0f));
        counter.SetCount(toPoint(v) == Point4(4.0f, 2.0f, 3.0f, 5.0f));


        cout << "Testing Point4 class methods complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
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
struct TestHomogeneousPoint3
{
private:
    Counter counter;
public:
    void Initialize(void)
    {
        HomogeneousPoint3 t(1.0f, 2.0f, 3.0f, 1.0f);
        cout << "Testing HomogeneousPoint3 initialization...\n";
        IS_EQUAL(t.ToString(), ("{p = ("+to_string(1.0f)+", "+to_string(2.0f)+", "+to_string(3.0f)+")| w = "+to_string(1.0f)+"}"));
        counter.SetCount(t.ToString() == "{p = ("+to_string(1.0f)+", "+to_string(2.0f)+", "+to_string(3.0f)+")| w = "+to_string(1.0f)+"}");
        t += HomogeneousPoint3(4.0f, 6.0f,-6.0f, 2.0f);
        IS_EQUAL(t.ToString(), "{p = ("+to_string(6.0f)+", "+to_string(10.0f)+", "+to_string(0.0f)+")| w = "+to_string(2.0f)+"}");
        counter.SetCount(t.ToString() == "{p = ("+to_string(6.0f)+", "+to_string(10.0f)+", "+to_string(0.0f)+")| w = "+to_string(2.0f)+"}");
        t -= HomogeneousPoint3(4.0f, 6.0f,-6.0f, 2.0f);
        IS_EQUAL(t.ToString(), "{p = ("+to_string(4.0f)+", "+to_string(8.0f)+", "+to_string(12.0f)+")| w = "+to_string(4.0f)+"}");
        counter.SetCount(t.ToString() == "{p = ("+to_string(4.0f)+", "+to_string(8.0f)+", "+to_string(12.0f)+")| w = "+to_string(4.0f)+"}");

        t = HomogeneousPoint3(Point3(1.0f, 2.0f, 3.0f), 2.0f);
        IS_EQUAL(t.ToString(), "{p = ("+to_string(2.0f)+", "+to_string(4.0f)+", "+to_string(6.0f)+")| w = "+to_string(2.0f)+"}");
        counter.SetCount(t.ToString() == "{p = ("+to_string(2.0f)+", "+to_string(4.0f)+", "+to_string(6.0f)+")| w = "+to_string(2.0f)+"}");

        cout << "Testing HomogeneousPoint3 initialization complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void ValueChange(void)
    {
        cout << "Testing HomogeneousPoint3 value change..." << endl;
        HomogeneousPoint3 t(1.0f, 2.0f, 3.0f, 1.0f);
        IS_EQUAL(t, HomogeneousPoint3(1.0f, 2.0f, 3.0f, 1.0f));
        counter.SetCount(t == HomogeneousPoint3(1.0f, 2.0f, 3.0f, 1.0f));

        t.x = 4.0f; t.y = 6.0f; t.z = -6.0f; t.w = 2.0f;
        IS_EQUAL(t, HomogeneousPoint3(4.0f, 6.0f, -6.0f, 2.0f));
        counter.SetCount(t == HomogeneousPoint3(4.0f, 6.0f, -6.0f, 2.0f));
        IS_EQUAL(t.toPoint3(), Point3(2.0f, 3.0f, -3.0f));
        counter.SetCount(t.toPoint3() == Point3(2.0f, 3.0f, -3.0f));
        IS_EQUAL(t.PointPart(), Point3(4.0f, 6.0f, -6.0f));
        counter.SetCount(t.PointPart() == Point3(4.0f, 6.0f, -6.0f));
        IS_NOTEQUAL(t, HomogeneousPoint3(1.0f, 2.0f, 3.0f, 1.0f));
        counter.SetCount(t != HomogeneousPoint3(1.0f, 2.0f, 3.0f, 1.0f));

        t = HomogeneousPoint3(2.0f, 4.0f, 6.0f, 2.0f);
        IS_NOTEQUAL(t, HomogeneousPoint3(1.0f, 2.0f, 3.0f, 2.0f));
        counter.SetCount(t != HomogeneousPoint3(1.0f, 2.0f, 3.0f, 2.0f));
        IS_EQUAL(t, HomogeneousPoint3(1.0f, 2.0f, 3.0f, 1.0f));
        counter.SetCount(t == HomogeneousPoint3(1.0f, 2.0f, 3.0f, 1.0f));

        HomogeneousPoint3 x(3.0f, 2.0f, 1.0f, 1.0f);
        t = x;
        IS_EQUAL(t, HomogeneousPoint3(6.0f, 4.0f, 2.0f, 2.0f));
        counter.SetCount(t == HomogeneousPoint3(6.0f, 4.0f, 2.0f, 2.0f));
        IS_NOTEQUAL(t, HomogeneousPoint3(1.0f, 2.0f, 3.0f, 1.0f));
        counter.SetCount(t != HomogeneousPoint3(1.0f, 2.0f, 3.0f, 1.0f));

        cout << "Testing HomogeneousPoint3 value change complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        cout << "Testing HomogeneousPoint3 memory placement..." << endl;
        HomogeneousPoint3 s(1.0f, 2.0f, 3.0f, 1.0f), t(3.0f, 2.0f, 3.0f, 2.0f);
        HomogeneousPoint3 *a, *b;
        a = &s; b = &t;
        IS_NOTEQUAL(a, b);
        counter.SetCount(a != b);
        b = &s;
        IS_EQUAL(a, b);
        counter.SetCount(a == b);

        cout << "Testing HomogeneousPoint3 memory placement complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void ClassOperators(void)
    {
        cout << "Testing HomogeneousPoint3 class operators..." << endl;
        HomogeneousPoint3 t(1.0f, 2.0f, 3.0f, 1.0f);

        t += HomogeneousPoint3(2.0f, 2.0f, 2.0f, 2.0f);
        IS_EQUAL(t, HomogeneousPoint3(2.0f, 3.0f, 4.0f, 1.0f));
        counter.SetCount(t == HomogeneousPoint3(2.0f, 3.0f, 4.0f, 1.0f));

        t -= HomogeneousPoint3(2.0f, 2.0f, 2.0f, 2.0f);
        IS_EQUAL(t, HomogeneousPoint3(1.0f, 2.0f, 3.0f, 1.0f));
        counter.SetCount(t == HomogeneousPoint3(1.0f, 2.0f, 3.0f, 1.0f));

        t = HomogeneousPoint3(1.0f, 2.0f, 3.0f, 1.0f);
        t *= 2.0f;
        IS_EQUAL(t, HomogeneousPoint3(2.0f, 4.0f, 6.0f, 1.0f));
        counter.SetCount(t == HomogeneousPoint3(2.0f, 4.0f, 6.0f, 1.0f));
        IS_NOTEQUAL(t, HomogeneousPoint3(2.0f, 4.0f, 6.0f, 2.0f));
        counter.SetCount(t != HomogeneousPoint3(2.0f, 4.0f, 6.0f, 2.0f));

        t = HomogeneousPoint3(1.0f, 2.0f, 3.0f, 1.0f);
        float f = (t *= HomogeneousPoint3(2.0f, 2.0f, 2.0f, 2.0f));
        IS_EQUAL(f, 6.0f);
        counter.SetCount(f == 6.0f);

        t = HomogeneousPoint3(2.0f, 4.0f, 6.0f, 1.0f);
        t /= 2.0f;
        IS_EQUAL(t, HomogeneousPoint3(1.0f, 2.0f, 3.0f, 1.0f));
        counter.SetCount(t == HomogeneousPoint3(1.0f, 2.0f, 3.0f, 1.0f));
        IS_NOTEQUAL(t, HomogeneousPoint3(2.0f, 4.0f, 6.0f, 1.0f));
        counter.SetCount(t != HomogeneousPoint3(2.0f, 4.0f, 6.0f, 1.0f));

        t = HomogeneousPoint3(2.0f, 4.0f, 6.0f, 2.0f);
        IS_EQUAL(t.PointPart(), Point3(2.0f, 4.0f, 6.0f));
        counter.SetCount(t.PointPart() == Point3(2.0f, 4.0f, 6.0f));
        IS_NOTEQUAL(t.PointPart(), Point3(1.0f, 2.0f, 3.0f));
        counter.SetCount(t.PointPart() != Point3(1.0f, 2.0f, 3.0f));
        IS_EQUAL(t.toPoint3(), Point3(1.0f, 2.0f, 3.0f));
        counter.SetCount(t.toPoint3() == Point3(1.0f, 2.0f, 3.0f));
        IS_NOTEQUAL(t.toPoint3(), Point3(2.0f, 4.0f, 6.0f));
        counter.SetCount(t.toPoint3() != Point3(2.0f, 4.0f, 6.0f));

        IS_EQUAL(t.x, 2.0f);
        counter.SetCount(t.x == 2.0f);
        IS_EQUAL(t.y, 4.0f);
        counter.SetCount(t.y == 4.0f);
        IS_EQUAL(t.z, 6.0f);
        counter.SetCount(t.z == 6.0f);
        IS_EQUAL(t.w, 2.0f);
        counter.SetCount(t.w == 2.0f);

        cout << "Testing HomogeneousPoint3 class operators complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void Methods(void)
    {
        cout << "Testing HomogeneousPoint3 methods..." << endl;
        HomogeneousPoint3 t(1.0f, 2.0f, 3.0f, 1.0f), x(6.0f, 4.0f, 2.0f, 2.0f);

        IS_EQUAL((t+x), HomogeneousPoint3(4.0f, 4.0f, 4.0f, 1.0f));
        counter.SetCount((t+x) == HomogeneousPoint3(4.0f, 4.0f, 4.0f, 1.0f));
        IS_EQUAL((t-x), HomogeneousPoint3(-2.0f, 0.0f, 2.0f, 1.0f));
        counter.SetCount((t-x) == HomogeneousPoint3(-2.0f, 0.0f, 2.0f, 1.0f));
        IS_EQUAL((t*x), 10.0f);
        counter.SetCount((t*x) == 10.0f);
        IS_EQUAL((t*2.0f), HomogeneousPoint3(2.0f, 4.0f, 6.0f, 1.0f));
        counter.SetCount((t*2.0f) == HomogeneousPoint3(2.0f, 4.0f, 6.0f, 1.0f));
        IS_EQUAL((t/2.0f), HomogeneousPoint3(1.0f, 2.0f, 3.0f, 2.0f));
        counter.SetCount((t/2.0f) == HomogeneousPoint3(1.0f, 2.0f, 3.0f, 2.0f));


        Line L(1.0f, 2.0f, 3.0f, 3.0f, 4.0f, 5.0f);
        IS_EQUAL(ClosestPointToOrigin(L), HomogeneousPoint3(-2.0f, 4.0f, -2.0f, 14.0f));
        counter.SetCount(ClosestPointToOrigin(L) == HomogeneousPoint3(-2.0f, 4.0f, -2.0f, 14.0f));
        Plane p(1.0f, 2.0f, 3.0f, 2.0f);
        IS_EQUAL(ClosestPointToOrigin(p), HomogeneousPoint3(-2.0f, -4.0f, -6.0f, 14.0f));
        counter.SetCount(ClosestPointToOrigin(p) == HomogeneousPoint3(-2.0f, -4.0f, -6.0f, 14.0f));
        IS_EQUAL(FurthestPlaneFromOriginWithHomogeneousPoint(t), Plane(-1.0f, -2.0f, -3.0f, 14.0f));
        counter.SetCount(FurthestPlaneFromOriginWithHomogeneousPoint(t) == Plane(-1.0f, -2.0f, -3.0f, 14.0f));
        IS_EQUAL(MakePlane(L, t), Plane(3.0f, 4.0f, 5.0f, -26.0f));
        counter.SetCount(MakePlane(L, t) == Plane(3.0f, 4.0f, 5.0f, -26.0f));
        IS_EQUAL(MakeLine(t, x), Line(4.0f, 0.0f, -4.0f, -8.0f, 16.0f, -8.0f));
        counter.SetCount(MakeLine(t, x) == Line(4.0f, 0.0f, -4.0f, -8.0f, 16.0f, -8.0f));



        cout << "Testing HomogeneousPoint3 methods complete!\n";
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
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
struct TestLine
{
private:
    Counter counter;
public:
    void Initialize(void)
    {
        cout << "Testing Line initialization..." << endl;
        Line L(2.0f, 2.0f, 3.0f, -1.0f, 2.0f, -2.0f);

        IS_EQUAL(L.ToString(),
            "{d = ("+to_string(2.0f)+", "+to_string(2.0f)+", "+to_string(3.0f)+")| m = ("+to_string(-1.0f)+", "+to_string(2.0f)+", "+to_string(-2.0f)+")}");
        counter.SetCount(L.ToString() ==
            "{d = ("+to_string(2.0f)+", "+to_string(2.0f)+", "+to_string(3.0f)+")| m = ("+to_string(-1.0f)+", "+to_string(2.0f)+", "+to_string(-2.0f)+")}");
        L = Line(Vector3(1.0f, 2.0f, 3.0f), Vector3(4.0f, 5.0f, 6.0f));
        IS_EQUAL(L.ToString(),
            "{d = ("+to_string(1.0f)+", "+to_string(2.0f)+", "+to_string(3.0f)+")| m = ("+to_string(4.0f)+", "+to_string(5.0f)+", "+to_string(6.0f)+")}");
        counter.SetCount(L.ToString() ==
            "{d = ("+to_string(1.0f)+", "+to_string(2.0f)+", "+to_string(3.0f)+")| m = ("+to_string(4.0f)+", "+to_string(5.0f)+", "+to_string(6.0f)+")}");
        L = Line(Vector3(1.0f, 3.0f, 2.0f), Point3(2.0f, 3.5f, -1.0f));
        IS_EQUAL(L.ToString(),
            "{d = ("+to_string(1.0f)+", "+to_string(3.0f)+", "+to_string(2.0f)+")| m = ("+to_string(10.0f)+", "+to_string(-5.0f)+", "+to_string(2.5f)+")}");
        counter.SetCount(L.ToString() ==
            "{d = ("+to_string(1.0f)+", "+to_string(3.0f)+", "+to_string(2.0f)+")| m = ("+to_string(10.0f)+", "+to_string(-5.0f)+", "+to_string(2.5f)+")}");
        L = Line(Point3(2.0f, 3.0f, 1.0f), Point3(6.0f, 5.0f, 1.0f));
        IS_EQUAL(L.ToString(),
            "{d = ("+to_string(4.0f)+", "+to_string(2.0f)+", "+to_string(0.0f)+")| m = ("+to_string(-2.0f)+", "+to_string(4.0f)+", "+to_string(-8.0f)+")}");
        counter.SetCount(L.ToString() ==
            "{d = ("+to_string(4.0f)+", "+to_string(2.0f)+", "+to_string(0.0f)+")| m = ("+to_string(-2.0f)+", "+to_string(4.0f)+", "+to_string(-8.0f)+")}");
        L = Line(Point3(3.0f, 2.0f, 3.0f));
        IS_EQUAL(L.ToString(),
            "{d = ("+to_string(3.0f)+", "+to_string(2.0f)+", "+to_string(3.0f)+")| m = ("+to_string(0.0f)+", "+to_string(0.0f)+", "+to_string(0.0f)+")}");

        cout << "Testing of Line initalization complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void ValueChange(void)
    {
        cout << "Testing Line value change..." << endl;

        Line L(2.4f, 3.2f, 4.4f, 2.0f, 4.0f, 2.0f);
        IS_EQUAL(L.direction, Vector3(2.4f, 3.2f, 4.4f));
        counter.SetCount(L.direction == Vector3(2.4f, 3.2f, 4.4f));
        IS_EQUAL(L.moment, Vector3(2.0f, 4.0f, 2.0f));
        counter.SetCount(L.moment == Vector3(2.0f, 4.0f, 2.0f));
        L.direction = Vector3(2.0f, 1.0f, 3.0f);
        L.moment = Vector3(5.0f, 7.0f, 3.0f);
        IS_EQUAL(L.direction, Vector3(2.0f, 1.0f, 3.0f));
        counter.SetCount(L.direction == Vector3(2.0f, 1.0f, 3.0f));
        IS_EQUAL(L.moment, Vector3(5.0f, 7.0f, 3.0f));
        counter.SetCount(L.moment == Vector3(5.0f, 7.0f, 3.0f));
        L.direction.x = 0.1f; L.direction.y = 0.2f; L.direction.z = 0.3f;
        L.moment.x = 3.0f; L.moment.y = 4.0f; L.moment.z = 2.0f;
        IS_EQUAL(L.direction, Vector3(0.1f, 0.2f, 0.3f));
        counter.SetCount(L.direction == Vector3(0.1f, 0.2f, 0.3f));
        IS_EQUAL(L.moment, Vector3(3.0f, 4.0f, 2.0f));
        counter.SetCount(L.moment == Vector3(3.0f, 4.0f, 2.0f));

        cout << "Testing of Line value change complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        cout << "Testing Line memory placement..." << endl;
        Line L(2.0f, 2.0f, 3.0f, -1.0f, 2.0f, -2.0f);
        Line M(4.0f, 2.0f, 0.0f, 5.0f, -7.0f, -4.0f);
        Line *a, *b;
        a = &L;
        b = &M;
        IS_NOTEQUAL(a,b);
        counter.SetCount(a != b);
        b = &L;
        IS_EQUAL(a,b);
        counter.SetCount(a == b);

        cout << "Testing of Line memory placement complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void Methods(void)
    {
        cout << "Testing Line methods..." << endl;

        Line L(2.0f, 2.0f, 3.0f, -1.0f, 2.0f, -2.0f);
        Line M(4.0f, 2.0f, 0.0f, 5.0f, -7.0f, -4.0f);
        IS_CLOSE(DistanceTwoLines(L,M), (8.0f/7.0f));
        counter.SetCountClose(DistanceTwoLines(L,M), (8.0f/7.0f));

        Point3 p(3.0f, 2.0f, 3.0f);
        IS_CLOSE(DistanceLinePoint(L, p), sqrtf(42.0f)/sqrtf(17.0f));
        counter.SetCountClose(DistanceLinePoint(L, p), sqrtf(42.0f)/sqrtf(17.0f));
        IS_CLOSE(DistanceLineOrigin(L), 3.0f/sqrtf(17.0f));
        counter.SetCountClose(DistanceLineOrigin(L), 3.0f/sqrtf(17.0f));

        cout << "Testing of Line methods complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();

    }
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            LINE UNIT TESTING          " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
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
private:
    Counter counter;
public:
    void Initialize(void)
    {
        cout << "Testing Plane initialization..." << endl;
        Plane p(1.0f, 2.0f, 3.0f, 4.0f);
        IS_EQUAL(p.Normal(), Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(p.Normal() == Vector3(1.0f, 2.0f, 3.0f));
        IS_EQUAL(p.w, 4.0f);
        counter.SetCount(p.w == 4.0f);

        p = Plane(2.0f, 3.0f, 2.0f, 1.0f);
        IS_EQUAL(p.Normal(), Vector3(2.0f, 3.0f, 2.0f));
        counter.SetCount(p.Normal() == Vector3(2.0f, 3.0f, 2.0f));
        IS_EQUAL(p.w, 1.0f);
        counter.SetCount(p.w == 1.0f);

        cout << "Testing Plane initialization complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();

    }
    void ValueChange(void)
    {
        cout << "Testing Plane value change..." << endl;
        Plane p(1.0f, 2.0f, 3.0f, 4.0f);
        IS_EQUAL(p.Normal(), Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(p.Normal() == Vector3(1.0f, 2.0f, 3.0f));
        IS_EQUAL(p.w, 4.0f);
        counter.SetCount(p.w == 4.0f);
        p.x = 8.0f, p.y = 6.0f, p.z = 7.0f, p.w = 5.0f;
        IS_EQUAL(p.Normal(), Vector3(8.0f, 6.0f, 7.0f));
        counter.SetCount(p.Normal() == Vector3(8.0f, 6.0f, 7.0f));
        IS_EQUAL(p.w, 5.0f);
        counter.SetCount(p.w == 5.0f);

        cout << "Testing of Plane value change complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        cout << "Testing Plane memory placement..." << endl;
        Plane f(1.0f, 2.0f, 3.0f, 4.0f);
        Plane g(Vector3(1.0f, 2.0f, 3.0f), 4.0f);
        Plane *a = &f, *b = &g;
        IS_NOTEQUAL(a,b);
        counter.SetCount(a != b);
        IS_EQUAL(*a,*b);
        counter.SetCount(*a == *b);
        b = &f;
        IS_EQUAL(a,b);
        counter.SetCount(a == b);
        IS_EQUAL(*a, *b);
        counter.SetCount(*a == *b);
        cout << "Testing of Plane memory placement complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void Methods(void)
    {
        cout << "Testing Plane methods..." << endl;
        Plane f(1.0f, 2.0f, 3.0f, 4.0f);
        Vector3 v(2.0f, 3.0f, -2.0f);
        Point3 p(-1.0f, 5.0f, -4.0f);
        Line L(2.0f, 3.0f, -1.0f, 3.0f, -2.0f, -1.5f);


        IS_EQUAL(f*v, 2.0f);
        counter.SetCount(f*v == 2.0f);
        IS_EQUAL(f*p, 1.0f);
        counter.SetCount(f*p == 1.0f);
        IS_CLOSE(DistancePlanePoint(f, p), 1.0f/sqrtf(14.0f));
        counter.SetCountClose(DistancePlanePoint(f, p), 1.0f/sqrtf(14.0f));
        IS_CLOSE(DistancePlaneOrigin(f), 4.0f/sqrtf(14.0f));
        counter.SetCountClose(DistancePlaneOrigin(f), 4.0f/sqrtf(14.0f));
        IS_EQUAL(MakePlane(L, v), Plane(Vector3(-3.0f, 2.0f, 0.0f), -3.0f));
        counter.SetCount(MakePlane(L, v) == Plane(Vector3(-3.0f, 2.0f, 0.0f), -3.0f));
        IS_EQUAL(MakePlane(L, p), Plane(Vector3(-4.0f, 7.0f, 11.5f), 7.0f));
        counter.SetCount(MakePlane(L, p) == Plane(Vector3(-4.0f, 7.0f, 11.5f), 7.0f));
        IS_EQUAL(MakePlaneWithOrigin(L), Plane(Vector3(3.0f, -2.0f, -1.5f), 0.0f));
        counter.SetCount(MakePlaneWithOrigin(L) == Plane(Vector3(3.0f, -2.0f, -1.5f), 0.0f));

        L = Line(2.0f, -1.0f, 4.0f, 5.0f, 3.0f, -7.0f);
        IS_EQUAL(FurthestPlaneFromOriginWithLine(L), Plane(Vector3(5.0f, -34.0f, -11.0f), 83.0f));
        counter.SetCount(FurthestPlaneFromOriginWithLine(L) == Plane(Vector3(5.0f, -34.0f, -11.0f), 83.0f));

        Point3 q;
        bool b = Intersection(Point3(2.0f, 1.0f, 0.0f), Vector3(-1.0f, 1.0f, 3.0f), Plane(3.0f, -2.0f, 1.0f, -10.0f), &q);
        IS_TRUE(b);
        counter.SetCount(b);
        IS_EQUAL(q, Point3(5.0f, -2.0f, -9.0f));
        counter.SetCount(q == Point3(5.0f, -2.0f, -9.0f));
        b = Intersection(Point3(1.0f, -2.0f, -1.0f), Vector3(2.0f, 3.0f, 4.0f), Plane(1.0f, 2.0f, -2.0f, -5.0f), &q);
        IS_FALSE(b);
        counter.SetCount(!b);

        v = v.Zero(); p = p.Zero();
        b = Intersection(Plane(1.0f, 3.0f, 2.0f, -6.0f), Plane(2.0f, -1.0f, 1.0f, 2.0f), &p, &v);
        IS_TRUE(b);
        counter.SetCount(b);
        float d = DistanceLinePoint(Line(v,p), Point3(0.0f, 2.0f, 0.0f));
        IS_CLOSE(d, 0.0f);
        counter.SetCountClose(d, 0.0f);
        IS_EQUAL(v, Vector3(5.0f, 3.0f, -7.0f));
        counter.SetCount(v == Vector3(5.0f, 3.0f, -7.0f));

        b = Intersection(Plane(1.0f, 3.0f, 2.0f, -6.0f), Plane(-2.0f, -6.0f, -4.0f, 2.0f), &p, &v);
        IS_FALSE(b);
        counter.SetCount(!b);

        HomogeneousPoint3 h;
        b = Intersection(Line(Vector3(-1.0f, 1.0f, 3.0f), Point3(2.0f, 1.0f, 0.0f)),
                        Plane(3.0f, -2.0f, 1.0f, -10.0f), &h);
        IS_TRUE(b);
        counter.SetCount(b);
        IS_EQUAL(h.toPoint3(), Point3(5.0f, -2.0f, -9.0f));
        counter.SetCount(h.toPoint3() == Point3(5.0f, -2.0f, -9.0f));


        cout << "Testing of Plane methods complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();

    }
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "            PLANE UNIT TESTING          " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
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
struct TestTriangle2
{
private:
    Counter counter;
public:
    void Initialize(void)
    {
        cout << "Testing Triangle2 initialization..." << endl;
        Triangle2 t(Point2(1.0f, 1.0f), Point2(3.0f, 1.0f), Point2(2.0f, 2.5f));
        IS_EQUAL(t.GetVertexA(), Point2(1.0f, 1.0f));
        counter.SetCount(t.GetVertexA() == Point2(1.0f, 1.0f));
        IS_EQUAL(t.GetVertexB(), Point2(3.0f, 1.0f));
        counter.SetCount(t.GetVertexB() == Point2(3.0f, 1.0f));
        IS_EQUAL(t.GetVertexC(), Point2(2.0f, 2.5f));
        counter.SetCount(t.GetVertexC() == Point2(2.0f, 2.5f));
        IS_EQUAL(t.GetEdgeAB(), Vector2(2.0f, 0.0f));
        counter.SetCount(t.GetEdgeAB() == Vector2(2.0f, 0.0f));
        IS_EQUAL(t.GetEdgeBC(), Vector2(-1.0f, 1.5f));
        counter.SetCount(t.GetEdgeBC() == Vector2(-1.0f, 1.5f));
        IS_EQUAL(t.GetEdgeAC(), Vector2(1.0f, 1.5f));
        counter.SetCount(t.GetEdgeAC() == Vector2(1.0f, 1.5f));
        cout << "Testing Triangle2 initialization complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void ValueChange(void)
    {
        cout << "Testing Triangle2 value change..." << endl;
        Triangle2 t(Point2(3.0f, 2.0f), Point2(-2.5f, 1.0f), Point2(0.0f, 0.5f));
        IS_EQUAL(t.GetVertexA(), Point2(3.0f, 2.0f));
        counter.SetCount(t.GetVertexA() == Point2(3.0f, 2.0f));
        IS_EQUAL(t.GetVertexB(), Point2(-2.5f, 1.0f));
        counter.SetCount(t.GetVertexB() == Point2(-2.5f, 1.0f));
        IS_EQUAL(t.GetVertexC(), Point2(0.0f, 0.5f));
        counter.SetCount(t.GetVertexC() == Point2(0.0f, 0.5f));

        t = Triangle2(Point2(-2.0f, 1.0f), Point2(2.0f, 0.5f), Point2(0.5f, 4.0f));
        IS_EQUAL(t.GetVertexA(), Point2(-2.0f, 1.0f));
        counter.SetCount(t.GetVertexA() == Point2(-2.0f, 1.0f));
        IS_EQUAL(t.GetVertexB(), Point2(2.0f, 0.5f));
        counter.SetCount(t.GetVertexB() == Point2(2.0f, 0.5f));
        IS_EQUAL(t.GetVertexC(), Point2(0.5f, 4.0f));
        counter.SetCount(t.GetVertexC() == Point2(0.5f, 4.0f));

        t.SetPoints(Point2(-2.0f, -2.0f), Point2(-1.0f, -6.0f), Point2(1.0f, -3.0f));
        IS_EQUAL(t.GetVertexA(), Point2(-2.0f, -2.0f));
        counter.SetCount(t.GetVertexA() == Point2(-2.0f, -2.0f));
        IS_EQUAL(t.GetVertexB(), Point2(-1.0f, -6.0f));
        counter.SetCount(t.GetVertexB() == Point2(-1.0f, -6.0f));
        IS_EQUAL(t.GetVertexC(), Point2(1.0f, -3.0f));
        counter.SetCount(t.GetVertexC() == Point2(1.0f, -3.0f));

        cout << "Testing Triangle2 value change complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        cout << "Testing Triangle2 memory placement..." << endl;
        Triangle2 t1(Point2(3.0f, 2.0f), Point2(-2.5f, 1.0f), Point2(0.0f, 0.5f));
        Triangle2 t2 = t1;
        Triangle2 *a, *b;
        a = &t1, b = &t2;
        IS_EQUAL(*a, *b);
        counter.SetCount(*a == *b);
        IS_NOTEQUAL(a, b);
        counter.SetCount(a != b);
        b = &t1;
        IS_EQUAL(a, b);
        counter.SetCount(a == b);
        cout << "Testing Triangle2 memory placement complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void Methods(void)
    {
        cout << "Testing Triangle2 methods..." << endl;
        Triangle2 t1(Point2(3.0f, 2.0f), Point2(-2.5f, 1.0f), Point2(0.0f, 0.5f));
        IS_CLOSE(t1.Area(), 2.625f);
        counter.SetCountClose(t1.Area(), 2.625f);
        IS_EQUAL(t1.Perimeter(), 11.493782f);
        counter.SetCountClose(t1.Perimeter(), 11.493782f);

        cout << "Testing Triangle2 methods complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "           TRIANGLE2 UNIT TESTING          " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
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
private:
    Counter counter;
public:
    void Initialize(void)
    {
        cout << "Testing Triangle3 initialization..." << endl;
        Triangle3 t(Point3(1.0f, 1.0f, 1.0f), Point3(3.0f, 2.0f, 1.0f), Point3(2.0f, 2.5f, 3.0f));
        IS_EQUAL(t.GetVertexA(), Point3(1.0f, 1.0f, 1.0f));
        counter.SetCount(t.GetVertexA() == Point3(1.0f, 1.0f, 1.0f));
        IS_EQUAL(t.GetVertexB(), Point3(3.0f, 2.0f, 1.0f));
        counter.SetCount(t.GetVertexB() == Point3(3.0f, 2.0f, 1.0f));
        IS_EQUAL(t.GetVertexC(), Point3(2.0f, 2.5f, 3.0f));
        counter.SetCount(t.GetVertexC() == Point3(2.0f, 2.5f, 3.0f));
        IS_EQUAL(t.GetEdgeAB(), Vector3(2.0f, 1.0f, 0.0f));
        counter.SetCount(t.GetEdgeAB() == Vector3(2.0f, 1.0f, 0.0f));
        IS_EQUAL(t.GetEdgeBC(), Vector3(-1.0f, 0.5f, 2.0f));
        counter.SetCount(t.GetEdgeBC() == Vector3(-1.0f, 0.5f, 2.0f));
        IS_EQUAL(t.GetEdgeAC(), Vector3(1.0f, 1.5f, 2.0f));
        counter.SetCount(t.GetEdgeAC() == Vector3(1.0f, 1.5f, 2.0f));
        cout << "Testing Triangle3 initialization complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void ValueChange(void)
    {
        cout << "Testing Triangle3 value change..." << endl;
        Triangle3 t(Point3(1.0f, 1.0f, 1.0f), Point3(2.0f, 2.5f, 3.0f), Point3(3.0f, 2.0f, 1.0f));
        IS_EQUAL(t.GetVertexA(), Point3(1.0f, 1.0f, 1.0f));
        counter.SetCount(t.GetVertexA() == Point3(1.0f, 1.0f, 1.0f));
        IS_EQUAL(t.GetVertexB(), Point3(2.0f, 2.5f, 3.0f));
        counter.SetCount(t.GetVertexB() == Point3(2.0f, 2.5f, 3.0f));
        IS_EQUAL(t.GetVertexC(), Point3(3.0f, 2.0f, 1.0f));
        counter.SetCount(t.GetVertexC() == Point3(3.0f, 2.0f, 1.0f));

        t = Triangle3(Point3(-2.0f, -1.0f, 0.0f), Point3(1.0f, 1.5f, 2.0f), Point3(1.0f, 2.0f, 3.0f));
        IS_EQUAL(t.GetVertexA(), Point3(-2.0f, -1.0f, 0.0f));
        counter.SetCount(t.GetVertexA() == Point3(-2.0f, -1.0f, 0.0f));
        IS_EQUAL(t.GetVertexB(), Point3(1.0f, 1.5f, 2.0f));
        counter.SetCount(t.GetVertexB() == Point3(1.0f, 1.5f, 2.0f));
        IS_EQUAL(t.GetVertexC(), Point3(1.0f, 2.0f, 3.0f));
        counter.SetCount(t.GetVertexC() == Point3(1.0f, 2.0f, 3.0f));

        t.SetPoints(Point3(-2.0f, -2.0f, -2.0f), Point3(-1.0f, -3.0f, -5.0f), Point3(2.0f, -4.0f, 6.0f));
        IS_EQUAL(t.GetVertexA(), Point3(-2.0f, -2.0f, -2.0f));
        counter.SetCount(t.GetVertexA() == Point3(-2.0f, -2.0f, -2.0f));
        IS_EQUAL(t.GetVertexB(), Point3(-1.0f, -3.0f, -5.0f));
        counter.SetCount(t.GetVertexB() == Point3(-1.0f, -3.0f, -5.0f));
        IS_EQUAL(t.GetVertexC(), Point3(2.0f, -4.0f, 6.0f));
        counter.SetCount(t.GetVertexC() == Point3(2.0f, -4.0f, 6.0f));

        cout << "Testing Triangle3 value change complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        cout << "Testing Triangle3 memory placement..." << endl;
        Triangle3 t1(Point3(3.0f, 2.0f, 1.0f), Point3(-2.5f, 1.0f, 0.0f), Point3(2.0f, -1.5f, 3.5f));
        Triangle3 t2 = t1;
        Triangle3 *a, *b;
        a = &t1, b = &t2;
        IS_EQUAL(*a, *b);
        counter.SetCount(*a == *b);
        IS_NOTEQUAL(a, b);
        counter.SetCount(a != b);
        b = &t1;
        IS_EQUAL(a, b);
        counter.SetCount(a == b);
        cout << "Testing Triangle3 memory placement complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void Methods(void)
    {
        cout << "Testing Triangle3 methods..." << endl;
        Triangle3 t1(Point3(3.0f, 2.0f, 1.0f), Point3(-2.5f, 1.0f, -4.0f), Point3(0.0f, 0.5f, 1.0f));
        IS_CLOSE(t1.Area(), 8.786530885f);
        counter.SetCountClose(t1.Area(), 8.786530885f);
        IS_EQUAL(t1.Perimeter(), 16.466587f);
        counter.SetCountClose(t1.Perimeter(), 16.466587f);

        cout << "Testing Triangle3 methods complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void AllTests(void)
    {
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "           TRIANGLE3 UNIT TESTING          " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * *" << endl << endl;

        Initialize();
        ValueChange();
        MemoryPlacement();
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
private:
    Counter counter;
public:
    void Initialize(void)
    {
        cout << "Testing Matrix2 initialization..." << endl;
        Matrix2 M(1.0f, 2.0f, 3.0f, 4.0f);
        IS_EQUAL(M.Row(0), Vector2(1.0f, 2.0f));
        counter.SetCount(M.Row(0) == Vector2(1.0f, 2.0f));
        IS_EQUAL(M.Row(1), Vector2(3.0f, 4.0f));
        counter.SetCount(M.Row(1) == Vector2(3.0f, 4.0f));
        IS_EQUAL(M.Col(0), Vector2(1.0f, 3.0f));
        counter.SetCount(M.Col(0) == Vector2(1.0f, 3.0f));
        IS_EQUAL(M.Col(1), Vector2(2.0f, 4.0f));
        counter.SetCount(M.Col(1) == Vector2(2.0f, 4.0f));

        M = Matrix2(Vector2(-3.0f, -4.0f), Vector2(5.0f, 6.0));
        IS_EQUAL(M.Col(0), Vector2(-3.0f, -4.0f));
        counter.SetCount(M.Col(0) == Vector2(-3.0f, -4.0f));
        IS_EQUAL(M.Col(1), Vector2(5.0f, 6.0f));
        counter.SetCount(M.Col(1) == Vector2(5.0f, 6.0f));
        IS_EQUAL(M.Row(0), Vector2(-3.0f, 5.0f));
        counter.SetCount(M.Row(0) == Vector2(-3.0f, 5.0f));
        IS_EQUAL(M.Row(1), Vector2(-4.0f, 6.0f));
        counter.SetCount(M.Row(1) == Vector2(-4.0f, 6.0f));

        M = M.Identity();
        IS_EQUAL(M.Row(0), Vector2(1.0f, 0.0f));
        counter.SetCount(M.Row(0) == Vector2(1.0f, 0.0f));
        IS_EQUAL(M.Row(1), Vector2(0.0f, 1.0f));
        counter.SetCount(M.Row(1) == Vector2(0.0f, 1.0f));

        M = M.Zero();
        IS_EQUAL(M.Row(0), Vector2(0.0f, 0.0f));
        counter.SetCount(M.Row(0) == Vector2(0.0f, 0.0f));
        IS_EQUAL(M.Row(1), Vector2(0.0f, 0.0f));
        counter.SetCount(M.Row(1) == Vector2(0.0f, 0.0f));

        cout << "Testing Matrix2 initialization complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void ValueChange(void)
    {
        cout << "Testing Matrix2 value change..." << endl;
        Matrix2 M(1.0f, 2.0f, 3.0f, 4.0f);
        IS_EQUAL(M.Row(0), Vector2(1.0f, 2.0f));
        counter.SetCount(M.Row(0) == Vector2(1.0f, 2.0f));
        IS_EQUAL(M.Row(1), Vector2(3.0f, 4.0f));
        counter.SetCount(M.Row(1) == Vector2(3.0f, 4.0f));

        M = Matrix2(2.0f, 5.0f, -9.0f, -3.0f);
        IS_EQUAL(M.Row(0), Vector2(2.0f, 5.0f));
        counter.SetCount(M.Row(0) == Vector2(2.0f, 5.0f));
        IS_EQUAL(M.Row(1), Vector2(-9.0f, -3.0f));
        counter.SetCount(M.Row(1) == Vector2(-9.0f, -3.0f));

        Matrix2 A = M.Zero();
        M = A;
        IS_EQUAL(M.Row(0), Vector2(0.0f, 0.0f));
        counter.SetCount(M.Row(0) == Vector2(0.0f, 0.0f));
        IS_EQUAL(M.Row(1), Vector2(0.0f, 0.0f));
        counter.SetCount(M.Row(1) == Vector2(0.0f, 0.0f));

        cout << "Testing Matrix2 value change complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        cout << "Testing Matrix2 memory placement..." << endl;
        Matrix2 A(1.0f, 2.0f, 3.0f, 4.0f);
        Matrix2 B = A;

        Matrix2 *x = &A, *y = &B;
        IS_NOTEQUAL(x, y);
        counter.SetCount(x != y);
        IS_EQUAL(*x, *y);
        counter.SetCount(*x == *y);

        y = &A;
        IS_EQUAL(x, y);
        counter.SetCount(x == y);

        cout << "Testing Matrix2 memory placement complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();
    }
    void ClassOperators(void)
    {
        cout << "Testing Matrix2 class operators..." << endl;

        Matrix2 A(1.0f, 2.0f, 3.0f, 4.0f);
        Matrix2 B(5.0f, -3.0f, 7.0f, -1.0f);
        Matrix2 copyA = A;

        A += B;
        IS_EQUAL(A, Matrix2(6.0f, -1.0f, 10.0f, 3.0f));
        counter.SetCount(A == Matrix2(6.0f, -1.0f, 10.0f, 3.0f));
        A = copyA;

        A -= B;
        IS_EQUAL(A, Matrix2(-4.0f, 5.0f, -4.0f, 5.0f));
        counter.SetCount(A == Matrix2(-4.0f, 5.0f, -4.0f, 5.0f));
        A = copyA;

        A *= 2.0f;
        IS_EQUAL(A, Matrix2(2.0f, 4.0f, 6.0f, 8.0f));
        counter.SetCount(A == Matrix2(2.0f, 4.0f, 6.0f, 8.0f));

        A /= 2.0f;
        IS_EQUAL(A, Matrix2(1.0f, 2.0f, 3.0f, 4.0f));
        counter.SetCount(A == Matrix2(1.0f, 2.0f, 3.0f, 4.0f));

        cout << "Testing Matrix2 class operators complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();

    }
    void Methods(void)
    {
        cout << "Testing Matrix2 methods..." << endl;

        Matrix2 M(1.0f, 2.0f, 3.0f, 4.0f);
        Matrix2 A(5.0f, -3.0f, 7.0f, -1.0f);
        Vector2 col(-4, 3);
        float c = 1.0f;
        float copyC;

        IS_EQUAL(M+A, Matrix2(6.0f, -1.0f, 10.0f, 3.0f));
        counter.SetCount(M+A == Matrix2(6.0f, -1.0f, 10.0f, 3.0f));
        IS_EQUAL(M-A, Matrix2(-4.0f, 5.0f, -4.0f, 5.0f));
        counter.SetCount(M-A == Matrix2(-4.0f, 5.0f, -4.0f, 5.0f));
        IS_EQUAL(M*2.0f, Matrix2(2.0f, 4.0f, 6.0f, 8.0f));
        counter.SetCount(M*2.0f == Matrix2(2.0f, 4.0f, 6.0f, 8.0f));
        IS_EQUAL(2.0f*M, Matrix2(2.0f, 4.0f, 6.0f, 8.0f));
        counter.SetCount(2.0f*M == Matrix2(2.0f, 4.0f, 6.0f, 8.0f));
        IS_EQUAL(M/2.0f, Matrix2(0.5f, 1.0f, 1.5f, 2.0f));
        counter.SetCount(M/2.0f == Matrix2(0.5f, 1.0f, 1.5f, 2.0f));
        IS_EQUAL(M*A, Matrix2(19.0f, -5.0f, 43.0f, -13.0f));
        counter.SetCount(M*A == Matrix2(19.0f, -5.0f, 43.0f, -13.0f));
        IS_EQUAL(M*col, Vector2(2.0f, 0.0f));
        counter.SetCount(M*col == Vector2(2.0f, 0.0f));

        IS_EQUAL(Diagonal(M), Vector2(1.0f, 4.0f));
        counter.SetCount(Diagonal(M) == Vector2(1.0f, 4.0f));
        IS_EQUAL(Transpose(M), Matrix2(1.0f, 3.0f, 2.0f, 4.0f));
        counter.SetCount(Transpose(M) == Matrix2(1.0f, 3.0f, 2.0f, 4.0f));
        IS_EQUAL(Inverse(M), Matrix2(-2.0f,  1.0f, 1.5f, -0.5f));
        counter.SetCount(Inverse(M) == Matrix2(-2.0f,  1.0f, 1.5f, -0.5f));
        IS_EQUAL(REF(M, &c), Matrix2(1.0f, 2.0f, 0.0f, 1.0f)); copyC = c; c = 1.0f;
        counter.SetCount(REF(M, &c) == Matrix2(1.0f, 2.0f, 0.0f, 1.0f));
        IS_EQUAL(c, -2.0f);
        counter.SetCount(copyC == -2.0f);
        IS_EQUAL(Det(M), c);
        counter.SetCount(Det(M) == c);
        IS_EQUAL(Trace(M), 5.0f);
        counter.SetCount(Trace(M) == 5.0f);
        IS_EQUAL(Cofactor(M), Matrix2(4.0f, -3.0f, -2.0f, 1.0f));
        counter.SetCount(Cofactor(M) == Matrix2(4.0f, -3.0f, -2.0f, 1.0f));
        IS_EQUAL(Adjugate(M), Matrix2(4.0f, -2.0f, -3.0f, 1.0f));
        counter.SetCount(Adjugate(M) == Matrix2(4.0f, -2.0f, -3.0f, 1.0f));
        IS_EQUAL(Scale(2.0f, 3.0f), Matrix2(2.0f, 0.0f, 0.0f, 3.0f));
        counter.SetCount(Scale(2.0f, 3.0f) == Matrix2(2.0f, 0.0f, 0.0f, 3.0f));
        IS_EQUAL(Scale(3.0f, Vector2(1.0f, 2.0f)), Matrix2(0.6f, 0.8f, 0.8f, -0.6f));
        counter.SetCount(Scale(3.0f, Vector2(1.0f, 2.0f)) == Matrix2(0.6f, 0.8f, 0.8f, -0.6f));

        M = ((1.0f/sqrtf(2.0f)) * Matrix2(1.0f, 1.0f, 1.0f, -1.0f));
        IS_TRUE(IsOrthogonal(M));
        counter.SetCount(IsOrthogonal(M));

        Vector2 u(2.0f, 3.0f), v(3.0f, -2.0f);
        Matrix2 S = Skew(0.5235987756f, u, v);
        Matrix2 E(0.733531f, 0.177646f, -0.399704f, 1.266469f);
        IS_EQUAL(S, E);
        counter.SetCount(S == E);
        S = SkewDegrees(30.0f, u, v);
        IS_EQUAL(S, E);
        counter.SetCount(S == E);
        S = Matrix2(0.342020143326f, -0.9396926207859f, 0.9396926207859f, 0.342020143326f);
        IS_EQUAL(Rotate(1.221730476396f), S);
        counter.SetCount(Rotate(1.221730476396f) == S);
        IS_EQUAL(RotateDegrees(70.0f), S);
        counter.SetCount(RotateDegrees(70.0f) == S);
        IS_EQUAL(Reflection((7.0f/18.0f)*PI), Matrix2(-0.76604444f, 0.6427876096f, 0.6427876096f, 0.76604444f));
        counter.SetCount(Reflection((7.0f/18.0f)*PI) == Matrix2(-0.76604444f, 0.6427876096f, 0.6427876096f, 0.76604444f));
        IS_EQUAL(Involution(Vector2(3.0f, 2.0f)), Matrix2(0.384616f, 0.923077f, 0.923077f, -0.384615f));
        counter.SetCount(Involution(Vector2(3.0f, 2.0)) == Matrix2(0.384616f, 0.923077f, 0.923077f, -0.384615f));
        cout << "Testing Matrix2 methods complete!" << endl;
        cout << "-Total Tests: " << to_string(counter.GetTotal()) << endl;
        cout << "-Tests Passed: " << to_string(counter.GetCountPass()) << endl;
        cout << "-Tests Failed: " << to_string(counter.GetCountFail()) << endl << endl;
        counter.Reset();


    }
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
private:
    Counter counter;
public:
    void Initialize(void)
    {
        Print("Testing Matrix3 initialization...");
        Matrix3 M(  1.0f, 2.0f, 3.0f,
                    4.0f, 5.0f, 6.0f,
                    7.0f, 8.0f, 9.0f);
        IS_EQUAL(M.Row(0), Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(M.Row(0) == Vector3(1.0f, 2.0f, 3.0));
        IS_EQUAL(M.Row(1), Vector3(4.0f, 5.0f, 6.0f));
        counter.SetCount(M.Row(1) == Vector3(4.0f, 5.0f, 6.0));
        IS_EQUAL(M.Row(2), Vector3(7.0f, 8.0f, 9.0f));
        counter.SetCount(M.Row(2) == Vector3(7.0f, 8.0f, 9.0));

        M = Matrix3(Vector3(2.0f, 8.0f, 14.0f),
                    Vector3(4.0f, 10.0f, 16.0f),
                    Vector3(6.0f, 12.0f, 18.0f));
        IS_EQUAL(M.Row(0), Vector3(2.0f, 4.0f, 6.0f));
        counter.SetCount(M.Row(0) == Vector3(2.0f, 4.0f, 6.0f));
        IS_EQUAL(M.Row(1), Vector3(8.0f, 10.0f, 12.0f));
        counter.SetCount(M.Row(1) == Vector3(8.0f, 10.0f, 12.0f));
        IS_EQUAL(M.Row(2), Vector3(14.0f, 16.0f, 18.0f));
        counter.SetCount(M.Row(2) == Vector3(14.0f, 16.0f, 18.0f));

        M = M.Identity();
        IS_EQUAL(M.Row(0), Vector3(1.0f, 0.0f, 0.0f));
        counter.SetCount(M.Row(0) == Vector3(1.0f, 0.0f, 0.0f));
        IS_EQUAL(M.Row(1), Vector3(0.0f, 1.0f, 0.0f));
        counter.SetCount(M.Row(1) == Vector3(0.0f, 1.0f, 0.0f));
        IS_EQUAL(M.Row(2), Vector3(0.0f, 0.0f, 1.0f));
        counter.SetCount(M.Row(2) == Vector3(0.0f, 0.0f, 1.0f));

        M = M.Zero();
        IS_EQUAL(M.Row(0), Vector3(0.0f, 0.0f, 0.0f));
        counter.SetCount(M.Row(0) == Vector3(0.0f, 0.0f, 0.0f));
        IS_EQUAL(M.Row(1), Vector3(0.0f, 0.0f, 0.0f));
        counter.SetCount(M.Row(1) == Vector3(0.0f, 0.0f, 0.0f));
        IS_EQUAL(M.Row(2), Vector3(0.0f, 0.0f, 0.0f));
        counter.SetCount(M.Row(2) == Vector3(0.0f, 0.0f, 0.0f));

        Print("Testing Matrix3 initialization complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void ValueChange(void)
    {
        Print("Testing Matrix3 value change...");

        Matrix3 M(  1.0f, 2.0f, 3.0f,
                    4.0f, 5.0f, 6.0f,
                    7.0f, 8.0f, 9.0f);
        IS_EQUAL(M.Row(0), Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(M.Row(0) == Vector3(1.0f, 2.0f, 3.0f));
        IS_EQUAL(M.Row(1), Vector3(4.0f, 5.0f, 6.0f));
        counter.SetCount(M.Row(1) == Vector3(4.0f, 5.0f, 6.0f));
        IS_EQUAL(M.Row(2), Vector3(7.0f, 8.0f, 9.0f));

        M = Matrix3(7.0f, -3.0f, 12.0f,
                    11.0f, 8.0f, -2.0f,
                    -1.0f, 16.0f, 3.0f);
        IS_EQUAL(M.Col(0), Vector3(7.0f, 11.0f, -1.0f));
        counter.SetCount(M.Col(0) == Vector3(7.0f, 11.0f, -1.0f));
        IS_EQUAL(M.Col(1), Vector3(-3.0f, 8.0f, 16.0f));
        counter.SetCount(M.Col(1) == Vector3(-3.0f, 8.0f, 16.0f));
        IS_EQUAL(M.Col(2), Vector3(12.0f, -2.0f, 3.0f));
        counter.SetCount(M.Col(2) == Vector3(12.0f, -2.0f, 3.0f));

        Matrix3 A = M.Identity();
        M = A;
        IS_EQUAL(M.Row(0), Vector3(1.0f, 0.0f, 0.0f));
        counter.SetCount(M.Row(0) == Vector3(1.0f, 0.0f, 0.0f));
        IS_EQUAL(M.Row(1), Vector3(0.0f, 1.0f, 0.0f));
        counter.SetCount(M.Row(1) == Vector3(0.0f, 1.0f, 0.0f));
        IS_EQUAL(M.Row(2), Vector3(0.0f, 0.0f, 1.0f));
        counter.SetCount(M.Row(2) == Vector3(0.0f, 0.0f, 1.0f));

        Print("Testing Matrix3 value change complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        Print("Testing Matrix3 memory placement...");
        Matrix3 M(1.0f, 2.0f, 3.0f,
                  4.0f, 5.0f, 6.0f,
                  7.0f, 8.0f, 9.0f);
        Matrix3 A = M;
        Matrix3 *x=&M, *y=&A;

        IS_NOTEQUAL(x, y);
        counter.SetCount(x != y);
        IS_EQUAL(*x, *y);
        counter.SetCount(*x == *y);

        y = &M;
        IS_EQUAL(x, y);
        counter.SetCount(x == y);

        Print("Testing Matrix3 memory placement complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void ClassOperators(void)
    {
        Print("Testing Matrix3 class operators...");

        Matrix3 A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
        Matrix3 B(3.0f, 4.0f, 3.0f, -1.0f, 1.0f, 2.0f, -2.0f, -4.0f, 1.0f);
        Matrix3 copyA = A;

        A += B;
        IS_EQUAL(A, Matrix3(4.0f, 6.0f, 6.0f, 3.0f, 6.0f, 8.0f, 5.0f, 4.0f, 10.0f));
        counter.SetCount(A == Matrix3(4.0f, 6.0f, 6.0f, 3.0f, 6.0f, 8.0f, 5.0f, 4.0f, 10.0f));
        A = copyA;

        A -= B;
        IS_EQUAL(A, Matrix3(-2.0f, -2.0f, 0.0f, 5.0f, 4.0f, 4.0f, 9.0f, 12.0f, 8.0f));
        counter.SetCount(A == Matrix3(-2.0f, -2.0f, 0.0f, 5.0f, 4.0f, 4.0f, 9.0f, 12.0f, 8.0f));
        A = copyA;

        A *= 2.0f;
        IS_EQUAL(A, Matrix3(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f));
        counter.SetCount(A == Matrix3(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f));

        A /= 2.0f;
        IS_EQUAL(A, Matrix3(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f));
        counter.SetCount(A == Matrix3(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f));

        Print("Testing Matrix3 class operators complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void Methods(void)
    {
        Print("Testing Matrix3 methods...");

        Matrix3 A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
        Matrix3 B(3.0f, 4.0f, 3.0f, -1.0f, 1.0f, 2.0f, -2.0f, -4.0f, 1.0f);
        Vector3 v(4.5f, 3.0f, -2.5f);

        float c = 1.0f;
        float copyC;

        IS_EQUAL(A+B, Matrix3(4.0f, 6.0f, 6.0f, 3.0f, 6.0f, 8.0f, 5.0f, 4.0f, 10.0f));
        counter.SetCount(A+B == Matrix3(4.0f, 6.0f, 6.0f, 3.0f, 6.0f, 8.0f, 5.0f, 4.0f, 10.0f));
        IS_EQUAL(A-B, Matrix3(-2.0f, -2.0f, 0.0f, 5.0f, 4.0f, 4.0f, 9.0f, 12.0f, 8.0f));
        counter.SetCount(A-B == Matrix3(-2.0f, -2.0f, 0.0f, 5.0f, 4.0f, 4.0f, 9.0f, 12.0f, 8.0f));
        IS_EQUAL(A*2.0f, Matrix3(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f));
        counter.SetCount(A*2.0f == Matrix3(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f));
        IS_EQUAL(2.0f*A, Matrix3(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f));
        counter.SetCount(2.0f*A == Matrix3(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f));
        IS_EQUAL(A/2.0f, Matrix3(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f));
        counter.SetCount(A/2.0f == Matrix3(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f));
        IS_EQUAL(A*B, Matrix3(-5.0f, -6.0f, 10.0f, -5.0f, -3.0f, 28.0f, -5.0f, 0.0f, 46.0f));
        counter.SetCount(A*B == Matrix3(-5.0f, -6.0f, 10.0f, -5.0f, -3.0f, 28.0f, -5.0f, 0.0f, 46.0f));
        IS_EQUAL(A*v, Vector3(3.0f, 18.0f, 33.0f));
        counter.SetCount(A*v == Vector3(3.0f, 18.0f, 33.0f));

        IS_EQUAL(Diagonal(A), Vector3(1.0f, 5.0f, 9.0f));
        counter.SetCount(Diagonal(A) == Vector3(1.0f, 5.0f, 9.0f));
        IS_EQUAL(Transpose(A), Matrix3(1.0f, 4.0f, 7.0f, 2.0f, 5.0f, 8.0f, 3.0f, 6.0f, 9.0f));
        counter.SetCount(Transpose(A) == Matrix3(1.0f, 4.0f, 7.0f, 2.0f, 5.0f, 8.0f, 3.0f, 6.0f, 9.0f));

        Matrix3 R = REF(A, &c);
        IS_EQUAL(R, Matrix3(1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 2.0f, 0.0f, 0.0f, 0.0f));
        counter.SetCount(R == Matrix3(1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 2.0f, 0.0f, 0.0f, 0.0f));
        IS_EQUAL(c, -3.0f);
        counter.SetCount(c == -3.0f);
        IS_EQUAL(Det(B), 33.0f);
        counter.SetCount(Det(B) == 33.0f);
        IS_EQUAL(Trace(A), 15.0f);
        counter.SetCount(Trace(A) == 15.0f);
        IS_EQUAL(Inverse(B), (1.0f/33.0f)*Matrix3(9.0f, -16.0f, 5.0f, -3.0f, 9.0f, -9.0f, 6.0f, 4.0f, 7.0f));
        counter.SetCount(Inverse(B) == (1.0f/33.0f)*Matrix3(9.0f, -16.0f, 5.0f, -3.0f, 9.0f, -9.0f, 6.0f, 4.0f, 7.0f));
        IS_EQUAL(Adjugate(A), Matrix3(-3.0f, 6.0f, -3.0f, 6.0f, -12.0f, 6.0f, -3.0f, 6.0f, -3.0f));
        counter.SetCount(Adjugate(A) == Matrix3(-3.0f, 6.0f, -3.0f, 6.0f, -12.0f, 6.0f, -3.0f, 6.0f, -3.0f));
        IS_EQUAL(Cofactor(A), Transpose(Matrix3(-3.0f, 6.0f, -3.0f, 6.0f, -12.0f, 6.0f, -3.0f, 6.0f, -3.0f)));
        counter.SetCount(Cofactor(A) == Transpose(Matrix3(-3.0f, 6.0f, -3.0f, 6.0f, -12.0f, 6.0f, -3.0f, 6.0f, -3.0f)));
        IS_EQUAL(Scale(3.0f, 4.0f, 2.0f), Matrix3(3.0f, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 2.0f));
        counter.SetCount(Scale(3.0f, 4.0f, 2.0f) == Matrix3(3.0f, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 2.0f));

        R = Matrix3(1.486486f, 0.648649f, 1.135135f, 0.648649f, 1.864865f, -1.513513f, 1.135135f, -1.513513f, 3.648649f);
        IS_EQUAL(Scale(-3.0f, Vector3(-1.5f, 2.0f, 3.5f)), R);
        counter.SetCount(Scale(-3.0f, Vector3(-1.5f, 2.0f, 3.5f)) == R);
        IS_TRUE(IsOrthogonal((1.0f/3.0f) * Matrix3(1.0f, 2.0f, 2.0f, 2.0f, 1.0f, -2.0f, -2.0f, 2.0f, -1.0f)));
        counter.SetCount(IsOrthogonal((1.0f/3.0f) * Matrix3(1.0f, 2.0f, 2.0f, 2.0f, 1.0f, -2.0f, -2.0f, 2.0f, -1.0f)));
        IS_FALSE(IsOrthogonal(A));
        counter.SetCount(!IsOrthogonal(A));

        R = Matrix3(1.281153f, -0.843459f, -0.843459f, -0.062478f, 1.187435f, 0.187435f, 0.156196f, -0.468588f, 0.531412f);
        IS_EQUAL(Skew(0.95993108859688f, Vector3(-9.0f, 2.0f, -5.0f), Vector3(-1.0f, 3.0f, 3.0f) ), R);
        counter.SetCount(Skew(0.95993108859688f, Vector3(-9.0f, 2.0f, -5.0f), Vector3(-1.0f, 3.0f, 3.0f)) == R);
        IS_EQUAL(SkewDegrees(55.0f, Vector3(-9.0f, 2.0f, -5.0f), Vector3(-1.0f, 3.0f, 3.0f)), R);
        counter.SetCount(SkewDegrees(55.0f, Vector3(-9.0f, 2.0f, -5.0f), Vector3(-1.0f, 3.0f, 3.0f)) == R);

        float cs = cos(PI/3.0f);
        float sn = sin(PI/3.0f);
        IS_EQUAL(RotateAboutX(PI/3.0f), Matrix3(1.0f, 0.0f, 0.0f, 0.0f, cs, -sn, 0.0f, sn, cs));
        counter.SetCount(RotateAboutX(PI/3.0f) == Matrix3(1.0f, 0.0f, 0.0f, 0.0f, cs, -sn, 0.0f, sn, cs));
        IS_EQUAL(RotateAboutY(PI/3.0f), Matrix3(cs, 0.0f, sn, 0.0f, 1.0f, 0.0f, -sn, 0.0f, cs));
        counter.SetCount(RotateAboutY(PI/3.0f) == Matrix3(cs, 0.0f, sn, 0.0f, 1.0, 0.0f, -sn, 0.0f, cs));
        IS_EQUAL(RotateAboutZ(PI/3.0f), Matrix3(cs, -sn, 0.0f, sn, cs, 0.0f, 0.0f, 0.0f, 1.0f));
        counter.SetCount(RotateAboutZ(PI/3.0f) == Matrix3(cs, -sn, 0.0f, sn, cs, 0.0f, 0.0f, 0.0f, 1.0f));

        R = Matrix3(0.642857f, 0.622936f, -0.445741f,
                    -0.765794f, 0.535714f, -0.355767f,
                    0.017169f, 0.570053f, 0.821429f);
        IS_EQUAL(RotateAboutAxis(PI/3.0f, Vector3(2.0f, -1.0f, -3.0f)), R);
        counter.SetCount(RotateAboutAxis(PI/3.0f, Vector3(2.0f, -1.0f, -3.0f)) == R);
        IS_EQUAL(RotateAboutAxisDegrees(60.0f, Vector3(2.0f, -1.0f, -3.0f)), R);
        counter.SetCount(RotateAboutAxisDegrees(60.0f, Vector3(2.0f, -1.0f, -3.0f)) == R);
        IS_EQUAL(RotateAboutAxis(PI/3.0f, Vector3(0.534522f, -0.267261f, -0.801784f)), R);
        counter.SetCount(RotateAboutAxis(PI/3.0f, Vector3(0.534522f, -0.267261f, -0.801784f)) == R);
        IS_EQUAL(RotateAboutAxisDegrees(60.0f, Vector3(0.534522f, -0.267261f, -0.801784f)), R);
        counter.SetCount(RotateAboutAxisDegrees(60.0f, Vector3(0.534522f, -0.267261f, -0.801784f)) == R);

        R = Matrix3(0.857143f, -0.285714f, -0.428571f,
                    -0.285714f, 0.428571f, -0.857143f,
                    -0.428571f, -0.857143f, -0.285714f);
        IS_EQUAL(Reflection(Vector3(1.0f, 2.0f, 3.0f)), R);
        counter.SetCount(Reflection(Vector3(1.0f, 2.0f, 3.0f)) == R);

        R = Matrix3(-0.857143f, 0.285714f, 0.428571f,
                    0.285714f, -0.428571f, 0.857143f,
                    0.428571f, 0.857143f, 0.285714f);
        IS_EQUAL(Involution(Vector3(1.0f, 2.0f, 3.0f)), R);
        counter.SetCount(Involution(Vector3(1.0f, 2.0f, 3.0f)) == R);

        Print("Testing Matrix3 methods complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
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
private:
    Counter counter;
public:
    void Initialize(void)
    {
        Print("Testing Matrix4 intialization...");
        Matrix4 M(  1.0f, 2.0f, 3.0f, 4.0f,
                    5.0f, 6.0f, 7.0f, 8.0f,
                    9.0f, 10.0f, 11.0f, 12.0f,
                    13.0f, 14.0f, 15.0f, 16.0f);
        IS_EQUAL(M.Row(0), Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        counter.SetCount(M.Row(0) == Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        IS_EQUAL(M.Row(1), Vector4(5.0f, 6.0f, 7.0f, 8.0f));
        counter.SetCount(M.Row(1) == Vector4(5.0f, 6.0f, 7.0f, 8.0f));
        IS_EQUAL(M.Row(2), Vector4(9.0f, 10.0f, 11.0f, 12.0f));
        counter.SetCount(M.Row(2) == Vector4(9.0f, 10.0f, 11.0f, 12.0f));
        IS_EQUAL(M.Row(3), Vector4(13.0f, 14.0f, 15.0f, 16.0f));
        counter.SetCount(M.Row(3) == Vector4(13.0f, 14.0f, 15.0f, 16.0f));

        M = Matrix4(Vector4(-2.0f, 4.0f, -6.0f, 8.0f),
                    Vector4(3.0f, -5.0f, 7.0f, -9.0f),
                    Vector4(-4.0f, 5.0f, 8.0f, -10.0f),
                    Vector4(1.0f, 4.0f, -5.0f, -8.0f));

        IS_EQUAL(M.Col(0), Vector4(-2.0f, 4.0f, -6.0f, 8.0f));
        counter.SetCount(M.Col(0) == Vector4(-2.0f, 4.0f, -6.0f, 8.0f));
        IS_EQUAL(M.Col(1), Vector4(3.0f, -5.0f, 7.0f, -9.0f));
        counter.SetCount(M.Col(1) == Vector4(3.0f, -5.0f, 7.0f, -9.0f));
        IS_EQUAL(M.Col(2), Vector4(-4.0f, 5.0f, 8.0f, -10.0f));
        counter.SetCount(M.Col(2) == Vector4(-4.0f, 5.0f, 8.0f, -10.0f));
        IS_EQUAL(M.Col(3), Vector4(1.0f, 4.0f, -5.0f, -8.0f));
        counter.SetCount(M.Col(3) == Vector4(1.0f, 4.0f, -5.0f, -8.0f));

        M = M.Identity();
        IS_EQUAL(M.Row(0), Vector4(1.0f, 0.0f, 0.0f, 0.0f));
        counter.SetCount(M.Row(0) == Vector4(1.0f, 0.0f, 0.0f, 0.0f));
        IS_EQUAL(M.Row(1), Vector4(0.0f, 1.0f, 0.0f, 0.0f));
        counter.SetCount(M.Row(1) == Vector4(0.0f, 1.0f, 0.0f, 0.0f));
        IS_EQUAL(M.Row(2), Vector4(0.0f, 0.0f, 1.0f, 0.0f));
        counter.SetCount(M.Row(2) == Vector4(0.0f, 0.0f, 1.0f, 0.0f));
        IS_EQUAL(M.Row(3), Vector4(0.0f, 0.0f, 0.0f, 1.0f));
        counter.SetCount(M.Row(3) == Vector4(0.0f, 0.0f, 0.0f, 1.0f));

        M = M.Zero();
        IS_EQUAL(M.Row(0), Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        counter.SetCount(M.Row(0) == Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        IS_EQUAL(M.Row(1), Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        counter.SetCount(M.Row(1) == Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        IS_EQUAL(M.Row(2), Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        counter.SetCount(M.Row(2) == Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        IS_EQUAL(M.Row(3), Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        counter.SetCount(M.Row(3) == Vector4(0.0f, 0.0f, 0.0f, 0.0f));

        Print("Testing Matrix4 methods complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void ValueChange(void)
    {
        Print("Testing Matrix4 value change...");
        Matrix4 M(  1.0f, 2.0f, 3.0f, 4.0f,
                    5.0f, 6.0f, 7.0f, 8.0f,
                    9.0f, 10.0f, 11.0f, 12.0f,
                    13.0f, 14.0f, 15.0f, 16.0f);

        IS_EQUAL(M.Col(0), Vector4(1.0f, 5.0f, 9.0f, 13.0f));
        counter.SetCount(M.Col(0) == Vector4(1.0f, 5.0f, 9.0f, 13.0f));
        IS_EQUAL(M.Col(1), Vector4(2.0f, 6.0f, 10.0f, 14.0f));
        counter.SetCount(M.Col(1) == Vector4(2.0f, 6.0f, 10.0f, 14.0f));
        IS_EQUAL(M.Col(2), Vector4(3.0f, 7.0f, 11.0f, 15.0f));
        counter.SetCount(M.Col(2) == Vector4(3.0f, 7.0f, 11.0f, 15.0f));
        IS_EQUAL(M.Col(3), Vector4(4.0f, 8.0f, 12.0f, 16.0f));
        counter.SetCount(M.Col(3) == Vector4(4.0f, 8.0f, 12.0f, 16.0f));

        Matrix4 A(Vector4(2.0f, 6.0f, 4.0f, 8.0f),
                    Vector4(-4.0f, -1.0f, -3.0f, 5.0f),
                    Vector4(3.0f,  -6.0f, -1.0f, 4.0f),
                    Vector4(-5.0f, 4.0f, -3.0f, 2.0f));

        M = A;
        IS_EQUAL(M.Row(0), Vector4(2.0f, -4.0f, 3.0f, -5.0f));
        counter.SetCount(M.Row(0) == Vector4(2.0f, -4.0f, 3.0f, -5.0f));
        IS_EQUAL(M.Row(1), Vector4(6.0f, -1.0f, -6.0f, 4.0f));
        counter.SetCount(M.Row(1) == Vector4(6.0f, -1.0f, -6.0f, 4.0f));
        IS_EQUAL(M.Row(2), Vector4(4.0f, -3.0f, -1.0f, -3.0f));
        counter.SetCount(M.Row(2) == Vector4(4.0f, -3.0f, -1.0f, -3.0f));
        IS_EQUAL(M.Row(3), Vector4(8.0f, 5.0f, 4.0f, 2.0f));
        counter.SetCount(M.Row(3) == Vector4(8.0f, 5.0f, 4.0f, 2.0f));

        Print("Testing Matrix4 methods complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        Print("Testing Matrix4 memory placement...");
        Matrix4 M(  1.0f, 2.0f, 3.0f, 4.0f,
                    5.0f, 6.0f, 7.0f, 8.0f,
                    9.0f, 10.0f, 11.0f, 12.0f,
                    13.0f, 14.0f, 15.0f, 16.0f);
        Matrix4 A = M;
        Matrix4 *x = &M, *y = &A;

        IS_NOTEQUAL(x, y);
        counter.SetCount(x != y);
        IS_EQUAL(*x, *y);
        counter.SetCount(*x == *y);

        y = &M;
        IS_EQUAL(x, y);
        counter.SetCount(x == y);
        Print("Testing Matrix4 memory placement complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void ClassOperators(void)
    {
        Print("Testing Matrix4 class operators...");
        Matrix4 M(  1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
                    9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
        Matrix4 A(  -2.0f, 4.0f, -5.0f, -3.0f, 8.0f, 7.0f, -3.0f, 2.0f,
                    -1.0f, 4.0f, -2.0f, 10.0f, 9.0f, -1.0f, 2.0f, 3.0f);
        Matrix4 copyM = M;

        M += A;
        IS_EQUAL(M, Matrix4(-1.0f, 6.0f, -2.0f, 1.0f, 13.0f, 13.0f, 4.0f, 10.0f,
                            8.0f, 14.0f, 9.0f, 22.0f, 22.0f, 13.0f, 17.0f, 19.0f));
        counter.SetCount(M ==
                        Matrix4(-1.0f, 6.0f, -2.0f, 1.0f, 13.0f, 13.0f, 4.0f, 10.0f,
                                8.0f, 14.0f, 9.0f, 22.0f, 22.0f, 13.0f, 17.0f, 19.0f));
        M -= copyM;
        IS_EQUAL(M, A);
        counter.SetCount(M == A);
        M = copyM;

        M*=2.0f;
        IS_EQUAL(M, Matrix4(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f,
                            18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f));
        counter.SetCount(M ==
                        Matrix4(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f,
                                18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f));
        M/=2.0f;
        IS_EQUAL(M, copyM);
        counter.SetCount(M == copyM);


        Print("Testing Matrix4 class operators complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void Methods(void)
    {
        Print("Testing Matrix4 methods...");
        Matrix4 M(  1.0f, 2.0f, 3.0, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
                    9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
        Matrix4 A(  -2.0f, 4.0f, -5.0f, -3.0f, 8.0f, 7.0f, -3.0f, 2.0f,
                    -1.0f, 4.0f, -2.0f, 10.0f, 9.0f, -1.0f, 2.0f, 3.0f);
        Matrix4 R;
        Vector4 v(8.0f, -4.0f, 3.0f, 5.0f);
        float c = 1.0f, copyC;

        IS_EQUAL(M+A, Matrix4(-1.0f, 6.0f, -2.0f, 1.0f, 13.0f, 13.0f, 4.0f, 10.0f,
                            8.0f, 14.0f, 9.0f, 22.0f, 22.0f, 13.0f, 17.0f, 19.0f));
        counter.SetCount(M+A ==
                    Matrix4(-1.0f, 6.0f, -2.0f, 1.0f, 13.0f, 13.0f, 4.0f, 10.0f,
                            8.0f, 14.0f, 9.0f, 22.0, 22.0f, 13.0f, 17.0f, 19.0f));
        IS_EQUAL(M-A, Matrix4(  3.0f, -2.0f, 8.0f, 7.0f, -3.0f, -1.0f, 10.0f, 6.0f,
                            10.0f, 6.0f, 13.0f, 2.0f, 4.0f, 15.0f, 13.0f, 13.0f));
        counter.SetCount(M-A ==
                    Matrix4(  3.0f, -2.0f, 8.0f, 7.0f, -3.0f, -1.0f, 10.0f, 6.0f,
                                10.0f, 6.0f, 13.0f, 2.0f, 4.0f, 15.0f, 13.0f, 13.0f));
        IS_EQUAL(M*A, Matrix4(  47.0f, 26.0f, -9.0f, 43.0f, 103.0f, 82.0f, -41.0f, 91.0f,
                            159.0f, 138.0f, -73.0f, 139.0f, 215.0f, 194.0f, -105.0f, 187.0f));
        counter.SetCount(M*A ==
                    Matrix4(  47.0f, 26.0f, -9.0f, 43.0f, 103.0f, 82.0f, -41.0f, 91.0f,
                            159.0f, 138.0f, -73.0f, 139.0f, 215.0f, 194.0f, -105.0f, 187.0f));
        IS_EQUAL(2.0f*M, Matrix4(   2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f,
                                18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f));
        counter.SetCount(2.0f*M ==
                    Matrix4(   2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f,
                            18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f));
        IS_EQUAL(M*2.0f, Matrix4(   2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f,
                                18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f));
        counter.SetCount(M*2.0f ==
                    Matrix4(   2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f,
                            18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f));
        M *= 2.0f;
        IS_EQUAL(M/2.0f, Matrix4(  1.0f, 2.0f, 3.0, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
                    9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
        counter.SetCount(M/2.0f ==
                    Matrix4(  1.0f, 2.0f, 3.0, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
                            9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
        M /= 2.0f;

        IS_EQUAL(Diagonal(M), Vector4(1.0f, 6.0f, 11.0f, 16.0f));
        counter.SetCount(Diagonal(M) == Vector4(1.0f, 6.0f, 11.0f, 16.0f));
        IS_EQUAL(Transpose(M), Matrix4(Vector4(1.0f, 2.0f, 3.0f, 4.0f),
                                        Vector4(5.0f, 6.0f, 7.0f, 8.0f),
                                        Vector4(9.0f, 10.0f, 11.0f, 12.0f),
                                        Vector4(13.0f, 14.0f, 15.0f, 16.0f)));

        counter.SetCount(Transpose(M) == Matrix4(Vector4(1.0f, 2.0f, 3.0f, 4.0f),
                                                Vector4(5.0f, 6.0f, 7.0f, 8.0),
                                                Vector4(9.0f, 10.0f, 11.0f, 12.0f),
                                                Vector4(13.0f, 14.0f, 15.0f, 16.0f)));
        R = REF(M, &c);
        IS_EQUAL(R, Matrix4(1.0f, 2.0f, 3.0f, 4.0f, 0.0f, 1.0f, 2.0f, 3.0f,
                                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
        counter.SetCount(R == Matrix4(1.0f, 2.0f, 3.0f, 4.0f, 0.0f, 1.0f, 2.0f, 3.0f,
                                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
        IS_EQUAL(c, -4.0f);
        counter.SetCount(c == -4.0f);
        IS_CLOSE(Det(A), -1633.999878f);
        counter.SetCount(Det(A) == -1633.999878f);
        IS_EQUAL(Det(M), 0.0f);
        counter.SetCount(Det(M) == 0.0f);
        IS_EQUAL(Trace(M), 34.0f);
        counter.SetCount(Trace(M) == 34.0f);

        R = Inverse(A);
        Matrix4 expectedR = (1.0f/1634.0f)*Matrix4(104.0f, -12.0f, -30.0f, 212.0f,
                                                    -455.0f, 461.0f, -73.0f, -519.0f,
                                                    -757.0f, 433.0f, -143.0f, -569.0f,
                                                    41.0f, -99.0f, 161.0f, 115.0f);
        IS_EQUAL(R, expectedR);
        counter.SetCount(R == expectedR);
        IS_EQUAL(Adjugate(M), M.Zero());
        counter.SetCount(Adjugate(M) == M.Zero());
        IS_EQUAL(Cofactor(M), M.Zero());
        counter.SetCount(Cofactor(M) == M.Zero());

        R = Adjugate(A);
        expectedR = (-1.0f)*Matrix4(104.0f, -12.000004f, -29.999998f, 211.99997f,
                                    -455.0f, 460.99994f, -72.999985f, -518.99994f,
                                    -757.0f, 432.99997f, -142.99999f, -568.99994f,
                                    41.0f, -99.0f, 160.99997f, 115.000015f);

        IS_EQUAL(R, expectedR);
        counter.SetCount(R == expectedR);
        R = Cofactor(A);
        IS_EQUAL(R, Transpose(expectedR));
        counter.SetCount(R == Transpose(expectedR));
        IS_EQUAL(Scale(3.0f, 2.0f, -3.0f, -2.0f), Matrix4(3.0f, 0.0f, 0.0f, 0.0f,
                                                            0.0f, 2.0f, 0.0f, 0.0f,
                                                            0.0f, 0.0f, -3.0f, 0.0f,
                                                            0.0f, 0.0f, 0.0f, -2.0f));
        counter.SetCount(Scale(3.0f, 2.0f, -3.0f, -2.0f) == Matrix4(3.0f, 0.0f, 0.0f, 0.0f,
                                                            0.0f, 2.0f, 0.0f, 0.0f,
                                                            0.0f, 0.0f, -3.0f, 0.0f,
                                                            0.0f, 0.0f, 0.0f, -2.0f));
        R = Scale(3.0f, Vector4(-9.0f, 2.0f, -5.0f, 4.0f));
        expectedR = Matrix4(-0.285714f, -0.285714f, 0.714286f, -0.571429f,
                            -0.285714f, 0.936508f, -0.158730f, 0.126984f,
                            0.714286f, -0.158730f, 0.603175f, -0.317460f,
                            -0.571429f, 0.126984, -0.317460f, 0.746032f);
        IS_EQUAL(R, expectedR);
        counter.SetCount(R == expectedR);
        R = Skew(3.0f, Vector4(-1.0f, 2.0f, -5.0f, 5.0f), Vector4(-9.0f, 3.0f, -2.0f, -5.0f));
        expectedR = Matrix4(1.04405f, 0.079289f, -0.026430f, 0.017620f,
                            -0.008810f, 0.984142f, 0.005286f, -0.003524f,
                            0.017620f, 0.031716f, 0.989428f, 0.007048f,
                            -0.044050f, -0.079289f, 0.026430f, 0.982380f);

        R = Reflection(Vector4(3.0f, -2.0f, 4.5f, -1.5f));
        expectedR = Matrix4(0.492958f, 0.338028f, -0.760563f, 0.253521f,
                            0.338028f, 0.774648f, 0.507042f, -0.169014f,
                            -0.760563f, 0.507042f, -0.140845f, 0.380282f,
                            0.253521f, -0.169014f, 0.380282f, 0.873239f);
        IS_EQUAL(R, expectedR);
        counter.SetCount(R == expectedR);

        R = Involution(Vector4(3.0f, -2.0f, 4.5f, -1.5f));
        IS_EQUAL(R, -1.0f*expectedR);
        counter.SetCount(R == -1.0f*expectedR);



        Print("Testing Matrix4 methods complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }


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
    void Initialize(void)
    {
        Print("Testing Transform3 initalization...");

        Transform3 T(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
        IS_EQUAL(T.Row(0), Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(T.Row(0) == Vector3(1.0f, 2.0f, 3.0f));
        IS_EQUAL(T.Row(1), Vector3(4.0f, 5.0f, 6.0f));
        counter.SetCount(T.Row(1) == Vector3(4.0f, 5.0f, 6.0f));
        IS_EQUAL(T.Row(2), Vector3(0.0f, 0.0f, 1.0f));
        counter.SetCount(T.Row(2) == Vector3(0.0f, 0.0f, 1.0f));
        IS_EQUAL(T.Col(0), Vector2(1.0f, 4.0f));
        counter.SetCount(T.Col(0) == Vector2(1.0f, 4.0f));
        IS_EQUAL(T.Col(1), Vector2(2.0f, 5.0f));
        counter.SetCount(T.Col(1) == Vector2(2.0f, 5.0f));
        IS_EQUAL(T.GetTranslation(), Point2(3.0f, 6.0f));
        counter.SetCount(T.GetTranslation() == Point2(3.0f, 6.0f));

        Transform3 A(Vector2(-3.0f, 2.0f), Vector2(-2.0f, 1.5f), Point2(4.0f, 5.0f));
        IS_EQUAL(A.Row(0), Vector3(-3.0f, -2.0f, 4.0f));
        counter.SetCount(A.Row(0) == Vector3(-3.0f, -2.0f, 4.0f));
        IS_EQUAL(A.Row(1), Vector3(2.0f, 1.5f, 5.0f));
        counter.SetCount(A.Row(1) == Vector3(2.0f, 1.5f, 5.0f));
        IS_EQUAL(T.Row(2), Vector3(0.0f, 0.0f, 1.0f));
        counter.SetCount(T.Row(2) == Vector3(0.0f, 0.0f, 1.0f));
        IS_EQUAL(A.Col(0), Vector2(-3.0f, 2.0f));
        counter.SetCount(A.Col(0) == Vector2(-3.0f, 2.0f));
        IS_EQUAL(A.Col(1), Vector2(-2.0f, 1.5f));
        counter.SetCount(A.Col(1) == Vector2(-2.0f, 1.5f));
        IS_EQUAL(A.GetTranslation(), Point2(4.0f, 5.0f));
        counter.SetCount(A.GetTranslation() == Point2(4.0f, 5.0f));

        Transform3 B(Matrix2(2.0f, -3.0f, 5.0f, -4.0f), Point2(-1.5f, 2.5f));
        IS_EQUAL(B.Row(0), Vector3(2.0f, -3.0f, -1.5f));
        counter.SetCount(B.Row(0) == Vector3(2.0f, -3.0f, -1.5f));
        IS_EQUAL(B.Row(1), Vector3(5.0f, -4.0f, 2.5f));
        counter.SetCount(B.Row(1) == Vector3(5.0f, -4.0f, 2.5f));
        IS_EQUAL(T.Row(2), Vector3(0.0f, 0.0f, 1.0f));
        counter.SetCount(T.Row(2) == Vector3(0.0f, 0.0f, 1.0f));
        IS_EQUAL(B.Col(0), Vector2(2.0f, 5.0f));
        counter.SetCount(B.Col(0) == Vector2(2.0f, 5.0f));
        IS_EQUAL(B.Col(1), Vector2(-3.0f, -4.0f));
        counter.SetCount(B.Col(1) == Vector2(-3.0f, -4.0f));
        IS_EQUAL(B.GetTranslation(), Point2(-1.5f, 2.5f));
        counter.SetCount(B.GetTranslation() == Point2(-1.5f, 2.5f));

        Print("Testing Transform3 initalization complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void ValueChange(void)
    {
        Print("Testing Transform3 value change...");

        Transform3 T(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
        Transform3 B(2.0f, -3.5f, 4.0f, -2.0f, -1.0f, 2.5f);

        IS_EQUAL(T.Row(0), Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(T.Row(0) == Vector3(1.0f, 2.0f, 3.0f));
        IS_EQUAL(T.Row(1), Vector3(4.0f, 5.0f, 6.0f));
        counter.SetCount(T.Row(1) == Vector3(4.0f, 5.0f, 6.0f));
        IS_EQUAL(T.Row(2), Vector3(0.0f, 0.0f, 1.0f));
        counter.SetCount(T.Row(2) == Vector3(0.0f, 0.0f, 1.0f));
        IS_EQUAL(T.Col(0), Vector2(1.0f, 4.0f));
        counter.SetCount(T.Col(0) == Vector2(1.0f, 4.0f));
        IS_EQUAL(T.Col(1), Vector2(2.0f, 5.0f));
        counter.SetCount(T.Col(1) == Vector2(2.0f, 5.0f));
        IS_EQUAL(T.GetTranslation(), Point2(3.0f, 6.0f));
        counter.SetCount(T.GetTranslation() == Point2(3.0f, 6.0f));

        T = B;
        IS_EQUAL(T.Row(0), Vector3(2.0f, -3.5f, 4.0f));
        counter.SetCount(T.Row(0) == Vector3(2.0f, -3.5f, 4.0f));
        IS_EQUAL(T.Row(1), Vector3(-2.0f, -1.0f, 2.5f));
        counter.SetCount(T.Row(1) == Vector3(-2.0f, -1.0f, 2.5f));
        IS_EQUAL(T.Row(2), Vector3(0.0f, 0.0f, 1.0f));
        counter.SetCount(T.Row(2) == Vector3(0.0f, 0.0f, 1.0f));
        IS_EQUAL(T.Col(0), Vector2(2.0f, -2.0f));
        counter.SetCount(T.Col(0) == Vector2(2.0f, -2.0f));
        IS_EQUAL(T.Col(1), Vector2(-3.5f, -1.0f));
        counter.SetCount(T.Col(1) == Vector2(-3.5f, -1.0f));
        IS_EQUAL(T.GetTranslation(), Point2(4.0f, 2.5f));
        counter.SetCount(T.GetTranslation() == Point2(4.0f, 2.5f));

        T = Transform3(2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f);
        IS_EQUAL(T.Row(0), Vector3(2.0f, 2.0f, 2.0f));
        counter.SetCount(T.Row(0) == Vector3(2.0f, 2.0f, 2.0f));
        IS_EQUAL(T.Row(1), Vector3(3.0f, 3.0f, 3.0f));
        counter.SetCount(T.Row(1) == Vector3(3.0f, 3.0f, 3.0f));
        IS_EQUAL(T.Row(2), Vector3(0.0f, 0.0f, 1.0f));
        counter.SetCount(T.Row(2) == Vector3(0.0f, 0.0f, 1.0f));
        IS_EQUAL(T.Col(0), Vector2(2.0f, 3.0f));
        counter.SetCount(T.Col(0) == Vector2(2.0f, 3.0f));
        IS_EQUAL(T.Col(1), Vector2(2.0f, 3.0f));
        counter.SetCount(T.Col(1) == Vector2(2.0f, 3.0f));
        IS_EQUAL(T.GetTranslation(), Point2(2.0f, 3.0f));
        counter.SetCount(T.GetTranslation() == Point2(2.0f, 3.0f));

        T = T.Identity();
        IS_EQUAL(T.Row(0), Vector3(1.0f, 0.0f, 0.0f));
        counter.SetCount(T.Row(0) == Vector3(1.0f, 0.0f, 0.0f));
        IS_EQUAL(T.Row(1), Vector3(0.0f, 1.0f, 0.0f));
        counter.SetCount(T.Row(1) == Vector3(0.0f, 1.0f, 0.0f));
        IS_EQUAL(T.Row(2), Vector3(0.0f, 0.0f, 1.0f));
        counter.SetCount(T.Row(2) == Vector3(0.0f, 0.0f, 1.0f));
        IS_EQUAL(T.Col(0), Vector2(1.0f, 0.0f));
        counter.SetCount(T.Col(0) == Vector2(1.0f, 0.0f));
        IS_EQUAL(T.Col(1), Vector2(0.0f, 1.0f));
        counter.SetCount(T.Col(1) == Vector2(0.0f, 1.0f));
        IS_EQUAL(T.GetTranslation(), Point2(0.0f, 0.0f));
        counter.SetCount(T.GetTranslation() == Point2(0.0f, 0.0f));

        T = T.Zero();
        IS_EQUAL(T.Row(0), Vector3(0.0f, 0.0f, 0.0f));
        counter.SetCount(T.Row(0) == Vector3(0.0f, 0.0f, 0.0f));
        IS_EQUAL(T.Row(1), Vector3(0.0f, 0.0f, 0.0f));
        counter.SetCount(T.Row(1) == Vector3(0.0f, 0.0f, 0.0f));
        IS_EQUAL(T.Row(2), Vector3(0.0f, 0.0f, 1.0f));
        counter.SetCount(T.Row(2) == Vector3(0.0f, 0.0f, 1.0f));
        IS_EQUAL(T.Col(0), Vector2(0.0f, 0.0f));
        counter.SetCount(T.Col(0) == Vector2(0.0f, 0.0f));
        IS_EQUAL(T.Col(1), Vector2(0.0f, 0.0f));
        counter.SetCount(T.Col(1) == Vector2(0.0f, 0.0f));
        IS_EQUAL(T.GetTranslation(), Point2(0.0f, 0.0f));
        counter.SetCount(T.GetTranslation() == Point2(0.0f, 0.0f));

        Print("Testing Transform3 value change complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        Print("Testing Transform3 memory placement...");

        Transform3 T(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
        Transform3 B = T;
        Transform3 *x = &T, *y = &B;

        IS_NOTEQUAL(x, y);
        counter.SetCount(x != y);
        IS_EQUAL(*x, *y);
        counter.SetCount(*x == *y);

        y = &T;
        IS_EQUAL(x, y);
        counter.SetCount(x == y);

        Print("Testing Transform3 memory placement complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void ClassOperators(void)
    {
        Print("Testing Transform3 class operators...");

        Transform3 T(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
        Transform3 B(2.0f, -3.5f, 4.0f, -2.0f, -1.0f, 2.5f);
        Transform3 copyT = T;

        IS_EQUAL(T[0], Vector2(1.0f, 4.0f));
        counter.SetCount(T[0] == Vector2(1.0f, 4.0f));
        IS_EQUAL(T[1], Vector2(2.0f, 5.0f));
        counter.SetCount(T[1] == Vector2(2.0f, 5.0f));
        IS_EQUAL(T[2], Vector2(3.0f, 6.0f));
        counter.SetCount(T[2] == Vector2(3.0f, 6.0f));

        T += B;
        IS_EQUAL(T, Transform3(3.0f, -1.5f, 7.0f, 2.0f, 4.0f, 8.5f));
        counter.SetCount(T == Transform3(3.0f, -1.5f, 7.0f, 2.0f, 4.0f, 8.5f));

        T -= B;
        IS_EQUAL(T, copyT);
        counter.SetCount(T == copyT);

        T *= 2.0f;
        IS_EQUAL(T, Transform3(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f));
        counter.SetCount(T == Transform3(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f));

        T /= 2.0f;
        IS_EQUAL(T, copyT);
        counter.SetCount(T == copyT);


        Print("Testing Transform3 class operators complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void Methods(void)
    {
        Print("Testing Transform3 methods...");

        Transform3 T(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
        Transform3 B(2.0f, -3.5f, 4.0f, -2.0f, -1.0f, 2.5f);
        Transform3 copyT = T;
        Vector2 v(3.0f, -7.0f);
        Point2 p = reinterpret_cast<const Point2& >(v);

        IS_EQUAL(T+B, Transform3(3.0f, -1.5f, 7.0f, 2.0f, 4.0f, 8.5f));
        counter.SetCount(T+B == Transform3(3.0f, -1.5f, 7.0f, 2.0f, 4.0f, 8.5f));
        IS_EQUAL((T+B).Row(2), Vector3(0.0f, 0.0f, 1.0f));
        counter.SetCount((T+B).Row(2) == Vector3(0.0f, 0.0f, 1.0f));
        IS_EQUAL(T-B, Transform3(-1.0f, 5.5f, -1.0f, 6.0f, 6.0f, 3.5f));
        counter.SetCount(T-B == Transform3(-1.0f, 5.5f, -1.0f, 6.0f, 6.0f, 3.5f));
        IS_EQUAL((T-B).Row(2), Vector3(0.0f, 0.0f, 1.0f));
        counter.SetCount((T-B).Row(2) == Vector3(0.0f, 0.0f, 1.0f));
        IS_EQUAL(T*B, Transform3(-2.0f, -5.5f, 12.0f, -2.0f, -19.0f, 34.5f));
        counter.SetCount(T*B == Transform3(-2.0f, -5.5f, 12.0f, -2.0f, -19.0f, 34.5f));
        IS_EQUAL(T*v, Vector2(-11.0f, -23.0f));
        counter.SetCount(T*v == Vector2(-11.0f, -23.0f));
        IS_EQUAL(T*p, Point2(-11.0f, -23.0f));
        counter.SetCount(T*p == Point2(-11.0f, -23.0f));

        IS_EQUAL(T*2.0f, Transform3(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f));
        counter.SetCount(T*2.0f == Transform3(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f));
        IS_EQUAL(2.0f*T, Transform3(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f));
        counter.SetCount(2.0f*T == Transform3(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f));
        IS_EQUAL(T/2.0f, Transform3(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f));
        counter.SetCount(T/2.0f == Transform3(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f));

        IS_EQUAL(Inverse(T), Transform3(-5.0f/3.0f, 2.0f/3.0f, 1.0f, 4.0f/3.0f, -1.0f/3.0f, -2.0f));
        counter.SetCount(Inverse(T) == Transform3(-5.0f/3.0f, 2.0f/3.0f, 1.0f, 4.0f/3.0f, -1.0f/3.0f, -2.0f));

        Print("Testing Transform3 methods complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
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
    void Initialize(void)
    {
        Print("Testing Transform4 initialization...");

        Transform4 T(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f);
        IS_EQUAL(T.Row(0), Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        counter.SetCount(T.Row(0) == Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        IS_EQUAL(T.Row(1), Vector4(5.0f, 6.0f, 7.0f, 8.0f));
        counter.SetCount(T.Row(1) == Vector4(5.0f, 6.0f, 7.0f, 8.0f));
        IS_EQUAL(T.Row(2), Vector4(9.0f, 10.0f, 11.0f, 12.0f));
        counter.SetCount(T.Row(2) == Vector4(9.0f, 10.0f, 11.0f, 12.0f));
        IS_EQUAL(T.Row(3), Vector4(0.0f, 0.0f, 0.0f, 1.0f));
        counter.SetCount(T.Row(3) == Vector4(0.0f, 0.0f, 0.0f, 1.0f));
        IS_EQUAL(T.Col(0), Vector3(1.0f, 5.0f, 9.0f));
        counter.SetCount(T.Col(0) == Vector3(1.0f, 5.0f, 9.0f));
        IS_EQUAL(T.Col(1), Vector3(2.0f, 6.0f, 10.0f));
        counter.SetCount(T.Col(1) == Vector3(2.0f, 6.0f, 10.0f));
        IS_EQUAL(T.Col(2), Vector3(3.0f, 7.0f, 11.0f));
        counter.SetCount(T.Col(2) == Vector3(3.0f, 7.0f, 11.0f));
        IS_EQUAL(T.GetTranslation(), Point3(4.0f, 8.0f, 12.0f));
        counter.SetCount(T.GetTranslation() == Point3(4.0f, 8.0f, 12.0f));

        Transform4 A(Vector3(-2.0f, 3.0f, -4.0f), Vector3(6.0f, 7.0f, -8.0f), Vector3(-5.0f, -1.0f, 9.0f), Point3(-3.5f, 2.5f, -1.5f));
        IS_EQUAL(A.Row(0), Vector4(-2.0f, 6.0f, -5.0f, -3.5f));
        counter.SetCount(A.Row(0) == Vector4(-2.0f, 6.0f, -5.0f, -3.5f));
        IS_EQUAL(A.Row(1), Vector4(3.0f, 7.0f, -1.0f, 2.5f));
        counter.SetCount(A.Row(1) == Vector4(3.0f, 7.0f, -1.0f, 2.5f));
        IS_EQUAL(A.Row(2), Vector4(-4.0f, -8.0f, 9.0f, -1.5f));
        counter.SetCount(A.Row(2) == Vector4(-4.0f, -8.0f, 9.0f, -1.5f));
        IS_EQUAL(A.Row(3), Vector4(0.0f, 0.0f, 0.0f, 1.0f));
        counter.SetCount(A.Row(3) == Vector4(0.0f, 0.0f, 0.0f, 1.0f));
        IS_EQUAL(A.Col(0), Vector3(-2.0f, 3.0f, -4.0f));
        counter.SetCount(A.Col(0) == Vector3(-2.0f, 3.0f, -4.0f));
        IS_EQUAL(A.Col(1), Vector3(6.0f, 7.0f, -8.0f));
        counter.SetCount(A.Col(1) == Vector3(6.0f, 7.0f, -8.0f));
        IS_EQUAL(A.Col(2), Vector3(-5.0f, -1.0f, 9.0f));
        counter.SetCount(A.Col(2) == Vector3(-5.0f, -1.0f, 9.0f));
        IS_EQUAL(A.GetTranslation(), Point3(-3.5f, 2.5f, -1.5f));
        counter.SetCount(A.GetTranslation() == Point3(-3.5f, 2.5f, -1.5f));

        Transform4 B(Matrix3(1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f), Point3(8.0f, 8.0f, 8.0f));
        IS_EQUAL(B.Row(0), Vector4(1.0f, 1.0f, 1.0f, 8.0f));
        counter.SetCount(B.Row(0) == Vector4(1.0f, 1.0f, 1.0f, 8.0f));
        IS_EQUAL(B.Row(1), Vector4(2.0f, 2.0f, 2.0f, 8.0f));
        counter.SetCount(B.Row(1) == Vector4(2.0f, 2.0f, 2.0f, 8.0f));
        IS_EQUAL(B.Row(2), Vector4(3.0f, 3.0f, 3.0f, 8.0f));
        counter.SetCount(B.Row(2) == Vector4(3.0f, 3.0f, 3.0f, 8.0f));
        IS_EQUAL(B.Row(3), Vector4(0.0f, 0.0f, 0.0f, 1.0f));
        counter.SetCount(B.Row(3) == Vector4(0.0f, 0.0f, 0.0f, 1.0f));
        IS_EQUAL(B.Col(0), Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(B.Col(0) == Vector3(1.0f, 2.0f, 3.0f));
        IS_EQUAL(B.Col(1), Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(B.Col(1) == Vector3(1.0f, 2.0f, 3.0f));
        IS_EQUAL(B.Col(2), Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(B.Col(2) == Vector3(1.0f, 2.0f, 3.0f));
        IS_EQUAL(B.GetTranslation(), Point3(8.0f, 8.0f, 8.0f));
        counter.SetCount(B.GetTranslation() == Point3(8.0f, 8.0f, 8.0f));

        Print("Testing Transform4 initialization complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void ValueChange(void)
    {
        Print("Testing Transform4 value change...");
        Transform4 A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f);
        Transform4 B(-3.0f, 1.0f, -4.0f, -5.0f, -7.0f, 13.0f, 2.5f, 4.5f, 5.0f, 1.0f, -1.0f, 3.5f);

        A = B;
        IS_EQUAL(A.Row(0), Vector4(-3.0f, 1.0f, -4.0f, -5.0f));
        counter.SetCount(A.Row(0) == Vector4(-3.0f, 1.0f, -4.0f, -5.0f));
        IS_EQUAL(A.Row(1), Vector4(-7.0f, 13.0f, 2.5f, 4.5f));
        counter.SetCount(A.Row(1) == Vector4(-7.0f, 13.0f, 2.5f, 4.5f));
        IS_EQUAL(A.Row(2), Vector4(5.0f, 1.0f, -1.0f, 3.5f));
        counter.SetCount(A.Row(2) == Vector4(5.0f, 1.0f, -1.0f, 3.5f));
        IS_EQUAL(A.Row(3), Vector4(0.0f, 0.0f, 0.0f, 1.0f));
        counter.SetCount(A.Row(3) == Vector4(0.0f, 0.0f, 0.0f, 1.0f));
        IS_EQUAL(A.Col(0), Vector3(-3.0f, -7.0f, 5.0f));
        counter.SetCount(A.Col(0) == Vector3(-3.0f, -7.0f, 5.0f));
        IS_EQUAL(A.Col(1), Vector3(1.0f, 13.0f, 1.0f));
        counter.SetCount(A.Col(1) == Vector3(1.0f, 13.0f, 1.0f));
        IS_EQUAL(A.Col(2), Vector3(-4.0f, 2.5f, -1.0f));
        counter.SetCount(A.Col(2) == Vector3(-4.0f, 2.5f, -1.0f));
        IS_EQUAL(A.GetTranslation(), Point3(-5.0f, 4.5f, 3.5f));
        counter.SetCount(A.GetTranslation() == Point3(-5.0f, 4.5f, 3.5f));

        A = Transform4(1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f);
        IS_EQUAL(A.Row(0), Vector4(1.0f, 1.0f, 1.0f, 1.0f));
        counter.SetCount(A.Row(0) == Vector4(1.0f, 1.0f, 1.0f, 1.0f));
        IS_EQUAL(A.Row(1), Vector4(2.0f, 2.0f, 2.0f, 2.0f));
        counter.SetCount(A.Row(1) == Vector4(2.0f, 2.0f, 2.0f, 2.0f));
        IS_EQUAL(A.Row(2), Vector4(3.0f, 3.0f, 3.0f, 3.0f));
        counter.SetCount(A.Row(2) == Vector4(3.0f, 3.0f, 3.0f, 3.0f));
        IS_EQUAL(A.Row(3), Vector4(0.0f, 0.0f, 0.0f, 1.0f));
        counter.SetCount(A.Row(3) == Vector4(0.0f, 0.0f, 0.0f, 1.0f));
        IS_EQUAL(A.Col(0), Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(A.Col(0) == Vector3(1.0f, 2.0f, 3.0f));
        IS_EQUAL(A.Col(1), Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(A.Col(1) == Vector3(1.0f, 2.0f, 3.0f));
        IS_EQUAL(A.Col(2), Vector3(1.0f, 2.0f, 3.0f));
        counter.SetCount(A.Col(2) == Vector3(1.0f, 2.0f, 3.0f));
        IS_EQUAL(A.GetTranslation(), Point3(1.0f, 2.0f, 3.0f));
        counter.SetCount(A.GetTranslation() == Point3(1.0f, 2.0f, 3.0f));

        Print("Testing Transform4 value change complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        Print("Testing Transform4 memory placement...");
        Transform4 A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f);
        Transform4 B = A;
        Transform4 *x = &A, *y = &B;

        IS_NOTEQUAL(x, y);
        counter.SetCount(x != y);
        IS_EQUAL(*x, *y);
        counter.SetCount(*x == *y);

        y = &A;
        IS_EQUAL(x, y);
        counter.SetCount(x == y);

        Print("Testing Transform4 memory placement complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void ClassOperators(void)
    {
        Print("Testing Transform4 class operators...");

        Transform4 A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f);
        Transform4 B(-3.0f, 1.0f, -4.0f, -5.0f, -7.0f, 13.0f, 2.5f, 4.5f, 5.0f, 1.0f, -1.0f, 3.5f);
        Transform4 copyA =  A;

        IS_EQUAL(A[0], Vector3(1.0f, 5.0f, 9.0f));
        counter.SetCount(A[0] == Vector3(1.0f, 5.0f, 9.0f));
        IS_EQUAL(A[1], Vector3(2.0f, 6.0f, 10.0f));
        counter.SetCount(A[1] == Vector3(2.0f, 6.0f, 10.0f));
        IS_EQUAL(A[2], Vector3(3.0f, 7.0f, 11.0f));
        counter.SetCount(A[2] == Vector3(3.0f, 7.0f, 11.0f));
        IS_EQUAL(A[3], Vector3(4.0f, 8.0f, 12.0f));
        counter.SetCount(A[3] == Vector3(4.0f, 8.0f, 12.0f));

        A += B;
        IS_EQUAL(A, Transform4(-2.0f, 3.0f, -1.0f, -1.0f, -2.0f, 19.0f, 9.5, 12.5f, 14.0f, 11.0f, 10.0f, 15.5f));
        counter.SetCount(A == Transform4(-2.0f, 3.0f, -1.0f, -1.0f, -2.0f, 19.0f, 9.5, 12.5f, 14.0f, 11.0f, 10.0f, 15.5f));

        A -= B;
        IS_EQUAL(A, copyA);
        counter.SetCount(A == copyA);

        A *= 2.0f;
        IS_EQUAL(A, Transform4(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f));
        counter.SetCount(A == Transform4(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f));

        A /= 2.0f;
        IS_EQUAL(A, copyA);
        counter.SetCount(A == copyA);

        Print("Testing Transform4 class operators complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void Methods(void)
    {
        Print("Testing Transform4 methods...");

        Transform4 A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f);
        Transform4 B(-3.0f, 1.0f, -4.0f, -5.0f, -7.0f, 13.0f, 2.5f, 4.5f, 5.0f, 1.0f, -1.0f, 3.5f);
        Transform4 copyA =  A;

        Vector3 v (1.0f, -2.0f, 3.0f);
        Point3 p = reinterpret_cast<const Point3&>(v);
        Plane f(2.0f, 3.0f, 4.0f, 5.0f);
        Line L(1.0f, 2.0f, 3.0f, -2.5, -2.0, 1.0f);

        IS_EQUAL(A+B, Transform4(-2.0f, 3.0f, -1.0f, -1.0f, -2.0f, 19.0f, 9.5, 12.5f, 14.0f, 11.0f, 10.0f, 15.5f));
        counter.SetCount(A+B == Transform4(-2.0f, 3.0f, -1.0f, -1.0f, -2.0f, 19.0f, 9.5, 12.5f, 14.0f, 11.0f, 10.0f, 15.5f));
        A += B;
        IS_EQUAL(A-B, copyA);
        counter.SetCount(A-B == copyA);
        A = copyA;
        IS_EQUAL(A*B, Transform4(-2.0f, 30.0f, -2.0f, 18.5f, -22.0f, 90.0f, -12.0f, 34.5f, -42.0f, 150.0f, -22.0f, 50.5f));
        counter.SetCount(A*B == Transform4(-2.0f, 30.0f, -2.0f, 18.5f, -22.0f, 90.0f, -12.0f, 34.5f, -42.0f, 150.0f, -22.0f, 50.5f));
        IS_EQUAL(A*v, Vector3(6.0f, 14.0f, 22.0f));
        counter.SetCount(A*v == Vector3(6.0f, 14.0f, 22.0f));
        IS_EQUAL(v*A, Vector3(18.0f, 20.0f, 22.0f));
        counter.SetCount(v*A == Vector3(18.0f, 20.0f, 22.0f));
        IS_EQUAL(A*p, Point3(6.0f, 14.0f, 22.0f));
        counter.SetCount(A*p == Point3(6.0f, 14.0f, 22.0f));
        IS_EQUAL(p*A, Point3(18.0f, 20.0f, 22.0f));
        counter.SetCount(p*A == Point3(18.0f, 20.0f, 22.0f));
        IS_EQUAL(A*f, Plane(40.0f, 96.0f, 152.0f, 5.0f));
        counter.SetCount(A*f == Plane(40.0f, 96.0f, 152.0f, 5.0f));
        IS_EQUAL(f*A, Plane(53.0f, 62.0f, 71.0f, 85.0f));
        counter.SetCount(f*A == Plane(53.0f, 62.0f, 71.0f, 85.0f));
        IS_EQUAL(Inverse(B), Transform4(-0.0455882f, -0.00882353f, 0.160294f, -0.749265f,
                                        0.0161765f, 0.0676471f, 0.104412f, -0.588971f,
                                        -0.211765f, 0.0235294f, -0.0941176f, -0.835294f));
        counter.SetCount(Inverse(B) == Transform4(-0.0455882f, -0.00882353f, 0.160294f, -0.749265f,
                                                0.0161765f, 0.0676471f, 0.104412f, -0.588971f,
                                                -0.211765f, 0.0235294f, -0.0941176f, -0.835294f));
        IS_EQUAL(Reflection(f), Transform4(0.724138f, -0.413793f, -0.551724f, -3.713907f,
                                            -0.413793f, 0.379310f, -0.827586f, -5.570860f,
                                            -0.551724f, -0.827586f, -0.103448f, -7.427814f));
        counter.SetCount(Reflection(f) == Transform4(0.724138f, -0.413793f, -0.551724f, -3.713907f,
                                                    -0.413793f, 0.379310f, -0.827586f, -5.570860f,
                                                    -0.551724f, -0.827586f, -0.103448f, -7.427814f));
        IS_EQUAL(TransformLine(L, B), Line(-13.0f, 26.5f, 4.0f, -119.0f, -56.0f, -313.25f));
        counter.SetCount(TransformLine(L, B) == Line(-13.0f, 26.5f, 4.0f, -119.0f, -56.0f, -313.25f));


        Print("Testing Transform4 methods complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
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
    void Initialize(void)
    {
        Print("Testing Quaternion initialization...");

        Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
        IS_EQUAL(q.x, 1.0f); counter.SetCount(q.x == 1.0f);
        IS_EQUAL(q.y, 2.0f); counter.SetCount(q.y == 2.0f);
        IS_EQUAL(q.z, 3.0f); counter.SetCount(q.z == 3.0f);
        IS_EQUAL(q.w, 4.0f); counter.SetCount(q.w == 4.0f);

        Quaternion r(Vector3(3.0f, -4.0f, 2.0f), -1.0f);
        IS_EQUAL(r.x, 3.0f); counter.SetCount(r.x == 3.0f);
        IS_EQUAL(r.y, -4.0f); counter.SetCount(r.y == -4.0f);
        IS_EQUAL(r.z, 2.0f); counter.SetCount(r.z == 2.0f);
        IS_EQUAL(r.w, -1.0f); counter.SetCount(r.w == -1.0f);

        IS_EQUAL(q.GetVector(), Vector3(1.0f, 2.0f, 3.0));
        counter.SetCount(q.GetVector() == Vector3(1.0f, 2.0f, 3.0));
        IS_EQUAL(r.GetVector(), Vector3(3.0f, -4.0f, 2.0f));
        counter.SetCount(r.GetVector() == Vector3(3.0f, -4.0f, 2.0f));

        Print("Testing Quaternion initialization complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void ValueChange(void)
    {
        Print("Testing Quaternion value change...");

        Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
        q = Quaternion(Vector3(3.0f, -4.0f, 2.0f), -1.0f);
        IS_EQUAL(q.x, 3.0f); counter.SetCount(q.x == 3.0f);
        IS_EQUAL(q.y, -4.0f); counter.SetCount(q.y == -4.0f);
        IS_EQUAL(q.z, 2.0f); counter.SetCount(q.z == 2.0f);
        IS_EQUAL(q.w, -1.0f); counter.SetCount(q.w == -1.0f);

        q = Quaternion(4.0f, -5.0f, -2.0f, 3.0f);
        IS_EQUAL(q.x, 4.0f); counter.SetCount(q.x == 4.0f);
        IS_EQUAL(q.y, -5.0f); counter.SetCount(q.y == -5.0f);
        IS_EQUAL(q.z, -2.0f); counter.SetCount(q.z == -2.0f);
        IS_EQUAL(q.w, 3.0f); counter.SetCount(q.w == 3.0f);

        Quaternion r(-9.0f, 2.0f, -7.0f, 4.0f);
        q = r;
        IS_EQUAL(q.x, -9.0f); counter.SetCount(q.x == -9.0f);
        IS_EQUAL(q.y, 2.0f); counter.SetCount(q.y == 2.0f);
        IS_EQUAL(q.z, -7.0f); counter.SetCount(q.z == -7.0f);
        IS_EQUAL(q.w, 4.0f); counter.SetCount(q.w == 4.0f);

        q.SetRotation(Matrix3(3.0f, 2.0f, -3.0f, -2.0f, 1.0f, -2.0f, -1.0f, -1.0f, 3.0f));
        IS_EQUAL(q, Quaternion(0.108465f, -0.2169305f, -0.4338609f, 0.8677218f));
        counter.SetCount(q == Quaternion(0.108465f, -0.2169305f, -0.4338609f, 0.8677218f));

        q = r;
        Matrix3 m = q.GetRotation();
        IS_EQUAL(m, Matrix3(0.29333f, 0.133333f, 0.946667f, -0.613333f, -0.733333f, 0.293333f, 0.733333f, -0.666667f, -0.133333f));
        counter.SetCount(m == Matrix3(0.29333f, 0.133333f, 0.946667f, -0.613333f, -0.733333f, 0.293333f, 0.733333f, -0.666667f, -0.133333f));

        Print("Testing Quaternion value change complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void MemoryPlacement(void)
    {
        Print("Testing Quaternion memory placement...");
        Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion p = q, *x = &p, *y =  &q;
        IS_NOTEQUAL(x, y);  counter.SetCount(x != y);
        IS_EQUAL(*x, *y); counter.SetCount(*x == *y);

        y = &p;
        IS_EQUAL(x,y); counter.SetCount(x == y);

        Print("Testing Quaternion memory placement complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void ClassOperators(void)
    {
        Print("Testing Quaternion class operators...");

        Quaternion p(4.0f, -3.0f, -7.0f, 2.0f);
        Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion copyP = p;

        p += q;
        IS_EQUAL(p, Quaternion(5.0f, -1.0f, -4.0f, 6.0f));
        counter.SetCount(p == Quaternion(5.0f, -1.0f, -4.0f, 6.0f));
        p -= q;
        IS_EQUAL(p, copyP); counter.SetCount(p == copyP);
        p *= 2.0f;
        IS_EQUAL(p, Quaternion(8.0f, -6.0f, -14.0f, 4.0f));
        counter.SetCount(p == Quaternion(8.0f, -6.0f, -14.0f, 4.0f));
        p /= 2.0f;
        IS_EQUAL(p, copyP); counter.SetCount(p == copyP);
        p *= q;
        IS_EQUAL(p, Quaternion(23.0f, -27.0f, -11.0f, 31.0f));
        counter.SetCount(p == Quaternion(23.0f, -27.0f, -11.0f, 31.0f));


        Print("Testing Quaternion class operators complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
    void Methods(void)
    {
        Print("Testing Quaternion methods...");

        Quaternion p(4.0f, -3.0f, -7.0f, 2.0f);
        Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion copyP = p;

        IS_EQUAL(p+q, Quaternion(5.0f, -1.0f, -4.0f, 6.0f));
        counter.SetCount(p+q == Quaternion(5.0f, -1.0f, -4.0f, 6.0f));
        IS_EQUAL(p-q, Quaternion(3.0f, -5.0f, -10.0f, -2.0f));
        counter.SetCount(p-q == Quaternion(3.0f, -5.0f, -10.0f, -2.0f));
        IS_EQUAL(p*2.0f, Quaternion(8.0f, -6.0f, -14.0f, 4.0f));
        counter.SetCount(p*2.0f == Quaternion(8.0f, -6.0f, -14.0f, 4.0f));
        IS_EQUAL(2.0f*p, Quaternion(8.0f, -6.0f, -14.0f, 4.0f));
        counter.SetCount(2.0f*p == Quaternion(8.0f, -6.0f, -14.0f, 4.0f));
        IS_EQUAL(p/2.0f, Quaternion(2.0f, -1.5f, -3.5f, 1.0f));
        counter.SetCount(p/2.0f == Quaternion(2.0f, -1.5f, -3.5f, 1.0f));
        IS_EQUAL(p*q, Quaternion(23.0f, -27.0f, -11.0f, 31.0f));
        counter.SetCount(p*q == Quaternion(23.0f, -27.0f, -11.0f, 31.0f));

        Vector3 v(3.0f, -1.0f, 2.0f);
        IS_EQUAL(Transform(v, p), Vector3(182.0f, -194.0f, 176.0f));
        counter.SetCount(Transform(v, p) == Vector3(182.0f, -194.0f, 176.0f));

        Print("Testing Quaternion methods complete!");
        Print("-Total Tests: " + to_string(counter.GetTotal()));
        Print("-Tests Passed: " + to_string(counter.GetCountPass()));
        Print("-Tests Failed: " + to_string(counter.GetCountFail()) + "\n");
        counter.Reset();
    }
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