/*! 
        DISCLAIMER: 
            The following code was written using examples from the first two volumes 
            of Eric Lengyel's "Foundations of Game Engine Development", and as such 
            all intellectual accreditation of said code is given to Dr. Lengyel alone.

            The expansions and modifications I made upon his examples can be considered
            trivial, as Dr. Lengyel himself suggests in the texts to expand upon the
            materials presented.

*/
#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "Vectors.h"

/*
        2D Points
*/
struct Point2 : Vector2
{
    Point2() = default;
    Point2(float x, float y) : Vector2(x,y) {}
};
inline Point2 operator +(const Point2& p0, const Point2& p1)
{
    return (Point2(p0.x + p1.x, p0.y + p1.y));
}
inline Vector2 operator -(const Point2& p0, const Point2& p1)
{
    return (Vector2(p0.x - p1.x, p0.y - p1.y));
}

/*
        3D Points
*/
struct Point3 : Vector3
{
    Point3() = default;
    Point3(float x, float y, float z) : Vector3(x,y,z) {}
};
inline Point3 operator +(const Point3& p0, const Point3& p1)
{
    return (Point3(p0.x + p1.x, p0.y + p1.y, p0.z + p1.z));
}
inline Vector3 operator -(const Point3& p0, const Point3& p1)
{
    return (Vector3(p0.x - p1.x, p0.y - p1.y, p0.z - p1.z));
}

/*
        4D Points
*/
struct Point4 : Vector4
{
    Point4() = default;
    Point4(float w, float x, float y, float z) : Vector4(w,x,y,z) {}
};
inline Point4 operator +(const Point4& p0, const Point4& p1)
{
    return (Point4(p0.w + p1.w, p0.x + p1.x, p0.y + p1.y, p0.z + p1.z));
}
inline Vector4 operator -(const Point4& p0, const Point4& p1)
{
    return (Vector4(p0.w - p1.w, p0.x - p1.x, p0.y - p1.y, p0.z - p1.z));
}