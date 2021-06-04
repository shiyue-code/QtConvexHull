#ifndef JARVISCONVEXHULL_H
#define JARVISCONVEXHULL_H

#include "point.h"

#include <vector>


/**
 * @brief The JarvisConvexHull class
 * Jarvis步进法, 也可称为卷包裹法
 */

namespace ConvexHull {

using namespace Shape2D;

class JarvisConvexHull
{
public:
    JarvisConvexHull(const Path2D& path);

    //计算凸包并返回结果
    Path2D execute();

    //结果
    Path2D result();

private:

    //找到y最小，如果出现多个ymin, 选取其中的xmin, 作为首点
    //复杂度 n
    void sort();

    //n*H   H为凸包上的点数
    void loop();

    //判断p2是否在 p0p1顺时针方向, 顺时针则选取p2
    bool judge(const Shape2D::Point2D& p0, const Shape2D::Point2D& p1, const Shape2D::Point2D& p2) const;

private:
    Path2D convexHull;
    Path2D points;
};
}
#endif // JARVISCONVEXHULL_H
