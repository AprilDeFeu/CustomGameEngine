#include "Vectors.h"
#include "Geometry.h"

//---------------------------------------------------------------------------------------------
//                                          METHODS
//---------------------------------------------------------------------------------------------

// * * * * * INTERSECTIONS * * * * * //

bool Intersection(   const Point3& p, const Vector3& v, 
                            const Plane& f, Point3 *q)
{
    float fv = (f*v);
    if (fabs(fv) > FLT_MIN)
    {
        *q = toPoint(p - (v*((f*p)/fv)));
        return (true);
    }
    return (false);
}

bool Intersection(   const Plane& f0, const Plane& f1, Point3 *p, Vector3 *v)
{
    const Vector3& n0 = f0.Normal();
    const Vector3& n1 = f1.Normal();

    *v = CrossProduct(n0,n1);
    float det = (*v * *v);
    if (fabs(det) > FLT_MIN)
    {
        *p = toPoint((CrossProduct(*v, n1)*f0.w + CrossProduct(n0,*v)*f1.w)/det);
        return true;
    }
    return false;
}

bool Intersection(const Plane& f0, const Plane& f1, const Plane&f2, Point3 *p)
{
    const Vector3& n0 = f0.Normal();
    const Vector3& n1 = f1.Normal();
    const Vector3& n2 = f2.Normal();

    Vector3 n0xn1 = CrossProduct(n0,n1);
    float det = (n0xn1*n2);
    if (fabs(det) > FLT_MIN)
    {
        *p = toPoint((CrossProduct(n2, n1)*f0.w + CrossProduct(n0,n2)*f1.w - n0xn1*f2.w)/det);
        return true;
    }
    return false;
}

bool Intersection(const Line& L, const Plane& p, HomogeneousPoint3 *h)
{
    float pd = p*L.direction;
    if (fabs(pd) > FLT_MIN)
    {
        Vector3 toPoint = (CrossProduct(L.moment, p.Normal()) + p.w*L.direction);
        HomogeneousPoint3 h_tmp = HomogeneousPoint3(toPoint.x, toPoint.y, toPoint.z,(-1.0f*p.Normal()*L.direction));
        *h = h_tmp;
        return true;
    }
    return false;
}

// * * * * * EXTRAS * * * * * //

Point3 ClosestDistanceToPoint(const Vector3& v, const Point3& p)
{
    Point3 *q = new Point3(0.0f, 0.0f, 0.0f);
    Plane f(v, (-1.0f*v*p));
    if (Intersection(p, v, f, q)) 
    {
        Point3 res = *q;
        delete q;
        
        return res;
    }
    delete q;
    // This should only be reached if, for some reason, there is no orthogonal
    // plane to the given line, which I think should be impossible.
    return Point3(-FLT_MIN, -FLT_MIN, -FLT_MIN);
}

Plane TranslatePlane(const Plane& f, const Vector3& t)
{
    return Plane(f.Normal(), f.w - (f.Normal()*t));
}

float DistanceBetweenLines( const Point3& p0, const Vector3& v0, const Point3& p1, const Vector3& v1)
{
    Vector3 u = (p1-p0);

    float v00 = (v0*v0);
    float v11 = (v1*v1);
    float v01 = (v0*v1);
    float det = (v01*v01) - (v00*v11);

    if (fabs(det) > FLT_MIN)
    {
        det = 1.0f/det;
        float uv0 = (u*v0);
        float uv1 = (u*v1);
        float x0 = ((v01*uv1) - (v11*uv0))*det;
        float x1 = ((v00*uv1) - (v01*uv0))*det;

        return (Magnitude(u + (v1*x1) - (v0*x0)));
    } 
    Vector3 a = CrossProduct(u,v0);
    return (sqrt((a*a)/v00));
}