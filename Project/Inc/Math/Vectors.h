#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Math\Helpers.h"

using namespace std;

//---------------------------------------------------------------------------------------------
//                                        EXCEPTIONS
//---------------------------------------------------------------------------------------------

struct ZeroVectorE : public runtime_error
{ZeroVectorE() : runtime_error("Math Error: Vector being projected onto is zero vector.\n"){}};

struct ZeroMagnitudeE : public runtime_error
{ZeroMagnitudeE() : runtime_error("Math Error: The magnitude of a vector in the denominator is zero.\n"){}};

//---------------------------------------------------------------------------------------------
//                                        CLASSES
//---------------------------------------------------------------------------------------------

/*! @class Vector2
 *  @brief 2D Vector data structure
 *  @param x First component
 *  @param y Second component
 *  @param Zero() Creates a zero vector (0.0f, 0.0f)
 */
struct Vector2
{
    float x, y;
    //! @public @memberof Vector2
    //! @brief Creates an empty Vector2 data structure
    Vector2() = default;
    //! @public @memberof Vector2
    //! @brief Creates a Vector2 data structure (float x, float y)
    Vector2(float a, float b) {x = a; y = b;}

    Vector2& operator +=(const Vector2& vec) {x += vec.x; y += vec.y; return (*this);}
    Vector2& operator -=(const Vector2& vec) {x -= vec.x; y -= vec.y; return (*this);}
    float operator *=(const Vector2& vec) {return x * vec.x + y * vec.y;}
    Vector2& operator *=(float scalar) {x *= scalar; y *= scalar; return (*this);}
    Vector2& operator /=(float scalar) {float sc = (1.0f/scalar); x *= sc; y *= sc; return (*this);}
    const bool operator ==(const Vector2& vec) const {return (CloseFloat(x,vec.x) && CloseFloat(y, vec.y));}
    const bool operator !=(const Vector2& vec) const {return !((*this)==vec);}
    float& operator [](int i) {return ((&x)[i]);}
    const float& operator [](int i) const {return ((&x)[i]);}
    //! @public @memberof Vector2
    //! @brief Creates a 2D vector (0.0f, 0.0f)
    const Vector2 Zero(void) const {return Vector2(0.0f, 0.0f);}
    //! @public @memberof Vector2
    //! @brief Yields this Vector2 as a string representation
    const string ToString(void) const {return "(" + to_string(x) + ", " + to_string(y) + ")";}
    //! @public @memberof Vector2
    //! @brief Prints this Vector2
    void Print(void) {cout << "Vector2: " << (*this).ToString() << "\n";}
};

/*! @class Vector3
 *  @brief 3D Vector data structure (float x, float y, float z)
 *  @param x First component
 *  @param y Second component
 *  @param z Third component
 *  @param Zero() Creates a zero vector (0.0f, 0.0f, 0.0f)
 */
struct Vector3
{
    float x, y, z;
    //! @public @memberof Vector3
    //! @brief Creates an empty Vector3 data structure
    Vector3() = default;
    //! @public @memberof Vector3
    //! @brief Creates a Vector3 data structure (float x, float y, float z)
    Vector3(float a, float b, float c) {x = a;  y = b;  z = c;}

    Vector3& operator +=(const Vector3& vec) {x += vec.x; y += vec.y; z += vec.z; return (*this);}
    Vector3& operator -=(const Vector3& vec) {x -= vec.x; y -= vec.y; z -= vec.z; return (*this);}
    float operator *=(const Vector3& vec) {return x * vec.x + y * vec.y + z * vec.z;}
    Vector3& operator *=(float scalar) {x *= scalar; y *= scalar; z *= scalar; return (*this);}
    Vector3& operator /=(float scalar)
    {float sc = (1.0f/scalar); x *= sc; y *= sc; z *= sc; return (*this);}
    const bool operator ==(const Vector3& vec) const {return (CloseFloat(x, vec.x) && CloseFloat(y, vec.y) && CloseFloat(z, vec.z));}
    const bool operator !=(const Vector3& vec) const {return !((*this) == vec);}
    float& operator [](int i) {return ((&x)[i]);}
    const float& operator [](int i) const {return ((&x)[i]);}
    //! @public @memberof Vector3
    //! @brief Creates a 3D vector (0.0f, 0.0f, 0.0f)
    const Vector3 Zero(void) const {return Vector3(0.0f, 0.0f, 0.0f);}
    //! @public @memberof Vector3
    //! @brief Yields this Vector3 as a string representation
    const string ToString(void) const {return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";}
    //! @public @memberof Vector3
    //! @brief Prints this Vector3
    void Print(void) {cout << "Vector3: " << (*this).ToString() << "\n";}

};

/*! @class Vector4
 *  @brief 3D Vector data structure (float w, float x, float y, float z)
 *  @param x First component
 *  @param y Second component
 *  @param z Third component
 *  @param w Fourth component
 *  @param Zero() Creates a zero vector (0.0f, 0.0f, 0.0f, 0.0f)
 *
 */
struct Vector4
{
    float x, y, z, w;
    //! @public @memberof Vector4
    //! @brief Creates an empty Vector4 data structure
    Vector4() = default;
    //! @public @memberof Vector4
    //! @brief Creates a Vector4 data structure (float x, float y, float z, float w)
    Vector4(float a, float b, float c, float n) {x = a; y = b; z = c; w = n;}

    Vector4& operator +=(const Vector4& vec) {x += vec.x; y += vec.y; z += vec.z; w += vec.w; return (*this);}
    Vector4& operator -=(const Vector4& vec) {x -= vec.x; y -= vec.y; z -= vec.z; w -= vec.w; return (*this);}
    Vector4& operator *=(float scalar) {x *= scalar; y *= scalar; z *= scalar; w *= scalar; return (*this);}
    float operator *=(const Vector4& vec) {return x * vec.x + y * vec.y + z * vec.z + w * vec.w;}
    Vector4& operator /=(float scalar) {float sc = (1.0f/scalar); x *= sc; y *= sc; z *= sc; w *= sc; return (*this);}
    const bool operator ==(const Vector4& vec) const {return (CloseFloat (x, vec.x) && CloseFloat(y, vec.y) && CloseFloat(z, vec.z) && CloseFloat(w, vec.w));}
    const bool operator !=(const Vector4& vec) const {return (!((*this) == (vec)));}
    float& operator [](int i) {return ((&x)[i]);}
    const float& operator [](int i) const {return ((&x)[i]);}
    //! @public @memberof Vector4
    //! @brief Creates a 4D vector (0.0f, 0.0f, 0.0f, 0.0f)
    const Vector4 Zero(void) const {return Vector4(0.0f, 0.0f, 0.0f, 0.0f);}
    //! @public @memberof Vector4
    //! @brief Yields this Vector4 as a string representation
    const string ToString(void) const
    {return "(" + to_string(x) + ", " + to_string(y) +
            ", " + to_string(z) + ", " + to_string(w) + ")";}
    //! @public @memberof Vector4
    //! @brief Prints this Vector4
    void Print(void) {cout << "Vector4: " << (*this).ToString() << "\n";}
};

//---------------------------------------------------------------------------------------------
//                                      INLINE FUNCTIONS
//---------------------------------------------------------------------------------------------

// * * * * * POWER * * * * * //
/*!
 * @brief Tail-recursive power function.
 * @see Power(double base, double int, int exp) in Helpers.h for more details.
 * @param base The base value to exponentiate
 * @param exponent The exponent
 * @return [double] base^exponent : base to the power of exponent
 */
inline double Power(double base, int exponent) {return Power(base, exponent, 1.0);}

// * * * * * INNER PRODUCTS * * * * * //

//! @brief Calculates inner product for two Vector2 structures. This is the function that is used by the
//!        dot product operator.
//! @param v1 First vector
//! @param v2 Second vector
//! @return [float] Value of their innner product.
inline float InnerProduct(const Vector2& v1, const Vector2& v2) {return (v1.x * v2.x) + (v1.y * v2.y);}
//! @brief Calculates inner product for two Vector3 structures. This is the function that is used by the
//!        dot product operator.
//! @param v1 First vector
//! @param v2 Second vector
//! @return [float] Value of their innner product.
inline float InnerProduct(const Vector3& v1, const Vector3& v2) {return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));}
//! @brief Calculates inner product for two Vector4 structures. This is the function that is used by the
//!        dot product operator.
//! @param v1 First vector
//! @param v2 Second vector
//! @return [float] Value of their innner product.
inline float InnerProduct(const Vector4& v1, const Vector4& v2) {return ((v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z) + (v1.w*v2.w));}

// * * * * * OPERATORS * * * * * //

// VECTOR2

inline Vector2 operator +(const Vector2& v1, const Vector2& v2) {return (Vector2(v1.x + v2.x, v1.y + v2.y));}
inline Vector2 operator -(const Vector2& v1, const Vector2& v2) {return (Vector2(v1.x - v2.x, v1.y - v2.y));}
inline Vector2 operator *(const Vector2& vec, float scalar) {return (Vector2(vec.x * scalar, vec.y * scalar));}
inline Vector2 operator *(float scalar, const Vector2& vec) {return (vec * scalar);}
inline float operator *(const Vector2& a, const Vector2& b) {return InnerProduct(a,b);}
inline Vector2 operator /(const Vector2& vec, float scalar) {scalar = 1.0f/scalar; return (scalar*vec);}
inline Vector2 operator -(const Vector2& vec) {return (Vector2(-vec.x, -vec.y));}

// VECTOR3

inline Vector3 operator +(const Vector3& v1, const Vector3& v2) {return (Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));}
inline Vector3 operator -(const Vector3& v1, const Vector3& v2) {return (Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));}
inline Vector3 operator *(const Vector3& vec, float scalar) {return (Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar));}
inline Vector3 operator *(float scalar, const Vector3& vec) {return (vec * scalar);}
inline float operator *(const Vector3& a, const Vector3& b){return InnerProduct(a,b);}
inline Vector3 operator /(const Vector3& vec, float scalar) {scalar = 1.0f/scalar; return (scalar * vec);}
inline Vector3 operator -(const Vector3& vec) {return (Vector3(-vec.x, -vec.y, -vec.z));}

//  VECTOR4

inline Vector4 operator +(const Vector4& v1, const Vector4& v2) {return (Vector4(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z, v1.w+v2.w));}
inline Vector4 operator -(const Vector4& v1, const Vector4& v2) {return (Vector4(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z, v1.w-v2.w));}
inline Vector4 operator *(const Vector4& vec, float scalar) {return (Vector4(vec.x*scalar, vec.y*scalar, vec.z*scalar, vec.w*scalar));}
inline Vector4 operator *(float scalar, const Vector4& vec) {return (vec * scalar);}
inline float operator *(const Vector4& a, const Vector4& b) {return InnerProduct(a,b);}
inline Vector4 operator /(const Vector4& vec, float scalar) {scalar = 1.0f/scalar; return (scalar * vec);}
inline Vector4 operator -(const Vector4& vec) {return (Vector4(-vec.x, -vec.y, -vec.z, -vec.w));}

// * * * * * MAGNITUDES * * * * * //

//! @brief Yields the magnitude of a Vector2 structure
//! @param vec The vector to find the magnitude for
//! @return [float] Value of the magnitude
inline float Magnitude(const Vector2& vec) {return sqrt((vec.x * vec.x) + (vec.y * vec.y));}
//! @brief Yields the magnitude of a Vector3 structure
//! @param vec The vector to find the magnitude for
//! @return [float] Value of the magnitude
inline float Magnitude(const Vector3& vec) {return sqrt((vec.x*vec.x) + (vec.y*vec.y) + (vec.z*vec.z));}
//! @brief Yields the magnitude of a Vector4 structure
//! @param vec The vector to find the magnitude for
//! @return [float] Value of the magnitude
inline float Magnitude(const Vector4& vec) {return sqrt((vec.x*vec.x) + (vec.y*vec.y) + (vec.z*vec.z) + (vec.w*vec.w));}

// * * * * * NORMALIZATION * * * * * //

//! @brief Normalizes a Vector2 structure
//! @param vec The vector to normalize
//! @return [Vector2] Normalized vector
inline Vector2 Normalize(const Vector2& vec) {return (vec / Magnitude(vec));}
//! @brief Normalizes a Vector3 structure
//! @param vec The vector to normalize
//! @return [Vector3] Normalized vector
inline Vector3 Normalize(const Vector3& vec) {return (vec / Magnitude(vec));}
//! @brief Normalizes a Vector4 structure
//! @param vec The vector to normalize
//! @return [Vector4] Normalized vector
inline Vector4 Normalize(const Vector4& vec) {return (vec / Magnitude(vec));}

// * * * * * SWAP * * * * * //
/*!
 * @brief Swaps the values of two vectors
 * @param v1 First vector
 * @param v2 Second vector
 */
inline void Swap(Vector2 *v1, Vector2 *v2)
{
    Vector2 tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}
/*!
 * @brief Swaps the values of two vectors
 * @param v1 First vector
 * @param v2 Second vector
 */
inline void Swap(Vector3 *v1, Vector3 *v2)
{
    Vector3 tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}
/*!
 * @brief Swaps the values of two vectors
 * @param v1 First vector
 * @param v2 Second vector
 */
inline void Swap(Vector4 *v1, Vector4 *v2)
{
    Vector4 tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}

//---------------------------------------------------------------------------------------------
//                                          FUNCTIONS
//---------------------------------------------------------------------------------------------

// * * * * * 3D CROSS PRODUCT * * * * * //

//! @class Vector3
//! @brief Generates the cross product between two Vector3 structures
//! @param v1 First vector
//! @param v2 Second vector
//! @return [Vector3] The cross product v1 x v2
Vector3 CrossProduct(const Vector3& v1,const Vector3& v2);

// * * * * * 3D SCALAR TRIPLE PRODUCT * * * * * //
//! @brief Calculates the scalar triple product for three Vector3 structures
//! @param v1 First vector
//! @param v2 Second vector
//! @param v3 Third vector
//! @return [float]
float ScalarTripleProduct(const Vector3& v1,const Vector3& v2,const Vector3& v3);

// * * * * * ANGLES * * * * * //

//! @brief Calculates the angle (in radians) between two Vector2 structures
//! @param v1 The first vector
//! @param v2 The second vector
//! @return [float] Angle between vectors
float Angle(const Vector2& v1, const Vector2& v2);
//! @brief Calculates the angle (in radians) between two Vector3 structures
//! @param v1 The first vector
//! @param v2 The second vector
//! @return [float] Angle between vectors
float Angle(const Vector3& v1, const Vector3& v2);
//! @brief Calculates the angle (in radians) between two Vector4 structures
//! @param v1 The first vector
//! @param v2 The second vector
//! @return [float] Angle between vectors
float Angle(const Vector4& v1, const Vector4& v2);
//! @brief Calculates the angle (in degrees) between two Vector2 structures
//! @param v1 The first vector
//! @param v2 The second vector
//! @return [float] Angle between vectors
inline float AngleDegrees(const Vector2& v1, const Vector2& v2) {return (Angle(v1,v2)*180.0f / PI);}
//! @brief Calculates the angle (in degrees) between two Vector3 structures
//! @param v1 The first vector
//! @param v2 The second vector
//! @return [float] Angle between vectors
inline float AngleDegrees(const Vector3& v1, const Vector3& v2) {return (Angle(v1,v2)*180.0f / PI);}
//! @brief Calculates the angle (in degrees) between two Vector4 structures
//! @param v1 The first vector
//! @param v2 The second vector
//! @return [float] Angle between vectors
inline float AngleDegrees(const Vector4& v1, const Vector4& v2) {return (Angle(v1,v2)*180.0f / PI);}

// * * * * * PROJECTIONS * * * * * //

//! @brief Projects the first Vector2 structure onto the second Vector2 structure
//! @param v1 First vector
//! @param v2 Second vector
//! @return [Vector2] v1 projected onto v2
//! @warning If v2 is a zero vector, this function will return an exception
Vector2 Projection(const Vector2& v1, const Vector2& v2);
//! @brief Projects the first Vector3 structure onto the second Vector3 structure
//! @param v1 First vector
//! @param v2 Second vector
//! @return [Vector3] v1 projected onto v2
//! @warning If v2 is a zero vector, this function will return an exception
Vector3 Projection(const Vector3& v1, const Vector3& v2);
//! @brief Projects the first Vector4 structure onto the second Vector4 structure
//! @param v1 First vector
//! @param v2 Second vector
//! @return [Vector4] v1 projected onto v2
//! @warning If v2 is a zero vector, this function will return an exception
Vector4 Projection(const Vector4& v1, const Vector4& v2);

// * * * * * REJECTIONS * * * * * //

//! @brief Rejects the first Vector2 structure onto the second Vector2 structure
//! @param v1 First vector
//! @param v2 Second vector
//! @return [Vector2] v1 rejected onto v2
//! @warning If v2 is a zero vector, this function will return an exception
inline Vector2 Rejection(const Vector2& v1, const Vector2& v2) {return (v1 - Projection(v1, v2));}
//! @brief Rejects the first Vector3 structure onto the second Vector3 structure
//! @param v1 First vector
//! @param v2 Second vector
//! @return [Vector3] v1 rejected onto v2
//! @warning If v2 is a zero vector, this function will return an exception
inline Vector3 Rejection(const Vector3& v1, const Vector3& v2) {return (v1 - Projection(v1, v2));}
//! @brief Rejects the first Vector4 structure onto the second Vector2 structure
//! @param v1 First vector
//! @param v2 Second vector
//! @return [Vector4] v1 rejected onto v2
//! @warning If v2 is a zero vector, this function will return an exception
inline Vector4 Rejection(const Vector4& v1, const Vector4& v2) {return (v1 - Projection(v1, v2));}