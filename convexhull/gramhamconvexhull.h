#ifndef GRAMHAMCONVEXHULL_H
#define GRAMHAMCONVEXHULL_H

#include "point.h"

#include <vector>
/**
 * @brief The GramhamConvexhull class
 *      Gramham 扫描法
 ***/
namespace ConvexHull {

using namespace Shape2D;

class GramhamConvexhull
{
public:
    GramhamConvexhull(const Path2D& path);

    //计算凸包并返回结果
    Path2D execute();

    //结果
    Path2D result();

    //
    Path2D sortedPoints();

private:

    //1. 找到y最小，如果出现多个ymin, 选取其中的xmin, 作为首点   n
    //2. Angle-X角度排序   nlogn
    void sort();

    //2. 按顺序找凸包    n
    void loop();

    //return true if cross(p0p1, p1p2) > 0 , otherwise return false
    //判断三点是否逆时针
    // a. 逆时针，则p1, 暂定为凸包点
    // b. 共线且|p0p1| > |p0p2| 暂定为凸包点
    //否则不是
    bool judge(const Shape2D::Point2D& p0, const Shape2D::Point2D& p1, const Shape2D::Point2D& p2) const;

private:
    Path2D convexHull;
    Path2D points;
};

}

#endif // GRAMHAMCONVEXHULL_H
