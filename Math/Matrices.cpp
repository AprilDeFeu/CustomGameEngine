#include "Matrices.h"
#include <iomanip>
#include <iostream>
#include <cfloat>

//---------------------------------------------------------------------------------------------
//                                         CLASS METHODS
//---------------------------------------------------------------------------------------------

using namespace std;

// * * * * * MATRIX4 * * * * * //
string Matrix4::ToString(void)
{
    string s;
    for (int i=0; i<4; i++)
    {
        s += "\t[";
        for (int j=0; j<4; j++)
        {
            if (j!=3) s += to_string(m[j][i]) + ", ";
            else s += to_string(m[j][i]);
        }
        s+= "]\n";
    }
    return s;
}

// * * * * * QUATERNIONS * * * * * //

Matrix3 Quaternion::GetRotation(void)
{
    float x2 = x*x; float y2 = y*y; float z2 = z*z;
    float xy = x*y; float xz = x*z; float yz = y*z;
    float wx = w*x; float wy = w*y; float wz = w*z;

    return (Matrix3(
        1.0f - 2.0f*(y2 + z2), 2.0f*(xy - wz), 2.0f*(xz + wy),
        2.0f*(xy + wz), 1.0f - 2.0f*(x2 + z2), 2.0f*(yz - wx),
        2.0f*(xz - wy), 2.0f*(yz + wx), 1.0f - 2.0f*(x2 + y2)));
}

void Quaternion::SetRotation(const Matrix3& M)
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

// * * * * * REF * * * * * //

Matrix2 REF(const Matrix2& M, float *c)
{
    cout << setprecision(13);
    Matrix2 pr = M;
    Vector2 row1 = M.Row(0);
    Vector2 row2 = M.Row(1);

    int counter = 0;
    // Matrix is zero, return itself
    if (row1 == row1.Zero() && row2 == row2.Zero()) return M;
    // Matrix is already REF, return itself
    if (row1.x == 1.0f
    && row2.x == 0.0f && row2.y == 1.0f) return M;
    // (0,0) is not a pivot, swap row1 and row2
    if (row1.x == 0.0f)
    {
        Swap(&row1, &row2);
    }
    // (0,0) is pivot but not reduced, divide row1 by (0,0)
    if (row1.x != 1.0f && row1.x != 0.0f)
    {
        *c *= row1.x;
        row1 /= row1.x;
    }
    // (0,0) is reduced and pivot, reduce row2
    if (fabs(1.0f-row1.x) > FLT_MIN && fabs(1.0f-row1.x) < 0.000001f) row1.x = 1.0f;
    if (row1.x == 1.0f && row2.x != 0.0f)
    {
        row2 -= row2.x*row1;
    }

    // (1,1) is pivot but not reduced. Divide row2 by (1,1)
    if (row2.y != 1.0f && row2.y != 0.0f)
    {
        *c *= row2.y;
        row2 /= row2.y;
    }
    return Matrix2(row1.x, row1.y, fabs(row2.x), row2.y);
}

Matrix3 REF(const Matrix3& M, float *c)
{
    Vector3 row1 = M.Row(0);
    Vector3 row2 = M.Row(1);
    Vector3 row3 = M.Row(2);

    // Matrix is zero, return itself
    if (row1 == row1.Zero()
    && row2 == row2.Zero()
    && row3 == row3.Zero())
    return M;
    // Matrix is already REF, return itself
    if (row1.x == 1.0f
    && row2.x == 0.0f && row2.y == 1.0f
    && row3.x == 0.0f && row3.y == 0.0f && row3.z == 1.0f) return M;
    // (0,0) is not a pivot, swap row1 and row2
    if (row1.x == 0.0f) Swap(&row1, &row2);
    // (0,0) is not a pivot, swap row1 and row3
    if (row1.x == 0.0f) Swap(&row1, &row3);
    // (0,0) is pivot but not reduced, divide row1 by (0,0)
    if (row1.x != 1.0f && row1.x != 0.0f)
    {
        *c *= row1.x;
        row1 /= row1.x;
    }
    // (0,0) is reduced and pivot, reduce row2
    if (fabs(1.0f-row1.x) > FLT_MIN && fabs(1.0f-row1.x) < 0.000001f) row1.x = 1.0f;
    if (row1.x == 1.0f && row2.x != 0.0f) row2 -= row2.x*row1;
    // (0,0) is reduced and pivot, reduce row3
    if (row1.x == 1.0f && row3.x != 0.0f) row3 -= row3.x*row1;
    // Create submatrix
    Matrix2 subM = Matrix2(row2.y, row2.z, row3.y, row3.z);
    // Perform REF on submatrix
    subM = REF(subM, c);
    row2.y = subM(0,0); row2.z = subM(0,1);
    row3.y = subM(1,0); row3.z = subM(1,1);

    return Matrix3
    (row1.x, row1.y, row1.z,
    fabs(row2.x), row2.y, row2.z,
    fabs(row3.x), fabs(row3.y), row3.z);
}

Matrix4 REF(const Matrix4& M, float *c)
{
    Vector4 row1(M.Row(0));
    Vector4 row2(M.Row(1));
    Vector4 row3(M.Row(2));
    Vector4 row4(M.Row(3));

    // Matrix is zero, return itself
    if(row1 == row1.Zero() && row2 == row2.Zero()
    && row3 == row3.Zero() && row4 == row4.Zero())
    return M;
    // Matrix is already REF, return itself
    if(row1.x == 1.0f
    && row2.x == 0.0f && row2.y == 1.0f
    && row3.x == 0.0f && row3.y == 0.0f && row3.z == 1.0f
    && row4.x == 0.0f && row4.y == 0.0f && row4.z == 0.0f && row4.w == 1.0f) return M;
    // (0,0) is not a pivot, swap row1 and row2
    if (row1.x == 0.0f) Swap(&row1, &row2);
    // (0,0) is not a pivot, swap row1 and row3
    if (row1.x == 0.0f) Swap(&row1, &row3);
    // (0,0) is not a pivot, swap row1 and row4
    if (row1.x == 0.0f) Swap(&row1, &row4);
    // (0,0) is pivot but not reduced, divide row1 by (0,0)
    if (row1.x != 1.0f && row1.x != 0.0f)
    {
        *c *= row1.x;
        row1 /= row1.x;
    }
    if (fabs(1.0f-row1.x) > FLT_MIN && fabs(1.0f-row1.x) < 0.000001f) row1.x = 1.0f;
    // (0,0) is reduced and pivot, reduce row2
    if (row1.x == 1.0f && row2.x != 0.0f) row2 -= row2.x*row1;
    // (0,0) is reduced and pivot, reduce row3
    if (row1.x == 1.0f && row3.x != 0.0f) row3 -= row3.x*row1 ;
    // (0,0) is reduced and pivot, reduce row4
    if (row1.x == 1.0f && row4.x != 0.0f) row4 -= row4.x*row1;
    // Create submatrix

    Matrix3 subM = Matrix3(row2.y, row2.z, row2.w,
                            row3.y, row3.z, row3.w,
                            row4.y, row4.z, row4.w);
    // Perform REF on subM
    subM = REF(subM, c);
    row2.y = subM(0,0); row2.z = subM(0,1); row2.w = subM(0,2);
    row3.y = subM(1,0); row3.z = subM(1,1); row3.w = subM(1,2);
    row4.y = subM(2,0); row4.z = subM(2,1); row4.w = subM(2,2);

    return Matrix4
    (row1.x, row1.y, row1.z, row1.w,
    fabs(row2.x), row2.y, row2.z, row2.w,
    fabs(row3.x), fabs(row3.y), row3.z, row3.w,
    fabs(row4.x), fabs(row4.y), fabs(row4.z), row4.w);
}

// * * * * * DETERMINANT * * * * * //

float Det(const Matrix4& M)
{
    Vector4 row1 = M.Row(0);
    Vector4 row2 = M.Row(1);
    Vector4 row3 = M.Row(2);
    Vector4 row4 = M.Row(3);

    if (row1.x == 0.0f) Swap(&row1, &row2);
    if (row1.x == 0.0f) Swap(&row1, &row3);
    if (row1.x == 0.0f) Swap(&row1, &row4);

    if (row1.x != 0.0f)
    {
        if(row2.x != 0.0f) row2 -= (row2.x/row1.x)*row1;
        if(row3.x != 0.0f) row3 -= (row3.x/row1.x)*row1;
        if(row4.x != 0.0f) row4 -= (row4.x/row1.x)*row1;
    }

    if (row2.y == 0.0f) Swap(&row2, &row3);
    if (row2.y == 0.0f) Swap(&row2, &row4);

    if (row2.y != 0.0f)
    {
        if (row3.y != 0.0f) row3 -= (row3.y/row2.y)*row2;
        if (row4.y != 0.0f) row4 -= (row4.y/row2.y)*row2;
    }

    if (row3.z == 0.0f) Swap(&row3, &row4);

    if (row3.z != 0.0f)
    {
        if (row4.z != 0.0f) row4 -= (row4.z/row3.z)*row3;
    }

    return (row1.x * row2.y * row3.z * row4.w);

}

// * * * * * INVERSE * * * * * //

Matrix2 Inverse(const Matrix2& M)
{
    try
    {
        if (Det(M) == 0.0f) throw NonInvertibleE();
        return (1.0/Det(M)) * Matrix2(M(1,1), -1.0*M(0,1), -1.0*M(1,0), M(0,0));
    }
    catch(NonInvertibleE& e)
    {
        cout << "Exception occurred!\n" << e.what();
    }
    return M.Zero();
}

Matrix3 Inverse(const Matrix3& M)
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
    return M.Zero();
}

Matrix4 Inverse(const Matrix4& M)
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
    return M.Zero();
}

Transform3 Inverse(const Transform3& T)
{
    const Matrix3& M = Matrix3( T(0,0), T(0,1), T(0,2),
                                T(1,0), T(1,1), T(1,2),
                                0.0f,   0.0f,   1.0f);
    Matrix3 Inv = Inverse(M);
    return (Transform3(Inv(0,0), Inv(0,1), Inv(0,2), Inv(1,0), Inv(1,1), Inv(1,2)));
}

Transform4 Inverse(const Transform4& T)
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
    return T.Zero();
}

// * * * * * ORTHOGONALITY CHECK * * * * * //

bool IsOrthogonal(const Matrix2& M)
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

bool IsOrthogonal(const Matrix3& M)
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

bool IsOrthogonal(const Matrix4& M)
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

// * * * * * SKEW MATRICES * * * * * //

Matrix2 Skew(float angle, const Vector2& u1, const Vector2& u2)
{
    angle = tan(angle);
    float x = angle * u1.x;
    float y = angle * u1.y;

    return (Matrix2(x*u2.x + 1.0f, x*u2.y,
                    y*u2.x, y*u2.y + 1.0f));
}

Matrix3 Skew(float angle, const Vector3& u1, const Vector3& u2)
{
    angle = tan(angle);
    float x = angle * u1.x;
    float y = angle * u1.y;
    float z = angle * u1.z;

    return (Matrix3(x*u2.x + 1.0f, x*u2.y, x*u2.z,
                    y*u2.x, y*u2.y + 1.0f, y*u2.z,
                    z*u2.x, z*u2.y, z*u2.z + 1.0f));
}

Matrix4 Skew(float angle, const Vector4& u1, const Vector4& u2)
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

// * * * * * ROTATIONS * * * * * //

Matrix3 RotateAboutX(float angle)
{
    float cs = cos(angle);
    float sn = sin(angle);

    return (Matrix3(1.0f, 0.0f, 0.0f,
                    0.0f, cs, -sn,
                    0.0f, sn, cs));
}

Matrix3 RotateAboutY(float angle)
{
    float cs = cos(angle);
    float sn = sin(angle);

    return (Matrix3(cs, 0.0f, sn,
                    0.0f, 1.0f, 0.0f,
                    -sn, 0.0f, cs));
}

Matrix3 RotateAboutZ(float angle)
{
    float cs = cos(angle);
    float sn = sin (angle);

    return (Matrix3(cs, -sn, 0.0f,
                    sn, cs, 0.0f,
                    0.0f, 0.0f, 1.0f));
}

Matrix3 RotateAboutAxis(float angle, const Vector3& axis)
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

// * * * * * REFLECTION/INVOLUTION * * * * * //

Matrix3 Reflection(const Vector3& u)
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

Transform4 Reflection(const Plane& f)
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

Matrix3 Involution(const Vector3& u)
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

// * * * * * EXTRAS * * * * * //

Line TransformLine(const Line& L, const Transform4& T)
{
    Matrix3 adj(CrossProduct(T[1], T[2]), CrossProduct(T[2],T[0]), CrossProduct(T[0], T[1]));
    const Point3& p = T.GetTranslation();
    Vector3 v = T*L.direction;
    Vector3 m = adj*L.moment + CrossProduct(p, v);
    return (Line(v,m));
}

Vector3 Transform(const Vector3& v, const Quaternion& q)
{
    const Vector3& u = q.GetVector();
    float uDotU= u.x*u.x + u.y*u.y + u.z*u.z;
    return (v*(q.w*q.w - uDotU) + u*u*v*2.0f + CrossProduct(u,v)*q.w*2.0f);
}