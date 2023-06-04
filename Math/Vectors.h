#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>

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
 *  @brief 2D Vector data structure (float x, float y)
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
    Vector2& operator *=(float scalar) {x *= scalar; y *= scalar; return (*this);}
    Vector2& operator /=(float scalar) {float sc = (1.0f/scalar); x *= sc; y *= sc; return (*this);}
    float& operator [](int i) {return ((&x)[i]);}
    const float& operator [](int i) const {return ((&x)[i]);}
    //! @public @memberof Vector2
    //! @brief Creates a 2D vector (0.0f, 0.0f)
    const Vector2& Zero(void) const {return Vector2(0.0f, 0.0f);}
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
    Vector3& operator *=(float scalar) {x *= scalar; y *= scalar; z *= scalar; return (*this);}
    Vector3& operator /=(float scalar)
    {float sc = (1.0f/scalar); x *= sc; y *= sc; z *= sc; return (*this);}
    float& operator [](int i) {return ((&x)[i]);}
    const float& operator [](int i) const {return ((&x)[i]);}
    //! @public @memberof Vector3
    //! @brief Creates a 3D vector (0.0f, 0.0f, 0.0f)
    const Vector3& Zero(void) const {return Vector3(0.0f, 0.0f, 0.0f);}
};

/*! @class Vector4 
 *  @brief 3D Vector data structure (float w, float x, float y, float z)
 *  @param w First component
 *  @param x Second component
 *  @param y Third component
 *  @param z Fourth component
 *  @param Zero() Creates a zero vector (0.0f, 0.0f, 0.0f, 0.0f)
 */
struct Vector4
{
    float w, x, y, z;
    //! @public @memberof Vector4
    //! @brief Creates an empty Vector4 data structure
    Vector4() = default;
    //! @public @memberof Vector4
    //! @brief Creates a Vector4 data structure (float w, float x, float y, float z)
    Vector4(float n, float a, float b, float c) {w = n; x = a; y = b; z = c;}

    Vector4& operator +=(const Vector4& vec) {w += vec.w; x += vec.x; y += vec.y; z += vec.z; return (*this);}
    Vector4& operator -=(const Vector4& vec) {w -= vec.w; x -= vec.x; y -= vec.y; z -= vec.z; return (*this);}
    Vector4& operator *=(float scalar) {w *= scalar; x *= scalar; y *= scalar; z *= scalar; return (*this);}
    Vector4& operator /=(float scalar) {float sc = (1.0f/scalar); w *= sc; x *= sc; y *= sc; z *= sc; return (*this);} 
    float& operator [](int i) {return ((&x)[i]);}
    const float& operator [](int i) const {return ((&x)[i]);}
    //! @public @memberof Vector4
    //! @brief Creates a 4D vector (0.0f, 0.0f, 0.0f, 0.0f)
    const Vector4& Zero(void) const {return Vector4(0.0f, 0.0f, 0.0f, 0.0f);}
};

//---------------------------------------------------------------------------------------------
//                                      INLINE FUNCTIONS
//---------------------------------------------------------------------------------------------

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
inline float InnerProduct(const Vector4& v1, const Vector4& v2) {return ((v1.w*v2.w) + (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z));}

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

inline Vector4 operator +(const Vector4& v1, const Vector4& v2) {return (Vector4(v1.w+v2.w, v1.x+v2.x, v1.y+v2.y, v1.z+v2.z));}
inline Vector4 operator -(const Vector4& v1, const Vector4& v2) {return (Vector4(v1.w-v2.w, v1.x-v2.x, v1.y-v2.y, v1.z-v2.z));}
inline Vector4 operator *(const Vector4& vec, float scalar) {return (Vector4(vec.w*scalar, vec.x*scalar, vec.y*scalar, vec.z*scalar));}
inline Vector4 operator *(float scalar, const Vector4& vec) {return (vec * scalar);}
inline float operator *(const Vector4& a, const Vector4& b) {return InnerProduct(a,b);}
inline Vector4 operator /(const Vector4& vec, float scalar) {scalar = 1.0f/scalar; return (scalar * vec);}
inline Vector4 operator -(const Vector4& vec) {return (Vector4(-vec.w, -vec.x, -vec.y, -vec.z));}

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
inline float Magnitude(const Vector4& vec) {return sqrt((vec.w*vec.w) + (vec.x*vec.x) + (vec.y*vec.y) + (vec.z*vec.z));}

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