#ifndef POINT_H
#define POINT_H

#include <cfloat>
#include <cmath>
#include <vector>

#include <QRectF>

namespace Shape2D {

constexpr double pi = 3.14159265358979323846; // pi
constexpr double piX2 = pi * 2; //2*PI
constexpr double pi_2 = pi / 2; //2*PI

class Math {
public:
    static double correctAngle(double a)
    {
        return fmod(pi + remainder(a - pi, piX2), piX2);
    }
};

template <typename T>
bool isEqual(T v1, T v2)
{
    return v1 == v2;
}

template <>
inline bool isEqual<double>(double v1, double v2)
{
    return abs(v1 - v2) < DBL_EPSILON;
}

template <>
inline bool isEqual<float>(float v1, float v2)
{
    return abs(v1 - v2) < FLT_EPSILON;
}

template <typename T>
class Point {
public:
    T x { 0 };
    T y { 0 };
    bool valid { false };

public:
    Point() = default;

    Point(T x, T y)
        : x(x)
        , y(y)
        , valid(true)
    {
    }

    Point(const Point& pt)
        : x(pt.x)
        , y(pt.y)
        , valid(pt.valid)
    {
    }

    operator bool() const
    {
        return valid;
    }

    //angle-X
    double angle() const
    {
        return Math::correctAngle(atan2(y, x));
    }

    double angleTo(const Point& pt) const
    {
        return (pt - *this).angle();
    }

    T dot(const Point& pt) const
    {
        return x * pt.x + y * pt.y;
    }

    T cross(const Point& pt) const
    {
        return x * pt.y - y * pt.x;
    }

    T distance2(const Point& pt) const
    {
        return (pt - *this).square();
    }

    T distance(const Point& pt) const
    {
        return (pt - *this).norm();
    }

    T norm() const
    {
        return sqrt(x * x + y * y);
    }

    T square() const
    {
        return x * x + y * y;
    }

    Point operator-(const Point& pt) const
    {
        return { x - pt.x, y - pt.y };
    }

    Point operator+(const Point& pt) const
    {
        return { x + pt.x, y + pt.y };
    }

    Point& operator=(const Point& pt)
    {
        x = pt.x;
        y = pt.y;
        valid = pt.valid;
        return *this;
    }

    Point& operator-=(const Point& pt)
    {
        x -= pt.x;
        y -= pt.y;
        return *this;
    }

    Point& operator+=(const Point& pt)
    {
        x += pt.x;
        y += pt.y;
        return *this;
    }

    bool operator==(const Point& pt) const
    {
        return valid && pt && isEqual(x, pt.x) && isEqual(y, pt.y);
    }

    bool operator!=(const Point& pt) const
    {
        return !(pt == *this);
    }
};

typedef Point<double> Point2D;
typedef std::vector<Point2D> Path2D;

}

#endif // POINT_H
