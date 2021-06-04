#include "jarvisconvexhull.h"

#include <algorithm>
#include <cfloat>

namespace ConvexHull {

JarvisConvexHull::JarvisConvexHull(const Path2D& path)
    :points(path)
{}

Path2D JarvisConvexHull::execute()
{
    if(points.empty())
        return {};
    convexHull.clear();

    sort();
    loop();

    return convexHull;
}

Path2D JarvisConvexHull::result()
{
    return convexHull;
}

//找到y最小，如果出现多个ymin, 选取其中的xmin
void JarvisConvexHull::sort()
{
    double xTmp = FLT_MAX;
    double ymin = FLT_MAX;
    int minIndexY = 0;
    int ptSize = (int)points.size();
    for(int i = 0; i < ptSize; ++i)
    {
        if(abs(points[i].y - ymin) < DBL_EPSILON)
        {
            if(points[i].x < xTmp)
            {
                ymin = points[i].y;
                xTmp = points[i].x;
                minIndexY = i;
            }
        }
        else if(points[i].y < ymin)
        {
            ymin = points[i].y;
            xTmp = points[i].x;
            minIndexY = i;
        }
    }

    auto ptTmp = points[minIndexY];
    points[minIndexY] = points[0];
    points[0] = ptTmp;
}

void JarvisConvexHull::loop()
{
    size_t pointsize = points.size();

    if(pointsize  < 3)
        return;
    convexHull.reserve(pointsize);
    std::vector<int> pathIndex(pointsize);
    int index = 0;
    pathIndex[index] = 0;
    int next = 0;

    do
    {
        next = 0;

        for(size_t i = 1; i < pointsize; ++i)
        {
            if(judge(points[pathIndex[index]], points[next], points[i]))
            {
                next = i;
            }
        }

        pathIndex[++index] = next;
    } while( next != 0);

    ++index;

    for(int i = 0; i < index; ++i)
    {
        convexHull.push_back(points[pathIndex[i]]);
    }
}


//判断p2是否在 p0p1顺时针方向
bool JarvisConvexHull::judge(const Point2D &p0, const Point2D &p1, const Point2D &p2) const
{
    double cross = (p1-p0).cross(p2-p1);
    return cross < 0
            || (cross < DBL_EPSILON
                 && p1.distance2(p0) < p2.distance2(p0));
}




}
