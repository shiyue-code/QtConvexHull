#include "myctrlview.h"

#include "convexhull/point.h"
#include "convexhull/UtilTool.h"

#include <QMouseEvent>

using namespace Shape2D;

MyCtrlView::MyCtrlView(QWidget *parent)
    :KWCtrlView(parent)
{

}

void MyCtrlView::ResetView()
{
    auto box = Tools::calcBoundingBox(points);

    if (!box)
    {
        return;
    }

    m_rect.setCoords(box.left(), box.top(), box.right(), box.bottom());

    double aspect;

    m_fScale = 1.0f;
    m_dViewW = m_rect.width() * 0.51 /** (sqrt(5.0))/3.0*/;
    m_dViewW = (m_dViewW < 1e-6) ? 1 : m_dViewW;

    m_dViewH = m_rect.height() * 0.51/* * (sqrt(5.0))/3.0*/;
    m_dViewH = (m_dViewH < 1e-6) ? 1: m_dViewH;

    if (this->height() == 0)
    {
        aspect = (GLdouble)this->width();
    }
    else
    {
        aspect = (GLdouble)this->width()/(GLdouble)this->height();
    }

    m_dXTrans = -(m_rect.left() + m_rect.right())/2.0f;
    m_dYTrans = -(m_rect.top() + m_rect.bottom())/2.0f;


    if (m_dViewW < m_dViewH * aspect)
        m_dViewW = m_dViewH * aspect;
    else
        m_dViewH = m_dViewW/aspect;

    KWCtrlView::ResetView();
    update();
}

void MyCtrlView::DrawGLSence(QPainter &painter)
{
    glPointSize(pointSize);



    if(!points.empty())
    {
        glColor3f(1, 1, 1);
        glBegin(GL_POINTS);
        for(const Point& pt: points)
        {
            glVertex2d(pt.x, pt.y);
        }
        glEnd();

    }

    if(!convexHull.empty())
    {
        glColor3f(0, 1, 0);
        glBegin(GL_LINE_STRIP);
        for(const Point& pt: convexHull)
        {
            glVertex2d(pt.x, pt.y);
        }
        glVertex2d(convexHull[0].x, convexHull[0].y);
        glEnd();

        glColor3f(1, 0, 0);
        glBegin(GL_POINTS);
        glVertex2d(convexHull[0].x, convexHull[0].y);
        glEnd();
    }



}

void MyCtrlView::setPointSize(int size)
{
    pointSize = size;

}

void MyCtrlView::setPoints(const MyCtrlView::Path &path)
{
    points = path;

    ResetView();
}

void MyCtrlView::setConvexHull(const MyCtrlView::Path &path)
{
    convexHull = path;
}

void MyCtrlView::mouseDoubleClickEvent(QMouseEvent *evt)
{
    if(evt->button() == Qt::LeftButton)
        ResetView();

    return KWCtrlView::mouseDoubleClickEvent(evt);
}
