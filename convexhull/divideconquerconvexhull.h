#ifndef DIVIDECONQUERCONVEXHULL_H
#define DIVIDECONQUERCONVEXHULL_H

#include "point.h"

#include <vector>

/**
 * @brief The DivideConquerConvexHull class
 * 分而治之
 */

namespace ConvexHull {

using namespace Shape2D;

class DivideConquerConvexHull
{
public:
    DivideConquerConvexHull(const Path2D& path);

    //计算凸包并返回结果
    Path2D execute();

    //结果
    Path2D result();

private:

    //1. 查找x最小和最大
    std::vector<int> findXMinMax();
    //2. 递归
    std::vector<int> recursion(const std::vector<int> &path, const int &p1, const int &p2);

    int findMaxDist(const std::vector<int> &indexs,
                     const Point2D &p0, const Point2D &p1);

    //选择p0 p1 pi 逆时针的点
    void select(const std::vector<int> &indexs,
                const Point2D &p0, const Point2D &p1, std::vector<int> &selectIndex);

    //合并
    std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right);

    //三点逆时针 true
    //否则 false
    bool judge(const Point2D &p0, const Point2D &p1, const Point2D &p2);

private:
    Path2D convexHull;
    Path2D points;
};

}
#endif // DIVIDECONQUERCONVEXHULL_H
