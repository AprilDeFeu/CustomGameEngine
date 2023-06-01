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

using namespace std;
/*
        EXCEPTIONS
*/
struct ZeroVectorE : public runtime_error
{
    ZeroVectorE() : runtime_error("Math Error: Vector being projected onto is zero vector.\n")
    {}
};

struct ZeroMagnitudeE : public runtime_error
{
    ZeroMagnitudeE() : runtime_error("Math Error: The magnitude of a vector in the denominator is zero.\n")
    {}
};

/*
        VECTOR 2D
*/
struct Vector2
{
    float x, y;

    Vector2(float a, float b)
    {
        x = a;
        y = b;
    }

    Vector2& operator +=(const Vector2& vec)
    {
        x += vec.x;
        y += vec.y;
        return (*this);
    }

    Vector2& operator -=(const Vector2& vec)
    {
        x -= vec.x;
        y -= vec.y;
        return (*this);
    }

    Vector2& operator *=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        return (*this);
    }

    Vector2& operator /=(float scalar)
    {
        float sc = (1.0f/scalar);
        x *= sc;
        y *= sc;
        return (*this);
    }

    float& operator [](int i)
    {
        return ((&x)[i]);
    }

    const float& operator [](int i) const
    {
        return ((&x)[i]);
    }
};

// Vector2 Inline functions
inline float InnerProduct(const Vector2& v1, const Vector2& v2)
{
    return (v1.x * v2.x) + (v1.y + v2.y);
}

inline Vector2 operator +(const Vector2& v1, const Vector2& v2)
{
    return (Vector2(v1.x + v2.x, v1.y + v2.y));
}

inline Vector2 operator -(const Vector2& v1, const Vector2& v2)
{
    return (Vector2(v1.x - v2.x, v1.y - v2.y));
}

inline Vector2 operator *(const Vector2& vec, float scalar)
{
    return (Vector2(vec.x * scalar, vec.y * scalar));
}

inline Vector2 operator *(float scalar, const Vector2& vec)
{
    return (vec * scalar);
}

inline float operator *(const Vector2& a, const Vector2& b)
{
    return InnerProduct(a,b);
}

inline Vector2 operator /(const Vector2& vec, float scalar)
{
    scalar = 1.0f/scalar;
    return (scalar * vec);
}

inline Vector2 operator -(const Vector2& vec)
{
    return (Vector2(-vec.x, -vec.y));
}

inline float Magnitude(const Vector2& vec)
{
    return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

inline Vector2 Normalize(const Vector2& vec)
{
    return (vec / Magnitude(vec));
}

inline float Angle(const Vector2& v1, const Vector2& v2)
{
    try
    {
        if (Magnitude(v1) == 0 || Magnitude(v2) == 0) throw ZeroMagnitudeE();
        return acos(InnerProduct(v1, v2) / (Magnitude(v1) * Magnitude(v2)));
    }
    catch(ZeroMagnitudeE& e)
    {
        cout << "Exception occurred!\n" << e.what();
    }
    
    
}

// Projects v1 onto v2
inline Vector2 Projection(const Vector2& v1, const Vector2& v2)
{
    try 
    {
        if (v2*v2 == 0.0f) throw ZeroVectorE();
        return (((v1*v2) / (v2*v2)) * v2);
    }

    catch (ZeroVectorE& e)
    {
        cout << "Exception occurred!\n" << e.what();
    }
}

inline Vector2 Rejection(const Vector2& v1, const Vector2& v2)
{
    return (v1 - Projection(v1, v2));
}
/*
        VECTOR 3D
*/
struct Vector3
{
    float x, y, z;

    Vector3(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }
    
    Vector3& operator +=(const Vector3& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        return (*this);
    }

    Vector3& operator -=(const Vector3& vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        return (*this);
    }

    Vector3& operator *=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return (*this);
    }

    Vector3& operator /=(float scalar)
    {
        float sc = (1.0f/scalar);
        x *= sc;
        y *= sc;
        z *= sc;
        return (*this);
    }

    float& operator [](int i)
    {
        return ((&x)[i]);
    }

    const float& operator [](int i) const
    {
        return ((&x)[i]);
    }
};

// Vector 3 Inline functions
inline float InnerProduct(const Vector3& v1, const Vector3& v2)
{
    return ((v1.x * v2.x) + (v1.y + v2.y) + (v1.z + v2.z));
}

inline Vector3 operator +(const Vector3& v1, const Vector3& v2)
{
    return (Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

inline Vector3 operator -(const Vector3& v1, const Vector3& v2)
{
    return (Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

inline Vector3 operator *(const Vector3& vec, float scalar)
{
    return (Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar));
}

inline Vector3 operator *(float scalar, const Vector3& vec)
{
    return (vec * scalar);
}

inline float operator *(const Vector3& a, const Vector3& b)
{
    return InnerProduct(a,b);
}

inline Vector3 operator /(const Vector3& vec, float scalar)
{
    scalar = 1.0f/scalar;
    return (scalar * vec);
}

inline Vector3 operator -(const Vector3& vec)
{
    return (Vector3(-vec.x, -vec.y, -vec.z));
}

inline float Magnitude(const Vector3& vec)
{
    return sqrt((vec.x*vec.x) + (vec.y*vec.y) + (vec.z*vec.z));
}

inline Vector3 Normalize(const Vector3& vec)
{
    return (vec / Magnitude(vec));
}

inline float Angle(const Vector3& v1, const Vector3& v2)
{
    try
    {
        if (Magnitude(v1)==0 || Magnitude(v2)==0) throw ZeroMagnitudeE();
        return acos((v1 * v2) / (Magnitude(v1) * Magnitude(v2)));
    }
    catch(ZeroMagnitudeE& e)
    {
        cout << "Exception occurred!\n" << e.what();
    }
    
}
inline Vector3 Projection(const Vector3& v1, const Vector3& v2)
{
    try 
    {
        if ((v2 * v2) == 0.0f) throw ZeroVectorE();
        return (((v1 * v2) / (v2 * v2)) * v2);
    }

    catch (ZeroVectorE& e)
    {
        cout << "Exception occurred!\n" << e.what();
    }
}
inline Vector3 Rejection(const Vector3& v1, const Vector3& v2)
{
    return (v1 - Projection(v1, v2));
}
inline Vector3 CrossProduct(const Vector3& v1,const Vector3& v2)
{
    return (Vector3(v1.y*v2.z - v1.z*v2.y,
                    v1.z*v2.x - v1.x*v2.z,
                    v1.x*v2.y - v1.y*v2.x));
}
inline float ScalarTripleProduct(const Vector3& v1,const Vector3& v2,const Vector3& v3)
{
    // Returns (v1 x v2) * v3
    return (CrossProduct(v1, v2) * v3);
}
/*
        VECTOR 4D
*/
struct Vector4
{
    float w, x, y, z;

    Vector4(float n, float a, float b, float c)
    {
        w = n;
        x = a;
        y = b;
        z = c;
    }

    Vector4& operator +=(const Vector4& vec)
    {
        w += vec.w;
        x += vec.x;
        y += vec.y;
        z += vec.z;
        return (*this);
    }

    Vector4& operator -=(const Vector4& vec)
    {
        w -= vec.w;
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        return (*this);
    }

    Vector4& operator *=(float scalar)
    {
        w *= scalar;
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return (*this);
    }

    Vector4& operator /=(float scalar)
    {
        float sc = (1.0f/scalar);
        w *= sc;
        x *= sc;
        y *= sc;
        z *= sc;
        return (*this);
    }
    
    float& operator [](int i)
    {
        return ((&x)[i]);
    }

    const float& operator [](int i) const
    {
        return ((&x)[i]);
    }
};

// Vector4 inline functions
inline float InnerProduct(const Vector4& v1, const Vector4& v2)
{
    return ((v1.w*v2.w) + (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z));
}

inline Vector4 operator +(const Vector4& v1, const Vector4& v2)
{
    return (Vector4(v1.w+v2.w, v1.x+v2.x, v1.y+v2.y, v1.z+v2.z));
}

inline Vector4 operator -(const Vector4& v1, const Vector4& v2)
{
    return (Vector4(v1.w-v2.w, v1.x-v2.x, v1.y-v2.y, v1.z-v2.z));
}

inline Vector4 operator *(const Vector4& vec, float scalar)
{
    return (Vector4(vec.w*scalar, vec.x*scalar, vec.y*scalar, vec.z*scalar));
}

inline Vector4 operator *(float scalar, const Vector4& vec)
{
    return (vec * scalar);
}
inline float operator *(const Vector4& a, const Vector4& b)
{
    return InnerProduct(a,b);
}

inline Vector4 operator /(const Vector4& vec, float scalar)
{
    scalar = 1.0f/scalar;
    return (scalar * vec);
}

inline Vector4 operator -(const Vector4& vec)
{
    return (Vector4(-vec.w, -vec.x, -vec.y, -vec.z));
}

inline float Magnitude(const Vector4& vec)
{
    return sqrt((vec.w*vec.w) + (vec.x*vec.x) + (vec.y*vec.y) + (vec.z*vec.z));
}

inline Vector4 Normalize(const Vector4& vec)
{
    return (vec / Magnitude(vec));
}

inline float Angle(const Vector4& v1, const Vector4& v2)
{
    try
    {
        if (Magnitude(v1)==0 || Magnitude(v2)==0) throw ZeroMagnitudeE();
        return acos((v1 * v2) / (Magnitude(v1) * Magnitude(v2)));
    }
    catch(ZeroMagnitudeE& e)
    {
        cout << "Exception occurred!\n" << e.what();
    }
    
}
inline Vector4 Projection(const Vector4& v1, const Vector4& v2)
{
    try 
    {
        if ((v2 * v2) == 0.0f) throw ZeroVectorE();
        return (((v1 * v2) / (v2 * v2)) * v2);
    }

    catch (ZeroVectorE& e)
    {
        cout << "Exception occurred!\n" << e.what();
    }
}
inline Vector4 Rejection(const Vector4& v1, const Vector4& v2)
{
    return (v1 - Projection(v1, v2));
}