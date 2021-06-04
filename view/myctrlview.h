#ifndef MYCTRLVIEW_H
#define MYCTRLVIEW_H

#include "kwctrlview.h"
#include "convexhull/point.h"

#include <vector>

class MyCtrlView : public KWCtrlView
{
    typedef Shape2D::Point2D Point;
    typedef Shape2D::Path2D Path;

public:
    MyCtrlView(QWidget *parent = nullptr);

    void ResetView() override;

    void setPointSize(int size);
    void setPoints(const Path &path);
    void setConvexHull(const Path &path);

protected:
     void mouseDoubleClickEvent(QMouseEvent *event) override;

protected:
    void DrawGLSence(QPainter &painter) override;



private:
    Path points;
    Path convexHull;

    int pointSize = 5;
};

#endif // MYCTRLVIEW_H
