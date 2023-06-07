#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cfloat>
#include <string>
#include "Math\Vectors.h"

//---------------------------------------------------------------------------------------------
//                                        CLASSES
//---------------------------------------------------------------------------------------------

// * * * * * POINTS * * * * * //

/*!
 * @class Point2 @extends Vector2
 * @brief 2D Point data structure (float x, float y)
 * @param x First coordinate
 * @param y Second coordinate
 * @param Zero() Creates a zero point (0.0f, 0.0f)
 */
struct Point2 : Vector2
{
    //! @public @memberof Point2
    //! @brief Creates an empty Point2 structure
    Point2() = default;
    //! @public @memberof Point2
    //! @brief Creates a Point2 structure (float x, float y)
    Point2(float x, float y) : Vector2(x,y) {}
    //! @public @memberof Point2
    //! @brief Creates a zero point (0.0f, 0.0f)
    const Point2 Zero(void) const {return Point2(0.0f, 0.0f);}
    void Print(void) {cout << "Point2: " << (*this).ToString() << "\n";}
    Vector2 operator -= (const Point2& p) {return Vector2(x-p.x, y-p.y);}
};
/*!
 * @class Point3 @extends Vector3
 * @brief 3D Point data structure (float x, float y, float z)
 * @param x First coordinate
 * @param y Second coordinate
 * @param z Third coordinate
 * @param Zero() Creates a zero point (0.0f, 0.0f, 0.0f)
 */
struct Point3 : Vector3
{
    //! @public @memberof Point3
    //! @brief Creates an empty Point3 structure
    Point3() = default;
    //! @public @memberof Point3
    //! @brief Creates a Point3 structure
    Point3(float x, float y, float z) : Vector3(x,y,z) {}
    //! @public @memberof Point3
    //! @brief Creates a zero point (0.0f, 0.0f, 0.0f)
    const Point3 Zero(void) const {return Point3(0.0f, 0.0f, 0.0f);}
    void Print(void) {cout << "Point3: " << (*this).ToString() << "\n";}
    Vector3 operator -= (const Point3& p) {return Vector3(x-p.x, y-p.y, z-p.z);}
};
/*!
 * @class Point4 @extends Vector4
 * @brief 4D Point data structure (float x, float y, float z, float w)
 * @param x First coordinate
 * @param y Second coordinate
 * @param x Third coordinate
 * @param w fourth coordinate
 * @param Zero() Creates a zero point (0.0f, 0.0f, 0.0f, 0.0f)
 */
struct Point4 : Vector4
{
    //! @public @memberof Point4
    //! @brief Creates an empty Point4 structure
    Point4() = default;
    //! @public @memberof Point4
    //! @brief Creates a Point3 structure (float w, float x, float y, float z)
    Point4(float x, float y, float z, float w) : Vector4(x,y,z,w) {}
    //! @public @memberof Point4
    //! @brief Creates a zero point (0.0f, 0.0f, 0.0f, 0.0f)
    const Point4 Zero(void) const {return Point4(0.0f, 0.0f, 0.0f, 0.0f);}
    void Print(void) {cout << "Point4: " << (*this).ToString() << "\n";}
    Vector4 operator -= (const Point4& p) {return Vector4(x-p.x, y-p.y, z-p.z, w-p.w);}
};

// * * * * * LINES * * * * * //

/*!
 * @class Line
 * @brief 3D Line data structure using plucker coordinates.
 * @param direction Vector denoting the direction of the line
 * @param moment Vector denoting the moment of the line
 */
struct Line
{
    Vector3 direction;
    Vector3 moment;

    //! @public @memberof Line
    //! @brief Creates a Line structure with no defined direction or moment
    Line() = default;
    //! @public @memberof Line
    //! @brief Creates a Line structure with direction (dx, dy, dz) and moment (mx, my, mz)
    Line(float dx, float dy, float dz, float mx, float my, float mz) :
        direction (dx, dy, dz), moment (mx, my, mz) {}
    //! @public @memberof Line
    //! @brief Creates a Line structure with direction (d) and moment (m)
    Line(const Vector3& d, const Vector3& m) {direction = d; moment = m;}
    //! @public @memberof Line
    //! @brief Creates a Line structure with direction (d) and moment (CrossProduct(p, d))
    Line(const Vector3& d, const Point3& p) {direction = d;moment = CrossProduct(p, d);}
    //! @public @memberof Line
    //! @brief Creates a Line structure with direction (p1-p0) and moment (CrossProduct(p0, p1))
    Line(const Point3& p0, const Point3& p1) {direction = (p1-p0);moment = CrossProduct(p0, p1);}
    //! @public @memberof Line
    //! @brief Creates a Line structure with direction (point - origin) and
    //!        moment (origin), where (origin) = (0.0f, 0.0f, 0.0f)
    Line(const Point3& point) {direction = point; moment = direction.Zero();}
    const bool operator ==(const Line& L) const {return (direction == L.direction && moment == L.moment);}
    const bool operator !=(const Line& L) const {return (direction != L.direction || moment != L.moment);}
    string ToString(void) {return "{d = "+direction.ToString()+"| m  = "+moment.ToString()+"}";}
    void Print(void) {cout << "Line: " << (*this).ToString() << endl;}
};

// * * * * * PLANES * * * * * //

/*!
 * @class Plane
 * @brief Plane data structure in 3D space, defined with a normal vector (x,y,z) and a constant (w)
 * @param x X-axis component of normal vector
 * @param y Y-axis component of normal vector
 * @param z Z-axis component of normal vector
 * @param w constant value, defined as the negative inner product of the normal vector and a
 *          point on the plane: -(n*p) = w
 * @param Normal() Yields all three components of the normal vector as a Vector3 structure (x,y,z)
 */
struct Plane
{
    float   x,y,z,w;
    //! @public @memberof Plane
    //! @brief Creates a Plane structure with no defined normal vector or constant
    Plane() = default;
    //! @public @memberof Plane
    //! @brief Creates a Plane structure with normal components (x)=(nx), (y)=(ny), (z)=(nz),
    //!        and constant (w)=(wk)
    Plane(float nx, float ny, float nz, float wk) {x = nx; y = ny; z = nz; w = wk;}
    //! @public @memberof Plane
    //! @brief Creates a Plane structure with normal components (x)=(n.x), (y)=(n.y), (z)=(n.z),
    //!        and constant (w)=(wk)
    Plane(const Vector3& n, float wk){x = n.x; y = n.y; z = n.z; w = wk;}
    //! @public @memberof Plane
    //! @brief Returns all components of the plane's normal vector as a Vector3 structure (x,y,z)
    const Vector3 Normal(void) const {return Vector3(x,y,z);}
    const bool operator ==(const Plane& f) const {return (f.x == x && f.y == y && f.z == z && f.w == w);}
    const bool operator !=(const Plane& f) const {return !(f.x == x && f.y == y && f.z == z && f.w == w);}
    string ToString(void)
    {
        Vector3 n(x,y,z);
        return "{n = "+ n.ToString()+"| w = "+ to_string(w)+"}";
    }
    void Print(void) {cout << "Plane: " << (*this).ToString() << endl;}
};

// * * * * * 3D HOMOGENEOUS POINTS * * * * * //

/*!
 * @class HomogeneousPoint3
 * @brief Homogeneous coordinates structure (x, y, z, w).
 *        This structure is useful for Line structures, which we defined in Plucker coordinates,
 *        instead of Cartesian. The conversion between homogeneous coordinates and Cartesian
 *        coordinates is given by:
 *                                         (x, y, z, w) <=> (x/w, y/w, z/w)
 * @param x X-axis homogeneous coordinate
 * @param y Y-axis homogeneous coordinate
 * @param z Z-axis homogeneous coordinate
 * @param w Homogeneous coordinate factor for changing coordinates into Cartesian, and viceversa
 * @param PointPart() Returns only the point part of the HomogeneousPoint3 structure as a
 *                    Point3 structure (x, y, z)
 * @param toPoint3() Returns the Cartesian version of the HomogeneousPoint3 structure as a
 *                    Point3 structure (x/w, y/w, z/w)
 */
struct HomogeneousPoint3
{
    float x, y, z, w;
    //! @public @memberof HomogeneousPoint3
    //! @brief Creates an empty HomogeneousPoint3 structure
    HomogeneousPoint3() = default;
    //! @public @memberof HomogeneousPoint3
    //! @brief Creates a HomogeneousPoint3 structure with coordinates
    //!        (x)=(a), (y)=(b), (z)=(c), (w)=(k)
    HomogeneousPoint3(float a, float b, float c, float k) {x = a; y = b; z = c; w = k;}
    //! @public @memberof HomogeneousPoint3
    //! @brief Creates a HomogeneousPoint3 structure with coordinates
    //!        (x)=(p.x), (y)=(p.y), (z)=(p.z), (w)=(k)
    HomogeneousPoint3(const Point3& p, float k) {x = p.x*k, y = p.y*k, z = p.z*k, w = k;}
    HomogeneousPoint3 operator +=(const HomogeneousPoint3& h)
    {
        x = x*h.w + h.x*w;
        y = y*h.w + h.y*w;
        z = z*h.w + h.z*w;
        w *= h.w;
        return (*this);
    }
    HomogeneousPoint3 operator -=(const HomogeneousPoint3& h)
    {
        x = x*h.w - h.x*w;
        y = y*h.w - h.y*w;
        z = z*h.w - h.z*w;
        w *= h.w;
        return (*this);
    }
    HomogeneousPoint3 operator *=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return (*this);
    }
    HomogeneousPoint3 operator /=(float scalar)
    {
        scalar = 1.0f/scalar;
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return (*this);
    }
    //! @public @memberof HomogeneousPoint3
    //! @brief Returns only the point part of the HomogeneousPoint3 structure as a
    //!        Point3 structure (x, y, z)
    const Point3 PointPart() const {return Point3(x,y,z);}
    //! @public @memberof HomogeneousPoint3
    //! @brief Returns the Cartesian version of the HomogeneousPoint3 structure as a
    //!        Point3 structure (x/w, y/w, z/w)
    const Point3 toPoint3() const {return (Point3(x/w, y/w, z/w));}
    const bool operator ==(const HomogeneousPoint3& h) const {return ((*this).toPoint3() == h.toPoint3());}
    const bool operator !=(const HomogeneousPoint3& h) const {return !((*this).toPoint3() == h.toPoint3());}
    string ToString(void)
    {
        Point3 p(x,y,z);
        return "{p = "+ p.ToString()+"| w = "+ to_string(w)+"}";
    }
    void Print(void) {cout << "HomogeneousPoint3: " << (*this).ToString() << endl;}
};

struct Triangle2
{
protected:
    Point2 a, b, c;
    Vector2 ab, bc, ac;
    float abLength, bcLength, acLength;
public:
    Triangle2() = default;
    Triangle2(Point2 u, Point2 v, Point2 w)
    {
        a = u; b = v; c = w;
        ab = b - a; bc = c - b; ac = c - a;
        abLength = Magnitude(ab); bcLength = Magnitude(bc); acLength = Magnitude(ac);
    }
    const float Area(void) const {return 0.5f*fabs(ab.x*ac.y - ac.x*ab.y);}
    const float Perimeter(void) const {return (abLength + bcLength + acLength);}
    const bool operator ==(const Triangle2& t) const {return (a == t.a && b == t.b && c == t.c);}
    const bool operator !=(const Triangle2& t) const {return !((*this) == t);}
    string ToString(void) {return "{A: " + a.ToString() + "| B: " + b.ToString() + "| C: " + c.ToString() + "}\n";}
    void Print(void) {cout << "Triangle2: " << (*this).ToString() << endl;}
    void SetPoints(Point2 u, Point2 v, Point2 w)
    {
        a = u; b = v; c = w;
        ab = b - a; bc = c - b; ac = c - a;
        abLength = Magnitude(ab); bcLength = Magnitude(bc); acLength = Magnitude(ac);
    }
    Point2 GetVertexA(void) {return a;}
    Point2 GetVertexB(void) {return b;}
    Point2 GetVertexC(void) {return c;}
    Vector2 GetEdgeAB(void) {return ab;}
    Vector2 GetEdgeBC(void) {return bc;}
    Vector2 GetEdgeAC(void) {return ac;}
    float GetEdgeABLength(void) {return abLength;}
    float GetEdgeBCLength(void) {return bcLength;}
    float GetEdgeACLength(void) {return acLength;}
};

struct Triangle3
{
protected:
    Point3 a, b, c;
    Vector3 ab, bc, ac;
    float abLength, bcLength, acLength;
public:
    Triangle3() = default;
    Triangle3(Point3 u, Point3 v, Point3 w)
    {
        a = u; b = v; c = w;
        ab = b - a; bc = c - b; ac = c - a;
        abLength = Magnitude(ab); bcLength = Magnitude(bc); acLength = Magnitude(ac);
    }
    const float Area(void) const {return 0.5f*Magnitude(CrossProduct(ab, ac));}
    const float Perimeter(void) const {return (abLength + bcLength + acLength);}
    const bool operator ==(const Triangle3& t) const {return (a == t.a && b == t.b && c == t.c);}
    const bool operator !=(const Triangle3& t) const {return !((*this) == t);}
    string ToString(void) {return "{A: " + a.ToString() + "| B: " + b.ToString() + "| C: " + c.ToString() + "}\n";}
    void Print(void) {cout << "Triangle3: " << (*this).ToString() << endl;}
    void SetPoints(Point3 u, Point3 v, Point3 w)
    {
        a = u; b = v; c = w;
        ab = b - a; bc = c - b; ac = c - a;
        abLength = Magnitude(ab); bcLength = Magnitude(bc); acLength = Magnitude(ac);
    }
    Point3 GetVertexA(void) {return a;}
    Point3 GetVertexB(void) {return b;}
    Point3 GetVertexC(void) {return c;}
    Vector3 GetEdgeAB(void) {return ab;}
    Vector3 GetEdgeBC(void) {return bc;}
    Vector3 GetEdgeAC(void) {return ac;}
    float GetEdgeABLength(void) {return abLength;}
    float GetEdgeBCLength(void) {return bcLength;}
    float GetEdgeACLength(void) {return acLength;}
};
//---------------------------------------------------------------------------------------------
//                                       INLINE OPERATORS
//---------------------------------------------------------------------------------------------

// * * * * * 2D POINTS * * * * * //

inline Point2 operator +(const Point2& p0, const Point2& p1)
    {return (Point2(p0.x + p1.x, p0.y + p1.y));}
inline Vector2 operator -(const Point2& p0, const Point2& p1)
    {return (Vector2(p0.x - p1.x, p0.y - p1.y));}
inline Point2 operator *(const Point2& p, float sc)
    {return Point2(p.x*sc, p.y*sc);}
inline Point2 operator *(float sc, const Point2& p)
    {return p*sc;}
inline Point2 operator /(const Point2& p, float sc)
    {return (1.0f/sc)*p;}

// * * * * * 3D POINTS * * * * * //

inline Point3 operator +(const Point3& p0, const Point3& p1)
    {return (Point3(p0.x + p1.x, p0.y + p1.y, p0.z + p1.z));}
inline Vector3 operator -(const Point3& p0, const Point3& p1)
    {return (Vector3(p0.x - p1.x, p0.y - p1.y, p0.z - p1.z));}
inline Point3 operator *(const Point3& p, float sc)
    {return Point3(p.x*sc, p.y*sc, p.z*sc);}
inline Point3 operator *(float sc, const Point3& p)
    {return p*sc;}
inline Point3 operator /(const Point3& p, float sc)
    {return (1.0f/sc)*p;}

// * * * * * 4D POINTS * * * * * //

inline Point4 operator +(const Point4& p0, const Point4& p1)
    {return (Point4(p0.x + p1.x, p0.y + p1.y, p0.z + p1.z, p0.w + p1.w));}
inline Vector4 operator -(const Point4& p0, const Point4& p1)
    {return (Vector4(p0.x - p1.x, p0.y - p1.y, p0.z - p1.z, p0.w - p1.w));}
inline Point4 operator *(const Point4& p, float sc)
    {return Point4(p.x*sc, p.y*sc, p.z*sc, p.w*sc);}
inline Point4 operator *(float sc, const Point4& p)
    {return p*sc;}
inline Point4 operator /(const Point4& p, float sc)
    {return (1.0f/sc)*p;}

// * * * * * PLANES * * * * * //

inline float operator *(const Plane& p, const Vector3& v) {return (p.x*v.x + p.y*v.y + p.z*v.z);}
inline float operator *(const Vector3& v, const Plane& p) {return (p*v);}
inline float operator *(const Plane& p, const Point3& q) {return (p.x*q.x + p.y*q.y + p.z*q.z);}
inline float operator *(const Point3& q, const Plane& p) {return (p*q);}

// * * * * * 3D HOMOGENEOUS POINTS * * * * * //

inline HomogeneousPoint3 operator +(const HomogeneousPoint3& p, const HomogeneousPoint3& q)
    {return (HomogeneousPoint3(p.x*q.w + q.x*p.w, p.y*q.w + q.y*p.w, p.z*q.w + q.z*p.w, p.w*q.w));}
inline HomogeneousPoint3 operator -(const HomogeneousPoint3& p, const HomogeneousPoint3& q)
    {return (HomogeneousPoint3(p.x*q.w - q.x*p.w, p.y*q.w - q.y*p.w, p.z*q.w - q.z*p.w, p.w*q.w));}
inline HomogeneousPoint3 operator *(const HomogeneousPoint3& p, float sc)
    {return (HomogeneousPoint3(p.x*sc, p.y*sc, p.z*sc, p.w));}
inline HomogeneousPoint3 operator *(float sc, const HomogeneousPoint3& p) {return p*sc;}
inline HomogeneousPoint3 operator /(const HomogeneousPoint3& p, float sc) {return (1.0f/sc)*p;}

//---------------------------------------------------------------------------------------------
//                                       INLINE METHODS
//---------------------------------------------------------------------------------------------

// * * * * * VECTOR-TO-POINT * * * * * //

/*!
 * @brief Converts a Vector2 structure to a Point2 structure
 * @param v The vector to be converted to a point
 * @return [Point2] The point
 */
inline Point2 toPoint(const Vector2& v) {return Point2(v.x, v.y);}
/*!
 * @brief Converts a Vector3 structure to a Point3 structure
 * @param v The vector to be converted to a point
 * @return [Point3] The point
 */
inline Point3 toPoint(const Vector3& v) {return Point3(v.x, v.y, v.z);}
/*!
 * @brief Converts a Vector3 structure to a Point3 structure
 * @param v The vector to be converted to a point
 * @return [Point3] The point
 */
inline Point4 toPoint(const Vector4& v) {return Point4(v.x, v.y, v.z, v.w);}

// * * * * * 3D NORMAL VECTOR FROM TRIANGLE VERTICES * * * * * //

/*!
 * @brief Generates a normal Vector3 structure using the coordinates of the three vertices of a triangle
 * @param p0 First vertex (x, y, z)
 * @param p1 Second vertex (x, y, z)
 * @param p2 Third vertex (x, y, z)
 * @return [Vector3] Normal vector CrossProduct(p1 - p0, p2 - p0)
 */
inline Vector3 Normal(const Point3& p0, const Point3& p1, const Point3& p2)
    {return (CrossProduct(p1-p0, p2-p0));}

// * * * * * INLINE DISTANCES * * * * * //

/*! @brief Calculates the distance from a given Point3 structure (q) to a given line (vt + p)
 *  @param q Given point, not on the line
 *  @param p Point on the line
 *  @param v Directional vector of the line
 *  @return [float] Distance from q to (vt + p)
 */
inline float DistanceToLine(const Point3& q, const Point3& p, const Vector3 v)
    {Vector3 a = CrossProduct(q-p, v); return (sqrt((a*a)/(v*v)));}
/*!
 * @brief Calculates the distance between two Line structures
 * @param A First line (Plucker coordinates)
 * @param B Second line (Plucker coordinates)
 * @return [float] Distance between A and B
 */
inline float DistanceTwoLines(const Line& A, const Line& B)
    {return ((fabs(A.direction*B.moment + B.direction*A.moment))/(Magnitude(CrossProduct(A.direction, B.direction))));}
/*!
 * @brief Calculates the distance from a given Point3 structure to a given Line structure (in Plucker coordinates)
 * @param L Line (in Plucker coordinates)
 * @param p Given point
 * @return [float] Distance between p and L
 */
inline float DistanceLinePoint(const Line& L, const Point3& p)
    {return (Magnitude(CrossProduct(L.direction, p) + L.moment)/Magnitude(L.direction));}
/*!
 * @brief Calculates the distance from a given Line structure (in Plucker coordinates) to the origin
 * @param L Line (in Plucker coordinates)
 * @return [float] Distance between origin and L
 */
inline float DistanceLineOrigin(const Line& L)
    {return (Magnitude(L.moment)/Magnitude(L.direction));}
/*!
 * @brief Calculates the distance between a given point and a given plane
 * @param f Given plane
 * @param p Given point
 * @return [float] Distance between f and p
 */
inline float DistancePlanePoint(const Plane& f, const Point3& p)
    {return (fabs(f.Normal()*p + f.w)/Magnitude(f.Normal()));}
/*!
 * @brief Calculates distance from given plane to origin
 * @param f Given plane
 * @return [float] Distance between origin and f
 */
inline float DistancePlaneOrigin(const Plane& f)
    {return (fabs(f.w)/Magnitude(f.Normal()));}
/*!
 * @brief Yields the closest homogeneous point on a Line structure to the origin
 * @param L The line
 * @return [HomogeneousPoint3] The homogenous point on L closest to the origin
 */

// * * * * * CLOSEST POINTS * * * * * //

inline HomogeneousPoint3 ClosestPointToOrigin(const Line& L)
    {Vector3 toPoint = CrossProduct(L.direction, L.moment); return (HomogeneousPoint3(toPoint.x, toPoint.y, toPoint.z, L.direction*L.direction));}
/*!
 * @brief Yields the closest homogeneous point on a Plane structure to the origin
 * @param p The plane
 * @return [HomogeneousPoint3] The homogenous point on p closest to the origin
 */
inline HomogeneousPoint3 ClosestPointToOrigin(const Plane& p)
    {return (HomogeneousPoint3(-1.0f*p.w*p.x, -1.0f*p.w*p.y, -1.0f*p.w*p.z, p.Normal()*p.Normal()));}

// * * * * * MAKE METHODS * * * * * //

inline Plane MakePlane(const Line& L, const Vector3 direction)
    {return (Plane(CrossProduct(L.direction, direction), -1.0f*(direction*L.moment))); }
inline Plane MakePlane(const Line& L, const Point3 p)
    {return (Plane(CrossProduct(L.direction, Vector3(p.x,p.y,p.z)) + L.moment, -1.0f*(Vector3(p.x,p.y,p.z)*L.moment)));}
inline Plane MakePlaneWithOrigin(const Line& L)
    {return (Plane(L.moment, 0));}
inline Plane FurthestPlaneFromOriginWithLine(const Line& L)
    {return (Plane(CrossProduct(L.moment, L.direction), L.moment*L.moment));}
inline Plane MakePlane(const Line& L, const HomogeneousPoint3 p)
    {return (Plane(CrossProduct(L.direction, p.PointPart()) + p.w*L.moment, -1.0f*(p.PointPart()*L.moment)));}
inline Plane FurthestPlaneFromOriginWithHomogeneousPoint(const HomogeneousPoint3 p)
    {return (Plane(-1.0f*p.w*p.PointPart(), p.PointPart()*p.PointPart()));}
inline Line MakeLine(const HomogeneousPoint3& p0, const HomogeneousPoint3& p1)
    {return (Line(p0.w*Point3(p1.x, p1.y, p1.z) - p1.w*Point3(p0.x, p0.y, p0.z), CrossProduct(Vector3(p0.x, p0.y, p0.z), Vector3(p1.x, p1.y, p1.z))));}

//---------------------------------------------------------------------------------------------
//                                          METHODS
//---------------------------------------------------------------------------------------------

// * * * * * INTERSECTIONS * * * * * //

/*!
 * @brief Changes the value of given point to the position at which a given line
 and a given plane intersect, if the intersection exists
 * @param p Point on the line
 * @param v Direction of the line
 * @param f Plane
 * @param q Pointer to point of intersection
 * @return [bool] Yields true if the intersection exists \n and changes the value of the
 * pointer to its location, false if it does not exist and leaves pointer unchanged
 */
bool Intersection(const Point3& p, const Vector3& v, const Plane& f, Point3 *q);
/*!
 * @brief Changes the value of given point and direction vector to define the line at which two planes intersect, if it exists.
 * @param f0 First plane
 * @param f1 Second plane
 * @param p Pointer to point on line of intersection
 * @param v Pointer to direction vector of line of intersection
 * @return [bool] Yields true if the intersection line exists \n and changes the values of the
 * pointers to define the line, false if it does not exist and leaves pointers unchanged
 */
bool Intersection(const Plane& f0, const Plane& f1, Point3 *p, Vector3 *v);
/*!
 * @brief Changes the value of given point to the position at which three planes intersect, if it exists
 * @param f0 First plane
 * @param f1 Second plane
 * @param f2 Third plane
 * @param p Pointer to point of intersection
 * @return [bool] Yields true if the intersection exists and changes the value of the
 * pointer to its location, false if it does not exist and leaves pointer unchanged
 */
bool Intersection(const Plane& f0, const Plane& f1, const Plane&f2, Point3 *p);
/*!
 * @brief Changes the value of given homogeneous point to the position at which a plane
 * and line intersect, if it exists
 * @param L The line
 * @param p the plane
 * @param h Pointer to homogeneous point of intersection
 * @return [bool] Yields true if the intersection exists and changes the value of the
 * pointer to its location, false if it does not exist and leaves pointer unchanged
 */
bool Intersection(const Line& L, const Plane& p, HomogeneousPoint3 *h);

// * * * * * EXTRAS * * * * * //

/*!
 * @brief Yields the closest point on a line to another point
 * @param v The vector defining the line
 * @param p The point to find closest point on line for
 * @return [Point3] Closest point on line (v) to point (p)
 */
Point3 ClosestDistanceToPoint(const Vector3& v, const Point3& p);
/*!
 * @brief Translates a plane by use of a translation vector
 * @param f The plane to be translated
 * @param t The translation vector
 * @return [Plane] Plane(f) translated by Vector3(t)
 */
Plane TranslatePlane(const Plane& f, const Vector3& t);
/*! @brief Calculates the distance from a given line to another given line
 *  @param p0 Point on first line
 *  @param v0 Direction of first line
 *  @param p1 Point on second line
 *  @param v1 Direction of second line
 *  @return Shortest distance from first line to the second line
 */
float DistanceBetweenLines( const Point3& p0, const Vector3& v0, const Point3& p1, const Vector3& v1);