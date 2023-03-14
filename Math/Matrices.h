#include "Vectors.h"

// DISCLAIMER - The following header file deals with square matrices only.

/*
        MATRICES 2D
*/
struct Matrix2
{
private:
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
// Inline functions
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


/*
        MATRICES 3D
*/
struct Matrix3
{
private:
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
    // Operators
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
// Inline functions
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
/*
        MATRICES 4D
*/
struct Matrix4
{
private:
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
// Inline functions
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
                 