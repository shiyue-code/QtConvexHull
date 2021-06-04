#include "divideconquerconvexhull.h"

#include <QDebug>

namespace ConvexHull {

using namespace std;

DivideConquerConvexHull::DivideConquerConvexHull(const Path2D &path)
    : points(path)
{

}

Path2D DivideConquerConvexHull::execute()
{
    convexHull.clear();
    size_t pointSize = points.size();
    if(pointSize <2)
        return {};

    auto minMaxIndex = findXMinMax();


    std::vector<int> indexs;

    for(size_t i = 0; i < pointSize; ++i)
        indexs.push_back(i);

    std::vector<int> left, right;

    select(indexs, points[minMaxIndex[0]], points[minMaxIndex[1]], left);
    select(indexs, points[minMaxIndex[1]], points[minMaxIndex[0]], right);

    indexs = merge(recursion(left, minMaxIndex[0], minMaxIndex[1]),
            recursion(right, minMaxIndex[1], minMaxIndex[0]));


    for(size_t i = 0; i <indexs.size(); ++i)
    {
        convexHull.push_back(points[indexs[i]]);
    }

    return convexHull;
}

Path2D DivideConquerConvexHull::result()
{
    return convexHull;
}

vector<int> DivideConquerConvexHull::findXMinMax()
{
    int pointSize = points.size();
    double xmin = FLT_MAX;
    double xmax = FLT_MIN;
    vector<int> result(2, -1);
    for(int i = 0; i < pointSize; ++i)
    {
        if(points[i].x < xmin)
        {
            xmin = points[i].x;
            result[0] = i;
        }
        else if(points[i].x > xmax)
        {
            xmax = points[i].x;
            result[1] = i;
        }
    }

    return result;
}

std::vector<int> DivideConquerConvexHull::recursion(const std::vector<int> &path, const int &p1, const int &p2)
{
    if( p1==p2)
        return {p1};

    if(path.empty())
        return {p1, p2};

    int maxIndex = findMaxDist(path, points[p1], points[p2]);

    if(maxIndex == -1)
        return {p1, p2};

    std::vector<int> left, right;
    select(path, points[p1], points[points[maxIndex]], left);
    select(path, points[maxIndex], points[p2], right);


    return merge(recursion(left, p1, maxIndex), recursion(right, maxIndex, p2));
}



int DivideConquerConvexHull::findMaxDist(const std::vector<int> &indexs, const Point2D &p0, const Point2D &p1)
{
    double maxCross = 0;
    int index = -1;
    for(size_t i : indexs)
    {
        double cross = (p1-p0).cross(points[i]-p1);
        if(cross > maxCross)
        {
            maxCross = cross;
            index = i;
        }
    }

    return index;
}

void DivideConquerConvexHull::select(const std::vector<int> &indexs, const Point2D &p0, const Point2D &p1, std::vector<int> &selectIndex)
{
    for(int i: indexs)
    {
        if(judge(p0, p1, points[i]) && p0!=i &&p1!=i)
        {
            selectIndex.push_back(i);
        }
    }
}


vector<int> DivideConquerConvexHull::merge(const vector<int> &left, const vector<int> &right)
{
    if(left.empty())
        return right;

    if(right.empty())
        return left;

    auto m = left;
    m.insert(m.cend(), right.cbegin()+1, right.cend());
    return m;
}

bool DivideConquerConvexHull::judge(const Point2D &p0, const Point2D &p1, const Point2D &p2)
{
    return (p1-p0).cross(p2-p1) > DBL_EPSILON;
}


}
