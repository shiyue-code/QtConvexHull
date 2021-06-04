#include "gramhamconvexhull.h"

#include <algorithm>
#include <cfloat>

namespace ConvexHull {

GramhamConvexhull::GramhamConvexhull(const Path2D & path)
    :points(path)
{

}

Path2D GramhamConvexhull::execute()
{
    if(points.empty())
        return {};

    convexHull.clear();

    sort();
    loop();

    return convexHull;
}

Path2D GramhamConvexhull::result()
{
    return convexHull;
}

Path2D GramhamConvexhull::sortedPoints()
{
    return points;
}

void GramhamConvexhull::sort()
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

    std::sort(points.begin()+1, points.end(),
              [=](const Point2D &p0, const Point2D &p1)->bool
    {
        return (p0-points[0]).angle() < (p1-points[0]).angle();
    });
}

void GramhamConvexhull::loop()
{
    size_t pointsize = points.size();

    if(pointsize  < 3)
        return;

    convexHull.reserve(pointsize);
    convexHull.push_back(points[0]);

    Point2D ptTmp = points[1];

    size_t i = 2;
    size_t ireal = i;
    do
    {
        ireal = i % pointsize;
        if(judge(convexHull.back(), ptTmp, points[ireal]) || convexHull.size() < 2)
        {
            convexHull.push_back(ptTmp);
            ptTmp = points[ireal];
            ++i;
        }
        else
        {
            ptTmp = convexHull.back();
            convexHull.pop_back();
        }
    } while(i <= pointsize);

//    if(judge(convexHull.back(), ptTmp, points[0]))
//    {
//        convexHull.push_back(ptTmp);
//    }
}

bool GramhamConvexhull::judge(const Point2D &p0, const Point2D &p1, const Point2D &p2) const
{
    double cross = (p1-p0).cross(p2-p1);
    return cross > 0
            || (abs(cross) < DBL_EPSILON
                 && p1.distance2(p0) > p2.distance2(p0));

    return (p1-p0).cross(p2-p1) > 0;
}
}


