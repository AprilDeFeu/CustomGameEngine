#pragma once
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>
#include "Math\Helpers.h"
#include "Math\Vectors.h"
#include "Math\Geometry.h"

//---------------------------------------------------------------------------------------------
//                                        EXCEPTIONS
//---------------------------------------------------------------------------------------------
struct NonInvertibleE : public runtime_error
{

    NonInvertibleE() : runtime_error("Math error: Given matrix is non-invertible.\n")
    {};
};
struct NonDiagonalizableE : public runtime_error
{
    NonDiagonalizableE() : runtime_error("Math error: Given matrix is not diagonalizable.\n")
    {};
};
//---------------------------------------------------------------------------------------------
//                                         CLASSES
//---------------------------------------------------------------------------------------------


/*!
 * @class Matrix2
 * @brief 2D square matrix data structure. Uses float values as matrix coefficients
 * @param M(i,j) Float accessed through the ith row and jth column
 * @param M[j] Vector2 accessed through jth column
 */
struct Matrix2
{
protected:
    float m[2][2];
public:
    //! @public @memberof Matrix2
    //! @brief Creates an empty Matrix2 structure
    Matrix2() = default;
    //! @public @memberof Matrix2
    //! @brief Creates an Matrix2 structure with 4 float matrix coefficients
    Matrix2(float a00, float a01, float a10, float a11)
    {
        m[0][0] = a00; m[0][1] = a10;
        m[1][0] = a01; m[1][1] = a11;
    }
    //! @public @memberof Matrix2
    //! @brief Creates an Matrix2 structure with 2 Vector2 components as columns
    Matrix2(const Vector2& a, const Vector2& b)
    {
        m[0][0] = a.x; m[0][1] = a.y;
        m[1][0] = b.x; m[1][1] = b.y;
    }
    // [float] Operator for access to ith row and jth column
    float& operator ()(int i, int j) {return (m[j][i]);}
    // [const float] Operator for access to ith row and jth column
    const float& operator ()(int i, int j) const {return (m[j][i]);}
    // [Vector3] Operator for access to jth column
    Vector2& operator [](int j) {return (*reinterpret_cast<Vector2 *>(m[j]));}
    // [const Vector3] Operator for access to jth column
    const Vector2& operator [](int j) const {return (*reinterpret_cast<const Vector2 *>(m[j]));}
    Matrix2& operator += (const Matrix2& A)
    {
        m[0][0] += A(0,0); m[0][1] += A(1,0);
        m[1][0] += A(0,1); m[1][1] += A(1,1);
        return (*this);
    }
    Matrix2& operator -= (const Matrix2& A)
    {
        m[0][0] -= A(0,0); m[0][1] -= A(1,0);
        m[1][0] -= A(0,1); m[1][1] -= A(1,1);
        return (*this);
    }
    Matrix2& operator *= (float sc)
    {
        m[0][0] *= sc; m[0][1] *= sc;
        m[1][0] *= sc; m[1][1] *= sc;
        return (*this);
    }
    Matrix2& operator /= (float sc)
    {
        sc = 1.0f/sc;
        m[0][0] *= sc; m[0][1] *= sc;
        m[1][0] *= sc; m[1][1] *= sc;
        return (*this);
    }
    const bool operator == (const Matrix2& A) const
    {
        return (*reinterpret_cast<const Vector2*>(m[0])==A[0]
        && *reinterpret_cast<const Vector2*>(m[1])==A[1]);
    }
    const bool operator != (const Matrix2& A) const
    {
        return !(*this == A);
    }
    //! @brief Returns the ith row as a Vector2 structure
    const Vector2 Row(int i) const
    {
        return Vector2(m[0][i], m[1][i]);
    }
    //! @brief Returns the jth row as a Vector2 structure
    const Vector2 Col(int j) const
    {
        return Vector2(m[j][0], m[j][1]);
    }
    //! @brief Returns a 2x2 identity matrix
    const Matrix2 Identity(void) const
    {return Matrix2(1.0f, 0.0f,
                    0.0f, 1.0f);}
    //! @brief Returns a 2x2 zero matrix
    const Matrix2 Zero(void) const
    {return Matrix2(0.0f, 0.0f,
                    0.0f, 0.0f);}
    string ToString(void)
    {
        string s;
        s += "\t[" + to_string(m[0][0]) + ", " + to_string(m[1][0]) + "]\n";
        s += "\t[" + to_string(m[0][1]) + ", " + to_string(m[1][1]) + "]\n";
        return s;
    }
    void Print(void) {cout << "Matrix2: \n" << (*this).ToString();}
};
/*!
 * @class Matrix3
 * @brief 3D square matrix data structure. Uses float values as matrix coefficients
 * @param M(i,j) Float accessed through the ith row and jth column
 * @param M[j] Vector3 accessed through jth column
 */
struct Matrix3
{
protected:
    float m[3][3];

public:
    //! @public @memberof Matrix3
    //! @brief Construct an empty Matrix3 structure
    Matrix3() = default;
    //! @public @memberof Matrix3
    //! @brief Construct a Matrix3 structure with 9 float matrix coefficients
    Matrix3(float a00, float a01, float a02,
            float a10, float a11, float a12,
            float a20, float a21, float a22)
    {m[0][0] = a00; m[0][1] = a10; m[0][2] = a20;
    m[1][0] = a01; m[1][1] = a11; m[1][2] = a21;
    m[2][0] = a02; m[2][1] = a12; m[2][2] = a22;}
    //! @public @memberof Matrix3
    //! @brief Construct a Matrix3 structure with 3 Vector3 components as columns
    Matrix3(const Vector3& a, const Vector3& b, const Vector3& c)
    {m[0][0] = a.x; m[0][1] = a.y; m[0][2] = a.z;
    m[1][0] = b.x; m[1][1] = b.y; m[1][2] = b.z;
    m[2][0] = c.x; m[2][1] = c.y; m[2][2] = c.z;}
    // [float] Operator for access to ith row and jth column
    float& operator ()(int i, int j) {return (m[j][i]);}
    // [const float] Operator for access to ith row and jth column
    const float& operator ()(int i, int j) const {return (m[j][i]);}
    // [Vector3] Operator for access to jth column
    Vector3& operator [](int j) {return (*reinterpret_cast<Vector3 *>(m[j]));}
    // [const Vector3] Operator for access to jth
    const Vector3& operator [](int j) const {return (*reinterpret_cast<const Vector3 *>(m[j]));}
    Matrix3& operator +=(const Matrix3& A)
    {
        m[0][0] += A(0,0); m[0][1] += A(1,0); m[0][2] += A(2,0);
        m[1][0] += A(0,1); m[1][1] += A(1,1); m[1][2] += A(2,1);
        m[2][0] += A(0,2); m[2][1] += A(1,2); m[2][2] += A(2,2);
        return (*this);
    }
    Matrix3& operator -=(const Matrix3& A)
    {
        m[0][0] -= A(0,0); m[0][1] -= A(1,0); m[0][2] -= A(2,0);
        m[1][0] -= A(0,1); m[1][1] -= A(1,1); m[1][2] -= A(2,1);
        m[2][0] -= A(0,2); m[2][1] -= A(1,2); m[2][2] -= A(2,2);
        return (*this);
    }
    Matrix3& operator *=(float sc)
    {
        m[0][0] *= sc; m[0][1] *= sc; m[0][2] *= sc;
        m[1][0] *= sc; m[1][1] *= sc; m[1][2] *= sc;
        m[2][0] *= sc; m[2][1] *= sc; m[2][2] *= sc;
        return (*this);
    }
    Matrix3& operator /=(float sc)
    {
        sc = 1.0f/sc;
        m[0][0] *= sc; m[0][1] *= sc; m[0][2] *= sc;
        m[1][0] *= sc; m[1][1] *= sc; m[1][2] *= sc;
        m[2][0] *= sc; m[2][1] *= sc; m[2][2] *= sc;
        return (*this);
    }
    const bool operator ==(const Matrix3& A) const
    {
        return (*reinterpret_cast<const Vector3*>(m[0])==A[0]
        && *reinterpret_cast<const Vector3*>(m[1])==A[1]
        && *reinterpret_cast<const Vector3*>(m[2])==A[2]);
    }
    const bool operator != (const Matrix3& A) const
    {
        return !(*this == A);
    }
    //! @brief Returns the ith row as a Vector2 structure
    const Vector3 Row(int i) const
    {
        return Vector3(m[0][i], m[1][i], m[2][i]);
    }
    //! @brief Returns the jth row as a Vector2 structure
    const Vector3 Col(int j) const
    {
        return Vector3(m[j][0], m[j][1], m[j][2]);
    }
    //! @brief Returns a 3x3 identity matrix
    const Matrix3 Identity(void) const
    {
        return Matrix3( 1.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 1.0f);
    }
    //! @brief Returns a 3x3 zero matrix
    const Matrix3 Zero(void) const
    {
        return Matrix3( 0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f);
    }
    string ToString(void)
    {
        string s;
        s += "\t[" + to_string(m[0][0]) + ", " + to_string(m[1][0]) + ", " + to_string(m[2][0]) + "]\n";
        s += "\t[" + to_string(m[0][1]) + ", " + to_string(m[1][1]) + ", " + to_string(m[2][1]) + "]\n";
        s += "\t[" + to_string(m[0][2]) + ", " + to_string(m[1][2]) + ", " + to_string(m[2][2]) + "]\n";
        return s;
    }
    void Print(void) {cout << "Matrix3: \n" << (*this).ToString();}
};
/*!
 * @class Matrix4
 * @brief 4D square matrix data structure. Uses float values as matrix coefficients
 * @param M(i,j) Float accessed throught the ith row and jth column
 * @param M[j] Vector4 accessed throught the jth column
 */
struct Matrix4
{
protected:
    float m[4][4];
public:
    //! @public @memberof Matrix4
    //! @brief Construct an empty Matrix4 structure
    Matrix4() = default;
    //! @public @memberof Matrix4
    //! @brief Construct a Matrix4 structure with 16 matrix coefficients
    Matrix4(float a00, float a01, float a02, float a03,
            float a10, float a11, float a12, float a13,
            float a20, float a21, float a22, float a23,
            float a30, float a31, float a32, float a33)
    {m[0][0] = a00; m[0][1] = a10; m[0][2] = a20; m[0][3] = a30;
    m[1][0] = a01; m[1][1] = a11; m[1][2] = a21; m[1][3] = a31;
    m[2][0] = a02; m[2][1] = a12; m[2][2] = a22; m[2][3] = a32;
    m[3][0] = a03; m[3][1] = a13; m[3][2] = a23; m[3][3] = a33;}
    //! @public @memberof Matrix4
    //! @brief Construct a Matrix4 structure with 4 Vector4 components as columns
    Matrix4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d)
    {m[0][0] = a.x; m[0][1] = a.y; m[0][2] = a.z; m[0][3] = a.w;
    m[1][0] = b.x; m[1][1] = b.y; m[1][2] = b.z; m[1][3] = b.w;
    m[2][0] = c.x; m[2][1] = c.y; m[2][2] = c.z; m[2][3] = c.w;
    m[3][0] = d.x; m[3][1] = d.y; m[3][2] = d.z; m[3][3] = d.w;}
    // [float] Operator for access to ith row and jth column
    float& operator ()(int i, int j) {return (m[j][i]);}
    // [const float] Operator for access to ith row and jth column
    const float& operator ()(int i, int j) const {return (m[j][i]);}
    // [Vector4] Operator for access to jth column
    Vector4& operator [](int j) {return (*reinterpret_cast<Vector4 *>(m[j]));}
    // [const Vector4] Operator for access to jth column
    const Vector4& operator [](int j) const {return (*reinterpret_cast<const Vector4 *>(m[j]));}
    Matrix4& operator +=(const Matrix4& A)
    {
        m[0][0] += A(0,0); m[0][1] += A(1,0); m[0][2] += A(2,0); m[0][3] += A(3,0);
        m[1][0] += A(0,1); m[1][1] += A(1,1); m[1][2] += A(2,1); m[1][3] += A(3,1);
        m[2][0] += A(0,2); m[2][1] += A(1,2); m[2][2] += A(2,2); m[2][3] += A(3,2);
        m[3][0] += A(0,3); m[3][1] += A(1,3); m[3][2] += A(2,3); m[3][3] += A(3,3);
        return (*this);
    }
    Matrix4& operator -=(const Matrix4& A)
    {
        m[0][0] -= A(0,0); m[0][1] -= A(1,0); m[0][2] -= A(2,0); m[0][3] -= A(3,0);
        m[1][0] -= A(0,1); m[1][1] -= A(1,1); m[1][2] -= A(2,1); m[1][3] -= A(3,1);
        m[2][0] -= A(0,2); m[2][1] -= A(1,2); m[2][2] -= A(2,2); m[2][3] -= A(3,2);
        m[3][0] -= A(0,3); m[3][1] -= A(1,3); m[3][2] -= A(2,3); m[3][3] -= A(3,3);
        return (*this);
    }
    Matrix4& operator *=(float sc)
    {
        m[0][0] *= sc; m[0][1] *= sc; m[0][2] *= sc; m[0][3] *= sc;
        m[1][0] *= sc; m[1][1] *= sc; m[1][2] *= sc; m[1][3] *= sc;
        m[2][0] *= sc; m[2][1] *= sc; m[2][2] *= sc; m[2][3] *= sc;
        m[3][0] *= sc; m[3][1] *= sc; m[3][2] *= sc; m[3][3] *= sc;
        return (*this);
    }
    Matrix4& operator /=(float sc)
    {
        sc = 1.0f/sc;
        m[0][0] *= sc; m[0][1] *= sc; m[0][2] *= sc; m[0][3] *= sc;
        m[1][0] *= sc; m[1][1] *= sc; m[1][2] *= sc; m[1][3] *= sc;
        m[2][0] *= sc; m[2][1] *= sc; m[2][2] *= sc; m[2][3] *= sc;
        m[3][0] *= sc; m[3][1] *= sc; m[3][2] *= sc; m[3][3] *= sc;
        return (*this);
    }
    const bool operator ==(const Matrix4& A) const
    {
        return (*reinterpret_cast<const Vector4*>(m[0])==A[0]
        && *reinterpret_cast<const Vector4*>(m[1])==A[1]
        && *reinterpret_cast<const Vector4*>(m[2])==A[2]
        && *reinterpret_cast<const Vector4*>(m[3])==A[3]);
    }
    const bool operator != (const Matrix4& A) const
    {
        return !(*this == A);
    }
    //! @brief Returns the ith row as a Vector2 structure
    const Vector4 Row(int i) const
    {
        return Vector4(m[0][i], m[1][i], m[2][i], m[3][i]);
    }
    //! @brief Returns the jth row as a Vector2 structure
    const Vector4 Col(int j) const
    {
        return Vector4(m[j][0], m[j][1], m[j][2], m[j][3]);
    }
    //! @brief Returns a 4x4 identity matrix
    const Matrix4 Identity(void) const
    {
        return Matrix4( 1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f);
    }
    //! @brief Returns a 4x4 zero matrix
    const Matrix4 Zero(void) const
    {
        return Matrix4( 0.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 0.0f);
    }
    string ToString(void);
    void Print(void)
    {
        cout << "Matrix4: \n" << (*this).ToString();
    }
};
/*!
 * @class Transform3 @extends Matrix3
 * @brief 3D square matrix for transfrom data structure. This is to be used to transform Matrix2 structures,
 *        and as such, the Transform3 structure is implemented through one transformation Matrix2 structure
 *        on the first two columns, and one translation Vector2 structure on the last column.
 *        The 3rd row is always (0,0,1).
 * @param T(i,j) Float accessed throught the ith row and jth column.
 * @param T[j] Vector2 accessed through the jth column. The last entry in the Transform's column is ignored.
 */
struct Transform3 : Matrix3
{
    //! @public @memberof Transform3
    //! @brief Constructs an empty Transform3 structure
    Transform3() = default;
    //! @public @memberof Transform3
    //! @brief Constructs a Transform3 structure with 6 float components
    Transform3( float t00, float t01, float t02,
                float t10, float t11, float t12)
    {
        m[0][0] = t00; m[0][1] = t10;
        m[1][0] = t01; m[1][1] = t11;
        m[2][0] = t02; m[2][1] = t12;

        m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;
    }
    //! @public @memberof Transform3
    //! @brief Constructs a Transform3 structure with 2 Vector2 components and a Point2 component
    Transform3( const Vector2& v0, const Vector2& v1, const Point2& p)
    {
        m[0][0] = v0.x; m[0][1] = v0.y;
        m[1][0] = v1.x; m[1][1] = v1.y;

        m[2][0] = p.x; m[2][1] = p.y;

        m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;
        }
    //! @public @memberof Transform3
    //! @brief Constructs a Transform3 structure with 1 Matrix2 component and a Point2 component
    Transform3( const Matrix2& A, const Point2&  p)
    {
        m[0][0] = A(0,0); m[0][1] = A(1,0);
        m[1][0] = A(0,1); m[1][1] = A(1,1);

        m[2][0] = p.x; m[2][1] = p.y;

        m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;}
    // [Vector2] Operator for access to jth column of Transform3, neglecting its thrid row.
    Vector2& operator [](int j) {return (*reinterpret_cast<Vector2 *>(m[j]));}
    // [const Vector2] Operator for access to jth column of Transform3, neglecting its thrid row.
    const Vector2& operator [](int j) const {return (*reinterpret_cast<const Vector2 *>(m[j]));}
    //! @public @memberof Transform3
    //! @brief Gets the translation vector of this Transform3 structure as a Point2 structure
    const Point2& GetTranslation(void) const{return (*reinterpret_cast<const Point2 *>(m[2]));}
    //! @public @memberof Transform3
    //! @brief Sets the translation vector of this Transform3 structure using a Point2 structure
    void SetTranslation(const Point2& p) {m[2][0] = p.x; m[2][1] = p.y;}

    const bool operator ==(const Transform3& T) const
    {
        return (*reinterpret_cast<const Vector2*>(m[0])==T[0]
            && *reinterpret_cast<const Vector2*>(m[1])==T[1]
            && *reinterpret_cast<const Vector2*>(m[2])==T[2]);
    }
    Transform3& operator +=(const Transform3& T)
    {
        m[0][0] += T(0,0); m[0][1] += T(1,0);
        m[1][0] += T(0,1); m[1][1] += T(1,1);
        m[2][0] += T(0,2); m[2][1] += T(1,2);
        return (*this);
    }
    Transform3& operator -=(const Transform3& T)
    {
        m[0][0] -= T(0,0); m[0][1] -= T(1,0);
        m[1][0] -= T(0,1); m[1][1] -= T(1,1);
        m[2][0] -= T(0,2); m[2][1] -= T(1,2);
        return (*this);
    }
    Transform3& operator *=(const Transform3& T)
    {
        m[0][0] = m[0][0]*T(0,0) + m[1][0]*T(1,0);
        m[1][0] = m[0][0]*T(0,1) + m[1][0]*T(1,1);
        m[2][0] = m[0][0]*T(0,2) + m[1][0]*T(1,2) + m[2][0];
        m[0][1] = m[0][1]*T(0,0) + m[1][1]*T(1,0);
        m[1][1] = m[0][1]*T(0,1) + m[1][1]*T(1,1);
        m[2][1] = m[0][1]*T(0,2) + m[1][1]*T(1,2) + m[2][1];
        return (*this);
    }
    Transform3& operator *=(float f)
    {
        m[0][0] *= f; m[0][1] *= f;
        m[1][0] *= f; m[1][1] *= f;
        m[2][0] *= f; m[2][1] *= f;
        return (*this);
    }
    Transform3& operator /=(float f)
    {
        float sc = 1.0f/f;
        m[0][0] *= sc; m[0][1] *= sc;
        m[1][0] *= sc; m[1][1] *= sc;
        m[2][0] *= sc; m[2][1] *= sc;
        return (*this);
    }
    const Transform3 Zero() const  {return Transform3( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);}

};
/*!
 * @class Transform4 @extends Matrix4
 * @brief 4D square matrix for transfrom data structure. This is to be used to transform Matrix3 structures,
 *        and as such, the Transform4 structure is implemented through one transformation Matrix3 structure
 *        on the first three columns, and one translation Vector3 structure on the last column.
 *        The 3rd row is always (0,0,0,1).
 * @param T(i,j) Float accessed throught the ith row and jth column.
 * @param T[j] Vector3 accessed through the jth column. The last entry in the Transform's column is ignored.
 */
struct Transform4 : Matrix4
{
    //! @public @memberof Transform4
    //! @brief Constructs an empty Transform4 structure
    Transform4() = default;
    //! @public @memberof Transform4
    //!@brief Constructs a Transform4 structure with 12 float components
    Transform4( float t00, float t01, float t02, float t03,
                float t10, float t11, float t12, float t13,
                float t20, float t21, float t22, float t23)
    {
        m[0][0] = t00; m[0][1] = t10; m[0][2] = t20;
        m[1][0] = t01; m[1][1] = t11; m[1][2] = t21;
        m[2][0] = t02; m[2][1] = t12; m[2][2] = t22;
        m[3][0] = t03; m[3][1] = t13; m[3][2] = t23;

        m[0][3] = 0.0f; m[1][3] = 0.0f; m[2][3] = 0.0f; m[3][3]=1.0f;
    }
    //! @public @memberof Transform4
    //! @brief Constructs a Transform4 structure with 3 Vector3 components and one Point3 component
    Transform4(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Point3& p)
    {
        m[0][0] = v0.x; m[0][1] = v0.y; m[0][2] = v0.z;
        m[1][0] = v1.x; m[1][1] = v1.y; m[1][2] = v1.z;
        m[2][0] = v2.x; m[2][1] = v2.y; m[2][2] = v2.z;

        m[3][0] = p.x; m[3][1] = p.y; m[3][2] = p.z;

        m[0][3] = 0.0f; m[1][3] = 0.0f; m[2][3] = 0.0f; m[3][3]=1.0f;
    }
    //! @public @memberof Transform4
    //! @brief Constructs a Transform4 structure with 1 Matrix3 component and one Point3 component
    Transform4(const Matrix3& A, const Point3& p)
    {
        m[0][0] = A(0,0); m[0][1] = A(1,0); m[0][2] = A(2,0);
        m[1][0] = A(0,1); m[1][1] = A(1,1); m[1][2] = A(2,1);
        m[2][0] = A(0,2); m[2][1] = A(1,2); m[2][2] = A(2,2);

        m[3][0] = p.x; m[3][1] = p.y; m[3][2] = p.z;

        m[0][3] = 0.0f; m[1][3] = 0.0f; m[2][3] = 0.0f; m[3][3]=1.0f;
    }
    //! @public @memberof Transform4
    //! @brief [Vector3] Operator for access to the jth column of this Transform4 structure, neglecting its fourth row.
    Vector3& operator [](int j) {return (*reinterpret_cast<Vector3 *>(m[j]));}
    //! @public @memberof Transform4
    //! @brief [const Vector3] Operator for access to the jth column of this Transform4 structure, neglecting its fourth row.
    const Vector3& operator [](int j) const {return (*reinterpret_cast<const Vector3 *>(m[j]));}
    //! @public @memberof Transform4
    //! @brief Gets the translation vector of this Transform4 as a Point3 structure
    const Point3& GetTranslation(void) const {return (*reinterpret_cast<const Point3 *>(m[3]));}
    //! @public @memberof Transform4
    //! @brief Sets the translation vector of this Transform4 using a Point3 structure
    void SetTranslation(const Point3& p) {m[3][0] = p.x; m[3][1] = p.y; m[3][2] = p.z;}

    const bool operator ==(const Transform4& T) const
    {
        return (*reinterpret_cast<const Vector3*>(m[0])==T[0]
            && *reinterpret_cast<const Vector3*>(m[1])==T[1]
            && *reinterpret_cast<const Vector3*>(m[2])==T[2]
            && *reinterpret_cast<const Vector3*>(m[3])==T[3]);
    }
    Transform4& operator +=(const Transform4& T)
    {
        m[0][0] += T(0,0); m[0][1] += T(1,0); m[0][2] += T(2,0);
        m[1][0] += T(0,1); m[1][1] += T(1,1); m[1][2] += T(2,1);
        m[2][0] += T(0,2); m[2][1] += T(1,2); m[2][2] += T(2,2);
        m[3][0] += T(0,3); m[3][1] += T(1,3); m[3][2] += T(2,3);
        return (*this);
    }
    Transform4& operator -=(const Transform4& T)
    {
        m[0][0] -= T(0,0); m[0][1] -= T(1,0); m[0][2] -= T(2,0);
        m[1][0] -= T(0,1); m[1][1] -= T(1,1); m[1][2] -= T(2,1);
        m[2][0] -= T(0,2); m[2][1] -= T(1,2); m[2][2] -= T(2,2);
        m[3][0] -= T(0,3); m[3][1] -= T(1,3); m[3][2] -= T(2,3);
        return (*this);
    }
    Transform4& operator *=(const Transform4& T)
    {
        m[0][0] = m[0][0]*T(0,0) + m[1][0]*T(1,0) + m[2][0]*T(2,0);
        m[1][0] = m[0][0]*T(0,1) + m[1][0]*T(1,1) + m[2][0]*T(2,1);
        m[2][0] = m[0][0]*T(0,2) + m[1][0]*T(1,2) + m[2][0]*T(2,2);
        m[3][0] = m[0][0]*T(0,3) + m[1][0]*T(1,3) + m[2][0]*T(2,3) + m[3][0];
        m[0][1] = m[0][1]*T(0,0) + m[1][1]*T(1,0) + m[2][1]*T(2,0);
        m[1][1] = m[0][1]*T(0,1) + m[1][1]*T(1,1) + m[2][1]*T(2,1);
        m[2][1] = m[0][1]*T(0,2) + m[1][1]*T(1,2) + m[2][1]*T(2,2);
        m[3][1] = m[0][1]*T(0,3) + m[1][1]*T(1,3) + m[2][1]*T(2,3) + m[3][1];
        m[0][2] = m[0][2]*T(0,0) + m[1][2]*T(1,0) + m[2][2]*T(2,0);
        m[1][2] = m[0][2]*T(0,1) + m[1][2]*T(1,1) + m[2][2]*T(2,1);
        m[2][2] = m[0][2]*T(0,2) + m[1][2]*T(1,2) + m[2][2]*T(2,2);
        m[3][2] = m[0][2]*T(0,3) + m[1][2]*T(1,3) + m[2][2]*T(2,3) + m[3][2];
        return (*this);
    }
    Transform4& operator *=(float f)
    {
        m[0][0] *= f; m[0][1] *= f; m[0][2] *= f;
        m[1][0] *= f; m[1][1] *= f; m[1][2] *= f;
        m[2][0] *= f; m[2][1] *= f; m[2][2] *= f;
        m[3][0] *= f; m[3][1] *= f; m[3][2] *= f;
        return (*this);
    }
    Transform4& operator /=(float f)
    {
        float sc = 1.0f/f;
        m[0][0] *= sc; m[0][1] *= sc; m[0][2] *= sc;
        m[1][0] *= sc; m[1][1] *= sc; m[1][2] *= sc;
        m[2][0] *= sc; m[2][1] *= sc; m[2][2] *= sc;
        m[3][0] *= sc; m[3][1] *= sc; m[3][2] *= sc;
        return (*this);
    }
    const Transform4 Zero() const
    {
        Vector3 v;
        Point3 p;
        return Transform4(v.Zero(), v.Zero(), v.Zero(), p.Zero());
    }
};
/*!
 * @class Quaternion
 * @brief Very useful data structures to represent simple and complex rotations and orientations.
 *        They can be thought of as a Vector3 component (x,y,z) with a scalar component (w).
 *        For imaginary units i^2 = j^2 = k^2 = -1, we have the quaternion q = xi + yj + zk + w
 * @param x The x component of the quaternion
 * @param y The y component of the quaternion
 * @param z The z component of the quaternion
 * @param w The w component of the quaternion
 * @param GetRotation() Creates a Matrix3 structure representing the rotation of this quaternion
 * @param SetRotation() Sets the quaternion value using a Matrix3 structure representing a rotation
 *
 */
struct Quaternion
{
    float x,y,z,w;
    //! @public @memberof Quaternion
    //! @brief Constructs an empty quaternion
    Quaternion() = default;
    //! @public @memberof Quaternion
    //! @brief Constructs a quaternion with 4 float components
    Quaternion(float a, float b, float c, float sc) {x = a; y = b; z = c; w = sc;}
    //! @public @memberof Quaternion
    //! @brief Constructs a quaternion with 1 Vector3 component and a scalar component
    Quaternion(const Vector3& v, float sc) {x = v.x; y = v.y; z = v.z; w = sc;}
    //! @public @memberof Quaternion
    //! @brief Gets the components of the quaternion without the scalar component as a Vector3 structure
    const Vector3 GetVector(void) const {return (Vector3(x,y,z));}
    const bool operator ==(const Quaternion& q) const {return (x==q.x && y==q.y && z==q.z && w==q.w);}
    const bool operator !=(const Quaternion& q) const {return !(*this == q);}
    Quaternion& operator +=(const Quaternion& q) {x += q.x; y += q.y; z += q.z; w += q.w; return (*this);}
    Quaternion& operator -=(const Quaternion& q) {x -= q.x; y -= q.y; z -= q.z; w -= q.w; return (*this);}
    Quaternion& operator *=(float sc) {x  *= sc; y *= sc; z *= sc; w *= sc; return (*this);}
    Quaternion& operator /=(float sc) {sc = 1.0f/sc; x *= sc; y *= sc; z *= sc; w *= sc; return (*this);}
    Quaternion& operator *=(const Quaternion& q)
    {
        x = w*q.x + x*q.w + y*q.z - z*q.y;
        y = w*q.y - x*q.z + y*q.w + z*q.x;
        z = w*q.z + x*q.y - y*q.x + z*q.w;
        w = w*q.w - x*q.x - y*q.y - z*q.z;
        return (*this);
    }
    /*!
     * @public @memberof Quaternion
     * @brief Gets the rotation matrix as a Matrix3 structure representing this quaternion
     * @return [Matrix3] The rotation matrix of this quaternion
     */
    Matrix3 GetRotation(void);
    /*!
     * @brief Sets the value of this quaternion through a Matrix3 structure representing a rotation
     * @param M The matrix representing a rotation
     */
    void SetRotation(const Matrix3& M);
    string ToString(void) {return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ", " + to_string(w) + ")";}
    void Print(void) {cout << "Quaternion: " << ToString() << endl;}
};
//---------------------------------------------------------------------------------------------
//                                        INLINE FUNCTIONS
//---------------------------------------------------------------------------------------------

// * * * * * OPERATORS * * * * * //

//Matrix2

inline Matrix2 operator +(const Matrix2& A, const Matrix2& B)
{return (Matrix2(A(0,0)+B(0,0), A(0,1)+B(0,1),
                A(1,0)+B(1,0), A(1,1)+B(1,1)));}
inline Matrix2 operator *(const Matrix2& M, float sc)
{return (Matrix2(M(0,0)*sc, M(0,1)*sc, M(1,0)*sc, M(1,1)*sc));}
inline Matrix2 operator *(float sc, const Matrix2& M) {return (M*sc);}
inline Matrix2 operator /(const Matrix2& M, float sc) {return ((1.0f/sc) * M);}
inline Matrix2 operator *(const Matrix2& A, const Matrix2& B)
{return (Matrix2(A(0,0)*B(0,0) + A(0,1)*B(1,0),
                A(0,0)*B(0,1) + A(0,1)*B(1,1),
                A(1,0)*B(0,0) + A(1,1)*B(1,0),
                A(1,0)*B(0,1) + A(1,1)*B(1,1)));}
inline Vector2 operator *(const Matrix2& M, const Vector2& v)
{return (Vector2(M(0,0)*v.x + M(0,1)*v.y,
                M(1,0)*v.x + M(1,1)*v.y));}
inline Matrix2 operator -(const Matrix2& A, const Matrix2& B) {return (A + (-1.0f*B));}

// Matrix3

inline Matrix3 operator +(const Matrix3& A, const Matrix3& B)
{return (Matrix3(A(0,0)+B(0,0), A(0,1)+B(0,1), A(0,2)+B(0,2),
                A(1,0)+B(1,0), A(1,1)+B(1,1), A(1,2)+B(1,2),
                A(2,0)+B(2,0), A(2,1)+B(2,1), A(2,2)+B(2,2)));}
inline Matrix3 operator *(float sc, const Matrix3& M)
{return (Matrix3(sc*M(0,0), sc*M(0,1), sc*M(0,2),
                sc*M(1,0), sc*M(1,1), sc*M(1,2),
                sc*M(2,0), sc*M(2,1), sc*M(2,2)));}
inline Matrix3 operator *(const Matrix3& M, float sc) {return (sc*M);}
inline Matrix3 operator /(const Matrix3& M, float sc) {return ((1.0f/sc)*M);}
inline Matrix3 operator -(const Matrix3& A, const Matrix3& B) {return (A + (-1.0f * B));}
inline Matrix3 operator *(const Matrix3& A, const Matrix3& B)
{return (Matrix3(A(0,0)*B(0,0) + A(0,1)*B(1,0) + A(0,2)*B(2,0),
                A(0,0)*B(0,1) + A(0,1)*B(1,1) + A(0,2)*B(2,1),
                A(0,0)*B(0,2) + A(0,1)*B(1,2) + A(0,2)*B(2,2),
                A(1,0)*B(0,0) + A(1,1)*B(1,0) + A(1,2)*B(2,0),
                A(1,0)*B(0,1) + A(1,1)*B(1,1) + A(1,2)*B(2,1),
                A(1,0)*B(0,2) + A(1,1)*B(1,2) + A(1,2)*B(2,2),
                A(2,0)*B(0,0) + A(2,1)*B(1,0) + A(2,2)*B(2,0),
                A(2,0)*B(0,1) + A(2,1)*B(1,1) + A(2,2)*B(2,1),
                A(2,0)*B(0,2) + A(2,1)*B(1,2) + A(2,2)*B(2,2)));}
inline Vector3 operator *(const Matrix3& M, const Vector3& v)
{return (Vector3(M(0,0)*v.x + M(0,1)*v.y + M(0,2)*v.z,
                M(1,0)*v.x + M(1,1)*v.y + M(1,2)*v.z,
                M(2,0)*v.x + M(2,1)*v.y + M(2,2)*v.z));}

// Matrix4

inline Matrix4 operator +(const Matrix4& A, const Matrix4& B)
{return (Matrix4(A(0,0)+B(0,0), A(0,1)+B(0,1), A(0,2)+B(0,2), A(0,3)+B(0,3),
                A(1,0)+B(1,0), A(1,1)+B(1,1), A(1,2)+B(1,2), A(1,3)+B(1,3),
                A(2,0)+B(2,0), A(2,1)+B(2,1), A(2,2)+B(2,2), A(2,3)+B(2,3),
                A(3,0)+B(3,0), A(3,1)+B(3,1), A(3,2)+B(3,2), A(3,3)+B(3,3)));}
inline Matrix4 operator *(const Matrix4& A, const Matrix4& B)
{return (Matrix4(A(0,0)*B(0,0) + A(0,1)*B(1,0) + A(0,2)*B(2,0) + A(0,3)*B(3,0),
                A(0,0)*B(0,1) + A(0,1)*B(1,1) + A(0,2)*B(2,1) + A(0,3)*B(3,1),
                A(0,0)*B(0,2) + A(0,1)*B(1,2) + A(0,2)*B(2,2) + A(0,3)*B(3,2),
                A(0,0)*B(0,3) + A(0,1)*B(1,3) + A(0,2)*B(2,3) + A(0,3)*B(3,3),
                A(1,0)*B(0,0) + A(1,1)*B(1,0) + A(1,2)*B(2,0) + A(1,3)*B(3,0),
                A(1,0)*B(0,1) + A(1,1)*B(1,1) + A(1,2)*B(2,1) + A(1,3)*B(3,1),
                A(1,0)*B(0,2) + A(1,1)*B(1,2) + A(1,2)*B(2,2) + A(1,3)*B(3,2),
                A(1,0)*B(0,3) + A(1,1)*B(1,3) + A(1,2)*B(2,3) + A(1,3)*B(3,3),
                A(2,0)*B(0,0) + A(2,1)*B(1,0) + A(2,2)*B(2,0) + A(2,3)*B(3,0),
                A(2,0)*B(0,1) + A(2,1)*B(1,1) + A(2,2)*B(2,1) + A(2,3)*B(3,1),
                A(2,0)*B(0,2) + A(2,1)*B(1,2) + A(2,2)*B(2,2) + A(2,3)*B(3,2),
                A(2,0)*B(0,3) + A(2,1)*B(1,3) + A(2,2)*B(2,3) + A(2,3)*B(3,3),
                A(3,0)*B(0,0) + A(3,1)*B(1,0) + A(3,2)*B(2,0) + A(3,3)*B(3,0),
                A(3,0)*B(0,1) + A(3,1)*B(1,1) + A(3,2)*B(2,1) + A(3,3)*B(3,1),
                A(3,0)*B(0,2) + A(3,1)*B(1,2) + A(3,2)*B(2,2) + A(3,3)*B(3,2),
                A(3,0)*B(0,3) + A(3,1)*B(1,3) + A(3,2)*B(2,3) + A(3,3)*B(3,3)));}
inline Vector4 operator *(const Matrix4& M, const Vector4& v)
{return (Vector4(M(0,0)*v.w + M(0,1)*v.x + M(0,2)*v.y + M(0,3)*v.z,
                M(1,0)*v.w + M(1,1)*v.x + M(1,2)*v.y + M(1,3)*v.z,
                M(2,0)*v.w + M(2,1)*v.x + M(2,2)*v.y + M(2,3)*v.z,
                M(3,0)*v.w + M(3,1)*v.x + M(3,2)*v.y + M(3,3)*v.z));}
inline Matrix4 operator *(float sc, const Matrix4& M)
{return (Matrix4(sc*M(0,0), sc*M(0,1), sc*M(0,2), sc*M(0,3),
                sc*M(1,0), sc*M(1,1), sc*M(1,2), sc*M(1,3),
                sc*M(2,0), sc*M(2,1), sc*M(2,2), sc*M(2,3),
                sc*M(3,0), sc*M(3,1), sc*M(3,2), sc*M(3,3)));}
inline Matrix4 operator *(const Matrix4& M, float sc) {return (sc*M);}
inline Matrix4 operator /(const Matrix4& M, float sc) {return ((1.0f/sc)*M);}
inline Matrix4 operator -(const Matrix4& A, const Matrix4& B) {return (A + (-1.0f * B));}

// Transform3

inline Transform3 operator +(const Transform3& A, const Transform3& B)
{return (Transform3(
    A(0,0) + B(0,0), A(0,1) + B(0,1), A(0,2) + B(0,2),
    A(1,0) + B(1,0), A(1,1) + B(1,1), A(1,2) + B(1,2)));}
inline Transform3 operator *(float sc, const Transform3& T)
{return Transform3(
    sc*T(0,0), sc*T(0,1), sc*T(0,2),
    sc*T(1,0), sc*T(1,1), sc*T(1,2));}
inline Transform3 operator *(const Transform3& T, float sc) {return (sc*T);}
inline Transform3 operator /(const Transform3& T, float sc) {return (1.0f/sc) * T;}
inline Transform3 operator -(const Transform3& A, const Transform3& B) {return A + (-1.0f*B);}
inline Transform3 operator *(const Transform3& A, const Transform3& B)
{return (Transform3(
    A(0,0)*B(0,0) + A(0,1)*B(1,0),
    A(0,0)*B(0,1) + A(0,1)*B(1,1),
    A(0,0)*B(0,2) + A(0,1)*B(1,2) + A(0,2),
    A(1,0)*B(0,0) + A(1,1)*B(1,0),
    A(1,0)*B(0,1) + A(1,1)*B(1,1),
    A(1,0)*B(0,2) + A(1,1)*B(1,2) + A(1,2)));}
inline Vector2 operator *(const Transform3& T, const Vector2& v)
{return (Vector2(
    T(0,0)*v.x + T(0,1)*v.y,
    T(1,0)*v.x + T(1,1)*v.y));}
inline Point2 operator *(const Transform3& T, const Point2& p)
{return (Point2(
    T(0,0)*p.x + T(0,1)*p.y,
    T(1,0)*p.x + T(1,1)*p.y));}

// Transform4

inline Transform4 operator +(const Transform4& A, const Transform4& B)
{return (Transform4(
    A(0,0) + B(0,0), A(0,1) + B(0,1), A(0,2) + B(0,2), A(0,3) + B(0,3),
    A(1,0) + B(1,0), A(1,1) + B(1,1), A(1,2) + B(1,2), A(1,3) + B(1,3),
    A(2,0) + B(2,0), A(2,1) + B(2,1), A(2,2) + B(2,2), A(2,3) + B(2,3)));}
inline Transform4 operator *(float sc, const Transform4& T)
{return Transform4(
    sc*T(0,0), sc*T(0,1), sc*T(0,2), sc*T(0,3),
    sc*T(1,0), sc*T(1,1), sc*T(1,2), sc*T(1,3),
    sc*T(2,0), sc*T(2,1), sc*T(2,2), sc*T(2,3));}
inline Transform4 operator *(const Transform4& T, float sc) {return (sc*T);}
inline Transform4 operator /(const Transform4& T, float sc) {return (1.0f/sc) * T;}
inline Transform4 operator -(const Transform4& A, const Transform4& B) {return A + (-1.0f*B);}
inline Transform4 operator *(const Transform4& A, const Transform4& B)
{return (Transform4(
    A(0,0)*B(0,0) + A(0,1)*B(1,0) + A(0,2)*B(2,0),
    A(0,0)*B(0,1) + A(0,1)*B(1,1) + A(0,2)*B(2,1),
    A(0,0)*B(0,2) + A(0,1)*B(1,2) + A(0,2)*B(2,2),
    A(0,0)*B(0,3) + A(0,1)*B(1,3) + A(0,2)*B(2,3) + A(0,3),
    A(1,0)*B(0,0) + A(1,1)*B(1,0) + A(1,2)*B(2,0),
    A(1,0)*B(0,1) + A(1,1)*B(1,1) + A(1,2)*B(2,1),
    A(1,0)*B(0,2) + A(1,1)*B(1,2) + A(1,2)*B(2,2),
    A(1,0)*B(0,3) + A(1,1)*B(1,3) + A(1,2)*B(2,3) + A(1,3),
    A(2,0)*B(0,0) + A(2,1)*B(1,0) + A(2,2)*B(2,0),
    A(2,0)*B(0,1) + A(2,1)*B(1,1) + A(2,2)*B(2,1),
    A(2,0)*B(0,2) + A(2,1)*B(1,2) + A(2,2)*B(2,2),
    A(2,0)*B(0,3) + A(2,1)*B(1,3) + A(2,2)*B(2,3) + A(2,3)));}
inline Vector3 operator *(const Vector3& n, const Transform4& T)
{return (Vector3(
    n.x*T(0,0) + n.y*T(1,0) + n.z*T(2,0),
    n.x*T(0,1) + n.y*T(1,1) + n.z*T(2,1),
    n.x*T(0,2) + n.y*T(1,2) + n.z*T(2,2)));}
inline Vector3 operator *(const Transform4& T, const Vector3& v)
{return (Vector3(
    T(0,0)*v.x + T(0,1)*v.y + T(0,2)*v.z,
    T(1,0)*v.x + T(1,1)*v.y + T(1,2)*v.z,
    T(2,0)*v.x + T(2,1)*v.y + T(2,2)*v.z));}
inline Point3 operator *(const Transform4& T, const Point3& p)
{return (Point3(
    T(0,0)*p.x + T(0,1)*p.y + T(0,2)*p.z,
    T(1,0)*p.x + T(1,1)*p.y + T(1,2)*p.z,
    T(2,0)*p.x + T(2,1)*p.y + T(2,2)*p.z));}
inline Plane operator *(const Plane& f, const Transform4& T)
{
    return (Plane(
        f.x*T(0,0) + f.y*T(1,0) + f.z*T(2,0),
        f.x*T(0,1) + f.y*T(1,1) + f.z*T(2,1),
        f.x*T(0,2) + f.y*T(1,2) + f.z*T(2,2),
        f.x*T(0,3) + f.y*T(1,3) + f.z*T(2,3) + f.w
    ));
}

// Quaternions

inline Quaternion operator +(const Quaternion& a, const Quaternion& b)
{return (Quaternion(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w));}
inline Quaternion operator *(float sc, const Quaternion& q)
{return (Quaternion(sc*q.x, sc*q.y, sc*q.z, sc*q.w));}
inline Quaternion operator *(const Quaternion& q, float sc) {return sc*q;}
inline Quaternion operator /(const Quaternion& q, float sc) {return (1.0f/sc)*q;}
inline Quaternion operator -(const Quaternion& a, const Quaternion& b) {return (a + (-1.0f * b));}
inline Quaternion operator *(const Quaternion& q1, const Quaternion& q2)
{return (Quaternion(
    q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y,
    q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x,
    q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w,
    q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z
));}

// * * * * * METHODS * * * * * //

// Diagonals

/*!
 * @brief Returns the diagonal of the matrix
 * @param M Matrix to get the diagonal of
 * @return [Vector2] Diagonal of the matrix
 */
inline Vector2 Diagonal(const Matrix2& M) {return Vector2(M(0,0), M(1,1));}
/*!
 * @brief Returns the diagonal of the matrix
 * @param M Matrix to get the diagonal of
 * @return [Vector2] Diagonal of the matrix
 */
inline Vector3 Diagonal(const Matrix3& M) {return Vector3(M(0,0), M(1,1), M(2,2));}
/*!
 * @brief Returns the diagonal of the matrix
 * @param M Matrix to get the diagonal of
 * @return [Vector2] Diagonal of the matrix
 */
inline Vector4 Diagonal(const Matrix4& M) {return Vector4(M(0,0), M(1,1), M(2,2), M(3,3));}


// Transpose

/*! @brief Calculates the transpose of a 2x2 matrix
 *  @param[in] M 2x2 matrix to transpose
 *  @return [Matrix2] Transposed 2x2 matrix
 */
inline Matrix2 Transpose(const Matrix2& M)
{return (Matrix2(M(0,0), M(1,0), M(0,1), M(1,1)));}
/*! @brief Calculates the transpose of a 3x3 matrix
 *  @param[in] M 3x3 matrix to transpose
 *  @return [Matrix3] Transposed 3x3 matrix
 */
inline Matrix3 Transpose(const Matrix3& M)
{return (Matrix3(M(0,0), M(1,0), M(2,0),
                M(0,1), M(1,1), M(2,1),
                M(0,2), M(1,2), M(2,2)));}
/*! @brief Calculates the transpose of a 4x4 matrix
 *  @param[in] M 4x4 matrix to transpose
 *  @return [Matrix4] Transposed 4x4 matrix
 */
inline Matrix4 Transpose(const Matrix4& M)
{return (Matrix4( M(0,0), M(1,0), M(2,0), M(3,0),
                M(0,1), M(1,1), M(2,1), M(3,1),
                M(0,2), M(1,2), M(2,2), M(3,2),
                M(0,3), M(1,3), M(2,3), M(3,3)));}

//! REF  @note These functions are not inlined, but are used
//! immediately after they are declared, so they should go here

/*!
 * @brief Returns the reduced echelon form of a Matrix2 structure and a coefficient for the determinant
 * @param M Matrix to perform REF on
 * @param c Pointer to determinant coefficient. Should always be initialized to 1.0f
 * @return [Matrix2] Reduced echelon form of Matrix2
 */
Matrix2 REF(const Matrix2& M, float *c);
/*!
 * @brief Returns the reduced echelon form of a Matrix3 structure and a coefficient for the determinant
 * @param M Matrix to perform REF on
 * @param c Pointer to determinant coefficient. Should always be initialized to 1.0f
 * @return [Matrix3] Reduced echelon form of Matrix3
 */
Matrix3 REF(const Matrix3& M, float *c);
/*!
 * @brief Returns the reduced echelon form of a Matrix2 structure and a coefficient for the determinant
 * @param M Matrix to perform REF on
 * @param c Pointer to determinant coefficient. Should always be initialized to 1.0f
 * @return [Matrix2] Reduced echelon form of Matrix2
 */
Matrix4 REF(const Matrix4& M, float *c);

// Determinant

/*! @brief Calculates the determinant of a 2x2 matrix
 *  @param[in] M 2x2 matrix to find the determinant for
 *  @return [float] Determinant of 2x2 matrix
 */
inline float Det(const Matrix2& M)
    {return ((M(0,0) * M(1,1))-(M(0,1) * M(1,0)));}
/*! @brief Calculates the determinant of a 3x3 matrix
 *  @param[in] M 3x3 matrix to find the determinant for
 *  @return [float] Determinant of 3x3 matrix
 */
inline float Det(const Matrix3& M)
{
    return ((M(0,0) * Det(Matrix2(M(1,1), M(1,2), M(2,1), M(2,2))))
        -(M(0,1) * Det(Matrix2(M(1,0), M(1,2), M(2,0), M(2,2))))
        + (M(0,2) * Det(Matrix2(M(1,0), M(1,1), M(2,0), M(2,1)))));
}
/*! @brief Calculates the determinant of a 4x4 matrix
 *  @param[in] M 4x4 matrix to find the determinant for
 *  @return [float] Determinant of 4x4 matrix
 */
float Det(const Matrix4& M);

// Trace

/*! @brief Calculates the trace of a 2x2 matrix
 *  @param[in] M 2x2 matrix to find the trace for
 *  @return [float] Trace of 2x2 matrix
 */
inline float Trace(const Matrix2& M) {return (M(0,0) + M(1,1));}
/*! @brief Calculates the trace of a 3x3 matrix
 *  @param[in] M 3x3 matrix to find the trace for
 *  @return [float] Trace of 3x3 matrix
 */
inline float Trace(const Matrix3& M)  {return (M(0,0) + M(1,1) + M(2,2));}
/*! @brief Calculates the trace of a 4x4 matrix
 *  @param[in] M 4x4 matrix to find the trace for
 *  @return [float] Trace of 4x4 matrix
 */
inline float Trace(const Matrix4& M) {return (M(0,0) + M(1,1) + M(2,2) + M(3,3));}

// Inverse

/*! @brief Calculates the inverse of a 2x2 matrix
 *  @param[in] M 2x2 matrix to find the inverse for
 *  @return [Matrix2] Inverse of 2x2 matrix
 *  @warning If the determinant of M is zero,
 *  this function will throw an exception saying M is non-invertible
 */
Matrix2 Inverse(const Matrix2& M);
/*! @brief Calculates the inverse of a 3x3 matrix
 *  @param[in] M 3x3 matrix to find the inverse for
 *  @return [Matrix3] Inverse of 3x3 matrix
 *  @warning Will return an error if M is non-invertible
 */
Matrix3 Inverse(const Matrix3& M);
/*! @brief Calculates the inverse of a 4x4 matrix
 *  @param[in] M 4x4 matrix to find the inverse for
 *  @return [Matrix4] Inverse of 4x4 matrix
 *  @warning Will return an error if M is non-invertible
 */
Matrix4 Inverse(const Matrix4& M);
/*! @brief Generates the inverse of a 3D Transform
 *  @param T Transform to invert
 *  @return [Transform3] Inverted transform
 *  @warning Will give an error if the transform is non-invertible
 */
Transform3 Inverse(const Transform3& T);
/*! @brief Generates the inverse of a transform T
 *  @param T The transform to invert
 *  @returns [Transform4] Inverted Transform
 *  @warning Will give an error if the transform is non-invertible
 */
Transform4 Inverse(const Transform4& T);

// Adjugate

/*! @brief Calculates the adjugate of a 2x2 matrix
 *  @param[in] M 2x2 matrix to find the adjugate for
 *  @return [Matrix2] Adjugate of 2x2 matrix
 */
inline Matrix2 Adjugate(const Matrix2& M)
    {return Matrix2(M(1,1), -1.0*M(0,1), -1.0*M(1,0), M(0,0));}
/*! @brief Calculates the adjugate of a 3x3 matrix
 *  @param[in] M 3x3 matrix to find the adjugate for
 *  @return [Matrix3] Adjugate of 3x3 matrix
 */
Matrix3 Adjugate(const Matrix3& M);
/*! @brief Calculates the adjugate of a 4x4 matrix
 *  @param[in] M 4x4 matrix to find the adjugate for
 *  @return [Matrix4] Adjugate of 4x4 matrix
 */
Matrix4 Adjugate(const Matrix4& M);

// Cofactor

/*! @brief Calculates the cofactor of a 2x2 matrix
 *  @param[in] M 2x2 matrix to find the cofactor for
 *  @return [Matrix2] Cofactor of 2x2 matrix
 */
inline Matrix2 Cofactor(const Matrix2& M) {return (Transpose(Adjugate(M)));}
/*! @brief Calculates the cofactor of a 3x3 matrix
 *  @param[in] M 3x3 matrix to find the cofactor for
 *  @return [Matrix3] Cofactor of 3x3 matrix
 */
inline Matrix3 Cofactor(const Matrix3& M) {return (Transpose(Adjugate(M)));}
/*! @brief Calculates the cofactor of a 4x4 matrix
 *  @param[in] M 4x4 matrix to find the cofactor for
 *  @return [Matrix4] Cofactor of 4x4 matrix
 */
inline Matrix4 Cofactor(const Matrix4& M) {return (Transpose(Adjugate(M)));}

// Scaling

/*! @brief Generates 2x2 matrix of scale factors for x, y axes
 *  @param[in] scaleX Scale factor for the X axis
 *  @param[in] scaleY Scale factor for the Y axis
 *  @return [Matrix2] Scale data structure.
 */
inline Matrix2 Scale(float scaleX, float scaleY) {return (Matrix2(scaleX, 0.0f, 0.0f, scaleY));}
/*! @brief Generates 3x3 matrix of scale factors for x, y, z axes
 *  @param[in] scaleX Scale factor for the X axis
 *  @param[in] scaleY Scale factor for the Y axis
 *  @param[in] scaleZ Scale factor for the Z axis
 *  @return [Matrix3] Scale data structure.
 */
inline Matrix3 Scale(float scaleX, float scaleY, float scaleZ)
{return (Matrix3(scaleX, 0.0f, 0.0f,
                0.0f, scaleY, 0.0f,
                0.0f, 0.0f, scaleZ));}
/*! @brief Generates 4x4 matrix of scale factors for w, x, y, z axes
 *  @param[in] scaleW Scale factor for the W axis
 *  @param[in] scaleX Scale factor for the X axis
 *  @param[in] scaleY Scale factor for the Y axis
 *  @param[in] scaleZ Scale factor for the Z axis
 *  @return [Matrix4] Scale data structure.
 */
inline Matrix4 Scale(float scaleW, float scaleX, float scaleY, float scaleZ)
{return (Matrix4(scaleW, 0.0f, 0.0f, 0.0f,
                0.0f, scaleX, 0.0f, 0.0f,
                0.0f, 0.0f, scaleY, 0.0f,
                0.0f, 0.0f, 0.0f, scaleZ));}

/*!
 * @brief Generates 2x2 matrix of scale factor sc along an arbitary axis of unit length
 * @param sc Scaling factor
 * @param a Arbitrary axis given as a Vector2 structure
 * @return [Matrix2] Scale data sctucture.
 */
Matrix2 Scale(float sc, const Vector2& a);
/*!
 * @brief Generates 3x3 matrix of scale factor sc along an arbitary axis of unit length
 * @param sc Scaling factor
 * @param a Arbitrary axis given as a Vector3 structure
 * @return [Matrix3] Scale data sctucture.
 */
Matrix3 Scale(float sc, const Vector3& a);
/*!
 * @brief Generates 4x4 matrix of scale factor sc along an arbitary axis of unit length
 * @param sc Scaling factor
 * @param a Arbitrary axis given as a Vector4 structure
 * @return [Matrix4] Scale data sctucture.
 */
Matrix4 Scale(float sc, const Vector4& a);

//---------------------------------------------------------------------------------------------
//                                        MEHTODS
//---------------------------------------------------------------------------------------------

// Orthogonality check

/*! @brief Checks if 2x2 matrix is orthogonal
 *  @param[in] M 2x2 matrix to check for orthogonality
 *  @return [bool] stating whether M is orthogonal
 */
inline bool IsOrthogonal(const Matrix2& M) {return (M*Transpose(M) == M.Identity());}
/*! @brief Checks if 3x3 matrix is orthogonal
 *  @param[in] M 3x3 matrix to check for orthogonality
 *  @return [bool] stating whether M is orthogonal
 */
inline bool IsOrthogonal(const Matrix3& M) {return (M*Transpose(M) == M.Identity());}
/*! @brief Checks if 4x4 matrix is orthogonal
 *  @param[in] M 4x4 matrix to check for orthogonality
 *  @return [bool] Whether M is orthogonal
 */
inline bool IsOrthogonal(const Matrix4& M) {return (M*Transpose(M) == M.Identity());}

// Skew matrix
/*! @brief  Generates 2x2 skew matrix at an angle (radians) along a given direction
 *  @param angle The skew angle in radians
 *  @param u1 Unit vector giving first direction, must be orthogonal to u2
 *  @param u2 Unit vector giving second direction, must be orthogonal to u1
 *  @return [Matrix2] Skew matrix for given angle and orthogonal unit vectors
 */
Matrix2 Skew(float angle, const Vector2& u1, const Vector2& u2);
/*! @brief  Generates 3x3 skew matrix at an angle (radians) along a given direction
 *  @param angle The skew angle in radians
 *  @param u1 Unit vector giving first direction, must be orthogonal to u2
 *  @param u2 Unit vector giving second direction, must be orthogonal to u1
 *  @return [Matrix3] Skew matrix for given angle and orthogonal unit vectors
 */
Matrix3 Skew(float angle, const Vector3& u1, const Vector3& u2);
/*! @brief  Generates 4x4 skew matrix at an angle (radians) along a given direction
 *  @param angle The skew angle in radians
 *  @param u1 Unit vector giving first direction, must be orthogonal to u2
 *  @param u2 Unit vector giving second direction, must be orthogonal to u1
 *  @return [Matrix4] Skew matrix for given angle and orthogonal unit vectors
 */
Matrix4 Skew(float angle, const Vector4& u1, const Vector4& u2);
/*! @brief  Generates 2x2 skew matrix at an angle (degrees) along a given direction
 *  @param angle The skew angle in degrees
 *  @param u1 Unit vector giving first direction, must be orthogonal to u2
 *  @param u2 Unit vector giving second direction, must be orthogonal to u1
 *  @return [Matrix2] Skew matrix for given angle and orthogonal unit vectors
 */
inline Matrix2 SkewDegrees(float angle, const Vector2& u1, const Vector2& u2) {return (Skew(PI*angle/180.0f, u1, u2));}
/*! @brief  Generates 3x3 skew matrix at an angle (degrees) along a given direction
 *  @param angle The skew angle in degrees
 *  @param u1 Unit vector giving first direction, must be orthogonal to u2
 *  @param u2 Unit vector giving second direction, must be orthogonal to u1
 *  @return [Matrix3] Skew matrix for given angle and orthogonal unit vectors
 */
inline Matrix3 SkewDegrees(float angle, const Vector3& u1, const Vector3& u2) {return (Skew(PI*angle/180.0f, u1, u2));}
/*! @brief  Generates 4x4 skew matrix at an angle (degrees) along a given direction
 *  @param angle The skew angle in degrees
 *  @param u1 Unit vector giving first direction, must be orthogonal to u2
 *  @param u2 Unit vector giving second direction, must be orthogonal to u1
 *  @return [Matrix4] Skew matrix for given angle and orthogonal unit vectors
 */
inline Matrix4 SkewDegrees(float angle, const Vector4& u1, const Vector4& u2) {return (Skew(PI*angle/180.0f, u1, u2));}

// Rotations

/*!
 * @brief Generates a rotation matrix on the XY plane.
 * @param[in] angle The angle of rotation (radians)
 * @return [Matrix2] Rotation matrix on XY plane at angle.
 */
Matrix2 Rotate(float angle);
/*!
 * @brief Generates a rotation matrix on the XY plane.
 * @param[in] angle The angle of rotation (degrees)
 * @return [Matrix2] Rotation matrix on XY plane at angle.
 */
inline Matrix2 RotateDegrees(float angle) {return Rotate(angle*(PI/180.0f));}

/*! @brief Generates rotation matrix about the X axis
 *  @param[in] angle The angle of rotation (radians)
 *  @return [Matrix3] Rotation matrix about X axis at angle
 */
Matrix3 RotateAboutX(float angle);
/*! @brief Generates rotation matrix about the Y axis
 *  @param[in] angle The angle of rotation (radians)
 *  @return [Matrix3] Rotation matrix about Y axis at angle
 */
Matrix3 RotateAboutY(float angle);
/*! @brief Generates rotation matrix about the Z axis
 *  @param[in] angle The angle of rotation (radians)
 *  @return [Matrix3] Rotation matrix about Z axis at angle
 */
Matrix3 RotateAboutZ(float angle);
/*! @brief Generates rotation matrix about an arbitrary axis
 *  @param[in] angle The angle of rotation (radians)
 *  @param[in] ax An arbitrary axis to rotate about
 *  @return [Matrix3] Rotation matrix about axis at angle
 */
Matrix3 RotateAboutAxis(float angle, const Vector3& ax);

/*! @brief Generates rotation matrix about the X axis
 *  @param[in] angle The angle of rotation (degrees)
 *  @return [Matrix3] Rotation matrix about X axis at angle
 */
inline Matrix3 RotateAboutXDegrees(float angle)  {return (RotateAboutX(PI*angle/180.0f));}
/*! @brief Generates rotation matrix about the Y axis
 *  @param[in] angle The angle of rotation
 *  @return [Matrix3] Rotation matrix about Y axis at angle
 */
inline Matrix3 RotateAboutYDegrees(float angle) {return (RotateAboutY(PI*angle/180.0f));}
/*! @brief Generates rotation matrix about the Z axis
 *  @param[in] angle The angle of rotation (degrees)
 *  @return [Matrix3] Rotation matrix about Z axis at angle
 */
inline Matrix3 RotateAboutZDegrees(float angle) {return (RotateAboutZ(PI*angle/180.0f));}
/*! @brief Generates rotation matrix about an arbitrary axis
 *  @param[in] angle The angle of rotation (degrees)
 *  @param[in] axis An arbitrary axis to rotate about
 *  @return [Matrix3] Rotation matrix about axis at angle
 */
inline Matrix3 RotateAboutAxisDegrees(float angle, const Vector3& axis) {return (RotateAboutAxis(PI*angle/180.0f, axis));}

// Reflection/Involution

/*! @brief Generates reflection matrix through the perpendicular plane of a given vector
 *  @param[in] v Vector used to define plane of reflection
 *  @return [Matrix2] Reflection matrix for v
 */
Matrix2 Reflection(float angle);
/*! @brief Generates reflection matrix through the perpendicular plane of a given vector
 *  @param[in] v Vector used to define plane of reflection
 *  @return [Matrix3] Reflection matrix for v
 */
Matrix3 Reflection(const Vector3& v);
/*! @brief Generates reflection matrix through the perpendicular plane of a given vector
 *  @param[in] v Vector used to define plane of reflection
 *  @return [Matrix4] Reflection matrix for v
 */
Matrix4 Reflection(const Vector4& v);
/*!
 * @brief Generates a transform of a reflection through a given normalized plane
 * @param f The (presumably) normalized plane
 * @return [Transform4] 4x4 matrix representing the reflection transform through f
 */
Transform4 Reflection(const Plane& f);
/*! @brief Generates involution matrix through the perpendicular plane of a given vector
 *  @param[in] v Vector used to define plane of involution
 *  @return [Matrix3] Involution matrix for v
 */
Matrix2 Involution(const Vector2& v);
/*! @brief Generates involution matrix through the perpendicular plane of a given vector
 *  @param[in] v Vector used to define plane of involution
 *  @return [Matrix3] Involution matrix for v
 */
Matrix3 Involution(const Vector3& v);
/*! @brief Generates involution matrix through the perpendicular plane of a given vector
 *  @param[in] v Vector used to define plane of involution
 *  @return [Matrix4] Involution matrix for v
 */
Matrix4 Involution(const Vector4& v);

// Extras

/*!
 * @brief Transforms a Line structure using a Transform4 structure
 * @param[in] L Line to transform
 * @param[in] T The transform structure
 * @return [Line] L transformed by T
 */
Line TransformLine(const Line& L, const Transform4& T);
/*!
 * @brief Transforms a Vector3 structure using a Quaternion structure
 * @param v The Vector3 to transform
 * @param q The quaternion
 * @return [Vector3] (v) transformed by (q)
 */
Vector3 Transform(const Vector3& v, const Quaternion& q);