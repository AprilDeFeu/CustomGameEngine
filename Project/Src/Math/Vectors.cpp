#include "Math\Vectors.h"

//---------------------------------------------------------------------------------------------
//                                          FUNCTIONS
//---------------------------------------------------------------------------------------------

// * * * * * 3D CROSS PRODUCT * * * * * //

Vector3 CrossProduct(const Vector3& v1,const Vector3& v2)
{
    return (Vector3(v1.y*v2.z - v1.z*v2.y,
                    v1.z*v2.x - v1.x*v2.z,
                    v1.x*v2.y - v1.y*v2.x));
}

// * * * * * 3D SCALAR TRIPLE PRODUCT * * * * * //

float ScalarTripleProduct(const Vector3& v1,const Vector3& v2,const Vector3& v3)
{
    // Returns (v1 x v2) * v3
    return (CrossProduct(v1, v2) * v3);
}

// * * * * * ANGLES * * * * * //

float Angle(const Vector2& v1, const Vector2& v2)
{
    try {if (Magnitude(v1)==0 || Magnitude(v2)==0) throw ZeroMagnitudeE();}
    catch(ZeroMagnitudeE& e) {cout << "Exception occurred!\n" << e.what();}
    return acos(InnerProduct(v1, v2) / (Magnitude(v1) * Magnitude(v2)));
}

float Angle(const Vector3& v1, const Vector3& v2)
{
    try {if (Magnitude(v1)==0 || Magnitude(v2)==0) throw ZeroMagnitudeE();}
    catch(ZeroMagnitudeE& e) {cout << "Exception occurred!\n" << e.what();}
    return acos((v1 * v2) / (Magnitude(v1) * Magnitude(v2)));
}

float Angle(const Vector4& v1, const Vector4& v2)
{
    try {if (Magnitude(v1)==0 || Magnitude(v2)==0) throw ZeroMagnitudeE();}
    catch(ZeroMagnitudeE& e) {cout << "Exception occurred!\n" << e.what();}
    return acos((v1 * v2) / (Magnitude(v1) * Magnitude(v2)));
}

// * * * * * PROJECTIONS * * * * * //

Vector2 Projection(const Vector2& v1, const Vector2& v2)
{
    try {if (v2 * v2 == 0.0f) throw ZeroVectorE();}
    catch (ZeroVectorE& e) {cout << "Exception occurred!\n" << e.what();}
    return (((v1*v2) / (v2*v2)) * v2);
}

Vector3 Projection(const Vector3& v1, const Vector3& v2)
{
    try {if ((v2 * v2) == 0.0f) throw ZeroVectorE();}
    catch (ZeroVectorE& e) {cout << "Exception occurred!\n" << e.what();}
    return (((v1 * v2) / (v2 * v2)) * v2);
}

Vector4 Projection(const Vector4& v1, const Vector4& v2)
{
    try {if ((v2 * v2) == 0.0f) throw ZeroVectorE();}
    catch (ZeroVectorE& e) {cout << "Exception occurred!\n" << e.what();}
    return (((v1 * v2) / (v2 * v2)) * v2);
}
