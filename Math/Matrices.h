

//      INCLUDES
#pragma once
#include <stdexcept>
#include <cmath>
#include <iostream>
#include "Vectors.h"
#include "Geometry.h"

//      Exception class for instances of  non-invertible matrices.
struct NonInvertibleE : public runtime_error
{
    NonInvertibleE() : runtime_error("Math error: Given matrix is non-invertible.\n") 
    {};
};

//      MATRICES 2D

struct Matrix2
{
protected:
    float m[2][2];

public:
    Matrix2() = default;
    Matrix2(float a00, float a01,
            float a10, float a11)
    {
        m[0][0] = a00; m[0][1] = a10;
        m[1][0] = a01; m[1][1] = a11;
    }
    Matrix2(const Vector2& a, const Vector2& b)
    {
        m[0][0] = a.x; m[0][1] = a.y;
        m[1][0] = b.x; m[1][1] = b.y;
    }
    // Operators
    float& operator ()(int i, int j) {return (m[j][i]);}
    const float& operator ()(int i, int j) const {return (m[j][i]);}
    Vector2& operator [](int j) 
    {
        return (*reinterpret_cast<Vector2 *>(m[j]));
    }
    const Vector2& operator [](int j) const
    {
        return (*reinterpret_cast<const Vector2 *>(m[j]));
    }
    
};
//      2D Inline Operators

inline Matrix2 operator +(const Matrix2& A, const Matrix2& B)
{
    return 
        (Matrix2(A(0,0)+B(0,0), A(0,1)+B(0,1),
                A(1,0)+B(1,0), A(1,1)+B(1,1)));
}
inline Matrix2 operator *(const Matrix2& M, float sc)
{
    return (Matrix2(M(0,0)*sc, M(0,1)*sc, M(1,0)*sc, M(1,1)*sc));
}
inline Matrix2 operator *(float sc, const Matrix2& M)
{
    return (M*sc);
}
inline Matrix2 operator /(const Matrix2& M, float sc)
{
    return ((1.0f/sc) * M);
}
inline Matrix2 operator *(const Matrix2& A, const Matrix2& B)
{
    return (Matrix2(A(0,0)*B(0,0) + A(0,1)*B(1,0),
                    A(0,0)*B(0,1) + A(0,1)*B(1,1),
                    A(1,0)*B(0,0) + A(1,1)*B(1,0),
                    A(1,0)*B(0,1) + A(1,1)*B(1,1)));
}
inline Vector2 operator *(const Matrix2& M, const Vector2& v)
{
    return (Vector2(M(0,0)*v.x + M(0,1)*v.y,
                    M(1,0)*v.x + M(1,1)*v.y));
}
inline Matrix2 operator -(const Matrix2& A, const Matrix2& B)
{
    return (A + (-1.0f*B));
}
//      2D Inline functions - Methods
inline Vector2 Diagonal(const Matrix2& M)
{
    return Vector2(M(0,0), M(1,1));
}
/*! @brief Calculates the transpose of a 2x2 matrix
 *  @param[in] M 2x2 matrix to transpose
 *  @return [Matrix2] Transposed 2x2 matrix
 */
inline Matrix2 Transpose(const Matrix2& M)
{
    return (Matrix2(M(0,0), M(1,0),
                    M(0,1), M(1,1)));
}
/*! @brief Calculates the determinant of a 2x2 matrix
 *  @param[in] M 2x2 matrix to find the determinant for
 *  @return [float] Determinant of 2x2 matrix
 */
inline float Det(const Matrix2& M)
{
    return ((M(0,0) * M(1,1))-(M(0,1) * M(1,0)));
}
/*! @brief Calculates the trace of a 2x2 matrix
 *  @param[in] M 2x2 matrix to find the trace for
 *  @return [float] Trace of 2x2 matrix
 */
inline float Trace(const Matrix2& M)
{
    return (M(0,0) + M(1,1));
}
/*! @brief Calculates the adjugate of a 2x2 matrix
 *  @param[in] M 2x2 matrix to find the adjugate for
 *  @return [Matrix2] Adjugate of 2x2 matrix
 */
inline Matrix2 Adjugate(const Matrix2& M)
{
    return Matrix2(M(1,1), -1.0*M(0,1), -1.0*M(1,0), M(0,0));
}
/*! @brief Calculates the cofactor of a 2x2 matrix
 *  @param[in] M 2x2 matrix to find the cofactor for
 *  @return [Matrix2] Cofactor of 2x2 matrix
 */
inline Matrix2 Cofactor(const Matrix2& M)
{
    return (Transpose(Adjugate(M)));
}
/*! @brief Calculates the inverse of a 2x2 matrix
 *  @param[in] M 2x2 matrix to find the inverse for
 *  @return [Matrix2] Inverse of 2x2 matrix
 *  @warning If the determinant of M is zero, 
 *  this function will throw an exception saying M is non-invertible
 */
inline Matrix2 Inverse(const Matrix2& M)
{
    try
    {
        if (Det(M) == 0.0f) throw NonInvertibleE();
        return (1.0/Det(M)) * Adjugate(M);
    }
    catch(NonInvertibleE& e)
    {
        cout << "Exception occurred!\n" << e.what();
    }
}
/*! @brief Checks if 2x2 matrix is orthogonal
 *  @param[in] M 2x2 matrix to check for orthogonality
 *  @return [bool] stating whether M is orthogonal
 */
inline bool IsOrthogonal(const Matrix2& M)
{
    Matrix2 Id = M*Transpose(M);
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            if ((i==j && Id(i,j)!=1) || ((i!=j && Id(i,j)!=0))) return false;
        }
    }
    return true;
}

//     2D Transforms

/*! @brief Generates 2x2 matrix of scale factors for x, y axes
 *  @param[in] scaleX Scale factor for the X axis
 *  @param[in] scaleY Scale factor for the Y axis
 *  @return Matrix2 scale data structure.
 */
inline Matrix2 Scale(float scaleX, float scaleY)
{
    return (Matrix2(scaleX, 0.0f, 0.0f, scaleY));
}
/*! @brief  Generates 2x2 skew matrix at an angle along a given direction
 *  @param angle The skew angle
 *  @param u1 Unit vector giving first direction, must be orthogonal to u2
 *  @param u2 Unit vector giving second direction, must be orthogonal to u1
 *  @return [Matrix2] Skew matrix for given angle and orthogonal unit vectors
 */
inline Matrix2 Skew(float angle, const Vector2& u1, const Vector2& u2)
{
    angle = tan(angle);
    float x = angle * u1.x;
    float y = angle * u1.y;

    return (Matrix2(x*u2.x + 1.0f, x*u2.y, 
                    y*u2.x, y*u2.y + 1.0f));
}

//      MATRICES 3D

struct Matrix3
{
protected:
    float m[3][3];
    
public:
    Matrix3() = default;
    Matrix3(float a00, float a01, float a02,
            float a10, float a11, float a12,
            float a20, float a21, float a22)
    {
        m[0][0] = a00; m[0][1] = a10; m[0][2] = a20;
        m[1][0] = a01; m[1][1] = a11; m[1][2] = a21;
        m[2][0] = a02; m[2][1] = a12; m[2][2] = a22;
    }
    Matrix3(const Vector3& a, const Vector3& b, const Vector3& c)
    {
        m[0][0] = a.x; m[0][1] = a.y; m[0][2] = a.z;
        m[1][0] = b.x; m[1][1] = b.y; m[1][2] = b.z;
        m[2][0] = c.x; m[2][1] = c.y; m[2][2] = c.z;
    }
    float& operator ()(int i, int j) {return (m[j][i]);}
    const float& operator ()(int i, int j) const {return (m[j][i]);}
    Vector3& operator [](int j) 
    {
        return (*reinterpret_cast<Vector3 *>(m[j]));
    }
    const Vector3& operator [](int j) const
    {
        return (*reinterpret_cast<const Vector3 *>(m[j]));
    }
    
};
//      3D Inline operators
inline Matrix3 operator +(const Matrix3& A, const Matrix3& B)
{
    return (Matrix3(A(0,0)+B(0,0), A(0,1)+B(0,1), A(0,2)+B(0,2),
                    A(1,0)+B(1,0), A(1,1)+B(1,1), A(1,2)+B(1,2),
                    A(2,0)+B(2,0), A(2,1)+B(2,1), A(2,2)+B(2,2)));
}
inline Matrix3 operator *(float sc, const Matrix3& M)
{
    return (Matrix3(sc*M(0,0), sc*M(0,1), sc*M(0,2),
                    sc*M(1,0), sc*M(1,1), sc*M(1,2),
                    sc*M(2,0), sc*M(2,1), sc*M(2,2)));
}
inline Matrix3 operator *(const Matrix3& M, float sc)
{
    return (sc*M);
}
inline Matrix3 operator /(const Matrix3& M, float sc)
{
    return ((1.0f/sc)*M);
}
inline Matrix3 operator -(const Matrix3& A, const Matrix3& B)
{
    return (A + (-1.0f * B));
}

inline Matrix3 operator *(const Matrix3& A, const Matrix3& B)
{
    return (Matrix3(A(0,0)*B(0,0) + A(0,1)*B(1,0) + A(0,2)*B(2,0),
                    A(0,0)*B(0,1) + A(0,1)*B(1,1) + A(0,2)*B(2,1),
                    A(0,0)*B(0,2) + A(0,1)*B(1,2) + A(0,2)*B(2,2),
                    A(1,0)*B(0,0) + A(1,1)*B(1,0) + A(1,2)*B(2,0),
                    A(1,0)*B(0,1) + A(1,1)*B(1,1) + A(1,2)*B(2,1),
                    A(1,0)*B(0,2) + A(1,1)*B(1,2) + A(1,2)*B(2,2),
                    A(2,0)*B(0,0) + A(2,1)*B(1,0) + A(2,2)*B(2,0),
                    A(2,0)*B(0,1) + A(2,1)*B(1,1) + A(2,2)*B(2,1),
                    A(2,0)*B(0,2) + A(2,1)*B(1,2) + A(2,2)*B(2,2)));
}

inline Vector3 operator *(const Matrix3& M, const Vector3& v)
{
    return (Vector3(M(0,0)*v.x + M(0,1)*v.y + M(0,2)*v.z,
                    M(1,0)*v.x + M(1,1)*v.y + M(1,2)*v.z,
                    M(2,0)*v.x + M(2,1)*v.y + M(2,2)*v.z));
}
//      3D Inline Methods

inline Vector3 Diagonal(const Matrix3& M)
{
    return Vector3(M(0,0), M(1,1), M(2,2));
}
/*! @brief Calculates the transpose of a 3x3 matrix
 *  @param[in] M 3x3 matrix to transpose
 *  @return [Matrix3] Transposed 3x3 matrix
 */
inline Matrix3 Transpose(const Matrix3& M)
{
    return (Matrix3(M(0,0), M(1,0), M(2,0),
                    M(0,1), M(1,1), M(2,1),
                    M(0,2), M(1,2), M(2,2)));
}
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
/*! @brief Calculates the trace of a 3x3 matrix
 *  @param[in] M 3x3 matrix to find the trace for
 *  @return [float] Trace of 3x3 matrix
 */
inline float Trace(const Matrix3& M)
{
    return (M(0,0) + M(1,1) + M(2,2));
}
/*! @brief Calculates the inverse of a 3x3 matrix
 *  @param[in] M 3x3 matrix to find the inverse for
 *  @return [Matrix3] Inverse of 3x3 matrix
 *  @warning Will return an error if M is non-invertible
 */
inline Matrix3 Inverse(const Matrix3& M)
{
    const Vector3& m0 = M[0];
    const Vector3& m1 = M[1];
    const Vector3& m2 = M[2];
    float scalarTP = ScalarTripleProduct(m0,m1,m2); 
    
    try{
        
        if (scalarTP == 0.0f) throw NonInvertibleE();
        float sc = (1.0f/scalarTP);
        Vector3 v0 = CrossProduct(m1,m2);
        Vector3 v1 = CrossProduct(m2,m0);
        Vector3 v2 = CrossProduct(m0,m1);
        return (Matrix3(v0.x*sc, v0.y*sc, v0.z*sc,
                        v1.x*sc, v1.y*sc, v1.z*sc,
                        v2.x*sc, v2.y*sc, v2.z*sc));
    }
    catch (NonInvertibleE& e)
    {
        cout << "Exception occurred!\n" << e.what();
    } 
}
/*! @brief Calculates the adjugate of a 3x3 matrix
 *  @param[in] M 3x3 matrix to find the adjugate for
 *  @return [Matrix3] Adjugate of 3x3 matrix
 */
inline Matrix3 Adjugate(const Matrix3& M)
{
    return (Det(M)*Inverse(M));
} 
/*! @brief Calculates the cofactor of a 3x3 matrix
 *  @param[in] M 3x3 matrix to find the cofactor for
 *  @return [Matrix3] Cofactor of 3x3 matrix
 */
inline Matrix3 Cofactor(const Matrix3& M)
{
    return (Transpose(Adjugate(M)));
}
/*! @brief Checks if 3x3 matrix is orthogonal
 *  @param[in] M 3x3 matrix to check for orthogonality
 *  @return [bool] stating whether M is orthogonal
 */
inline bool IsOrthogonal(const Matrix3& M)
{
    Matrix3 Id = M*Transpose(M);
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if ((i==j && Id(i,j)!=1) || ((i!=j && Id(i,j)!=0))) return false;
        }
    }
    return true;
}

//      3D Transforms

struct Transform3 : Matrix3
{
    Transform3() = default;
    Transform3( float t00, float t01, float t02, 
                float t10, float t11, float t12)
    {
        m[0][0] = t00; m[0][1] = t10;  
        m[1][0] = t01; m[1][1] = t11;  
        m[2][0] = t02; m[2][1] = t12;  
         

        m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;
    }
    Transform3( const Vector2& v0, const Vector2& v1, const Point2& p)
    {
        m[0][0] = v0.x; m[0][1] = v0.y; 
        m[1][0] = v1.x; m[1][1] = v1.y; 
        m[2][0] = p.x; m[2][1] = p.y;

        m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f; 
    }
    Vector2& operator [](int j)
    {
        return (*reinterpret_cast<Vector2 *>(m[j]));
    }
    const Vector2& operator [](int j) const
    {
        return (*reinterpret_cast<const Vector2 *>(m[j]));
    }
    /*! @brief Gets translation point from this transform  
     *  @return [Point2] 2D Translation point
     */
    const Point2& GetTranslation(void) const
    {
        return (*reinterpret_cast<const Point2 *>(m[2]));
    }
    /*! @brief Sets translation point for this transform 
     *  @param p Point used to set translation
     */
    void SetTranslation(const Point2& p)
    {
        m[2][0] = p.x; m[2][1] = p.y;
    }
};


inline Transform3 operator +(const Transform3& A, const Transform3& B)
{
    return (Transform3(
        A(0,0) + B(0,0), A(0,1) + B(0,1), A(0,2) + B(0,2), 
        A(1,0) + B(1,0), A(1,1) + B(1,1), A(1,2) + B(1,2) 
    ));
}
inline Transform3 operator *(float sc, const Transform3& T)
{
    return Transform3(
        sc*T(0,0), sc*T(0,1), sc*T(0,2),
        sc*T(1,0), sc*T(1,1), sc*T(1,2)
    );
}
inline Transform3 operator *(const Transform3& T, float sc)
{
    return (sc*T);
}
inline Transform3 operator /(const Transform3& T, float sc)
{
    return (1.0f/sc) * T;
}
inline Transform3 operator -(const Transform3& A, const Transform3& B)
{
    return A + (-1.0f*B);
}
inline Transform3 operator *(const Transform3& A, const Transform3& B)
{
    return (Transform3(
        A(0,0)*B(0,0) + A(0,1)*B(1,0),
        A(0,0)*B(0,1) + A(0,1)*B(1,1),
        A(0,0)*B(0,2) + A(0,1)*B(1,2) + A(0,2),
        A(1,0)*B(0,0) + A(1,1)*B(1,0),
        A(1,0)*B(0,1) + A(1,1)*B(1,1),
        A(1,0)*B(0,2) + A(1,1)*B(1,2) + A(1,2)
    ));
}

inline Vector2 operator *(const Transform3& T, const Vector2& v)
{
    return (Vector2(
        T(0,0)*v.x + T(0,1)*v.y,
        T(1,0)*v.x + T(1,1)*v.y
    ));
}

inline Point2 operator *(const Transform3& T, const Point2& p)
{
    return (Point2(
        T(0,0)*p.x + T(0,1)*p.y,
        T(1,0)*p.x + T(1,1)*p.y
    ));
}
/*! @brief Generates the inverse of a 3D Transform
 *  @param T Transform to invert
 *  @return [Transform3] Inverted transform
 */
inline Transform3 Inverse(const Transform3& T)
{
    const Matrix3& M = Matrix3( T(0,0), T(0,1), T(0,2),
                                T(1,0), T(1,1), T(1,2),
                                0.0f,   0.0f,   1.0f);
    Matrix3 Inv = Inverse(M);
    return (Transform3(Inv(0,0), Inv(0,1), Inv(0,2), Inv(1,0), Inv(1,1), Inv(1,2)));
}
/*! @brief Generates rotation matrix about the X axis
 *  @param[in] angle The angle of rotation
 *  @return [Matrix3] Rotation matrix about X axis at angle
 */
inline Matrix3 RotateAboutX(float angle)
{
    float cs = cos(angle);
    float sn = sin(angle);

    return (Matrix3(1.0f, 0.0f, 0.0f, 
                    0.0f, cs, -sn, 
                    0.0f, sn, cs));
}
/*! @brief Generates rotation matrix about the Y axis
 *  @param[in] angle The angle of rotation
 *  @return [Matrix3] Rotation matrix about Y axis at angle
 */
inline Matrix3 RotateAboutY(float angle)
{
    float cs = cos(angle);
    float sn = sin(angle);

    return (Matrix3(cs, 0.0f, sn, 
                    0.0f, 1.0f, 0.0f, 
                    -sn, 0.0f, cs));
}
/*! @brief Generates rotation matrix about the Z axis
 *  @param[in] angle The angle of rotation
 *  @return [Matrix3] Rotation matrix about Z axis at angle
 */
inline Matrix3 RotateAboutZ(float angle)
{
    float cs = cos(angle);
    float sn = sin (angle);

    return (Matrix3(cs, -sn, 0.0f, 
                    sn, cs, 0.0f, 
                    0.0f, 0.0f, 1.0f));
}
/*! @brief Generates rotation matrix about an arbitrary axis
 *  @param[in] angle The angle of rotation
 *  @param[in] axis An arbitrary axis to rotate about
 *  @return [Matrix3] Rotation matrix about axis at angle
 */
inline Matrix3 RotateAboutAxis(float angle, const Vector3& axis)
{
    float cs = cos(angle);
    float sn = sin(angle);
    float delta = 1.0f - cs;

    float x = delta * axis.x;
    float y = delta * axis.y;
    float z = delta * axis.z;

    float aXY = x * axis.y;
    float aXZ = z * axis.z;
    float aYZ = y * axis.z;

    return (Matrix3(cs+x * axis.x, aXY-sn * axis.z, aXZ + sn*axis.y,
                    aXY + sn*axis.z, cs + y*axis.y, aYZ - sn*axis.x,
                    aXZ - sn*axis.y, aYZ + sn*axis.x, cs + z*axis.z));
}
/*! @brief Generates reflection matrix through the perpendicular plane of a given unit vector
 *  @param[in] u Unit vector used to define plane of reflection
 *  @return [Matrix3] Reflection matrix for unit vector
 */
inline Matrix3 Reflection(const Vector3& u)
{
    float x = u.x * -2.0f;
    float y = u.y * -2.0f;
    float z = u.z * -2.0f;
    float uXY = x * u.y;
    float uXZ = x * u.z;
    float uYZ = y * u.z;

    return (Matrix3(x * u.x+1.0f, uXY, uXZ,
                    uXY, y * u.y+1.0f, uYZ,
                    uXZ, uYZ, z * u.z+1.0f));
}
/*! @brief Generates involution matrix through the perpendicular plane of a given unit vector
 *  @param[in] u Unit vector used to define plane of involution
 *  @return [Matrix3] Involution matrix for unit vector
 */
inline Matrix3 Involution(const Vector3& u)
{
    float x = u.x * 2.0f;
    float y = u.y * 2.0f;
    float z = u.z * 2.0f;
    float uXY = x * u.y;
    float uXZ = x * u.z;
    float uYZ = y * u.z;

    return (Matrix3(x * u.x-1.0f, uXY, uXZ,
                    uXY, y * u.y-1.0f, uYZ,
                    uXZ, uYZ, z * u.z-1.0f));
}
/*! @brief Generates 3x3 matrix of scale factors for x, y, z axes
 *  @param[in] scaleX Scale factor for the X axis
 *  @param[in] scaleY Scale factor for the Y axis
 *  @param[in] scaleZ Scale factor for the Z axis
 *  @return [Matrix3] scale data structure.
 */
inline Matrix3 Scale(float scaleX, float scaleY, float scaleZ)
{
    return (Matrix3(scaleX, 0.0f, 0.0f,
                    0.0f, scaleY, 0.0f,
                    0.0f, 0.0f, scaleZ));
}
/*! @brief  Generates 3x3 skew matrix at an angle along a given direction
 *  @param angle The skew angle
 *  @param u1 Unit vector giving first direction, must be orthogonal to u2
 *  @param u2 Unit vector giving second direction, must be orthogonal to u1
 *  @return [Matrix3] Skew matrix for given angle and orthogonal unit vectors
 */
inline Matrix3 Skew(float angle, const Vector3& u1, const Vector3& u2)
{
    angle = tan(angle);
    float x = angle * u1.x;
    float y = angle * u1.y;
    float z = angle * u1.z;

    return (Matrix3(x*u2.x + 1.0f, x*u2.y, x*u2.z,
                    y*u2.x, y*u2.y + 1.0f, y*u2.z,
                    z*u2.x, z*u2.y, z*u2.z + 1.0f));
}

//        MATRICES 4D

struct Matrix4
{
protected:
    float m[4][4];
    
public:
    Matrix4() = default;
    Matrix4(float a00, float a01, float a02, float a03,
            float a10, float a11, float a12, float a13,
            float a20, float a21, float a22, float a23,
            float a30, float a31, float a32, float a33)
    {
        m[0][0] = a00; m[0][1] = a10; m[0][2] = a20; m[0][3] = a30;
        m[1][0] = a01; m[1][1] = a11; m[1][2] = a21; m[1][3] = a31;
        m[2][0] = a02; m[2][1] = a12; m[2][2] = a22; m[2][3] = a32;
        m[3][0] = a03; m[3][1] = a13; m[3][2] = a23; m[3][3] = a33;
    }
    Matrix4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d)
    {
        m[0][0] = a.w; m[0][1] = a.x; m[0][2] = a.y; m[0][3] = a.z;
        m[1][0] = b.w; m[1][1] = b.x; m[1][2] = b.y; m[1][3] = b.z;
        m[2][0] = c.w; m[2][1] = c.x; m[2][2] = c.y; m[2][3] = c.z;
        m[3][0] = d.w; m[3][1] = d.x; m[3][2] = d.y; m[3][3] = d.z;
    }
    // Operators
    float& operator ()(int i, int j) {return (m[j][i]);}
    const float& operator ()(int i, int j) const {return (m[j][i]);}
    Vector4& operator [](int j) 
    {
        return (*reinterpret_cast<Vector4 *>(m[j]));
    }
    const Vector4& operator [](int j) const
    {
        return (*reinterpret_cast<const Vector4 *>(m[j]));
    }
    
};
//      4D Inline Operators
inline Matrix4 operator +(const Matrix4& A, const Matrix4& B)
{
    return (Matrix4(A(0,0)+B(0,0), A(0,1)+B(0,1), A(0,2)+B(0,2), A(0,3)+B(0,3),
                    A(1,0)+B(1,0), A(1,1)+B(1,1), A(1,2)+B(1,2), A(1,3)+B(1,3),
                    A(2,0)+B(2,0), A(2,1)+B(2,1), A(2,2)+B(2,2), A(2,3)+B(2,3),
                    A(3,0)+B(3,0), A(3,1)+B(3,1), A(3,2)+B(3,2), A(3,3)+B(3,3)));
}
inline Matrix4 operator *(const Matrix4& A, const Matrix4& B)
{
    return (Matrix4(A(0,0)*B(0,0) + A(0,1)*B(1,0) + A(0,2)*B(2,0) + A(0,3)*B(3,0),
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
                    A(3,0)*B(0,3) + A(3,1)*B(1,3) + A(3,2)*B(2,3) + A(3,3)*B(3,3)));
}

inline Vector4 operator *(const Matrix4& M, const Vector4& v)
{
    return (Vector4(M(0,0)*v.w + M(0,1)*v.x + M(0,2)*v.y + M(0,3)*v.z,
                    M(1,0)*v.w + M(1,1)*v.x + M(1,2)*v.y + M(1,3)*v.z,
                    M(2,0)*v.w + M(2,1)*v.x + M(2,2)*v.y + M(2,3)*v.z,
                    M(3,0)*v.w + M(3,1)*v.x + M(3,2)*v.y + M(3,3)*v.z));
}
inline Matrix4 operator *(float sc, const Matrix4& M)
{
    return (Matrix4(sc*M(0,0), sc*M(0,1), sc*M(0,2), sc*M(0,3),
                    sc*M(1,0), sc*M(1,1), sc*M(1,2), sc*M(1,3),
                    sc*M(2,0), sc*M(2,1), sc*M(2,2), sc*M(2,3),
                    sc*M(3,0), sc*M(3,1), sc*M(3,2), sc*M(3,3)));
}
inline Matrix4 operator *(const Matrix4& M, float sc)
{
    return (sc*M);
}
inline Matrix4 operator /(const Matrix4& M, float sc)
{
    return ((1.0f/sc)*M);
}
inline Matrix4 operator -(const Matrix4& A, const Matrix4& B)
{
    return (A + (-1.0f * B));
}

//      4D Inline Methods

inline Vector4 Diagonal(const Matrix4& M)
{
    return Vector4(M(0,0), M(1,1), M(2,2), M(3,3));
}
/*! @brief Calculates the determinant of a 4x4 matrix
 *  @param[in] M 4x4 matrix to find the determinant for
 *  @return [float] Determinant of 4x4 matrix
 */
inline float Det(const Matrix4& M)
{
    return (M(0,0)*Det(Matrix3( M(1,1), M(1,2), M(1,3),
                                M(2,1), M(2,2), M(2,3),
                                M(3,1), M(3,2), M(3,3))) 
        - M(0,1) * Det(Matrix3( M(1,0), M(1,2), M(1,3),
                                M(2,0), M(2,2), M(2,3),
                                M(3,0), M(3,2), M(3,3))) 
        + M(0,2) * Det(Matrix3( M(1,0), M(1,1), M(1,3),
                                M(2,0), M(2,1), M(2,3),
                                M(3,0), M(3,1), M(3,3))) 
        - M(0,3) * Det(Matrix3( M(1,0), M(1,1), M(1,2),
                                M(2,0), M(2,1), M(2,2),
                                M(3,0), M(3,1), M(3,2))));
}       
/*! @brief Calculates the transpose of a 4x4 matrix
 *  @param[in] M 4x4 matrix to transpose
 *  @return [Matrix4] Transposed 4x4 matrix
 */
inline Matrix4 Transpose(const Matrix4& M)
{
    return (Matrix4( M(0,0), M(1,0), M(2,0), M(3,0),
                    M(0,1), M(1,1), M(2,1), M(3,1),
                    M(0,2), M(1,2), M(2,2), M(3,2),
                    M(0,3), M(1,3), M(2,3), M(3,3)));
} 
/*! @brief Calculates the inverse of a 4x4 matrix
 *  @param[in] M 4x4 matrix to find the inverse for
 *  @return [Matrix4] Inverse of 4x4 matrix
 */
inline Matrix4 Inverse(const Matrix4& M)
{
    const Vector3& m0 = reinterpret_cast<const Vector3&>(M[0]);
    const Vector3& m1 = reinterpret_cast<const Vector3&>(M[1]);
    const Vector3& m2 = reinterpret_cast<const Vector3&>(M[2]);
    const Vector3& m3 = reinterpret_cast<const Vector3&>(M[3]);
    const Vector4& v = Vector4(M(3,0), M(3,1), M(3,2), M(3,3));

    Vector3 a = CrossProduct(m0, m1);
    Vector3 b = CrossProduct(m2, m3);
    Vector3 c = m0*v.x - m1*v.w;
    Vector3 d = m2*v.z - m3*v.y;

    float det = (a*d)+(b*c);

    try
    {
        if (det == 0) throw NonInvertibleE();
        float sc = (1.0f / ((a*d)+(b*c)));
        a *= sc;
        b *= sc;
        c *= sc;
        d *= sc;

        Vector3 r0 = CrossProduct(m1, d) + b*v.x;
        Vector3 r1 = CrossProduct(d, m0) - b*v.w;
        Vector3 r2 = CrossProduct(m3, c) + a*v.z;
        Vector3 r3 = CrossProduct(c, m2) - a*v.y;

        return (Matrix4(r0.x, r0.y, r0.z, -(m1*b),
                        r1.x, r1.y, r1.z, (m0*b),
                        r2.x, r2.y, r2.z, -(m3*a),
                        r3.x, r3.y, r3.z, (m2*a)));
    }
    catch(NonInvertibleE& e)
    {
        cout << "Exception occurred!\n" << e.what();
    }
    
}
/*! @brief Calculates the adjugate of a 4x4 matrix
 *  @param[in] M 4x4 matrix to find the adjugate for
 *  @return [Matrix4] Adjugate of 4x4 matrix
 */
inline Matrix4 Adjugate(const Matrix4& M)
{
    return (Det(M)*Inverse(M));
}
/*! @brief Calculates the cofactor of a 4x4 matrix
 *  @param[in] M 4x4 matrix to find the cofactor for
 *  @return [Matrix4] Cofactor of 4x4 matrix
 */
inline Matrix4 Cofactor(const Matrix4& M)
{
    return (Transpose(Adjugate(M)));
}
/*! @brief Calculates the trace of a 4x4 matrix
 *  @param[in] M 4x4 matrix to find the trace for
 *  @return [float] Trace of 4x4 matrix
 */
inline float Trace(const Matrix4& M)
{
    return (M(0,0) + M(1,1) + M(2,2) + M(3,3));
}
/*! @brief Checks if 4x4 matrix is orthogonal
 *  @param[in] M 4x4 matrix to check for orthogonality
 *  @return [bool] Whether M is orthogonal
 */
inline bool IsOrthogonal(const Matrix4& M)
{
    Matrix4 Id = M*Transpose(M);
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if ((i==j && Id(i,j)!=1) || ((i!=j && Id(i,j)!=0))) return false;
        }
    }
    return true;
}

//      4D TRANSFORMS

struct Transform4 : Matrix4
{
    Transform4() = default;
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

    Transform4( const Vector3& v0, const Vector3& v1, const Vector3& v2, const Point3& p)
    {
        m[0][0] = v0.x; m[0][1] = v0.y; m[0][2] = v0.z;
        m[1][0] = v1.x; m[1][1] = v1.y; m[1][2] = v1.z;
        m[2][0] = v2.x; m[2][1] = v2.y; m[2][2] = v2.z;
        m[3][0] = p.x; m[3][1] = p.y; m[3][2] = p.z;

        m[0][3] = 0.0f; m[1][3] = 0.0f; m[2][3] = 0.0f; m[3][3]=1.0f;
    }

    Vector3& operator [](int j)
    {
        return (*reinterpret_cast<Vector3 *>(m[j]));
    }

    const Vector3& operator [](int j) const
    {
        return (*reinterpret_cast<const Vector3 *>(m[j]));
    }
    /*! @brief Gets translation point from this transform  
     *  @return [Point3] 3D Translation point
     */
    const Point3& GetTranslation(void) const
    {
        return (*reinterpret_cast<const Point3 *>(m[3]));
    }
    /*! @brief Sets translation point for this transform 
     *  @param p Point used to set translation
     */
    void SetTranslation(const Point3& p)
    {
        m[3][0] = p.x; m[3][1] = p.y; m[3][2] = p.z;
    }
};
inline Transform4 operator +(const Transform4& A, const Transform4& B)
{
    return (Transform4(
        A(0,0) + B(0,0), A(0,1) + B(0,1), A(0,2) + B(0,2), A(0,3) + B(0,3),
        A(1,0) + B(1,0), A(1,1) + B(1,1), A(1,2) + B(1,2), A(1,3) + B(1,3),
        A(2,0) + B(2,0), A(2,1) + B(2,1), A(2,2) + B(2,2), A(2,3) + B(2,3)
    ));
}
inline Transform4 operator *(float sc, const Transform4& T)
{
    return Transform4(
        sc*T(0,0), sc*T(0,1), sc*T(0,2), sc*T(0,3),
        sc*T(1,0), sc*T(1,1), sc*T(1,2), sc*T(1,3),
        sc*T(2,0), sc*T(2,1), sc*T(2,2), sc*T(2,3)
    );
}
inline Transform4 operator *(const Transform4& T, float sc)
{
    return (sc*T);
}
inline Transform4 operator /(const Transform4& T, float sc)
{
    return (1.0f/sc) * T;
}
inline Transform4 operator -(const Transform4& A, const Transform4& B)
{
    return A + (-1.0f*B);
}
inline Transform4 operator *(const Transform4& A, const Transform4& B)
{
    return (Transform4(
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
        A(2,0)*B(0,3) + A(2,1)*B(1,3) + A(2,2)*B(2,3) + A(2,3)
    ));
}
inline Vector3 operator *(const Vector3& n, const Transform4& T)
{
    return (Vector3(
        n.x*T(0,0) + n.y*T(1,0) + n.z*T(2,0),
        n.x*T(0,1) + n.y*T(1,1) + n.z*T(2,1),
        n.x*T(0,2) + n.y*T(1,2) + n.z*T(2,2)
    ));
}
inline Vector3 operator *(const Transform4& T, const Vector3& v)
{
    return (Vector3(
        T(0,0)*v.x + T(0,1)*v.y + T(0,2)*v.z,
        T(1,0)*v.x + T(1,1)*v.y + T(1,2)*v.z,
        T(2,0)*v.x + T(2,1)*v.y + T(2,2)*v.z
    ));
}

inline Point3 operator *(const Transform4& T, const Point3& p)
{
    return (Point3(
        T(0,0)*p.x + T(0,1)*p.y + T(0,2)*p.z,
        T(1,0)*p.x + T(1,1)*p.y + T(1,2)*p.z,
        T(2,0)*p.x + T(2,1)*p.y + T(2,2)*p.z
    ));
}

/*! @brief Generates the inverse of a transform T
 *  @param T The transform to invert
 *  @returns [Transform4] Inverted Transform
 *  @warning Will give an error if the transform is non-invertible
 */
inline Transform4 Inverse(const Transform4& T)
{
    const Vector3& w = T[0];
    const Vector3& x = T[1];
    const Vector3& y = T[2];
    const Vector3& z = T[3];

    Vector3 s = CrossProduct(w, x);
    Vector3 t = CrossProduct(y, z);

    float det = s*y;
    
    try {
        if (det == 0.0f) throw NonInvertibleE();
        float sc = 1.0f/(s*y);
        s *= sc;
        t *= sc;

        Vector3 vec = y*sc;
        Vector3 r0 = CrossProduct(x, vec);
        Vector3 r1 = CrossProduct(vec, w);

        return (Transform4(
            r0.x, r0.y, r0.z, -(x*t),
            r1.x, r1.y, r1.z, (w*t),
            s.x, s.y, s.z, -(z*s)));
    }
    catch (NonInvertibleE& e)
    {
        cout << "Exception occurred!\n" << e.what();
    }
} 

/*! @brief Generates 4x4 matrix of scale factors for w, x, y, z axes
 *  @param[in] scaleW Scale factor for the W axis
 *  @param[in] scaleX Scale factor for the X axis
 *  @param[in] scaleY Scale factor for the Y axis
 *  @param[in] scaleZ Scale factor for the Z axis
 *  @return [Matrix4] Scale data structure.
 */
inline Matrix4 Scale(float scaleW, float scaleX, float scaleY, float scaleZ)
{
    return (Matrix4(scaleW, 0.0f, 0.0f, 0.0f,
                    0.0f, scaleX, 0.0f, 0.0f,
                    0.0f, 0.0f, scaleY, 0.0f,
                    0.0f, 0.0f, 0.0f, scaleZ));
}
/*! @brief  Generates 4x4 skew matrix at an angle along a given direction
 *  @param angle The skew angle
 *  @param u1 Unit vector giving first direction, must be orthogonal to u2
 *  @param u2 Unit vector giving second direction, must be orthogonal to u1
 *  @return [Matrix4] Skew matrix for given angle and orthogonal unit vectors
 */
inline Matrix4 Skew(float angle, const Vector4& u1, const Vector4& u2)
{
    angle = tan(angle);
    float w = angle * u1.w;
    float x = angle * u1.x;
    float y = angle * u1.y;
    float z = angle * u1.z;

    return (Matrix4(w*u2.w + 1.0f, w*u2.x, w*u2.y, w*u2.z,
                    x*u2.w, x*u2.x + 1.0f, x*u2.y, x*u2.z,
                    y*u2.w, y*u2.x, y*u2.y + 1.0f, y*u2.z,
                    z*u2.w, z*u2.x, z*u2.y, z*u2.z + 1.0f));
}
/*!
 * @brief Generates a transform of a reflection through a given normalized plane
 * @param f The (presumably) normalized plane
 * @return [Transform4] 4x4 matrix representing the reflection transform through f
 */
inline Transform4 Reflection(const Plane& f)
{
    float x = f.x*(-2.0f);
    float y = f.y*(-2.0f);
    float z = f.z*(-2.0f);
    float nxy = x*f.y;
    float nxz = x*f.z;
    float nyz = y*f.z;

    return (Transform4( x*f.x + 1.0f, nxy, nxz, x*f.w,
                        nxy, y*f.y + 1.0f, nyz, y*f.w,
                        nxz, nyz, z*f.z + 1.0f, z*f.w));
}

inline Plane operator*(const Plane& f, const Transform4& T)
{
    return (Plane(
        f.x*T(0,0) + f.y*T(1,0) + f.z*T(2,0),
        f.x*T(0,1) + f.y*T(1,1) + f.z*T(2,1),
        f.x*T(0,2) + f.y*T(1,2) + f.z*T(2,2),
        f.x*T(0,3) + f.y*T(1,3) + f.z*T(2,3) + f.w
    ));
}

inline Line TransformLine(const Line& L, const Transform4& T)
{
    Matrix3 adj(CrossProduct(T[1], T[2]), CrossProduct(T[2],T[0]), CrossProduct(T[0], T[1]));
    const Point3& p = T.GetTranslation();
    Vector3 v = T*L.direction;
    Vector3 m = adj*L.moment + CrossProduct(p, v);
    return (Line(v,m));
}

//      QUATERNIONS

struct Quaternion
{
    float x,y,z,w;

    Quaternion() = default;
    Quaternion(float a, float b, float c, float sc)
    {
        x = a; y = b; z = c; w = sc;
    }
    Quaternion(const Vector3& v, float sc)
    {
        x = v.x; y = v.y; z = v.z; w = sc;
    }
    const Vector3& GetVector(void) const
    {
        return (reinterpret_cast<const Vector3&>(x));
    }
    Matrix3 GetRotation(void)
    {
        float x2 = x*x; float y2 = y*y; float z2 = z*z;
        float xy = x*y; float xz = x*z; float yz = y*z;
        float wx = w*x; float wy = w*y; float wz = w*z;

        return (Matrix3(
            1.0f - 2.0f*(y2 + z2), 2.0f*(xy - wz), 2.0f*(xz + wy),
            2.0f*(xy + wz), 1.0f - 2.0f*(x2 + z2), 2.0f*(yz - wx),
            2.0f*(xz - wy), 2.0f*(yz + wx), 1.0f - 2.0f*(x2 + y2)
        ));
    }
    void SetRotation(const Matrix3& M)
    {
        Vector3 v = Diagonal(M);
        float sum = v.x + v.y + v.z;
        if (sum > 0.0f)
        {
            w = sqrt(sum + 1.0f) * 0.5f;
            float scale = 0.25f/w;
            x = (M(2,1) - M(1,2)) * scale;
            y = (M(0,2) - M(2,0)) * scale;
            z = (M(1,0) - M(0,1)) * scale;
        } 
        else if ((v.x>v.y) && (v.x>v.z))
        {
            x = sqrt(v.x - v.y - v.z + 1.0f)*0.5f;
            float scale = 0.25f/x;
            y = (M(1,0) + M(0,1)) * scale;
            z = (M(0,2) + M(2,0)) * scale;
            w = (M(2,1) - M(1,2)) * scale; 
        }
        else if (v.y>v.z)
        {
            y = sqrt(v.y - v.x - v.z + 1.0f)* 0.5f;
            float scale = 0.25f/y;
            x = (M(1,0) + M(0,1)) * scale;
            z = (M(2,1) + M(1,2)) * scale;
            w = (M(0,2) - M(2,0)) * scale;
        }
        else
        {
            z = sqrt(v.z - v.x - v.y + 1.0f) * 0.5f;
            float scale = 0.25f/z;
            x = (M(0,2) + M(2,0)) * scale;
            y = (M(2,1) + M(1,2)) * scale;
            w = (M(1,0) - M(0,1)) * scale;
        }
    }
};
inline Quaternion operator +(const Quaternion& a, const Quaternion& b)
{
    return (Quaternion(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w));
}
inline Quaternion operator *(float sc, const Quaternion& q)
{
    return (Quaternion(sc*q.x, sc*q.y, sc*q.z, sc*q.w));
}
inline Quaternion operator *(const Quaternion& q, float sc)
{
    return sc*q;
}
inline Quaternion operator /(const Quaternion& q, float sc)
{
    return (1.0f/sc)*q;
}
inline Quaternion operator -(const Quaternion& a, const Quaternion& b)
{
    return (a + (-1.0f * b));
}
inline Quaternion operator *(const Quaternion& q1, const Quaternion& q2)
{
    return (Quaternion(
        q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y,
        q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x,
        q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w,
        q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z
    ));  
}
inline Vector3 Transform(const Vector3& v, const Quaternion& q)
{
    const Vector3& u = q.GetVector();
    float uDotU= u.x*u.x + u.y*u.y + u.z*u.z;
    return (v*(q.w*q.w - uDotU) + u*u*v*2.0f + CrossProduct(u,v)*q.w*2.0f);
}